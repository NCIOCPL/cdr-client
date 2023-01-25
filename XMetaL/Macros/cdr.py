"""Scripting for CDR XMetaL.

All the heavy lifting is done here, to keep the XML macro file very lean.
"""

# Standard library imports.
import base64
import ctypes
import datetime
import functools
import io
import logging
import os
import pathlib
import platform
import re
import time
import tkinter
from tkinter import ttk, messagebox, filedialog
from tkinter.scrolledtext import ScrolledText
import webbrowser

# Third-party library imports.
import dateutil.parser
from lxml import etree
from mutagen.mp3 import MP3
from PIL import Image, ImageTk
import requests
import win32api
import win32com
import win32con
import win32gui

# Menus and toolbars.
import cdrcontrols


class CDR:
    """Controller which handles all of the CDR XMetaL macros."""

    PATH = pathlib.Path(__file__).parent.parent.resolve()
    BLOB_BROWSE_DIRECTORY = PATH / "blob_browse_directory.cfg"
    FORMAT = "%(asctime)s [%(levelname)s] %(message)s"
    LOGFILE = "cdr-client.log"
    LOGDIR = PATH / "logs"
    LOGPATH = LOGDIR / LOGFILE
    PUBMED = "https://www.ncbi.nlm.nih.gov/entrez/"
    NAMESPACE = "cips.nci.nih.gov/cdr"
    PRIVATE_USE_CHARACTER = re.compile("[\uE000-\uF8FF]")
    REVISION_LEVEL_PROPOSED = 1
    REVISION_LEVEL_APPROVED = 2
    REVISION_LEVEL_PUBLISHED = 3
    CDR_ID = f"{{{NAMESPACE}}}id"
    CDR_REF = f"{{{NAMESPACE}}}ref"
    CDR_HREF = f"{{{NAMESPACE}}}href"
    DOM_NODE_TYPE_ELEMENT = 1
    DOM_NODE_TYPE_TEXT = 3
    XM_VIEW_UNSPECIFIED = -1
    XM_VIEW_NORMAL = DEFAULT_VIEW_MODE = 0
    XM_VIEW_TAGS_ON = 1
    XM_VIEW_PLAIN_TEXT = 2
    XM_VIEW_BROWSE = 3
    XM_ALERTS_ALL = -1
    XM_ALERTS_NONE = 0
    XM_PROMPT_TO_SAVE_CHANGES = 0
    XM_SAVE_CHANGES = 1
    XM_DO_NOT_SAVE_CHANGES = 2
    XM_COLLAPSE_END = 0
    XM_COLLAPSE_START = 1
    XM_MOVE = 0
    XM_EXTEND = 1
    XM_CONTROL_TYPE_BUTTON = 1
    XM_CONTROL_TYPE_POPUP = 5
    XM_COMMAND_BAR_POSITION_LEFT = 1
    XM_COMMAND_BAR_POSITION_TOP = 2
    XM_COMMAND_BAR_POSITION_RIGHT = 3
    XM_COMMAND_BAR_POSITION_BOTTOM = 4
    XM_COMMAND_BAR_POSITION_FLOATING = 5 # default
    XM_DEFAULT_CCURSOR = 0
    XM_FIND = 0
    XM_REPLACE = 1
    XM_REPLACE_FIND = 2
    XM_FIND_REPLACE_ALL = 3
    XM_ELEMENT = 0 # navigation
    XM_TABLE_CELL = 1
    XM_WORD_START = 2
    XM_WORD_END = 3
    XM_DEFAULT_CURSOR = 0
    XM_CURSOR_BUSY = 2
    XM_PI_TARGET = "xm-replace_text"
    BLOB_LINKING_ELEMENTS = "MediaLink", "SupplementaryInfoLink"
    DOCTYPES_WITH_BLOBS = "Media", "SupplementaryInfo"
    REVISION_MARKUP = "Insertion", "Deletion"
    FILETYPES = (
        ("All files", "*.*"),
        ("Word documents", "*.docx"),
        ("PDF documents", "*.pdf"),
        ("Excel workbooks", "*.xlsx"),
        ("Text files", "*.txt"),
    )
    SUPPRESSED_TOOLBARS = "Standard", "Repository", "Whiteboard"
    KEEP_VISIBLE = "Main Menu", "CDR", "Formatting"
    EDITABLE_MAILER_ELEMENTS = {
        "Received",
        "ChangesCategory",
        "Response",
        "Comment",
        "CallLog",
        "Resolution",
    }
    MIME_TYPES = {
        "application/pdf": ".pdf",
        "application/msword": ".doc",
        "application/vnd.ms-excel": ".xls",
        "vnd.openxmlformats-officedocument.spreadsheetml.sheet": ".xlsx",
        "application/vnd.wordperfect": ".wpd",
        "text/html": ".html",
        "text/rtf": ".rtf",
        "text/plain": ".txt",
        "message/rfc822": ".txt",
        "image/jpeg": ".jpg",
    }

    def __init__(self, app):
        """Perform setup which is not time-dependent."""

        self.LOGDIR.mkdir(parents=True, exist_ok=True)
        self.logger.debug("On_Macro_File_Load event fired.")
        self.app = app
        self.fragment_id_clipboard = None
        self.fragment_link_clipboard = None
        self.editing_element = False
        self.validation_error_sets = {}
        self.last_search = {}
        self.glossary_trees = {}
        self.toolbars = {}

    def handle_exceptions(fn):
        """Ensure that all of the macros catch and log exceptions."""

        def wrapper(self, *args, **kwargs):
            if fn.__name__.startswith("on_"):
                self.logger.debug("Invoked method %s", fn.__name__)
            else:
                self.logger.info("Invoked method %s", fn.__name__)
            if not self.document or self.can_run_macros:
                try:
                    return fn(self, *args, **kwargs)
                except BaseException as e:
                    self.app.Alert(f"{fn.__name__}: {e}")
                    self.logger.exception("failure")
                except:
                    error = "internal error - notify developers"
                    self.app.Alert(f"{fn.__name__}: {error}")
                    self.logger.exception("failure")
        return wrapper


    ######################################################################
    #                              PROPERTIES                            #
    ######################################################################

    @property
    def active_document_is_writable(self):
        """Is there an active document and if so, is it not read-only?"""

        root = self.document_element
        return root and root.getAttribute("readonly") != "yes"

    @functools.cached_property
    def api_server(self):
        """DSN name for the HTTPS CDR API host."""
        return os.getenv("CDR_API_HOST")

    @property
    def blob_directory(self):
        """Where to start browsing for a BLOB file."""

        if self.BLOB_BROWSE_DIRECTORY.exists():
            directory = self.BLOB_BROWSE_DIRECTORY.read_text()
            if directory:
                return directory.strip()
        return self.user_documents_directory

    @functools.cached_property
    def browser(self):
        """Used for launching web pages for the XMetaL user."""

        instance = webbrowser.Chrome(self.chrome_path)
        webbrowser.register("google-chrome", None, instance, preferred=True)
        return webbrowser.get("google-chrome")

    @property
    def can_run_macros(self):
        """Is running macros permitted right now?"""

        allowed = self.XM_VIEW_NORMAL, self.XM_VIEW_TAGS_ON
        if self.document.ViewType not in allowed:
            return False
        if not self.document.IsXML:
            return False
        return True

    @property
    def cdr_id(self):
        """Extract the CDR Document ID from the current document."""

        if not self.document_control:
            return None
        element = self._get_single_element("DocId", self.document_control)
        if not element:
            return None
        return self._get_text_content(element) or None

    @functools.cached_property
    def cgi_bin(self):
        """Base URL for the CDR Admin interface pages."""
        return f"https://{self.server}/cgi-bin/cdr"

    @functools.cached_property
    def chrome_path(self):
        """Users prefer to view web pages with Chrome. Find it."""

        vars = (
            "ProgramFiles",
            "ProgramW6432",
            "ProgramFiles(x86)",
            "APPDATA",
            "LOCALAPPDATA",
        )
        dirs = "Google", "Chrome", "Application"
        for var in vars:
            path = pathlib.Path(os.getenv(var), *dirs, "chrome.exe")
            if path.exists():
                return str(path)

    @functools.cached_property
    def client_logging_level(self):
        """Verbosity for client-side logging (default is "INFO")."""
        return os.getenv("CDR_CLIENT_LOGGING_LEVEL", "INFO")

    @property
    def current_element(self):
        """Find the element node for the current position."""

        if not self.app.Selection:
            return None
        node = self.app.Selection.ContainerNode
        if not node:
            return self.document_element
        while node and not self._is_element(node):
            node = node.parentNode
            self.logger.trace("current_element: node is %s", node)
        return self.cast(node) if node else None

    @property
    def current_element_writable(self):
        """True if the user should be able to modify the current element."""

        if not self.active_document_is_writable:
            return False
        if not self.current_element:
            return False
        if self.editing_element:
            return True
        name = self.current_element.nodeName
        if name in ("DocId", "DocType"):
            return False
        if self.doctype_name == "Mailer":
            return name in self.EDITABLE_MAILER_ELEMENTS
        return True

    @property
    def document(self):
        """The currently active document."""
        return self.app.ActiveDocument

    @property
    def document_blocked(self):
        """True if the current document is blocked from publication."""

        if not self.document_control:
            return False
        return self.document_control.getAttribute("blocked") == "Y"

    @property
    def document_control(self):
        """Find the CdrDocCtl block for the current document."""

        if not self.document:
            return None
        return self._get_single_element("CdrDocCtl")

    @property
    def document_element(self):
        """Top-level element for the current document."""
        return self.document.DocumentElement if self.document else None

    @property
    def document_path(self):
        """Path in the file system for the current document."""

        if not self.document:
            return None
        path = pathlib.Path(self.document.Path, self.document.name)
        self.logger.debug("current document path: %s", path)
        return str(path)

    @property
    def document_title(self):
        """Extract the CDR Document title from the current document."""

        if not self.document_control:
            return None
        element = self._get_single_element("DocTitle", self.document_control)
        if not element:
            return None
        return self._get_text_content(element) or None

    @property
    def document_version(self):
        """Determine the version of the active document, if any."""

        if not self.document_path:
            return None
        if "-V" in self.document_path:
            return self.document_path.split("-V")[1][:-4]

    @property
    def doctype_name(self):
        """String identifying the doccument type of the active document."""

        if not self.document or not self.document.doctype:
            return None
        return self.document.doctype.name

    @functools.cached_property
    def doctypes(self):
        """Dictionary of information on the CDR document types."""

        class Doctype:
            def __init__(self, node):
                self.name = node.get("Type")
                self.values = {}
                for child in node.findall("EnumSet"):
                    path = child.get("Node")
                    nodes = child.findall("ValidValue")
                    self.values[path] = [CDR.get_text(v) for v in nodes]
                nodes = node.findall("LinkingElements/LinkingElement")
                self.linking_elements = {CDR.get_text(v) for v in nodes}

        doctypes = {}
        root = etree.parse(self.PATH/"CdrDocTypes.xml").getroot()
        for node in root.findall("CdrGetDocTypeResp"):
            if node.get("Format") == "xml":
                doctype = Doctype(node)
                doctypes[doctype.name] = doctype
        return doctypes

    @functools.cached_property
    def home_directory(self):
        """User's home directory."""

        directory = os.getenv("USERPROFILE")
        if directory:
            return directory
        drive = os.getenv("HOMEDRIVE")
        path = os.getenv("HOMEPATH")
        return f"{drive}{path}" if drive and path else None

    @property
    def is_spanish_summary(self):
        """Determine whether the active document is a Spanish Summary."""

        if self.doctype_name != "Summary":
            return False
        node = self._get_single_element("SummaryLanguage")
        if not node:
            return False
        return self._get_text_content(node) == "Spanish"

    @property
    def location_id(self):
        """Value of the cdr:id attribute nearest the current location."""

        node = self.current_element
        while node:
            if node.nodeType == self.DOM_NODE_TYPE_ELEMENT:
                element = self.cast(node)
                self.logger.debug("location ID: examining %s", node.nodeName)
                fragment_id = element.getAttribute("cdr:id")
                if fragment_id:
                    return fragment_id
            node = node.parentNode
        return None

    @functools.cached_property
    def logger(self):
        """Logs actions performed by the macros and problems which result."""

        logging.TRACE = logging.DEBUG - 5
        logging.addLevelName(logging.TRACE, "TRACE")
        class LoggerWithTrace(logging.getLoggerClass()):
            def trace(self, msg, *args, **kwargs):
                self.log(logging.TRACE, msg, *args, **kwargs)
        logging.setLoggerClass(LoggerWithTrace)
        logger = logging.getLogger(__name__)
        logger.addHandler(self.logging_handler)
        logger.setLevel(self.client_logging_level)
        return logger

    @functools.cached_property
    def logging_handler(self):
        """Create this separately so we can unhook it at the right moment."""
        handler = logging.FileHandler(self.LOGPATH, encoding="utf-8")
        handler.setFormatter(logging.Formatter(self.FORMAT))
        return handler

    @functools.cached_property
    def path(self):
        """Location of the directory containing the user's XMetaL files."""
        return os.getenv("CDR_PATH")

    @functools.cached_property
    def server(self):
        """DNS name for web page URLs from the CDR on the current tier."""
        return os.getenv("CDR_HOST")

    @functools.cached_property
    def server_logging_level(self):
        """How verbose should the logs for the server be (default is "INFO")."""
        return os.getenv("CDR_SERVER_LOGGING_LEVEL", "INFO")

    @functools.cached_property
    def session(self):
        """String identifying the user's current login session."""
        return os.getenv("CDR_SESSION") or "guest"

    @functools.cached_property
    def tier(self):
        """String identifying the CDR tier we talk to (e.g., "PROD")."""
        return os.getenv("CDR_TIER")

    @functools.cached_property
    def user(self):
        """CDR account name for the current user."""
        return os.getenv("CDR_USER")

    @functools.cached_property
    def user_documents_directory(self):
        """Starting directory for file selection."""

        if self.home_directory:
            return f"{self.home_directory}\\Documents"
        return  "/"

    @functools.cached_property
    def window_rect(self):
        """Location of XMetaL on the screen."""
        return win32gui.GetWindowRect(self.app.WindowHandle)


    ######################################################################
    #                            EVENT MACROS                            #
    ######################################################################

    @handle_exceptions
    def on_application_close(self):
        """Display locked documents and close the CDR session."""

        # Record the firing of the event.
        self.logger.debug("On_Application_Close event fired")

        # Make sure we have a real CDR session.
        if self.session and self.user and self.session != "guest":

            # Has the user left any documents checked out?
            command_set = CommandSet(self, "CdrReport")
            command = command_set.command
            etree.SubElement(command, "ReportName").text = "Locked Documents"
            params = etree.SubElement(command, "ReportParams")
            param = etree.SubElement(params, "ReportParam")
            param.set("Name", "UserId")
            param.set("Value", self.user)
            response = command_set.send()
            cdr_ids = []
            for node in response.iter("ReportRow"):
                cdr_ids.append(self.get_text(node.find("DocId")))
            if cdr_ids:
                lines = (
                    "The following documents are still locked",
                    "by your CDR account:\n",
                    ", ".join(cdr_ids),
                )
                self.app.Alert("\n".join(lines))

            # Close the session.
            CommandSet(self, "CdrLogoff").send()

            # Send our log to the server.
            self.logger.removeHandler(self.logging_handler)
            logging.shutdown()
            self._send_client_log()

            # Toss things overboard which we will no longer need.
            self.fragment_id_clipboard = None
            self.fragment_link_clipboard = None
            self.editing_element = False
            self.validation_error_sets = {}
            self.last_search = {}
            self.glossary_trees = {}
            self.app = None

    @handle_exceptions
    def on_application_document_context_menu(self):
        """Create the context menu suitable for the active document."""

        # Record the firing of the event.
        self.logger.debug("On_Application_Document_Context_Menu event fired")

        # Collect some values we'll need.
        selection = self.app.Selection
        container = selection.ContainerNode
        doctype = self.document.doctype
        readonly = not self.active_document_is_writable

        # Start with the uncoditional macros at the top of the context menu.
        self._add_macro("-", "")
        self._add_macro("&Edit Element")
        self._add_macro("Linked Fragment Docs Report")
        self._add_macro("Copy Fragment Link")
        self._add_macro("Paste Fragment Link")

        # Add the macros which are only appropriate inside an element.
        if container and container.nodeType == self.DOM_NODE_TYPE_ELEMENT:
            if doctype.hasAttribute(container.nodeName, "Public"):
                if container.getAttribute("Public") == "No":
                    self._add_macro("Remove Public=No", "Set Public")
                else:
                    self._add_macro("Make Public=No", "Set Non-Public")
            link_id = container.getAttribute("cdr:ref")
            if not link_id:
                link_id = container.getAttribute("cdr:href")
            if link_id and "CDR" in link_id:
                self._add_macro("Open &Link For Editing")
                self._add_macro("Open Link &Readonly")

        # Add macros specific to Summary documents.
        if doctype.name == "Summary":
            if selection.IsParentElement("GlossaryTermRef"):
                self._add_macro("Add Glossary Phrase")

            # Add all the flavors of glossification macros.
            options = (
                "Genetics Terms",
                "Genetics Terms (include markup)",
                "Patient Terms",
                "Patient Terms (include markup)",
                "Document (wrap with Insertion)",
                "Document (dig and wrap with Insertion)",
                "Genetics Terms (wrap with Insertion)",
                "Genetics Terms (include markup and wrap with Insertion)",
                "Patient Terms (wrap with Insertion)",
                "Patient Terms (include markup and wrap with Insertion)",
            )
            for option in options:
                self._add_macro(f"Glossify {option}")

            # One last macro for summaries
            self._add_macro("Update SummaryRef Titles")

        # Add macros specific to Person documents.
        if doctype.name == "Person":
            self._add_macro("Retrieve Org Postal Address")
            self._add_macro("Copy Fragment ID")

        # Add macros specific to Organization documents.
        if doctype.name == "Organization":
            if selection.IsParentElement("Location"):
                self._add_macro("Persons Linking To This Location")
                self._add_macro("Remember Postal Address")

        # Add the macro specific to PDQBoardMemberInfo documents.
        if doctype.name == "PDQBoardMemberInfo":
            if selection.IsParentElement("PersonContactID"):
                self._add_macro("Paste Fragment ID")

        # Add the macro for showing linked BLOBs.
        if self._is_contained_in(*self.BLOB_LINKING_ELEMENTS):
            self._add_macro("Show Linked Object")

        # Add macros for comments.
        if self.document.Range.FindInsertLocation("Comment"):
            self._add_macro("Insert Comment")
            self._add_macro("Insert Comment For Translators")
        if self.document.Range.FindInsertLocation("ResponseToComment"):
            self._add_macro("Insert ResponseToComment")

        # More macros for Summary documents.
        if doctype.name == "Summary":
            names = []
            for prefix in ("Protocol", "Citation"):
                for suffix in ("Ref", "Link"):
                    names.append(f"{prefix}{suffix}")
            if self._is_contained_in(*names):
                if readonly:
                    self._add_macro("View Comment", "Edit Comment")
                else:
                    self._add_macro("Edit Comment")
                    self._add_macro("Set Last Reviewed Date Attribute")
            if not readonly and self.cdr_id and self.is_spanish_summary:
                self._add_macro("-", "")
                self._add_macro("Spanish Link ID Swap")

        # Finish off with some miscellaneous macros.
        if not readonly:
            self._add_macro("Set Source to Advisory Board")
            self._add_macro("Set Source to Editorial Board")
            self._add_macro("Apply Revision Level")
        self._add_macro("Character Count")
        if not readonly:
            self._add_macro("-", "")
            self._add_macro("Strip cdr:id Attributes")

    @handle_exceptions
    def on_application_elementlist_insert(self):
        """Enhance the glossary processing status block."""

        # Record the firing of the event.
        self.logger.debug("On_Application_ElementList_Insert event fired")

        # For now all we have to do involves glossary documents
        if self.doctype_name in ("GlossaryTermConcept", "GlossaryTermName"):
            names = (
                "ProcessingStatus",
                "ProcessingStatuses",
                "ProcessingStatusValue",
            )
            name = self.app.ElementList.SelectedName
            if name in names:
                element = etree.Element("ProcessingStatusValue")
                element.set("user", self.user)
                element.set("date", str(datetime.date.today()))
                prompt = "{ Select a processing status value (required) }"
                pi = etree.ProcessingInstruction(self.XM_PI_TARGET, prompt)
                element.append(pi)
                if name != "ProcessingStatusValue":
                    status_element = etree.Element("ProcessingStatus")
                    status_element.append(element)
                    element = status_element
                if name == "ProcessingStatuses":
                    statuses_element = etree.Element("ProcessingStatuses")
                    statuses_element.append(element)
                    element = statuses_element
                xml = etree.tostring(element, encoding="unicode")
                if self.app.Selection.CanPaste(xml):
                    self.app.Selection.PasteString(xml)
                else:
                    self.app.Alert(f"Can't paste {name}.")
                self.app.Selection.GotoPrevious(self.XM_WORD_START)

    @handle_exceptions
    def on_application_open_complete(self):
        """Add our UI customizations."""

        # Record the firing of the event.
        self.logger.debug("On_Application_Open_Complete event fired.")

        # Load the menus and toolbars.
        self._load_menus()
        self._load_toolbars()
        self._prune_formatting_toolbar()
        self._set_title_bar()
        self._adjust_toolbar_visibility()

    @handle_exceptions
    def on_commandbars_activate(self):
        """Make sure the right toolbars are shown.

        Invoked by the "On_CommandBars_Activate" event macro. For some reason,
        that event is fired twice when a document is opened.
        """

        # Record the firing of the event.
        self.logger.debug("On_CommandBars_Activate event fired")

        # Logic is extracted to a separately-callable method.
        self._adjust_toolbar_visibility()

    @handle_exceptions
    def on_document_open_complete(self):
        """Conditionally adjust the initial position of a newly opened doc.

        Because of a bug in XMetaL (#00014812) we have to defer this adjustment
        until later in order to avoid causing other running applications (such
        as Notepad or Emacs) to flicker.
        """

        # Record the firing of the event.
        self.logger.debug("On_Document_Open_Complete macro fired")

        # Queue this action for later.
        self.app.RunMacroOnIdle("_On_Document_Open_Complete")

    @handle_exceptions
    def on_document_open_view(self):
        """Always open documents in normal view."""

        # Record the firing of the event.
        self.logger.debug("On_Document_Open_View event fired")

        # Special handling for the macro file.
        if self.doctype_name == "MACROS":
            self._set_view_mode(self.XM_VIEW_TAGS_ON)
        else:
            self._set_view_mode(self.DEFAULT_VIEW_MODE)

    @handle_exceptions
    def on_dtd_open_complete(self):
        """Dynamically add elements/attributes not in the real DTDs."""

        # Record the firing of the event.
        self.logger.debug("On_DTD_Open_Complete event fired.")

        # Skip this for the tiny bug_repro document or the macros.
        doctype = self.app.NewDocumentType
        if doctype.name in ("a", "MACROS"):
            return

        # Add a new attribute for CDR issue #2730.
        self.logger.trace("adding blocked attribute")
        doctype.addEnumeratedAttribute("CdrDocCtl", "blocked",
            "Indicates whether the document has been marked 'Inactive'",
            9, # ordinary enumeration
            2, # default value is explicitly specified
            "N", "N", "Y")

        # Add the Deletion element.
        self.logger.trace("adding the Deletion element")
        doctype.addElement("Deletion", "Deletion", True , False)
        doctype.addAttribute("Deletion", "UserName", "", 0, 0)
        doctype.addAttribute("Deletion", "Time", "", 0, 0)
        doctype.addEnumeratedAttribute("Deletion", "RevisionLevel",
            "Indicates status of proposed deletion", 9, # ordinary enumeration
            2, # default value is explicitly specified
            "approved", "approved", "proposed", "publish", "rejected")
        doctype.addEnumeratedAttribute("Deletion", "Source",
            "Used to tag deletions submitted by an Advisory Board member",
            9, 0, # attribute is optional (#IMPLIED)
            "advisory-board", # this is ignored because attr-type is 0
            "advisory-board", "editorial-board")

        # Add the Insertion element.
        self.logger.trace("adding the Insertion element")
        doctype.addElement("Insertion", "Insertion", True , False)
        doctype.addAttribute("Insertion", "UserName", "", 0, 0)
        doctype.addAttribute("Insertion", "Time", "", 0, 0)
        doctype.addEnumeratedAttribute("Insertion", "RevisionLevel",
            "Indicates status of proposed insertion", 9, #ordinary enumeration
            2, # default value is explicity specified
            "approved", "approved", "proposed", "publish", "rejected")
        doctype.addEnumeratedAttribute("Insertion", "Source",
            "Used to tag insertions submitted by an Advisory Board member",
            9, 0, # attribute is optional (#IMPLIED)
            "advisory-board", # this is ignored because attr-type is 0
            "advisory-board", "editorial-board")

        # Add the element to markup up unwanted private use characters.
        self.logger.trace("adding the cdr:PrivateUseCharacter element")
        doctype.addElement("cdr:PrivateUseCharacter", "cdr:PrivateUseCharacter",
                           True, False)

        # Allow these elements anywhere.
        if doctype.hasElementType(doctype.name):
            if doctype.hasElementType("Deletion"):
                self.logger.trace("allowing the Deletion element anywhere")
                doctype.addElementToInclusions("Deletion", doctype.name)
            if doctype.hasElementType("Insertion"):
                self.logger.trace("allowing the Insertion element anywhere")
                doctype.addElementToInclusions("Insertion", doctype.name)
            if doctype.hasElementType("cdr:PrivateUseCharacter"):
                self.logger.trace("allowing the cdr:PUC element anywhere")
                doctype.addElementToInclusions("cdr:PrivateUseCharacter",
                                               doctype.name)

        # Allow the cdr-eid attribute everywhere.
        for element_type in doctype.elementTypes:
            self.logger.trace("adding the cdr-eid attribute to %s", element_type)
            #doctype.addAttribute(doctype.elementType(i), "cdr-eid", "", 1, 0)
            doctype.addAttribute(element_type, "cdr-eid", "", 1, 0)

    def on_mouse_over(self):
        """Reset UI elements in case they're stuck."""

        # Record the firing of the event.
        self.logger.debug("On_Mouse_Over event fired")

        # Fix any problems caused by other macros.
        self.app.SetStatusText("")
        self.app.SetCursor(self.XM_DEFAULT_CCURSOR)

    @handle_exceptions
    def on_update_ui(self):
        """Invoked when the document context changes.

        Oddly, this is invoked three times when the document is opened.
        """

        # Record the firing of the event.
        self.logger.debug("On_Update_UI event fired")

        # This only works if no On_Update_UI macro is defined for the DTD.
        if self.app.Selection and self.app.Selection.IsInsertionPoint:
            if self.document.ViewType == self.XM_VIEW_TAGS_ON:

                # Allow selection of the top-level element.
                if not self.app.Selection.ContainerNode:
                    self.app.Selection.MoveRight()
                if not self.app.Selection.ContainerNode:
                    self.app.Selection.MoveLeft()

        # Prevent modification of readonly content.
        if self.app.Selection:
            if not self.current_element_writable:
                self.app.Selection.ReadOnlyContainer = True
            else:
                self.app.Selection.ReadOnlyContainer = False
                self.app.Selection.WritePermittedContainer = True

        # Prevent saving of a readonly document.
        if not self.active_document_is_writable:
            self.app.DisableMacro("CDR Save")
            self.logger.debug("disabled the save command")

        # Make sure the title bar hasn't been messed with.
        self._set_title_bar()

    ######################################################################
    #            PUBLIC METHODS INVOKED BY OTHER XMETAL MACROS           #
    ######################################################################

    @handle_exceptions
    def accept_change(self):
        """Accept the current revision markup change."""

        if self.can_run_macros:
            if not self.active_document_is_writable:
                self.app.Alert("Document is not checked out for editing.")
            elif self.app.Selection:
                levels_up = 0
                name = self.app.Selection.ElementName(levels_up)
                if name == "Insertion":
                    self.app.Selection.RemoveContainerTags()
                elif name == "Deletion":
                    self.app.Selection.SelectContainerContents()
                    self.app.Selection.Delete()
                    self.app.Selection.RemoveContainerTags()
                else:
                    macro = "Accept Change"
                    where = "within Insertion or Deletion markup"
                    self.app.Alert(f"{macro} can ohly be used {where}.")

    @handle_exceptions
    def accept_changes(self):
        """Apply all revision markup changes in the document.

        The user selects a revision level. The software then finds all
        Insertion and Deletion elements whose RevisionLevel attribute value
        meet or exceed the user's chosen level. Each such Deletion element is
        stripped (along with its tags). For each matching Insertion element the
        Insertion tag is stripped but the contents are preserved and merged
        with the rest of the document.

        The dialog originally used for this macro was created using the
        XMetaL form toolkit. That form is broken under Python scripting.
        See bug report #00014805. Just as well, as that part of the APIs
        were poorly documented, and it makes sense to use the same tools
        for all our form dialog windows anyway.
        """

        # Don't do this while we're in plain text mode.
        if not self.can_run_macros:
            return

        def accept_all_changes_callback(_event=None):
            """Capture which level values were selected."""

            dialog.values.levels = set()
            for name in checkboxes:
                if checkboxes[name].get():
                    dialog.values.levels.add(name)
            dialog.close()

        # Let the user choose which levels to apply.
        callback = accept_all_changes_callback
        dialog = DialogBox(self, "Accept All Changes", callback)
        top = ttk.Frame(dialog.form)
        top.grid(row=0, column=0)
        style = ttk.Style()
        style.configure("Bold.TLabel", font=("TkDefaultFont", 9, "bold"))
        label = ttk.Label(text="Instructions", style="Bold.TLabel")
        frame = ttk.LabelFrame(top, labelwidget=label)
        frame.grid(row=0, column=0)
        instructions = (
            "Select levels of markup to be applied and press the Accept "
            "button, or press the Cancel button if you do not wish to apply "
            "any changes without reviewing them."
        )
        instructions_opts = dict(
            text=instructions,
            wraplength=250,
            anchor=tkinter.NW,
            justify=tkinter.LEFT,
        )
        instructions = ttk.Label(frame, **instructions_opts)
        instructions.grid(row=0, column=0, padx=5, pady=(5, 10))
        frame = ttk.Frame(top)
        frame.grid(row=0, column=1, padx=(25, 5))
        button_opts = dict(focus=True, frame=frame, pady=3)
        accept = dialog.add_button("Accept", callback, 0, 0, **button_opts)
        dialog.add_button("Cancel", dialog.close, 1, 0, frame=frame, pady=3)
        label = ttk.Label(text="Levels", style="Bold.TLabel")
        bottom = ttk.LabelFrame(dialog.form, labelwidget=label)
        bottom.grid(row=1, column=0, pady=10)
        checkboxes = {}
        box_opts = dict(frame=bottom, pady=(3, 8))
        values = (
            ("publish", 30, False),
            ("approved", 25, True),
            ("proposed", 30, False),
        )
        col = 0
        for name, padx, checked in values:
            box_opts["padx"] = padx
            box_opts["checked"] = checked
            checkboxes[name] = dialog.add_checkbox(name, 0, col, **box_opts)
            col += 1
        dialog.run(accept)

        # Make sure at least one level was selected.
        self.logger.debug("Accept Changes: levels=%r", dialog.values.levels)
        if dialog.values.levels is None or not dialog.values.levels:
            if dialog.values.levels is not None:
                self.app.Alert("No levels selected.")
            return

        # Remove the matching Deletion blocks.
        changes = 0
        selection = self.app.Selection.Duplicate
        selection.MoveToDocumentStart()
        while selection.MoveToElement("Deletion"):
            level = selection.ContainerNode.getAttribute("RevisionLevel")
            self.logger.debug("Checking Deletion with level %r", level)
            if level in dialog.values.levels:
                selection.SelectContainerContents()
                selection.Delete()
                selection.RemoveContainerTags()
                changes += 1
                self.logger.debug("Deletion block removed")

        # Handle the matching Insertion markup. Watch for invalid content.
        placeholder = "<?xm-replace_text Insert text here?>"
        selection.MoveToDocumentStart()
        while selection.MoveToElement("Insertion"):
            level = selection.ContainerNode.getAttribute("RevisionLevel")
            self.logger.debug("Checking Insertion with level %r", level)
            if level in dialog.values.levels:
                selection.SelectContainerContents()
                if selection.Text == placeholder:
                    selection.Delete()
                    self.logger.debug("dropped Insertion placeholder")
                if not selection.CanRemoveContainerTags:
                    self.logger.warning("Unable to remove Insertion tags.")
                    warning = (
                        f"An Insertion element with level {level!r} was found "
                        "whose contents would be invalid if they were merged "
                        "with the surrounding content. Therefore the tags for "
                        "this Insertion element will not be removed."
                    )
                    self.app.Alert(warning)
                else:
                    selection.RemoveContainerTags()
                    changes += 1
                    self.logger.debug("Insertion tags removed")

        # Report what we did.
        s = "" if changes == 1 else "s"
        message = f"Applied {changes} revision{s}"
        self.app.Alert(f"{message}.")
        self.logger.info(message)

    @handle_exceptions
    def add(self):
        template = self.app.Documents.ChooseTemplate()
        if template:
            self.logger.info("Opening template %s", template)
            self.app.Documents.OpenTemplate(template)

    @handle_exceptions
    def add_glossary_phrase(self):
        """Add the selected phrase to the external mapping table."""

        # Make sure we have a glossary term reference.
        selection = self.app.Selection
        element = selection.ContainerNode
        if not element or element.nodeName != "GlossaryTermRef":
            self.app.Alert("No GlossaryTermRef at the current location.")
            return

        # Extract the values we need for the command.
        doc_id = element.getAttribute("cdr:href")
        selection.SelectContainerContents()
        value = selection.Text
        language = "English"
        usage = "GlossaryTerm Phrases"
        if self.is_spanish_summary:
            language = "Spanish"
            usage = "Spanish GlossaryTerm Phrases"

        # Ask the server to add the phrase to the mapping table.
        command_set = CommandSet(self, "CdrAddExternalMapping")
        command = command_set.command
        etree.SubElement(command, "Usage").text = usage
        etree.SubElement(command, "Value").text = value
        if doc_id:
            etree.SubElement(command, "CdrId").text = doc_id
        response = command_set.send()

        # Report success
        msg = f"{language} glossary phrase added to external mapping table."
        if response:
            self.app.Alert(msg)

    @handle_exceptions
    def administrative_subsystem(self):
        """Launch the web menu for the CDR admin pages."""

        session = self.session or "guest"
        url = f"{self.cgi_bin}/Admin.py?Session={self.session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def advanced_search(self):
        """Launch web menu for advanced CDR searching."""

        session = self.session or "guest"
        url = f"{self.cgi_bin}/AdvancedSearch.py?Session={self.session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def apply_revision_level(self):
        """Identify the selected revision markup as for the advisory board."""

        if not self.active_document_is_writable:
            self.app.Alert("A writable document is not currently active.")
        else:
            def apply_revision_level_callback(_event=None):
                dialog.values.level = level.get()
                dialog.close()

            callback = apply_revision_level_callback
            dialog = DialogBox(self, "Apply Revision Level", callback)
            levels = "approved", "proposed", "publish", "rejected"
            opts = dict(default="approved", width=15)
            level = dialog.add_radios("Select Level", levels, 0, 0, **opts)
            column = ttk.Frame(dialog)
            column.grid(row=0, column=1)
            opts = dict(frame=column, padx=(20, 40), pady=3, focus=True)
            ok = dialog.add_button("OK", callback, 0, 0, **opts)
            dialog.add_button("Cancel", dialog.quit, 1, 0, **opts)
            dialog.run(ok)
            level = dialog.values.level
            if level:
                count = self._set_rev_markup_attrs("RevisionLevel", level)
                s = "" if count == 1 else "s"
                message = f"Marked {count} element{s} as {level!r}."
                self.app.Alert(message)
            else:
                self.app.Alert("Action canceled.")

    @handle_exceptions
    def audit_trail_report(self):
        """Bring up the audit trail report in the web browser."""

        if not self.cdr_id:
            self.app.Alert("Document has not yet been saved in the CDR.")
        else:
            url = f"{self.cgi_bin}/AuditTrail.py?id={self.cdr_id}"
            self.browser.open_new_tab(url)

    @handle_exceptions
    def back_out_rejected_markup(self):
        """Drop reject revision markup."""

        # Make sure we really want to do this.
        if not self.can_run_macros:
            return
        prompt = (
            "Do you want to back out all rejected changes "
            "without reviewing them?"
        )
        if not self.app.Confirm(prompt):
            return

        # Loop through the Deletion elements. Avoid making the doc invalid.
        changes = 0
        range = self.document.Range
        range.MoveToDocumentStart()
        while range.MoveToElement("Deletion"):
            level = range.ContainerNode.getAttribute("RevisionLevel")
            self.logger.debug("Checking Deletion with level %r", level)
            if level == "rejected":
                range.SelectContainerContents()
                if not range.CanRemoveContainerTags:
                    self.logger.warning("Unable to remove Deletion tags.")
                    warning = (
                        f"A Deletion element with level 'rejected' was found "
                        "whose contents would be invalid if they were merged "
                        "with the surrounding content. Therefore the tags "
                        "for this Deletion element will not be removed."
                    )
                    self.app.Alert(warning)
                else:
                    range.RemoveContainerTags()
                    changes += 1
                    self.logger.debug("Deletion tags removed")

        # Insertions are an easier case: the entire element goes away.
        range.MoveToDocumentStart()
        while range.MoveToElement("Insertion"):
            level = range.ContainerNode.getAttribute("RevisionLevel")
            self.logger.debug("Checking Insertion with level %r", level)
            if level == "rejected":
                range.SelectContainerContents()
                range.Delete()
                range.RemoveContainerTags()
                changes += 1
                self.logger.debug("Insertion tags removed")

        # Log what we did.
        s = "" if changes == 1 else "s"
        message = f"Backed out {changes} revision{s}"
        self.app.Alert(f"{message}.")
        self.logger.info(message)

    @handle_exceptions
    def bold_underline_report(self):
        """Launch the bold/underline Summary QC report for the current doc."""
        self._open_summary_qc_report("bu")

    @handle_exceptions
    def browser_launch_test(self):
        """Launch many browser pages in quick succession."""

        for _ in range(25):
            self.browser.open_new_tab("https://www.cancer.gov")

    @handle_exceptions
    def bug_repro(self):
        """Reproduce a bug in XMetaL's replaceChild() method.

        This is a bug which we ran into back in May of 2003,
        and we reported it to the vendor at least once. They
        couldn't find any trace of the original bug report,
        so we reported it again in September of 2007.

        The DTD for the repro case:
        <!-- a.dtd -->
        <!ELEMENT a (b, c+)>
        <!ELEMENT b (#PCDATA)>
        <!ELEMENT c (#PCDATA)>

        The document for the repro case:
        <!-- a.xml -->
        <a><b>blah</b><c>more blah</c></a>

        If you enter c in the window that pops up on invoking
        the macro, the replacement works fine.  But if you enter
        b, XMetaL's implementation of replaceChild() fails, as
        it can't figure out that the result of the replacement
        is going to be just as valid as the version of the document
        being replaced.

        As of late 2022, the vendor has still not fixed this bug.
        """

        element_name = self.app.Prompt("Element to replace?")
        doc = self.document
        new_element = doc.createElement(element_name)
        text_node = doc.createTextNode("foo")
        old_element = doc.getElementsByTagName(element_name).item(0)
        new_element.appendChild(text_node)
        old_element.parentNode.replaceChild(new_element, old_element)

    @handle_exceptions
    def character_count(self):
        """Count the number of characters in the selection (excluding tags)."""

        n = 0
        quote = None
        in_tag = False
        for character in self.app.Selection.Text:
            if in_tag:
                if quote:
                    if character == quote:
                        quote = None
                elif character == ">":
                    in_tag = False
                elif character in "'\"":
                    quote = character
            elif character == "<":
                in_tag = True
            else:
                n += 1
        s = "" if n == 1 else "s"
        self.app.Alert(f"Selection contains {n} character{s}.")

    @handle_exceptions
    def check_in(self):
        """Abandon changes to the current document."""

        # Make sure we have a document to be checked in.
        if not self.document:
            return self.app.Alert("There is no active document.")
        elif not self.cdr_id:
            return self.app.Alert("Document has never been stored in the CDR.")

        # Get confirmation from the user.
        def callback(_event=None):
            dialog.values.comment = comment.get("1.0", "end").strip()
            dialog.values.confirmed = True
            dialog.close()

        def keep_comment_short(_event=None):
            value = comment.get("1.0", "end")
            if len(value) > 255:
                dialog.bell()
                comment.delete("1.0", "end")
                comment.insert("end", value[:255])

        dialog = DialogBox(self, "Check In Current Document", callback)
        top = ttk.Frame(dialog.form)
        top.grid(row=0, column=0)
        instructions = (
            "Do you really want to check this document in and abandon "
            "any changes you have made?"
        )
        instructions = ttk.Label(top, text=instructions, wraplength=350)
        instructions.grid(row=0, column=0, padx=15, pady=15)
        buttons = ttk.Frame(top)
        buttons.grid(row=0, column=1, padx=10, pady=10)
        ok = dialog.add_button("OK", callback, 0, 0, frame=buttons, focus=True)
        dialog.add_button("Cancel", dialog.close, 1, 0, frame=buttons)
        bottom = ttk.Frame(dialog.form)
        bottom.grid(row=1, column=0, pady=(5, 15))
        label = ttk.Label(bottom, text="Comment", width=71)
        label.grid(row=0, column=0, pady=3)
        comment = dialog.add_textarea(1, 0, width=50, height=6, frame=bottom)
        comment.bind("<KeyRelease>", keep_comment_short)
        dialog.run(ok)

        if dialog.values.confirmed:
            cdr_id = self.cdr_id
            command_set = CommandSet(self, "CdrCheckIn")
            command = command_set.command
            command.set("Abandon", "Y")
            command.set("ForceCheckIn", "Y")
            etree.SubElement(command, "DocumentId").text = self.cdr_id
            if dialog.values.comment:
                text = dialog.values.comment
                etree.SubElement(command, "Comment").text = text
            if command_set.send():
                self.document.Close(self.XM_DO_NOT_SAVE_CHANGES)
                self._remove_doc(cdr_id)

    @handle_exceptions
    def clone_doc(self):
        """Create a clone of a Media or SupplementaryInfo document."""

        doctype = self.doctype_name
        if not doctype:
            raise Exception("No document is currently open.")
        if not self.cdr_id:
            raise Exception("The current document has not yet been saved.")
        if doctype not in ("Media", "SupplementaryInfo"):
            raise Exception(f"Clone of {doctype} docs not supported.")
        selection = self.document.Range
        selection.SelectAll()
        selection.Copy()
        root = etree.fromstring(self.app.Clipboard.Text.encode("utf-8"))
        node = root.find("CdrDocCtl/DocId")
        if node is None:
            raise Exception("Unable to find DocId element.")
        node.text = None
        text = "{The document ID will be assigned automatically.}"
        pi = etree.ProcessingInstruction(self.XM_PI_TARGET, text)
        node.append(pi)
        if doctype == "Media":
            comment = root.find("Comment")
            while comment is not None:
                root.remove(comment)
                comment = root.find("Comment")
            names = "LabelName", "ContentDescription", "MediaCaption"
            for node in root.iter(*names):
                node.set("language", "es")
            node = etree.SubElement(root, "TranslationOf")
            node.text = self.get_text(root.find("MediaTitle"), "<unknown>")
            node.set(self.CDR_REF, self.cdr_id)
        for node in root.iter("*"):
            if self.CDR_ID in node.attrib:
                del node.attrib[self.CDR_ID]
        if "readonly" in root.attrib:
            del root.attrib["readonly"]
        doctype_decl = f'<!DOCTYPE {doctype} SYSTEM "{doctype}.dtd">'
        xml = etree.tostring(root, encoding="unicode", doctype=doctype_decl)
        self.app.Documents.OpenString(xml, 0, "newdoc.xml", True, True, False)


    @handle_exceptions
    def copy_fragment_id(self):
        """Copy the nearest cdr:id to the fragment ID clipboard."""

        self.fragment_id_clipboard = None
        fragment_id = self._get_fragment_id()
        if fragment_id:
            self.fragment_id_clipboard = fragment_id
            self.app.Alert(f"{fragment_id} was saved to the clipboard.")
        else:
            self.app.Alert("No fragment ID found.")

    @handle_exceptions
    def copy_fragment_link(self):
        """Copy link to the nearest linkable fragment to a clipboard."""

        self.fragment_link_clipboard = None
        id = self.cdr_id
        fragment_id = self._get_fragment_id()
        if not id:
            self.app.Alert("This is a new document without a document ID.")
        elif not fragment_id:
            self.app.Alert("No fragment ID found.")
        else:
            link = self.fragment_link_clipboard = f"{id}#{fragment_id}"
            self.app.Alert(f"{link} was saved to the clipboard.")

    @handle_exceptions
    def country_qc_report(self):
        """Launch the Country QC report for the current doc."""

        if not self.cdr_id:
            self.app.Alert("Current document ID not found.")
            return
        session = self.session or "guest"
        filter = "Country QC Report Filter".replace(" ", "+")
        args = f"Session={session}&DocId={self.cdr_id}&Filter=name:{filter}"
        self.browser.open_new_tab(f"{self.cgi_bin}/Filter.py?{args}")

    @handle_exceptions
    def deletion(self):
        """Surround the selected content with a Deletion element."""

        if self.document.Range.IsInsertionPoint:
            return self.app.Alert("The current selection is empty.")
        if not self.app.Selection.CanSurround("Deletion"):
            return self.app.Alert("Deletion markup not allowed here.")
        self.app.Selection.Surround("Deletion")
        now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        element = self.app.Selection.ContainerNode
        element.setAttribute("UserName", self.user)
        element.setAttribute("Time", now)
        element.setAttribute("RevisionLevel", "proposed")

    @handle_exceptions
    def document_history_report(self):
        """Show information about the document's versions."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        parms = f"Session={self.session}&DocId={self.cdr_id}"
        url = f"{self.cgi_bin}/DocVersionHistory.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def druginfo_qc_report(self):
        """Launch the DrugInformationSummary QC report for the document."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        parms = "&".join([
            f"Session={self.session}",
            f"DocId={self.cdr_id}",
            "DocType=DrugInformationSummary",
        ])
        url = f"{self.cgi_bin}/QcReport.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def edit_comment(self):
        """Allow the user to edit the current element's comment attribute.

        The user can only view the comment if the document is read-only.
        """

        element = self.current_element
        if element:
            readonly = not self.active_document_is_writable
            title = "View Comment" if readonly else "Edit Comment"
            #element = self.cast(node)
            comment = element.getAttribute("comment") or ""
            text = self._edit_multiline_text(title, comment, readonly=readonly)
            if not readonly and text is not None:
                element.setAttribute("comment", text)

    @handle_exceptions
    def edit_element(self):
        """Edit a linking or valid-values element in a dialog window."""

        # Make sure editing is allowed.
        if not self.active_document_is_writable:
            return self.app.Alert("Document retrieved as read-only.")

        # Set up the environment for assisted editing.
        saved_flag = self.app.Selection.ReadOnlyContainer
        self.app.Selection.ReadOnlyContainer = False
        self.editing_element = True

        # See if the element is controlled by a valid-values list.
        element_name = self.current_element.nodeName
        values = self.doctypes[self.doctype_name].values.get(element_name)
        if values:
            values = sorted(values, key=str.lower)
            self.logger.debug("Edit Element vv list: %s", values)
            value = self._pick_valid_value(element_name, values)
            if value is not None:
                if not value:
                    self.app.Alert("No value was selected.")
                else:
                    self._set_current_element_text(value)

        # If not, let the user pick a link target.
        else:
            text = self._get_text_content(self.current_element)
            args = self.doctype_name, element_name, text
            target = self._pick_link_target(*args)
            self.logger.debug("Edit Element link target: %s", target)
            if target:
                match = re.match(r"\[([^]]+)\] (.*)", target.strip())
                if match:
                    ref = match.group(1)
                    doctype = self.document.doctype
                    if doctype.hasAttribute(element_name, "cdr:ref"):
                        self.logger.debug("setting cdr:ref to %s", ref)
                        self.current_element.setAttribute("cdr:ref", ref)
                        text = match.group(2)
                        self.logger.debug("setting text content to %r", text)
                        self._set_current_element_text(match.group(2))
                    else:
                        self.logger.debug("setting cdr:href to %s", ref)
                        self.current_element.setAttribute("cdr:href", ref)

        # Restore the editing environment.
        self.app.Selection.ReadOnlyContainer = saved_flag
        self.editing_element = False

    @handle_exceptions
    def edit_glossary_term_name_docs(self):
        """Open the name documents for this concept doc in edit mode."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        docs = self._get_glossary_names_for_concept()
        if not docs:
            return self.app.Alert("No term name documents found.")
        for id in docs:
            self._fetch_and_open_doc(id, checkout=True)

    @handle_exceptions
    def edit_linked_glossary_term_concept_doc(self):
        """Open the concept doc for the current name doc in edit mode."""

        root = self.document_element
        element = self._get_single_element("GlossaryTermConcept")
        if not element:
            return self.app.Alert("Can't find GlossaryTermConcept element.")
        doc_id = element.getAttribute("cdr:ref")
        self._fetch_and_open_doc(doc_id, checkout=True)

    @handle_exceptions
    def edit_svpc_docs(self):
        """Open linked SVPC documents for editing."""

        root = self.document_element
        if not root:
            return self.app.Alert("No document is open.")
        if root.nodeName != "Summary":
            return self.app.Alert("This is not a Summary document.")
        count = 0
        children = root.childNodes
        for i in range(children.length):
            node = children.item(i)
            if node.nodeName == "SummaryModuleLink":
                element = self.cast(node)
                doc_id = element.getAttribute("cdr:ref")
                self._fetch_and_open_doc(doc_id, checkout=True)
                count += 1
        if not count:
            self.app.Alert("No linked SVPC summaries found.")

    @handle_exceptions
    def find_next(self):
        """Bring up a dialog form for navigating the revision markup."""

        def find_next_callback(_event=None):
            self._find_markup(level.get(), True)
            dialog.lift()

        def find_prev_callback(_event=None):
            self._find_markup(level.get(), False)
            dialog.lift()

        dialog = DialogBox(self, "CDR Revision Markup Navigation")
        text = "Select revision level of markup to navigate to."
        instructions = ttk.Label(dialog.form, text=text)
        instructions.grid(row=0, column=0)
        bottom = ttk.Frame(dialog.form)
        bottom.grid(row=1, column=0)
        opts = dict(frame=bottom, default="approved", width=10, pady=25)
        levels = "publish", "approved", "proposed"
        level = dialog.add_radios("Level", levels, 0, 0, **opts)
        buttons = ttk.Frame(bottom)
        buttons.grid(row=0, column=1, padx=(20, 40))
        opts = dict(frame=buttons, pady=4)
        dialog.add_button("Prev", find_prev_callback, 0, 0, **opts)
        next = dialog.add_button("Next", find_next_callback, 1, 0, **opts)
        dialog.add_button("Done", dialog.close, 2, 0, **opts)
        dialog.run(next)

    @handle_exceptions
    def find_next_advisory_board_markup(self):
        """Navigate to the next advisory board Insertion or Deletion node."""

        self.logger.debug("top of find_next_advisory_board_markup()")
        while True:
            start = self.app.Selection.Duplicate
            self.app.Selection.GotoNext(self.XM_ELEMENT)
            if not start.IsLessThan(self.app.Selection.Duplicate):
                self.app.Alert("No more Advisory Board markup found.")
                break
            tag = self.app.Selection.ContainerName
            self.logger.debug(f"selection element is {tag}")
            if tag in ("Deletion", "Insertion"):
                element = self.app.Selection.ContainerNode
                source = element.GetAttribute("Source")
                self.logger.debug(f"source is {source}")
                if source == "advisory-board":
                    break

    @handle_exceptions
    def find_private_use_chars(self):
        """Find private use XML characters, as used by (e.g.) Microsoft.

        Replaces such characters with special markup, and navigates to
        the first occurrence.
        """

        def replace_private_use_char(match):
            """Regular expression callback function.

            Required positional argument:
                match - regular expression match object

            Return:
                string value to be substituted for the match
            """

            code = ord(match.group(0))
            return f"<{tag}>U+{code:04X}</{tag}>"

        # Make sure a document is open.
        if not self.document:
            return self.app.Alert("No document is open.")

        # Get the serialized XML string for the document.
        range = self.document.Range
        found = False
        range.SelectAll()
        xml = range.Text

        # See if we have any private use characters.
        tag = "cdr:PrivateUseCharacter"
        if self.PRIVATE_USE_CHARACTER.search(xml):
            xml = self.PRIVATE_USE_CHARACTER.sub(replace_private_use_char, xml)
            message = (
                f"Replaced private use characters; text is now {len(xml)} "
                "characters long."
            )
            self.app.Alert(message)
            saved_flag = self.document.RulesChecking
            self.document.RulesChecking = False
            range.Delete()
            self.document.RulesChecking = False
            range.PasteString(xml)
            self.document.RulesChecking = saved_flag
            range.MoveToDocumentStart()
            if range.moveToElement(tag):
                range.Select()
                range.SelectElement()
        else:
            self.app.Alert("No private use characters found.")

    @handle_exceptions
    def full_concept_qc_report(self):
        """Open a browser for the Full Concept QC report."""

        if not self.cdr_id:
            self.app.Alert("Glossary document has not yet been saved.")
        parms = f"Session={self.session or 'guest'}&DocId={self.cdr_id}"
        url = f"{self.cgi_bin}/GlossaryConceptFull.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def generate_qc_report(self):
        """Open a browser with the QC report for the current document."""

        if not self.cdr_id:
            self.app.Alert("Glossary document has not yet been saved.")
        parms = f"Session={self.session or 'guest'}&DocId={self.cdr_id}"
        url = f"{self.cgi_bin}/QcReport.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def glossary_phrase_search(self):
        """Open a browser with the QC report for the current document."""

        if not self.cdr_id:
            self.app.Alert("Glossary document has not yet been saved.")
        parms = f"Session={self.session or 'guest'}&Id={self.cdr_id}"
        url = f"{self.cgi_bin}/GlossaryTermPhrases.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def glossary_translation_job(self):
        """Open a new browser tab for the Glossary Translation Job report."""

        if not self.cdr_id:
            self.app.Alert("Glossary document has not yet been saved.")
        else:
            int_id = self.extract_id(self.cdr_id)
            session = self.session or "guest"
            parms = f"Session={session}&doc_id={int_id}"
            url = f"{self.cgi_bin}/glossary-translation-job.py?{parms}"
            self.browser.open_new_tab(url)

    @handle_exceptions
    def glossary_translation_job_queue(self):
        """Open a browser tab for the Glossary Translation Job Queue report."""

        session = self.session or "guest"
        url = f"{self.cgi_bin}/glossary-translation-jobs.py?Session={session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def glossary_translation_job_workflow_report(self):
        """Open a browser tab for the Glossary Translation Workflow report."""

        script = "glossary-translation-job-report.py"
        session = self.session or "guest"
        url = f"{self.cgi_bin}/{script}?Session={session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def glossify(self, **opts):
        """Apply glossary-term markup.

        Optional keywork parameters:
            wrap - if True, wrap the glossary markup in an Insertion element
            dig - if True, recurse into Insertion/Deletion markup
            audience - optionally restrict to terms with this audience
            dictionary - optionally restrict to terms in this dictionary
        """

        def glossify_markup_callback(_event=None):
            """"""
            if job.current_node:
                job.current_node.marked_up = True
            if opts.get("wrap"):
                self.logger.debug("wrapping range in <Insertion/> markup")
                job.range.Surround("Insertion")
            job.range.Surround(Glossifier.TAG_NAME)
            element = job.range.ContainerNode
            element.setAttribute("cdr:href", term.get().split(";")[0])
            if not glossify_find_next_match():
                dialog.make_not_topmost()
                self.app.Alert("No more glossary phrases found.")
                dialog.close()

        def glossify_skip_callback(_event=None):
            """"""
            if job.current_node:
                job.current_node.marked_up = True
            if not glossify_find_next_match():
                dialog.make_not_topmost()
                self.app.Alert("No more glossary phrases found.")
                dialog.close()

        def glossify_skip_once_callback(_event=None):
            """"""
            if not glossify_find_next_match():
                dialog.make_not_topmost()
                self.app.Alert("No more glossary phrases found.")
                dialog.close()

        def glossify_next_section_callback(_event=None):
            """"""
            if job.current_chain < len(job.chains):
                job.current_chain += 1
            if not glossify_find_next_match():
                dialog.make_not_topmost()
                self.app.Alert("No more glossary phrases found.")
                dialog.close()

        def glossify_preview_callback(_event=None):
            """"""
            if job.current_node:
                parms = f"DocId={job.current_node.doc_id}"
                url = f"{self.cgi_bin}/PublishPreview.py?{parms}"
                self.browser.open_new_tab(url)

        def glossify_find_next_match():
            match = job.find_next_match(self, tree)
            if not match:
                return False
            term_text, phrase_text = match
            term.config(state="normal")
            term.delete(0, "end")
            term.insert("end", term_text)
            term.config(state="readonly")
            phrase.config(state="normal")
            phrase.delete(0, "end")
            phrase.insert("end", phrase_text)
            phrase.config(state="readonly")
            return True

        # Make sure this is a summary document.
        if self.doctype_name != "Summary":
            return self.app.Alert("Current document is not a summary.")

        # Make sure the document is writable.
        if not self.active_document_is_writable:
            return self.app.Alert("No active writable document.")

        # Create an object for this glossification job.
        tree = self._get_glossary_tree(**opts)
        job = Glossifier(**opts)

        # Make sure we have SummarySections to glossify.
        if not job.find_chains(self):
            return self.app.Alert("No glossifiable sections found.")

        # Put up the dialog control box.
        dialog = DialogBox(self, "Glossify")
        frame = ttk.Frame(dialog.form)
        frame.grid(row=0, column=0)
        text_opts = dict(width=76, frame=frame, pady=3)
        phrase = dialog.add_text_field("Phrase", 0, 0, **text_opts)
        phrase.config(state="readonly")
        term = dialog.add_text_field("Term", 1, 0, **text_opts)
        term.config(state="readonly")
        buttons = ttk.Frame(dialog.form)
        buttons.grid(row=2, column=0, pady=(15, 0))
        button_info = (
            ("Markup", glossify_markup_callback),
            ("Skip", glossify_skip_callback),
            ("Skip This Time", glossify_skip_once_callback),
            ("Done", dialog.close),
            ("Next Section", glossify_next_section_callback),
            ("Preview", glossify_preview_callback),
        )
        button_opts = dict(frame=buttons, padx=4)
        for column, (label, callback) in enumerate(button_info):
            dialog.add_button(label, callback, 0, column, **button_opts)
        if not glossify_find_next_match():
            dialog.close()
            return self.app.Alert("No glossifiable phrases found.")
        dialog.run()

    @handle_exceptions
    def go_to_next_element(self):
        """Navigate to the next element in the active document."""

        self.app.Selection.GotoNext(self.XM_ELEMENT)
        self.app.Selection.SelectContainerContents()

    @handle_exceptions
    def go_to_previous_element(self):
        """Navigate to the previous element in the active document."""

        self.app.Selection.GotoPrevious(self.XM_ELEMENT)
        self.app.Selection.SelectContainerContents()

    @handle_exceptions
    def help(self):
        """Bring up the help pages in Google Chrome."""
        self.browser.open_new_tab(f"{self.cgi_bin}/Help.py")

    @handle_exceptions
    def insert_citation_link(self):
        """Insert a CitationLink element at the current position."""
        self.app.Selection.InsertWithTemplate("CitationLink")

    @handle_exceptions
    def insert_comment(self):
        """Insert a comment element at the current location."""

        range = self.document.Range
        if not range.FindInsertLocation("Comment"):
            message = "Can't insert Comment element under current position."
            self.app.Alert(message)
        else:
            xml = self._create_comment_element(as_string=True)
            self._paste_and_navigate(range, xml, "Comment")

    @handle_exceptions
    def insert_comment_for_translators(self):
        """Insert a comment node with a specific internal audience attr."""

        range = self.document.Range
        if not range.FindInsertLocation("Comment"):
            message = "Can't insert Comment element under current position."
            self.app.Alert(message)
        else:
            opts = dict(
                as_string=True,
                 specific_internal_audience="translators",
            )
            xml = self._create_comment_element(**opts)
            self._paste_and_navigate(range, xml, "Comment")

    @handle_exceptions
    def insert_current_date(self):
        """Insert today's date (ISO format) at the current position."""

        if self.app.Selection:
            self.app.Selection.Text = str(datetime.date.today())

    @handle_exceptions
    def insert_date_last_modified(self):
        """Insert a DateLastModified element in the current document."""

        range = self.document.Range
        range.MoveToDocumentEnd()
        if not range.MoveToElement("DateLastModified", False):
            if not range.FindInsertLocation("DateLastModified", False):
                self.app.Alert("Can't insert DateLastModified element.")
                return
            range.InsertWithTemplate("DateLastModified")
        range.Select()

    @handle_exceptions
    def insert_mailer_response(self):
        """Insert a Response element at the end of the open document."""

        range = self.app.ActiveDocument.Range
        range.MoveToDocumentEnd()
        if not range.FindInsertLocation("Response", False):
            return self.app.Alert("Can't insert Response element.")
        range.InsertWithTemplate("Response")
        range.Select()

    @handle_exceptions
    def insert_response_to_comment(self):
        """Insert a comment response element at the current location."""

        range = self.document.Range
        name = "ResponseToComment"
        if not range.FindInsertLocation(name):
            message = f"Can't insert {name} element under current position."
            self.app.Alert(message)
        else:
            prompt = "Your comment response here"
            opts = dict(as_string=True, tag=name, prompt=prompt)
            xml = self._create_comment_element(as_string=True, tag=name)
            self._paste_and_navigate(range, xml, name)

    @handle_exceptions
    def insert_type_of_change(self):
        """Insert a TypeOfChange block in the current Summary document."""

        range = self.document.Range
        tag = "TypeOfSummaryChange"
        if not range.FindInsertLocation(tag):
            message = f"Can't insert {tag} element under current position."
            self.app.Alert(message)
        else:
            node = etree.Element(tag)
            child = etree.SubElement(node, "TypeOfSummaryChangeValue")
            prompt = "{ Select a change type }"
            pi = etree.ProcessingInstruction(self.XM_PI_TARGET, prompt)
            child.append(pi)
            etree.SubElement(node, "User").text = self.user
            etree.SubElement(node, "Date").text = str(datetime.date.today())
            node.append(self._create_comment_element(prompt="Enter a Comment"))
            xml = etree.tostring(node, encoding="unicode", pretty_print=True)
            self._paste_and_navigate(range, xml, "Comment")

    @handle_exceptions
    def insert_user_id(self):
        """Insert the loging name as text content of the current element."""

        if self.app.Selection and self.user:
            self.app.Selection.Text = self.user

    @handle_exceptions
    def insertion(self):
        """Surround the selected content with an Insertion element."""

        if self.document.Range.IsInsertionPoint:
            if not self.app.Selection.CanInsert("Insertion"):
                return self.app.Alert("Unable to apply Insertion markup.")
            self.app.Selection.InsertElement("Insertion")
            self.app.Selection.InsertReplaceableText("Insert text here")
        else:
            if not self.app.Selection.CanSurround("Insertion"):
                return self.app.Alert("Unable to apply Insertion markup.")
            self.app.Selection.Surround("Insertion")
        now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        element = self.app.Selection.ContainerNode
        element.setAttribute("UserName", self.user)
        element.setAttribute("Time", now)
        element.setAttribute("RevisionLevel", "proposed")

    @handle_exceptions
    def itemized_list(self):
        """Insert an ItemizedList element at the current location."""

        self.app.Selection.InsertElement("ItemizedList")
        node = self.app.Selection.ContainerNode
        if node.nodeName != "ItemizedList":
            self.logger.warning("itemized list node name is %s", node.nodeName)
            return self.app.Alert("Failed inserting ItemizedList.")
        node.setAttribute("Style", "bullet")
        self.app.Selection.InsertWithTemplate("ListTitle")
        self._jump_past_element()
        self.app.Selection.InsertWithTemplate("ListItem")
        self._jump_past_element()
        self.app.Selection.InsertWithTemplate("ListItem")
        self._jump_past_element()
        self.app.Selection.InsertWithTemplate("ListItem")
        self.app.Selection.MoveUp()
        self.app.Selection.MoveUp()

    @handle_exceptions
    def jump_before_element(self):
        """Move in front of the current element."""
        self._jump_before_element()

    @handle_exceptions
    def jump_past_element(self):
        """Move past the current element."""
        self._jump_past_element()

    @handle_exceptions
    def licensee_qc_report(self):
        """Launch the browser for the Licensee QC report."""

        if not self.cdr_id:
            return self.app.Alert("Licensee document has not yet been saved.")
        session = self.session or "guest"
        filter = "Licensee QC Report Filter".replace(" ", "+")
        parms = f"Session={session}&DocId={self.cdr_id}&Filter=name:{filter}"
        url = f"{self.cgi_bin}/Filter.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def linked_docs_report(self):
        """Launch the browser for the Linked Documents report."""

        if not self.cdr_id:
            return self.app.Alert("Document has not yet been saved.")
        session = self.session or "guest"
        type = "Any Type".replace(" ", "+")
        parms = f"Session={session}&DocId={self.cdr_id}&LinkingDocType={type}"
        url = f"{self.cgi_bin}/LinkedDocs.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def linked_fragment_docs_report(self):
        """Launch the browser for the Linked Fragment Documents report."""

        if not self.cdr_id:
            return self.app.Alert("Document has not yet been saved.")
        fragment_id = self._get_fragment_id()
        if not fragment_id:
            message = "Unable to find fragment ID for current location."
            return self.app.Alert(message)
        session = self.session or "guest"
        parms = "&".join([
            f"Session={session}",
            f"DocId={self.cdr_id}",
            f"FragId={fragment_id}",
            "LinkingDocType=Any+Type",
        ])
        url = f"{self.cgi_bin}/LinkedDocs.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def make_citation_supplementary_info_doc(self):
        """Create and open a Citation SupplementaryInfo document."""

        # Grab the title of the Citation document while it's still active.
        title = self.document_title or "*** DocTitle not found ***"

        # Create and open the new document.
        filename = "CitationSupplementaryInfo.xml"
        path = pathlib.Path(self.path, "Template", "Cdr", filename)
        doc = self.app.Documents.OpenTemplate(str(path))

        # Find the Title element and populate it.
        element = self._get_single_element("Title", doc)
        if not element:
            return self.app.Alert("Title element not found.")
        child = element.firstChild
        while child:
            next_child = child.nextSibling
            element.removeChild(child)
            child = next_child
        text_node = doc.createTextNode(title)
        element.appendChild(text_node)

    @handle_exceptions
    def make_glossary_term_name_doc(self):
        """Create and open a GlossaryTermName document."""

        # Grab the ID of the concept document while it's still active.
        concept_id = self.cdr_id
        if not concept_id:
            return self.app.Alert("Concept document has not yet been saved.")

        # Create and open the name document.
        filename = "GlossaryTermName.xml"
        path = pathlib.Path(self.path, "Template", "Cdr", filename)
        doc = self.app.Documents.OpenTemplate(str(path))

        # Find the Title element and populate it.
        element = self._get_single_element("GlossaryTermConcept", doc)
        if not element:
            return self.app.Alert("GlossaryTermConcept element not found.")
        child = element.firstChild
        while child:
            next_child = child.nextSibling
            element.removeChild(child)
            child = next_child
        element.setAttribute("cdr:ref", concept_id)

    @handle_exceptions
    def media_side_by_side_report(self):
        """Launch the browser for the Media Side-by-Side report."""

        if not self.cdr_id:
            return self.app.Alert("Document has not yet been saved.")
        session = self.session or "guest"
        parms = f"Session={session}&DocId={self.cdr_id}"
        url = f"{self.cgi_bin}/MediaQcEnEs.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def media_translation_job(self):
        """Open a new browser tab for the Media Translation Job report."""

        session = self.session or "guest"
        if not self.cdr_id:
            self.app.Alert("Media document has not yet been saved.")
        else:
            int_id = self.extract_id(self.cdr_id)
            parms = f"Session={session}&english_id={int_id}"
            url = f"{self.cgi_bin}/media-translation-job.py?{parms}"
            self.browser.open_new_tab(url)

    @handle_exceptions
    def media_translation_job_queue(self):
        """Open a browser tab for the Media Translation Job Queue report."""

        session = self.session or "guest"
        url = f"{self.cgi_bin}/media-translation-jobs.py?Session={session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def media_translation_job_workflow_report(self):
        """Open a browser tab for the Media Translation Workflow report."""

        script = "media-translation-job-report.py"
        session = self.session or "guest"
        url = f"{self.cgi_bin}/{script}?Session={session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def navigate_comments(self):
        """Bring up a dialog interface for moving between comments."""

        def next_comment_callback(_event=None):
            self._find_comment(comment_type.get(), True)

        def prev_comment_callback(_event=None):
            self._find_comment(comment_type.get(), False)

        dialog = DialogBox(self, "Comment Navigation", next_comment_callback)
        types = "Advisory Board", "Internal", "External", "Permanent"
        opts = dict(default=types[0], width=15, padx=(10, 20))
        comment_type = dialog.add_radios("Comment type", types, 0, 0, **opts)
        buttons = ttk.Frame(dialog.form)
        buttons.grid(row=0, column=1)
        button_info = (
            ["Prev", prev_comment_callback, False],
            ["Next", next_comment_callback, True],
            ["Done", dialog.close, False],
        )
        opts = dict(frame=buttons, pady=3)
        next = None
        for row, (label, command, focus) in enumerate(button_info):
            opts["focus"] = focus
            button = dialog.add_button(label, command, row, 0, **opts)
            if focus:
                next = button
        dialog.run(next)

    @handle_exceptions
    def new_summary_section(self):
        """Insert a new SummarySection block in the active document."""

        if self.document:
            if not self.current_element_writable:
                return self.app.Alert("Can't insert into readonly document.")
            document_range = self.document.Range
            if document_range:
                document_range.Collapse()
            for _ in range(50):
                if not document_range:
                    break
                if document_range.CanInsert("SummarySection"):
                    document_range.InsertWithTemplate("SummarySection")
                    document_range.Select()
                    self.logger.info("Inserted a new summary section.")
                    break
                if not document_range.ContainerNode:
                    return self.app.Alert("Can't insert summary section.")
                document_range.SelectAfterContainer()

    @handle_exceptions
    def next_element(self):
        """Navigate to the next element."""

        self.app.Selection.GotoNext(self.XM_ELEMENT)
        self.app.Selection.SelectContainerContents()

    @handle_exceptions
    def open_application_macros(self):
        """Show the XML macro file."""
        self.app.Documents.Open(self.app.MacroFile, self.XM_VIEW_TAGS_ON)

    @handle_exceptions
    def open_board_member_doc(self):
        """Open the PDQBoardMemberInfo doc corresponding to this Person doc."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        command_set = CommandSet(self, "CdrReport")
        command = command_set.command
        etree.SubElement(command, "ReportName").text = "Board Member"
        params = etree.SubElement(command, "ReportParams")
        param = etree.SubElement(params, "ReportParam")
        param.set("Name", "PersonId")
        param.set("Value", self.cdr_id)
        response = command_set.send()
        for node in response.iter("BoardMember"):
            member_id = self.get_text(node)
            if member_id:
                return self._fetch_and_open_doc(member_id)

    @handle_exceptions
    def open_document_macros(self):
        if not self.document:
            return self.app.Alert("No open document.")
        if not self.document.MacroFile:
            return self.app.Alert("Current document has no macro file.")
        self.app.Documents.Open(self.document.MacroFile)

    @handle_exceptions
    def open_hp_summary(self):
        """Open the health-professional summary for the current patient doc."""

        element = self._get_single_element("PatientVersionOf")
        if not element:
            return self.app.Alert("PatientVersionOf element not found.")
        doc_id = element.getAttribute("cdr:ref")
        if not doc_id:
            return self.app.Alert("ID of HP summary not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def open_link_for_editing(self):
        """Open document linked by the current element in edit mode."""

        element = self.current_element
        if element:
            doc_id = element.getAttribute("cdr:ref")
            if not doc_id:
                doc_id = element.getAttribute("cdr:href")
            if not doc_id:
                return self.app.Alert("Current element has no link.")
            self._fetch_and_open_doc(doc_id, checkout=True)

    @handle_exceptions
    def open_link_readonly(self):
        """Open document linked by the current element in readonly mode."""

        element = self.current_element
        if element:
            doc_id = element.getAttribute("cdr:ref")
            if not doc_id:
                doc_id = element.getAttribute("cdr:href")
            if not doc_id:
                return self.app.Alert("Current element has no link.")
            self._fetch_and_open_doc(doc_id, checkout=False)

    @handle_exceptions
    def open_original_english_media_doc(self):
        """Open the English doc of which the active doc is a translation."""

        element = self._get_single_element("TranslationOf")
        if not element:
            return self.app.Alert("TranslationOf element not found.")
        doc_id = element.getAttribute("cdr:ref")
        if not doc_id:
            return self.app.Alert("ID of original media document not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def open_original_english_summary(self):
        """Open the English doc of which the active doc is a translation."""

        element = self._get_single_element("TranslationOf")
        if not element:
            return self.app.Alert("TranslationOf element not found.")
        doc_id = element.getAttribute("cdr:ref")
        if not doc_id:
            return self.app.Alert("ID of original summary not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def open_patient_summary(self):
        """Open the patient summary for the current health-professional doc."""

        if not self.cdr_id:
            return self.app.Alert("Current document not yet saved in the CDR.")
        command_set = CommandSet(self, "CdrReport")
        command = command_set.command
        etree.SubElement(command, "ReportName").text = "Patient Summary"
        params = etree.SubElement(command, "ReportParams")
        param = etree.SubElement(params, "ReportParam")
        param.set("Name", "HPSummary")
        param.set("Value", self.cdr_id)
        response = command_set.send()
        doc_id = None
        for node in response.iter("PatientSummary"):
            doc_id = self.get_text(node)
        if not doc_id:
            return self.app.Alert("Patient summary not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def open_person_doc_for_board_member(self):
        """Open Person document matching this PDQBoardMemberInfo document."""

        element = self._get_single_element("BoardMemberName")
        if not element:
            return self.app.Alert("BoardMemberName element not found.")
        doc_id = element.getAttribute("cdr:ref")
        if not doc_id:
            self.app.Alert("ID for Person document not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def open_translated_media_doc(self):
        """Get the Spanish version of the open English Media document."""

        if not self.cdr_id:
            return self.app.Alert("Current document not yet saved in the CDR.")
        doc_id = self._get_translated_doc_id(self.cdr_id)
        if not doc_id:
            return self.app.Alert("Spanish version of Medic doc not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def open_translated_summary(self):
        """Get the Spanish version of the open English Summary document."""

        if not self.cdr_id:
            return self.app.Alert("Current document not yet saved in the CDR.")
        doc_id = self._get_translated_doc_id(self.cdr_id)
        if not doc_id:
            return self.app.Alert("Spanish version of Summary doc not found.")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def ordered_list(self):
        """Insert an OrderedList element at the current location."""

        self.app.Selection.InsertElement("OrderedList")
        node = self.app.Selection.ContainerNode
        if node.nodeName != "OrderedList":
            self.logger.warning("ordered list node name is %s", node.nodeName)
            return self.app.Alert("Failed inserting OrderedList.")
        node.setAttribute("Style", "Arabic")
        self.app.Selection.InsertWithTemplate("ListTitle")
        self._jump_past_element()
        self.app.Selection.InsertWithTemplate("ListItem")
        self._jump_past_element()
        self.app.Selection.InsertWithTemplate("ListItem")
        self._jump_past_element()
        self.app.Selection.InsertWithTemplate("ListItem")
        self.app.Selection.MoveUp()
        self.app.Selection.MoveUp()

    @handle_exceptions
    def paste_fragment_id(self):
        """Paste fragment ID from special clipboard to current location."""

        container = self.app.Selection.ContainerNode
        if not self.fragment_id_clipboard:
            self.app.Alert("The fragment ID clipboard is empty.")
        elif not container or container.nodeType != self.DOM_NODE_TYPE_ELEMENT:
            self.app.Alert("Unable to find the current element.")
        elif self.document.doctype.name != "PDQBoardMemberInfo":
            self.app.Alert("Wrong document type for ID paste target.")
        elif container.nodeName != "PersonContactID":
            self.app.Alert("Current element is not PersonContactID.")
        else:
            self.app.Selection.SelectContainerContents()
            if self.app.Selection.ReadOnly:
                self.app.Alert("Cannot modify current element")
            else:
                self.app.Selection.Text = self.fragment_id_clipboard

    @handle_exceptions
    def paste_fragment_link(self):
        """Set the link attribute for the current element.

        Note that if appropriate we will also set the element's text content.
        """

        # Make sure we have something to paste.
        link = self.fragment_link_clipboard
        if not link:
            return self.app.Alert("CDR Fragment Link Clipboard is empty.")

        # Set up the editing environment.
        saved_flag = self.app.Selection.ReadOnlyContainer
        self.app.Selection.ReadOnlyContainer = False
        self.editing_element = True

        # Handle the easy cases.
        doctype = self.document.doctype
        element = self.current_element
        name = element.nodeName
        args = link, doctype.name, name
        self.logger.debug("link=%s doctype=%s element=%s", *args)
        if doctype.hasAttribute(name, "cdr:href"):
            self.logger.debug("setting @cdr:href to %s", link)
            element.setAttribute("cdr:href", link)
        elif doctype.hasAttribute(name, "Target"):
            self.logger.debug("setting @Target to %s", link)
            element.setAttribute("Target", link)

        # For the remaining supported case, we have more work to do.
        elif doctype.hasAttribute(name, "cdr:ref"):

            # Ask the CDR server for the denormalized data.
            command_set = CommandSet(self, "CdrPasteLink")
            command = command_set.command
            etree.SubElement(command, "SourceDocType").text = doctype.name
            etree.SubElement(command, "SourceElementType").text = name
            etree.SubElement(command, "TargetDocId").text = link
            response = command_set.send()
            if response:
                content = None
                for node in response.iter("DenormalizedContent"):
                    content = self.get_text(node, "").strip()
                    if content:
                        break

                # Replace the existing content.
                if content:
                    self.logger.debug("clearing old content")
                    child = element.firstChild
                    while child:
                        next = child.nextSibling
                        element.removeChild(child)
                        child = next
                    self.logger.debug("assigning new content=%s", content)
                    text_node = self.document.createTextNode(content)
                    element.appendChild(text_node)

                    # Plug in the link (only if we have denormalized content).
                    self.logger.debug("setting @cdr:ref to %s", link)
                    element.setAttribute("cdr:ref", link)

                else:
                    self.app.Alert("Can't find denormalized content.")

        # No other attributes are supported.
        else:
            self.app.Alert("Current element cannot accept links.")

        # Restore the editing environment.
        self.app.Selection.ReadOnlyContainer = saved_flag
        self.editing_element = False
        self.logger.debug("editing environment restored")

    def _open_summary_qc_report(self, report_type):
        """Launch a QC report for the active Summary doc in the web browser.

        Required positional argument:
            report_type - for example "bu" for the bold/underline report
        """

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        session = self.session or "guest"
        parms = "&".join([
            f"Session={session}",
            f"DocId={self.cdr_id}",
            "DocType=Summary",
            f"ReportType={report_type}",
        ])
        url = f"{self.cgi_bin}/QcReport.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def patient_summary_bu_qc_report(self):
        """Open the bold/underline QC report for the active summary doc."""
        self._open_summary_qc_report("patbu")


    @handle_exceptions
    def patient_summary_rs_qc_report(self):
        """Open the redline/strikeout QC report for the active summary doc."""
        self._open_summary_qc_report("pat")

    @handle_exceptions
    def persons_linking_to_org_loc(self):
        """Finds Person documents linking to the current Org location."""

        position = self.document.Range
        element = position.ContainerNode
        if element and element.nodeName != "Location":
            if position.IsParentElement("Location"):
                if position.MoveToElement("Location", False):
                    element = position.ContainerNode
        if not element or element.nodeName != "Location":
            self.app.Alert("The cursor is not inside a Location element.")
        elif not id:
            self.app.Alert("This is a new document with a document ID.")
        else:
            fragment = element.getAttribute("cdr:id")
            if not fragment:
                self.app.Alert("No location identifier found.")
            else:
                arg = f"FragLink={self.cdr_id}%23{fragment}"
                url = f"{self.cgi_bin}/PersonOrgLocLinks.py?{arg}"
                self.browser.open_new_tab(url)


    @handle_exceptions
    def pi_bug_repro(self):
        """Demonstrate broken handling of processing instructions.

        Here's the report we sent to Derek in October of 2007.

        Derek:

        Here's a strange one for you.  If you create a new document
        from a template using the menus (File / New ...) then the
        value of the processing instructions with xm-replace_text as
        the PI target appear in the elements as prompts.  That's the
        way those PIs are supposed to work.  In other words:

         <Foo><?xm-replace_text {
          You need to enter a Foo here
          }?></Foo>

        shows up in the document as the prompt { You need to enter a
        Foo here }.

        However if the new document is created by a macro, using that
        same template, and the macro inserts a new element with that
        *same* processing instruction, the PI target name appears in
        front of the prompt text in the document window:

          xm-replace_text { You need to enter a Foo here }.

        If the user switches to text mode and then back to normal (or
        tags-on) mode, the display of the prompts is correct for both
        elements.

        Somewhere along the way the vendor fixed the bug (but didn't
        let us know).
        """

        xml = """\
<?xml version="1.0" ?>
<!DOCTYPE xxtest SYSTEM "xxtest.dtd">
<xxtest>
 <CdrDocCtl>
  <DocId>CDR0123456789</DocId>
  <DocTitle>PI Bug Repro</DocTitle>
 </CdrDocCtl>
 <a><?xm-replace_text { Riveting prose here }?></a>
</xxtest>"""
        doc = self.app.Documents.OpenString(xml)
        element = doc.createElement("a")
        prompt = "{ Boring stuff here }"
        pi = doc.createProcessingInstruction(self.XM_PI_TARGET, prompt)
        element.appendChild(pi)
        doc.documentElement.appendChild(element)

    @handle_exceptions
    def previous_element(self):
        """Navigate to the previous element."""

        self.app.Selection.GotoPrevious(self.XM_ELEMENT)
        self.app.Selection.SelectContainerContents()

    @handle_exceptions
    def print(self):
        """Redirect user to workaround for XMetaL bug.

        Confirmed by Derek Read of SoftQuad Technical Support via email
        message received 2001-10-24. He filed a bug report at the time.
        Still not fixed as of 2022-12-23. Derek no longer works for the
        vendor.
        """

        # This doesn't work. Nor does invoking the Execute() method on the
        # CommandBarControl object.
        # self.app.RunKeyedMacro("Ctrl+P")

        # So this is the best we can do.
        lines = (
            "Sorry. Due to a bug in XMetaL, you must invoke the",
            "Print dialog box from the File menu or use Control+P.",
        )
        self.app.Alert("\n".join(lines))

    @handle_exceptions
    def publish_preview(self):
        """Launch the Publish Preview report for the active document."""
        self._publish_preview()

    @handle_exceptions
    def redline_strikeout_report(self):
        """Launch the redline/strikeout QC report for the current summary."""
        self._open_summary_qc_report("rs")

    @handle_exceptions
    def reject_change(self):
        """Back out the currently marked change.

        If the selection is inside an Insertion element the entier Insertion
        element and its contents are completely removed. If instead the
        selection is inside a Deletion element, then the Deletion tags are
        removed and the contents of the element are merged with the
        surrounding content of the document.
        """

        if not self.active_document_is_writable:
            return self.app.Alert("Document is not checked out for editing.")
        elif not self.app.Selection:
            return self.app.Alert("No selection found in the document.")
        element_name = self.app.Selection.ElementName(0)
        if element_name == "Deletion":
            self.app.Selection.RemoveContainerTags()
        elif element_name == "Insertion":
            self.app.Selection.SelectContainerContents()
            self.app.Selection.Delete()
            self.app.Selection.RemoveContainerTags()
        else:
            message = (
                "This command can only be used when the current selection's",
                "immediate parent is an Insertion or Deletion element.",
            )
            self.app.Alert("\n".join(message))

    @handle_exceptions
    def reload_css(self):
        """Reload the XMetaL display formatting instructions."""

        if self.document:
            self.document.RefreshCssStyle()

    @handle_exceptions
    def retrieve(self):
        """Fetch and open a document for a specified CDR ID."""

        def retrieve_callback(event=None):
            """Event handler for the OK button."""

            doc_id = doc_id_field.get()
            dialog.values.checkout = checkout_field.get()
            args = doc_id, dialog.values.checkout
            message = "Called retrieve_doc(doc_id=%s, checkout=%s)"
            self.logger.info(message, *args)
            if not doc_id:
                self.app.Alert("No document ID given.")
            else:
                try:
                    dialog.values.doc_id = self.extract_id(doc_id)
                except:
                    self.app.Alert(f"Invalid document ID {doc_id}.")
            dialog.close()
            self.logger.debug("back from dialog.close()")

        # Create the dialog form and register the callback.
        # values = dict(doc_id=None, checkout=False)
        dialog = DialogBox(self, "Retrieve CDR Document", retrieve_callback)
        doc_id_field = dialog.add_text_field("Document ID", 0, 0, focus=True)
        checkout_field = dialog.add_checkbox("Check Out?", 1, 1)
        dialog.add_button("OK", retrieve_callback, 0, 2)
        dialog.add_button("Cancel", dialog.close, 1, 2, pady=5)
        dialog.run(doc_id_field)
        values = dialog.values
        if values.doc_id:
            self._fetch_and_open_doc(values.doc_id, checkout=values.checkout)

    @handle_exceptions
    def retrieve_org_postal_address(self):
        """Insert a SpecificPostalAddress element into active Person doc."""

        # See if we are in a location which supports this.
        range = self.document.Range
        name = "OtherPracticeLocation"
        if not range.IsParentElement(name):
            return self.app.Alert(f"Unable to find {name} element.")
        range.MoveToElement(name, False)
        element = range.ContainerNode
        location = self._get_single_element("OrganizationLocation", element)
        if not location:
            return self.app.Alert("Address element not found.")
        ref = location.getAttribute("cdr:ref")
        if not ref:
            return self.app.Alert("Address link not found.")
        pieces = [s.strip() for s in ref.split("#")]
        if len(pieces) != 2:
            return self.app.Alert(f"Malformed address link {ref!r}.")
        doc_id, frag_id = pieces

        # Ask the server for the postal address information.
        command_set = CommandSet(self, "CdrFilter")
        filter_element = etree.SubElement(command_set.command, "Filter")
        filter_element.set("Name", "Organization Address Fragment")
        parms = etree.SubElement(command_set.command, "Parms")
        parm = etree.SubElement(parms, "Parm")
        etree.SubElement(parm, "Name").text = "fragId"
        etree.SubElement(parm, "Value").text = frag_id
        etree.SubElement(command_set.command, "Document").set("href", doc_id)
        response = command_set.send()
        path = "CdrResponse/CdrFilterResp/Document"
        xml = self.get_text(response.find(path))
        if not xml:
            return self.app.Alert("Unknown response from CDR server.")
        root = etree.fromstring(xml.encode("utf-8"))
        postal_address = root.find("PostalAddress")
        if not postal_address:
            return self.app.Alert("PostalAddress element not found.")
        address_type = postal_address.get("AddressType") or "US"

        # Create a string we can paste in using the XMetaL DOM API, which does
        # not allow us to add nodes to the tree directly. Use a wrapper element
        # to bridge between a namespace-aware API and a non-namespace-aware
        # interface.
        wrapper = etree.fromstring(f'<wrapper xmlns:cdr="{self.NAMESPACE}"/>')
        name = "SpecificPostalAddress"
        specific_address = etree.SubElement(wrapper, name)
        specific_address.set("AddressType", address_type)
        for child in postal_address.findall("*"):
            child.tail = None
            specific_address.append(child)
        xml = etree.tostring(wrapper, encoding="unicode", pretty_print=True)
        self.logger.debug("Wrapped XML is %s", xml)
        match = re.search(f"<{name}.+</{name}>", xml, re.DOTALL)
        xml = match.group(0)
        self.logger.debug("XML to be inserted is %s", xml)

        # Add the block to the document.
        location = self._find_or_create_child(range, name)
        if not location:
            return self.app.Alert(f"Failure creating {name} element.")
        location.SelectElement()
        location.Select()
        if not location.CanPaste(xml, False):
            self.app.warning("Unable to paste %r", xml)
            return self.app.Alert("Unable to insert address information.")
        location.PasteString(xml)

    @handle_exceptions
    def review_markup(self):
        """Let the user decide what to do for each revision markup element."""

        def review_markup_next(_event=None):
            """Navigate to the next revision markup element."""

            # Determine which markup elements we want.
            desired_level = level_filter.get() or "all"

            # Set up ranges to look for Insertion and Deletion elements.
            del_range = self.document.Range
            ins_range = self.document.Range

            # If we don't find another markup element, this is what we display.
            user = date = content = level = source = action = ""
            action = None

            # Keep going until we find a matching element.
            keep_going = True
            while keep_going:

                # Move to the next Deletion and Insertion elements.
                del_range.Collapse(self.XM_COLLAPSE_START)
                ins_range.Collapse(self.XM_COLLAPSE_START)
                found_del = del_range.MoveToElement("Deletion", True)
                found_ins = ins_range.MoveToElement("Insertion", True)


                args = found_ins, found_del
                self.logger.trace("found_ins=%s found_del=%s", *args)

                # Skip past elements with the wrong revision level.
                while found_del and desired_level != "all":
                    self.logger.trace("inside found_del loop")
                    node = del_range.ContainerNode
                    deletion_level = node.getAttribute("RevisionLevel")
                    self.logger.trace("deletion level: %s", deletion_level)
                    if deletion_level == desired_level:
                        break
                    del_range.Collapse(self.XM_COLLAPSE_START)
                    found_del = del_range.MoveToElement("Deletion", True)
                while found_ins and desired_level != "all":
                    self.logger.trace("inside found_ins loop")
                    node = ins_range.ContainerNode
                    insertion_level = node.getAttribute("RevisionLevel")
                    self.logger.trace("insertion level: %s", insertion_level)
                    if insertion_level == desired_level:
                        break
                    ins_range.Collapse(self.XM_COLLAPSE_START)
                    found_ins = ins_range.MoveToElement("Insertion", True)

                # Did we find a matching element?
                args = found_ins, found_del
                self.logger.trace("found_ins=%s found_del=%s", *args)
                if found_ins or found_del:

                    # If yes, stop the loop and choose the next element.
                    keep_going = False
                    if not found_del:
                        action = "insertion"
                    elif not found_ins:
                        action = "ddeletion"
                    elif ins_range.IsGreaterThan(del_range, False):
                        action = "ddeletion"
                    else:
                        action = "insertion"
                    self.logger.trace("found %s", action)
                    range = ins_range if action == "insertion" else del_range

                    # Extract and process the values we need to display.
                    range.SelectContainerContents()
                    range.Select()
                    node = range.ContainerNode
                    user = node.getAttribute("UserName")
                    date = parse_date(node.getAttribute("Time"))
                    self.logger.trace("user=%s date=%s", user, date)
                    source = map_source(node.getAttribute("Source"))
                    self.logger.trace("source=%s", source)
                    level = node.getAttribute("RevisionLevel")
                    content = range.Text
                    if len(content) > 25:
                        content = f"{content[:25]} ..."

                # If now, ask the user if we should try from the top.
                else:
                    prompt = "End of document; wrap from top?"
                    keep_going = messagebox.askyesno("Review Markup", prompt)
                    if keep_going:
                        del_range.MoveToDocumentStart()
                        ins_range.MoveToDocumentStart()

            # Whether we found a match or not, update the display.
            display["User"].set(user)
            display["Date"].set(date)
            display["Level"].set(level)
            display["Source"].set(source)
            display["Content"].set(content)
            display["Action"].set(action)
            for label in labels:
                self.logger.trace("%s=%s", label, display[label].get())

            # Update some button states.
            state = "normal" if action else "disabled"
            buttons["Accept"].config(state=state)
            buttons["Reject"].config(state=state)

        def review_markup_accept(_event=None):
            """Apply the revision and resolve the markup."""

            range = self.document.Range
            name = range.ElementName(0)
            self.logger.debug("accepting %s", name)
            if name == "Deletion":
                range.SelectContainerContents()
                range.Delete()
            range.RemoveContainerTags()
            review_markup_next()

        def review_markup_reject(_event=None):
            """Back out the revision markup."""

            range = self.document.Range
            name = range.ElementName(0)
            self.logger.debug("rejecting %s", name)
            if name == "Insertion":
                range.SelectContainerContents()
                range.Delete()
            range.RemoveContainerTags()
            review_markup_next()

        def map_source(value):
            """Transform the stored source value into the display equivalent.

            Required positional argument:
                value - string stored in the Source attribute

            Return:
                "Advisory Board" or "Editorial Board"
            """

            if value == "advisory-board":
                return "Advisory Board"
            return "Editorial Board"

        def parse_date(value):
            """Get an ISO-formatted date if the value is parseable.

            Required positional argument:
                value - string representing the date/time the markup was added

            Return:
                date as YYYY-MM-DD if parseable; else the original value
            """

            try:
                return str(dateutil.parser.parse(value))[:10]
            except:
                self.exception("unable to parse markup date/time %r", value)
                return value

        # Create the dialog window used to navigate and review the markup.
        dialog = DialogBox(self, "Review Markup", review_markup_next)

        # Create a row at the top of the dialog window.
        top = ttk.Frame(dialog.form)
        top.grid(row=0, column=0, padx=0)

        # Add radio buttons for selection revision level(s).
        levels = "all", "publish", "approved", "proposed"
        opts = dict(
            frame=top,
            default="all",
            width=23,
            sticky="W",
            padx=0,
            pady=0,
        )
        args = "Markup Level(s)", levels, 0, 0
        level_filter = dialog.add_radios(*args, **opts)

        # Add the action buttons to the right of the
        button_box = ttk.Frame(top)
        button_box.grid(row=0, column=1, padx=(20,0), sticky="W")
        button_info = (
            ("Next", review_markup_next, True, True),
            ("Accept", review_markup_accept, False, False),
            ("Reject", review_markup_reject, False, False),
            ("Done", dialog.close, False, True),
        )
        opts = dict(frame=button_box, pady=3)
        buttons = {}
        for row, (label, callback, focus, enabled) in enumerate(button_info):
            button = dialog.add_button(label, callback, row, 0, **opts)
            if focus:
                button.focus()
            if not enabled:
                button.config(state="disabled")
            buttons[label] = button

        # Create the frame in which we display the markup information.
        frame = ttk.LabelFrame(dialog.form, text="Current Markup")
        frame.grid(row=1, column=0, sticky="W", pady=10)
        labels = "User", "Date", "Level", "Source", "Content", "Action"
        label_opts = dict(column=0, sticky="W", padx=10)
        display_opts = dict(column=1, sticky="W")
        display = {}
        for row, label in enumerate(labels):
            var = display[label] = tkinter.StringVar()
            label_opts["row"] = display_opts["row"] = row
            if row == len(labels) - 1:
                label_opts["pady"] = display_opts["pady"] = (0, 10)
            ttk.Label(frame, text=label, width=10).grid(**label_opts)
            ttk.Label(frame, textvariable=var, width=30).grid(**display_opts)
        dialog.run(buttons["Next"])


    @handle_exceptions
    def save(self):
        """Save the currently active document in the CDR repository."""

        # Make sure saving is appropriate.
        if not self.active_document_is_writable:
            return self.app.Alert("Document is not locked for editing.")

        # Find out how the user wants to do this.
        doctype = self.doctype_name
        blob_allowed = doctype in self.DOCTYPES_WITH_BLOBS
        parms = self._get_save_parameters(blob_allowed, self.document_blocked)
        if not parms.confirmed:
            return

        # Create and submit the save request to the CDR server.
        new_doc = not self.cdr_id
        location_id = self.location_id
        start = datetime.datetime.now()
        response = self._save_document(self.cdr_id, doctype, parms)
        elapsed = datetime.datetime.now() - start

        # Make sure the document has a CDR ID.
        doc_id = self.get_text(response.find("CdrResponse/*/DocId"))
        if not doc_id:
            return self.app.Alert("Unable to find document ID.")

        # Tell the user what happened.
        validation_errors = ValidationErrors(response)
        if parms.validate and not validation_errors:
            self._show_validation_certificate(doc_id)
        message = f"Document stored successfully (elapsed: {elapsed}."
        if new_doc:
            message += "\nIt is now checked out to you"
            message += "\nPlease check it in when processing is complete."
        self.app.Alert(message)

        # Close the document; open it again if it wasn't unlocked.
        self.document.Close(self.XM_DO_NOT_SAVE_CHANGES)
        if not parms.unlock:
            self._open_doc(response, doc_id, checkout=True)
            if validation_errors:
                key = self.document_path
                self.validation_error_sets[key] = validation_errors
            if location_id:
                root = self.document_element
                if not self._move_to_location_id(location_id, root):
                    self.app.Alert(f"Unable to find location {location_id}")

        # If there were any validation errors, let the user know.
        if validation_errors:
            count = len(validation_errors.errors)
            self.app.Alert(f"Found {count} validation errors/warnings.")

    @handle_exceptions
    def sc_3quart(self):
        """Insert 3/4 special character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xBE")

    @handle_exceptions
    def sc_alpha(self):
        """Insert Greek alpha character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u03B1")

    @handle_exceptions
    def sc_beta(self):
        """Insert Greek beta character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u03B2")

    @handle_exceptions
    def sc_copy(self):
        """Insert copyright symbol."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xA9")

    @handle_exceptions
    def sc_cross(self):
        """Insert dagger special character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2020")

    @handle_exceptions
    def sc_dblx(self):
        """Insert double-dagger special character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2021")

    @handle_exceptions
    def sc_deg(self):
        """Insert degree special character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xB0")

    @handle_exceptions
    def sc_delta(self):
        """Insert Greek delta character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u03B4")

    @handle_exceptions
    def sc_down(self):
        """Insert down arrow character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2193")

    @handle_exceptions
    def sc_gamma(self):
        """Insert Greek gamma character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u03B3")

    @handle_exceptions
    def sc_ge(self):
        """Insert >= special character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2265")

    @handle_exceptions
    def sc_half(self):
        """Insert 1/2 special character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xBD")

    @handle_exceptions
    def sc_lapos(self):
        """Insert "smart" left apostrophe character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2018")

    @handle_exceptions
    def sc_le(self):
        """Insert <= character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2264")

    @handle_exceptions
    def sc_left(self):
        """Insert left-arrow character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2190")

    @handle_exceptions
    def sc_lquot(self):
        """Insert "smart" left-quote character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u201C")

    @handle_exceptions
    def sc_mdash(self):
        """Insert m-dash character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2014")

    @handle_exceptions
    def sc_mu(self):
        """Insert Greek mu character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u03BC")

    @handle_exceptions
    def sc_nbsp(self):
        """Insert non-breaking space character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xA0")

    @handle_exceptions
    def sc_plusmin(self):
        """Insert +/- character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xB1")

    @handle_exceptions
    def sc_quarter(self):
        """Insert 1/4 character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xBC")

    @handle_exceptions
    def sc_rapos(self):
        """Insert "smart" right apostrophe character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2019")

    @handle_exceptions
    def sc_reg(self):
        """Insert registered trademark character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\xAE")

    @handle_exceptions
    def sc_right(self):
        """Insert rignt arrow character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2192")

    @handle_exceptions
    def sc_rquot(self):
        """Insert "smart" right-quote character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u201D")

    @handle_exceptions
    def sc_tm(self):
        """Insert trademark character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2122")

    @handle_exceptions
    def sc_up(self):
        """Insert arrow up character."""

        if self.app.Selection:
            self.app.Selection.TypeText("\u2191")

    @handle_exceptions
    def search(self):
        """Search for and retrieve a specific CDR document."""

        def search_callback(_event=None):
            """Find documents matching the search criteria."""

            # Verify that we have the parameters we need.
            index = doctype.current()
            doctype_name = doctypes[index] if index else ""
            fragment = title.get()
            operator = locations.get(location.get())
            if not operator or not (doctype_name or fragment):
                return
            if not fragment and operator == "eq":
                return

            # Remember these values.
            self.last_search["title"] = fragment
            self.last_search["location"] = location.get()
            self.last_search["doctype"] = doctype_name or "Any Type"
            self.last_search["lock"] = lock.get()
            self.last_search["documents"] = []
            self.last_search["selected_document"] = None

            # Ask the CDR server to find the first 100 matching documents.
            command_set = CommandSet(self, "CdrSearch")
            query = etree.SubElement(command_set.command, "Query")
            query.set("MaxDocs", "100")
            test = f"CdrCtl/Title {operator} {fragment or '%'}"
            etree.SubElement(query, "Test").text = test
            if doctype_name:
                etree.SubElement(query, "DocType").text = doctype_name
            response = command_set.send()

            # Extract the list of documents we found.
            docs = []
            for node in response.iter("QueryResult"):
                doc_id = self.get_text(node.find("DocId"))
                doc_title = self.get_text(node.find("DocTitle"))
                docs.append(f" [{doc_id}] {doc_title} ")
            self.logger.debug("search found %d docs", len(docs))
            document.delete(0, "end")
            if docs:
                document.insert("end", *docs)
                self.last_search["documents"] = docs
                self.last_search["selected_document"] = docs[0]
                document.activate(0)
                document.selection_set(0)
                document.focus()
                buttons["Retrieve"].config(state="normal")
                buttons["Versions"].config(state="normal")
            else:
                self.app.Alert("No documents match this query.")
                buttons["Retrieve"].config(state="disabled")
                buttons["Versions"].config(state="disabled")

        def search_retrieve_callback(_event=None):
            """Open the current working version for the selected document."""

            selected = document.curselection()
            docs = self.last_search["documents"]
            self.logger.debug("selected=%s for %d docs", selected, len(docs))
            if selected and docs:
                selected_document = docs[selected[0]]
                self.last_search["selected_document"] = selected_document
                self.last_search["lock"] = lock.get()
                self.logger.debug("selected doc: %s", selected_document)
                match = re.search(r"^ \[([^]]+)\]", selected_document)
                doc_id = match.group(1)
                dialog.make_not_topmost()
                self._fetch_and_open_doc(doc_id, checkout=lock.get())
                dialog.close()

        def search_versions_callback(_event=None):
            """Chain to a second dialog form for selecting a version."""

            selected = document.curselection()
            docs = self.last_search["documents"]
            self.logger.debug("selected=%s for %d docs", selected, len(docs))
            if selected and docs:
                selected_document = docs[selected[0]]
                self.last_search["selected_document"] = selected_document
                self.last_search["lock"] = lock.get()
                self.logger.debug("selected doc: %s", selected_document)
                match = re.search(r"^ \[([^]]+)\]", selected_document)
                doc_id = match.group(1)
                command_set = CommandSet(self, "CdrListVersions")
                etree.SubElement(command_set.command, "DocId").text = doc_id
                response = command_set.send()
                versions = []
                for node in response.iter("Version"):
                    number = self.get_text(node.find("Num"))
                    comment = self.get_text(node.find("Comment"), "")
                    comment = self.normalize_space(comment or "No comment")
                    date = self.get_text(node.find("Date"))[:10]
                    versions.append(f" [{number}] {date} {comment} ")
                self.logger.info("Search found %d versions", len(versions))
                if versions:
                    self._pick_version(dialog, doc_id, versions)
                else:
                    self.app.Alert("No versions found.")


        def search_check_searchable(event=None):
            """Prevent search with no title fragment or doctype."""

            if title.get():
                buttons["Search"].config(state="normal")
            elif not doctype.current():
                buttons["Search"].config(state="disabled")
            else:
                operator = locations.get(location.get())
                state = "disabled" if operator == "eq" else "normal"
                buttons["Search"].config(state=state)

        def autocomplete(event=None):
            """Let the user navigate the doctypes more easily."""

            keypressed = event.char if event else None
            if keypressed:
                keypressed = keypressed.upper()
                i = doctype.current() + 1
                for _ in range(len(doctypes)):
                    if i == len(doctypes):
                        i = 0
                    k = doctypes[i][0].upper()
                    if k == keypressed:
                        doctype.current(i)
                        break
                    i += 1
                search_check_searchable()

        # Create the dialog box form and add the first field.
        dialog = DialogBox(self, "CDR Search", search_callback)
        top = ttk.Frame(dialog.form)
        top.grid(row=0, column=0, padx=10, pady=(10, 5), sticky="w")
        title_opts = dict(
            width=70,
            frame=top,
            sticky="w",
            padx=(0, 0),
            focus=True,
        )
        default_title = self.last_search.get("title")
        if default_title:
            title_opts["value"] = default_title
            title_opts["select"] = True
        title = dialog.add_text_field("Doc Title", 0, 0, **title_opts)
        title.bind("<KeyRelease>", search_check_searchable)

        # Add the doctype field next so that it's second in the tab order.
        middle = ttk.Frame(dialog.form)
        middle.grid(row=1, column=0, padx=10, pady=0, sticky="w")
        left = ttk.Frame(middle)
        left.grid(row=0, column=0, sticky="w", pady=0)
        doctype_wrapper = ttk.Frame(left)
        doctype_wrapper.grid(row=1, column=0, sticky="w", pady=(10, 0))
        label = ttk.Label(doctype_wrapper, text="Document Type")
        label.grid(row=0, column=0, padx=(0, 10), pady=0, sticky="w")
        doctypes = ["Any Type"] + sorted(self.doctypes)
        doctype_opts = dict(state="readonly", width=43, values=doctypes)
        doctype_opts["height"] = 24
        doctype = ttk.Combobox(doctype_wrapper, **doctype_opts)
        doctype.bind("<Key>", autocomplete)
        doctype.bind("<<ComboboxSelected>>", search_check_searchable)
        default_doctype = self.last_search.get("doctype", "Any Type")
        doctype.current(doctypes.index(default_doctype))
        doctype.grid(row=0, column=1, sticky="w", pady=0)

        # Add the remaining fields.
        upper = ttk.Frame(left)
        upper.grid(row=0, column=0, sticky="w", pady=0)
        lock_opts = dict(frame=upper, padx=(0, 40))
        if self.last_search.get("lock"):
            lock_opts["checked"] = True
        lock = dialog.add_checkbox("Check Out?", 0, 0, **lock_opts)
        locations = {
            "Start of title": "begins",
            "Anywhere in title": "contains",
            "Entire title": "eq",
        }
        location_args = "Location of string", locations.keys(), 0, 1
        default = self.last_search.get("location", "Start of title")
        location_opts = dict(frame=upper, default=default, width=20, pady=0)
        location = dialog.add_radios(*location_args, **location_opts)

        # add the buttons on the right side of the dialog box.
        button_frame = ttk.Frame(middle)
        button_frame.grid(
            row=0,
            column=1,
            padx=(25, 0),
            pady=(31, 0),
            sticky="nw",
        )
        button_opts = dict(frame=button_frame, pady=4)
        documents = self.last_search.get("documents", [])
        selected_document = self.last_search.get("selected_document")
        if documents and selected_document is None:
            selected_document = documents[0]
        can_search = default_title or default_doctype != "Any Type"
        button_info = (
            ("Search", search_callback, not can_search),
            ("Close", dialog.close, False),
            ("Retrieve", search_retrieve_callback, not documents),
            ("Versions", search_versions_callback, not documents),
        )
        buttons = {}
        for i, (name, callback, disable) in enumerate(button_info):
            b = dialog.add_button(name, callback, i, 0, **button_opts)
            buttons[name] = b
            if disable:
                b.config(state="disabled")
        buttons["Search"].bind("<Return>", search_callback)

        # Add the box where the matching documents are listed at the bottom.
        document_opts = dict(
            height=5,
            width=80,
            padx=10,
            pady=(25, 10),
            sticky="w",
            scrollbars="both",
            command=search_retrieve_callback,
        )
        if selected_document:
            document_opts["value"] = selected_document
        document = dialog.add_listbox(documents, 2, 0, **document_opts)
        title.select_range(0, "end")
        dialog.run(title)

    @handle_exceptions
    def search_pubmed(self):
        """Open the browser on NLM's PubMed web site."""
        self.browser.open_new_tab(self.PUBMED)

    @handle_exceptions
    def set_last_reviewed_date(self):
        """Set the LastReviewedDate attribute on the current element."""

        node = self.app.Selection.ContainerNode
        depth = 5
        while not self._is_element(node) and depth > 0:
            self.logger.debug(f"set_last_reviewed_date(): depth={depth}")
            node = node.parentNode
            depth -= 1
        if self._is_element(node):
            node.setAttribute("LastReviewedDate", str(datetime.date.today()))

    @handle_exceptions
    def set_non_public(self):
        """Set the Public attribute of the current element to "No"."""

        node = self.app.Selection.ContainerNode
        if not node or node.nodeType != self.DOM_NODE_TYPE_ELEMENT:
            return self.app.Alert("Can't find current element.")
        doctype = self.document.doctype
        if not doctype.hasAttribute(node.nodeName, "Public"):
            message = "Current element does not have a Public attribute."
            return self.app.Alert(message)
        saved_flag = self.app.Selection.ReadOnlyContainer
        self.app.Selection.ReadOnlyContainer = False
        self.editing_element = True
        node.setAttribute("Public", "No")
        self.editing_element = False
        self.app.Selection.ReadOnlyContainer = saved_flag

    @handle_exceptions
    def set_public(self):
        """Remove the Public attribute of the current element.

        The attribute's default value is "Yes".
        """

        node = self.app.Selection.ContainerNode
        if not node or node.nodeType != self.DOM_NODE_TYPE_ELEMENT:
            return self.app.Alert("Can't find current element.")
        doctype = self.document.doctype
        if not doctype.hasAttribute(node.nodeName, "Public"):
            message = "Current element does not have a Public attribute."
            return self.app.Alert(message)
        saved_flag = self.app.Selection.ReadOnlyContainer
        self.app.Selection.ReadOnlyContainer = False
        self.editing_element = True
        node.removeAttribute("Public")
        self.editing_element = False
        self.app.Selection.ReadOnlyContainer = saved_flag

    @handle_exceptions
    def set_source_to_advisory_board(self):
        """Identify the selected revision markup as for the advisory board."""

        if not self.active_document_is_writable:
            self.app.Alert("A writable document is not currently active.")
        else:
            count = self._set_rev_markup_attrs("Source", "advisory-board")
            s = "" if count == 1 else "s"
            message = f"Set Source to advisory-board for {count} element{s}."
            self.app.Alert(message)

    @handle_exceptions
    def set_source_to_editorial_board(self):
        """Identify the selected revision markup as for the editorial board."""

        if not self.active_document_is_writable:
            self.app.Alert("A writable document is not currently active.")
        else:
            count = self._set_rev_markup_attrs("Source", "editorial-board")
            s = "" if count == 1 else "s"
            message = f"Set Source to editorial-board for {count} element{s}."
            self.app.Alert(message)

    @handle_exceptions
    def show_checked_out_docs(self):
        """Bring up report showing documents checked out by this user."""

        parms = f"Session={self.session}&User={self.user}"
        url = f"{self.cgi_bin}/CheckedOutDocs.py?{parms}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def show_doc_blob(self):
        """Use the web interface for showing the document's blob."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        url = f"{self.cgi_bin}/GetCdrBlob.py?id={self.cdr_id}"
        if self.document_version:
            url += f"&ver={self.document_version}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def show_glossary_term_names(self):
        """Display a list of the names connected with the open concept doc."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        docs = self._get_glossary_names_for_concept()
        if not docs:
            return self.app.Alert("No term name documents found.")
        names = [f"    {self.normalize_space(n)}" for n in docs.values()]
        names = "\n".join(names)
        self.app.Alert(f"Term names:\n{names}")

    @handle_exceptions
    def show_info(self):
        try:
            uname = platform.uname()
            info = (
                f"CDR Server: {self.server}",
                f"API Server: {self.api_server}",
                f"Session: {self.session}",
                f"User: {self.user}",
                f"Path: {self.path}",
                f"Tier: {self.tier}",
                f"Client logging level: {self.client_logging_level}",
                f"Server logging level: {self.server_logging_level}",
                f"Python: {platform.python_version()}",
                f"System: {uname.system}",
                f"Version: {uname.version}",
                f"Architecture: {uname.machine}",
                f"Machine Name: {uname.node}",
            )
            self.app.Alert("\n".join(info))
        except Exception as e:
            self.app.Alert(f"oops! {e}")

    @handle_exceptions
    def show_linked_object(self):
        """Launch the app associated with the current element's linked blob."""

        # Make sure we have a link.
        if not self.document:
            return self.app.Alert("No document is currently open.")
        doc_id = self._get_object_link_id()
        if not doc_id:
            return self.app.Alert("No link found to a launchable object.")

        # Get the blob.
        command_set = CommandSet(self, "CdrGetDoc")
        command_set.command.set("IncludeXml", "Y")
        command_set.command.set("IncludeBlob", "Y")
        etree.SubElement(command_set.command, "DocId").text = doc_id
        etree.SubElement(command_set.command, "Lock").text = "N"
        response = command_set.send()
        doc = response.find("*/*/CdrDoc")
        if doc is None:
            return self.app.Alert("Unable to find CdrDoc element")
        xml = self.get_text(doc.find("CdrDocXml"))
        root = etree.fromstring(xml)
        extension = self._get_blob_extension(root)
        if not extension:
            return self.app.Alert("Can't determine media file extension.")
        encoded = self.get_text(doc.find("CdrDocBlob"))
        if not encoded:
            return self.app.Alert("Unable to find media bytes.")
        blob_bytes = base64.b64decode(encoded)

        # Save the blob.
        media_path = pathlib.Path(self.path, "Cdr", "Media")
        media_path.mkdir(exist_ok=True, parents=True)
        int_id = self.extract_id(doc_id)
        filename = f"CDR{int_id}{extension}"
        path = media_path / filename
        path.write_bytes(blob_bytes)

        # Open the blob.
        self.logger.info("Opening %s (%d bytes)", path, len(blob_bytes))
        args = None, "open", str(path), None, None, win32con.SW_SHOWNORMAL
        try:
            win32api.ShellExecute(*args)
        except:
            self.logger.exception("failure")
            lines = (
                f"Unable to open {path}.",
                "Do you need to register a default",
                "application for the file type?",
            )
            self.app.Alert("\n".join(lines))

    @handle_exceptions
    def show_next_validation_error(self):
        """Navigate to the next problem in the document."""

        if not self.document:
            return self.app.Alert("No document is currently active.")
        error_set = self.validation_error_sets.get(self.document_path)
        if not error_set:
            return self.app.Alert("No validation results available.")
        if not error_set.errors:
            return self.app.Alert("No validation errors found.")
        error = error_set.next()
        if not error:
            return self.app.Alert("No more validation errors found.")
        message = error.message
        if error.elevel:
            message = f"{message} ({error.elevel})"
        self.app.Alert(message)
        if not error.eid:
            return self.app.Alert("No error location specified by the server.")
        node = self.document.getElementById(error.eid)
        if not node:
            return self.app.Alert(f"Unable to find error {error.eid}.")
        self.app.Selection.SelectNodeContents(node)
        self.app.Selection.MoveLeft(self.XM_COLLAPSE_END)

    @handle_exceptions
    def show_server_free_space(self):
        """Show that we can talk to the CDR server directly from our script."""
        response = requests.get(f"{self.cgi_bin}/df.py")
        self.app.Alert(response.text)

    @handle_exceptions
    def spanish_link_id_swap(self):
        """Redirect links to the original English doc to this Spanish doc."""

        # Make sure we have what we need.
        doc = self.document
        node = self._get_single_element("TranslationOf", doc) if doc else None
        old_id = node.getAttribute("cdr:ref") if node else ""
        new_id = self.cdr_id if doc else None
        if not node:
            return self.app.Alert("TranslationOf element not found.")
        if not old_id:
            return self.app.Alert("TranslationOf document ID not found.")
        if len(old_id) != 13 or not old_id.startswith("CDR"):
            return self.app.Alert(f"Malformed TranslationOf ID: {old_id}")
        if not new_id:
            return self.app.Alert("Summary has not yet been saved.")
        if len(new_id) != 13 or not new_id.startswith("CDR"):
            return self.app.Alert(f"Malformed document ID: {new_id}")

        # Handle the internal links.
        replaced = 0
        elements = dict(
            SummaryFragmentRef="cdr:href",
            ReferencedTableNumber="Target",
            ReferencedFigureNumber="Target",
        )
        for name, attr in elements.items():
            links = doc.getElementsByTagName(name)
            for i in range(links.length):
                node = links.item(i)
                element = self.cast(node)
                link_id = element.getAttribute(attr)
                if link_id and link_id.startswith(old_id):
                    new_value = f"{new_id}{link_id[13:]}"
                    element.setAttribute(attr, new_value)
                    replaced += 1
                    args = name, attr, link_id, new_value
                    self.logger.debug("%s/@%s: replaced %r with %r", *args)

        # Handle links to other documents.
        elements = dict(
            MediaID="cdr:ref",
            MiscellaneousDocLink="cdr:ref",
            SummaryRef="cdr:href",
        )
        for name, attr in elements.items():
            links = doc.getElementsByTagName(name)
            for i in range(links.length):
                node = links.item(i)
                element = self.cast(node)
                link_id = element.getAttribute(attr)
                translated_id = self._get_translated_doc_id(link_id)
                if translated_id:
                    new_value = f"{translated_id}{link_id[13:]}"
                    element.setAttribute(attr, new_value)
                    replaced += 1
                    args = name, attr, link_id, new_value
                    self.logger.debug("%s/@%s: replaced %r with %r", *args)
                else:
                    args = name, attr, link_id
                    message = "%s/@%s: no translated id for %s"
                    self.logger.warning(message, *args)

        # Show the number of replacements we made.
        s = "" if replaced == 1 else "s"
        self.app.Alert(f"Swapped {replaced} link{s}.")

    @handle_exceptions
    def strip_id_attributes(self):
        """Recursively remove cdr:id attributes from the current selection."""

        if not self.active_document_is_writable:
            self.app.Alert("A writable document is not currently active.")
        else:
            self._strip_cdr_id_attributes(self.current_element)


    @handle_exceptions
    def table(self):
        """Launch the Table wizard.

        The code used for earlier versions of XMetaL is broken, because
        the Table menu has been removed. So now we use the toolbar button.
        """

        toolbar = self.app.CommandBars.item("Table")
        if not toolbar:
            return self.app.Alert("Can't find Table toolbar.")
        button = toolbar.Controls.item(1)
        if not button:
            return self.app.Alert("Unable to find the Insert Table button")
        button.Execute()

    @handle_exceptions
    def term_hierarchy(self):
        """Web interface for displaying Term document hierarchies."""

        if self.doctype_name == "Term" and self.cdr_id:
            url = f"{self.cgi_bin}/TermHierarchy.py?DocId={self.cdr_id}"
            self.browser.open_new_tab(url)

    @handle_exceptions
    def termname_with_concept_qc_report(self):
        """Launch the "TermName with Concept" report for the current doc."""

        if not self.cdr_id:
            return self.app.Alert("Current document ID not found.")
        session = self.session or "guest"
        filter = "QC GlossaryTermName with Concept Set".replace(" ", "+")
        parms = "&".join([
            f"Session={session}",
            f"DocId={self.cdr_id}",
            f"Filter=set:{filter}",
            "isqc=true",
        ])
        self.browser.open_new_tab(f"{self.cgi_bin}/Filter.py?{parms}")

    @handle_exceptions
    def termset_qc_report(self):
        """Launch the TermSet QC report for the current doc."""

        if not self.cdr_id:
            return self.app.Alert("Current document ID not found.")
        session = self.session or "guest"
        filter = "TermSet QC Report Filter".replace(" ", "+")
        parms = "&".join([
            f"Session={session}",
            f"DocId={self.cdr_id}",
            f"Filter=name:{filter}",
        ])
        self.browser.open_new_tab(f"{self.cgi_bin}/Filter.py?{parms}")

    @handle_exceptions
    def test_env_fetch(self):
        """Test fetch of an environment variable."""

        name = self.app.Prompt("Environment variable name?")
        value = os.getenv(name) or f"[Environment variable {name!r} not found]"
        self.app.Alert(value)

    @handle_exceptions
    def translation_job(self):
        """Open a new browser tab for the Summary Translation Job report."""

        element = self._get_single_element("TranslationOf")
        session = self.session or "guest"
        if element:
            doc_id = element.getAttribute("cdr:ref")
        else:
            doc_id = self.cdr_id
        if not doc_id:
            self.app.Alert("Summary has not yet been saved.")
        else:
            int_id = self.extract_id(doc_id)
            parms = f"Session={session}&english_id={int_id}"
            url = f"{self.cgi_bin}/translation-job.py?{parms}"
            self.browser.open_new_tab(url)

    @handle_exceptions
    def translation_job_queue(self):
        """Open a browser tab for the Summary Translation Job Queue report."""

        session = self.session or "guest"
        url = f"{self.cgi_bin}/translation-jobs.py?Session={session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def translation_job_workflow_report(self):
        """Open a browser tab for the Summary Translation Workflow report."""

        session = self.session or "guest"
        url = f"{self.cgi_bin}/translation-job-report.py?Session={session}"
        self.browser.open_new_tab(url)

    @handle_exceptions
    def update_summary_ref_titles(self):
        """Update the display text for links to the current Summary."""

        if not self.cdr_id:
            self.app.Alert("Summary document has not yet been saved.")
        else:
            parms = f"Session={self.session}&id={self.cdr_id}"
            url = f"{self.cgi_bin}/UpdateSummaryRefTitles.py?{parms}"
            self.browser.open_new_tab(url)

    @handle_exceptions
    def validate(self):
        """Ask the CDR server to validate the currently active document."""

        # Make sure we have a saved document to validate.
        if not self.cdr_id:
            return self.app.Alert("Document has never been saved.")

        # Find out how the user wants to do the validation.
        parms = self._get_validation_parameters()
        if not parms.validations:
            return

        # Assemble the validation command.
        command_set = CommandSet(self, "CdrValidateDoc")
        command_set.command.set("DocType", self.doctype_name)
        command_set.command.set("ErrorLocators", "Y")
        command_set.command.set("ValidationTypes", parms.validations)
        command_set.command.set("Id", self.cdr_id)
        doc = etree.SubElement(command_set.command, "CdrDoc")
        doc.set("Type", self.doctype_name)
        doc.set("RevisionFilterLevel", str(parms.filter_level))
        ctl = etree.SubElement(doc, "CdrDocCtl")
        etree.SubElement(ctl, "DocId").text = self.cdr_id
        etree.SubElement(ctl, "DocTitle").text = self.document_title
        root = etree.fromstring(self.document_element.xml)
        node = root.find("CdrDocCtl")
        if node is not None:
            root.remove(node)
        for node in root.xpath("//*[@readonly]"):
            self.logger.debug("removing readonly attribute from %s", node.tag)
            node.attrib.pop("readonly", None)
        xml = etree.tostring(root, encoding="unicode").replace("\r", "")
        self.logger.trace("Document XML for save:\n%s", xml)
        etree.SubElement(doc, "CdrDocXml").text = etree.CDATA(xml)

        # Do the validation and show the results.
        response = command_set.send()
        validation_errors = ValidationErrors(response)
        if validation_errors:
            count = len(validation_errors.errors)
            path = self.document_path
            self.logger.debug("saving %d errors for %s", count, path)
            self.validation_error_sets[path] = validation_errors
            self.document.Close(self.XM_DO_NOT_SAVE_CHANGES)
            opts = {}
            if "Checkout" in path:
                opts["checkout"] = True
            if "-V" in path:
                opts["version"] = path.split("-V")[1][:-4]
            self._open_doc(response, self.cdr_id, **opts)
            self.app.Alert(f"Found {count} validation errors/warnings.")
        else:
            self._show_validation_certificate(self.cdr_id)

    @handle_exceptions
    def view_gtn_docs(self):
        """Open the name documents for this concept doc in view mode."""

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        docs = self._get_glossary_names_for_concept()
        if not docs:
            return self.app.Alert("No term name documents found.")
        for id in docs:
            self._fetch_and_open_doc(id)

    @handle_exceptions
    def view_linked_gtc_doc(self):
        """Open the concept doc for the current name doc in view mode."""

        element = self._get_single_element("GlossaryTermConcept")
        if not element:
            return self.app.Alert("Can't find GlossaryTermConcept element.")
        doc_id = element.getAttribute("cdr:ref")
        self._fetch_and_open_doc(doc_id)

    @handle_exceptions
    def view_svpc_docs(self):
        """Open linked SVPC documents for viewing."""

        root = self.document_element
        if not root:
            return self.app.Alert("No document is open.")
        if root.nodeName != "Summary":
            return self.app.Alert("This is not a Summary document.")
        count = 0
        children = root.childNodes
        for i in range(children.length):
            node = children.item(i)
            if node.nodeName == "SummaryModuleLink":
                element = self.cast(node)
                doc_id = element.getAttribute("cdr:ref")
                self._fetch_and_open_doc(doc_id)
                count += 1
        if not count:
            self.app.Alert("No linked SVPC summaries found.")

    @handle_exceptions
    def xpath_bug_repro(self):
        """Repro case for XMetaL XPath bug.

        XMetaL can't find the matching element. The XPath expression
        is confirmed as correct at http://xpather.com/. Reported to
        the vendor 2008-04-10. Still not fixed as of late 2022.
        """

        xml = f"""\
<?xml version="1.0" ?>
<!DOCTYPE PoliticalSubUnit SYSTEM "PoliticalSubUnit.dtd">
<PoliticalSubUnit xmlns:cdr="{self.NAMESPACE}">
 <CdrDocCtl>
  <DocId>CDR9876543210</DocId>
  <DocTitle>XPath Bug Repro</DocTitle>
 </CdrDocCtl>
 <PoliticalSubUnitFullName>Duck Soup</PoliticalSubUnitFullName>
 <Country cdr:ref="CDR0123456789">Freedonia</Country>
</PoliticalSubUnit>"""

        doc = self.app.Documents.OpenString(xml)
        selectors = " and ".join([
            f'namespace-uri()="{self.NAMESPACE}"',
            'local-name()="ref"'
        ])
        xpath = f'//*[@*[{selectors}]="CDR0123456789"]'
        nodes = self.document.getNodesByXPath(xpath)
        if nodes.length:
            self.app.Alert("XMetaL found {xpath}.")
        else:
            self.app.Alert(f"Unable to find {xpath}.\nBug still not fixed.")


    ######################################################################
    #                      INTERNAL HELPER METHODS                       #
    ######################################################################

    def _add_macro(self, label, name=None):
        """Append a macro to the context popup menu.

        Required positional argument:
            label - What the user sees (with option hotkey "&" indicator)

        Optional keyword argument:
            name - override for macro name
        """

        self.app.AppendMacro(label, name or label.replace("&", ""))

    def _add_menu_item(self, menu, values):
        """Add the next item to the specified menu.

        Pass:
            menu - XMetaL object for the menu currently being built
            values - dictionary of values used for creating the menu item
        """

        control = menu.Controls.Add(5)
        item = self.cast(control, "CommandBarPopup")
        item.OnAction = values["macro"]
        item.DescriptionText = values["description"]
        item.caption = values["label"]
        item.BeginGroup = values.get("new_group", False)
        icon = values.get("icon")
        if icon:
            item.faceId = self.app.MakeFaceId(*icon)

    def _add_toolbar_button(self, bar, values):
        """Add the next button to the specified toolbar.

        Pass:
            bar - XMetaL object for the toolbar currently being built
            values - dictionary of values used for creating the button
        """

        control = bar.Controls.Add(self.XM_CONTROL_TYPE_BUTTON)
        if not control:
            raise Exception("Unable to create action control.")

        # Workaround for bug #00014801.
        button = self.cast(control, "CommandBarButton")
        if not button:
            raise Exception("Unable to create toolbar button.")
        button.OnAction = values["macro"]
        button.TooltipText = values["tooltip"]
        button.Enabled = True
        button.DescriptionText = values["description"]
        button.BeginGroup = values.get("new_group", False)
        # Broken. Bug report #00014801 filed with JustSystems. Works now.
        # Docs say FaceId but they mean faceId.
        button.faceId = self.app.MakeFaceId(*values["icon"])

    def _adjust_media_document_values(self, root, blob_bytes):
        """Tweak values in a Media document we're about to save.

        Require positional arguments:
            root - parsed XML document to be saved
            blob_bytes - file bytes for this Media document
        """

        # Set the dimensions for the possibly new image file.
        for node in root.iter("ImageDimensions"):
            image = Image.open(io.BytesIO(blob_bytes))
            width, height = image.size
            child = node.find("WidthPixels")
            if child is not None:
                self.logger.debug("image width: %s", width)
                child.text = str(width)
            child = node.find("HeightPixels")
            if child is not None:
                self.logger.debug("image height: %s", height)
                child.text = str(height)

        # Determine the duration of an audio Media file.
        for node in root.iter("SoundData"):
            mp3 = MP3(io.BytesIO(blob_bytes))
            seconds = int(round(mp3.info.length))
            child = node.find("RunSeconds")
            if child is not None:
                self.logger.debug("setting audio seconds to %s", seconds)
                child.text = str(seconds)

    def _adjust_toolbar_visibility(self):
        """Separated out so we can call it directly ourselves."""

        if self.app.CommandBars:
            bars = self.app.CommandBars
            doctype = self.doctype_name or ""
            for i in range(bars.Count):
                bar = bars.item(i+1)
                if bar.name in self.toolbars:
                    bar.visible = self.toolbars[bar.name] == doctype
                elif bar.name in self.SUPPRESSED_TOOLBARS:
                    bar.visible = False
                elif bar.name in self.KEEP_VISIBLE:
                    bar.visible = True

    def _can_open(self, cdr_id, **opts):
        """If the doc is already open with changes, can we overwrite them?

        Required positional arguments:
            cdr_id - identification of the CDR document to be opened

        Optional keyword arguments:
             version - identification of a specific document version to open
            checkout - if True, we're locking the document for editing

        Return:
            - True if the document is not already open
            - True if the document is open but there are no changes
            - True if the user approves abandoning those changes
            - Otherwise False
        """

        version = opts.get("version")
        int_id = self.extract_id(cdr_id)
        target = f"CDR{int_id}-V{version}" if version else f"CDR{int_id}"
        docs = self.app.Documents
        i = docs.Count
        while i > 0:
            doc = docs.item(i)
            self.logger.debug("comparing %s with %s", doc.Title, target)
            if doc.Title.startswith(f"{target} "):
                if not doc.Saved:
                    prompt = "\n".join([
                        f"A modified copy of {target} is already open.",
                        "Do you want to abandon the changes?",
                    ])
                    title = "Overwrite changes?"
                    keep_going = messagebox.askyesno(title, prompt)
                    if not keep_going:
                        return False
                doc.Close(self.XM_DO_NOT_SAVE_CHANGES)
            i -= 1
        self.logger.debug("_can_open() returning True")
        return True

    def _create_comment_element(self, **opts):
        """Assemble a comment node.

        Optional keyword arguments:
            tag - string to use for the element name (default is "Comment")
            audience - string for the audience attribute
            specific_internal_audience - e.g., "translators"
            prompt - string for the PI text (default is "Your comment here")
            as_string - if True, return the serialized XML for the element
        """

        element = etree.Element(opts.get("tag", "Comment"))
        element.set("user", self.user)
        element.set("date", str(datetime.date.today()))
        element.set("audience", opts.get("audience", "Internal"))
        name = "specific_internal_audience"
        if name in opts:
            element.set(name.replace("_", "-"), opts[name])
        prompt = opts.get("prompt", "Your comment here")
        pi = etree.ProcessingInstruction(self.XM_PI_TARGET, f"{{ {prompt} }}")
        element.append(pi)
        if opts.get("as_string"):
            return etree.tostring(element, encoding="unicode")
        return element

    def _edit_multiline_text(self, title, value, **opts):
        """Let the user edit a multi-line text value.

        Required positional arguments:
            title - string displayed at the top of the dialog box
            value - the original string value to be edited

        Optional keyword argument:
            readonly - if True, disable editing of the text

        Return:
            None if canceled or readonly; else the edited string value
        """

        def edit_multiline_text_callback(_event=None, readonly=False):
            """Capture the edited string value."""

            dialog.values.text = field.get("1.0", "end")
            dialog.close()

        callback = edit_multiline_text_callback
        dialog = DialogBox(self, title, None)
        field = dialog.add_textarea(0, 0, value=value)
        column = ttk.Frame(dialog.form)
        column.grid(row=0, column=1, padx=20)
        button_opts = dict(pady=3, frame=column)
        if opts.get("readonly"):
            dialog.add_button("OK", dialog.close, 0, 0, **button_opts)
            field.config(state="disabled")
        else:
            dialog.add_button("OK", callback, 0, 0, **button_opts)
            dialog.add_button("Cancel", dialog.close, 1, 0, **button_opts)
        dialog.run()
        return dialog.values.text

    def _fetch_and_open_doc(self, doc_id, **opts):
        """Get a document from the CDR server and open it in XMetaL.

        Required positional argument:
            doc_id - identification of the CDR document to be retrieved

        Optional keyword arguments:
            version - identification of a specific document version to fetch
            checkout - if True, lock the document for editing
        """

        if self._can_open(doc_id, **opts):
            message = "_fetch_and_open_doc(%s) opts=%s"
            self.logger.debug(message, doc_id, opts)
            response = self._fetch_doc(doc_id, **opts)
            if response is not None:
                self._open_doc(response, doc_id, **opts)

    def _fetch_candidate_link_targets(self, doctype, element_name, fragment):
        fragment = fragment.replace("[", "[[]").replace("_", "[_]")
        self.logger.debug("element=%s fragment=%s doctype=%s",
                          element_name, fragment, doctype)
        targets = []
        if doctype == "Person" and element_name == "FamilialCancerSyndrome":
            command_set = CommandSet(self, "CdrReport")
            command = command_set.command
            etree.SubElement(command, "ReportName").text = "GeneticsSyndromes"
            params = etree.SubElement(command, "ReportParams")
            param = etree.SubElement(params, "ReportParam")
            param.set("Name", "TitlePattern")
            param.set("Value", fragment)
            response = command_set.send()
            nodes = response.iter("ReportRow")
        else:
            command_set = CommandSet(self, "CdrSearchLinks")
            command = command_set.command
            command.set("MaxDocs", "150")
            etree.SubElement(command, "SourceDocType").text = doctype
            etree.SubElement(command, "SourceElementType").text = element_name
            etree.SubElement(command, "TargetTitlePattern").text = f"{fragment}%"
            response = command_set.send()
            nodes = response.iter("QueryResult")
        for node in nodes:
            doc_id = self.get_text(node.find("DocId"))
            title = self.get_text(node.find("DocTitle"))
            target = f" [{doc_id}] {title} "
            self.logger.debug("adding target %s", target)
            targets.append(target)
        return targets

    def _fetch_doc(self, doc_id, **opts):
        """Get the requested document from the CDR server.

        Required positional argument:
            doc_id - identification of the CDR document to be retrieved

        Optional keyword arguments:
            version - identification of a specific document version to fetch
            checkout - if True, lock the document for editing

        Return:
            parsed XML response to the request
        """

        self.logger.debug( "_fetch_doc(%s) with opts %s", doc_id, opts)
        version = opts.get("version", None)
        checkout = opts.get("checkout", False) and not version
        command_set = CommandSet(self, "CdrGetDoc")
        command = command_set.command
        command.set("includeBlob", "N")
        etree.SubElement(command, "DocId").text = str(doc_id)
        etree.SubElement(command, "Lock").text = "Y" if checkout else "N"
        if version:
            etree.SubElement(command, "DocVersion").text = str(version)
        self.logger.debug("calling CommandSet.send()")
        return command_set.send()

    def _fetch_link_location_targets(self, doc_id):
        """Get the picklist values for selecting an Organization address.

        Required positional argument:
            link - string in the form "[Doc ID] Organization

        Return:
            sequence of "[ID#fragment] address details" strings or None
        """

        # Ask the CDR server to extract the location addresses from the org doc.
        command_set = CommandSet(self, "CdrFilter")
        node = etree.SubElement(command_set.command, "Filter")
        node.set("Name", "Org Locations Picklist")
        parms = etree.SubElement(command_set.command, "Parms")
        parm = etree.SubElement(parms, "Parm")
        etree.SubElement(parm, "Name").text = "docId"
        etree.SubElement(parm, "Value").text = doc_id
        etree.SubElement(command_set.command, "Document").set("href", doc_id)
        response = command_set.send()
        for node in response.iter("Document"):
            xml = self.get_text(node)
            root = etree.fromstring(xml)
            targets = []
            for address in root.findall("Address"):
                id = self.get_text(address.find("Link"))
                text = self.get_text(address.find("Data"))
                targets.append(f" [{id}] {text} ")
            return targets
        return None

    def _find_comment(self, comment_type, forward):
        """Navigate to the next or previous markup element.

        Required positional arguments:
            comment_type - e.g., "Advisory Board" or "Permanent"
            forward - find next if True, previous if False
        """

        # Create a range object for searching.
        self.logger.debug("_find_comment(%s, %s)", comment_type, forward)
        range = self.document.Range

        # Figure out which attribute we want with which value.
        look_for = dict(
            Advisory_Board=("source", "advisory-board"),
            Internal=("audience", "Internal"),
            External=("audience", "External"),
            Permanent=("duration", "permanent"),
        )
        key = comment_type.replace(" ", "_")
        if key not in look_for:
            self.logger.error("_find_comment() bad type key: %r", key)
            return self.app.Alert("Internal error--unrecognized comment type.")
        name, value = look_for[key]

        # Keep looking until we find a comment, or the user tells us to stop.
        keep_going = True
        while keep_going:
            self.logger.debug("top of _find_comment() keep_going loop")
            range.Collapse(self.XM_COLLAPSE_START)
            found_comment = range.MoveToElement("Comment", forward)

            # Find a comment with a matching attribute.
            while found_comment:
                if range.ContainerNode.getAttribute(name) == value:
                    break
                range.Collapse(self.XM_COLLAPSE_START)
                found_comment = range.MoveToElement("Comment", forward)

            # If we found a matching caomment, move to it.
            if found_comment:
                keep_going = False
                range.SelectContainerContents()
                range.Select()

            # Otherwise, ask if we should wrap around.
            else:
                prompt = "End of document; wrap from top?"
                if not forward:
                    prompt = "Beginning of document; wrap from bottom?"
                keep_going = messagebox.askyesno("Continue?", prompt)
                if keep_going:
                    if forward:
                        self.logger.debug("starting over at the top")
                        range.MoveToDocumentStart()
                    else:
                        self.logger.debug("starting over at the bottom")
                        range.MoveToDocumentEnd()
                else:
                    self.logger.debug("user says we're done")

    def _find_markup(self, level, forward):
        """Navigate to the next or previous markup element.

        Required positional arguments:
            level - one of "publish", "approved", "proposed"
            forward - find next if True, previous if False
        """

        # Create range objects for searching.
        self.logger.debug("_find_markup(%s, %s)", level, forward)
        del_range = self.document.Range
        ins_range = self.document.Range

        # Keep looking until we find more markup, or the user tells us to stop.
        keep_going = True
        while keep_going:
            self.logger.debug("top of _find_markup() keep_going loop")
            del_range.Collapse(self.XM_COLLAPSE_START)
            ins_range.Collapse(self.XM_COLLAPSE_START)
            found_del = del_range.MoveToElement("Deletion", forward)
            found_ins = ins_range.MoveToElement("Insertion", forward)
            args = found_ins, found_del
            self.logger.debug("found_ins=%s found_del=%s", *args)

            # See if there's a Deletion element with the right revision level.
            while found_del:
                self.logger.debug("inside found_del loop")
                node = del_range.ContainerNode
                deletion_level = node.getAttribute("RevisionLevel")
                self.logger.debug("deletion level: %s", deletion_level)
                if deletion_level == level:
                    break
                del_range.Collapse(self.XM_COLLAPSE_START)
                found_del = del_range.MoveToElement("Deletion", forward)

            # Do the same thing for an Insertion element.
            while found_ins:
                self.logger.debug("inside found_ins loop")
                node = ins_range.ContainerNode
                insertion_level = node.getAttribute("RevisionLevel")
                self.logger.debug("insertion level: %s", insertion_level)
                if insertion_level == level:
                    break
                ins_range.Collapse(self.XM_COLLAPSE_START)
                found_ins = ins_range.MoveToElement("Insertion", forward)

            # If we found matching markup, navigate to it.
            args = found_ins, found_del
            self.logger.debug("found_ins=%s found_del=%s", *args)
            if found_ins or found_del:
                keep_going = False
                found = "Insertion"
                if not found_ins:
                    found = "Deletion"
                elif found_del:
                    if forward:
                        if ins_range.IsGreaterThan(del_range, False):
                            found = "Deletion"
                    elif del_range.IsGreaterThan(ins_range, False):
                        found = "Deletion"
                self.logger.debug("found %s", found)
                range = ins_range if found == "Insertion" else del_range
                range.SelectContainerContents()
                range.Select()

            # Otherwise, ask if we should wrap around.
            else:
                prompt = "End of document; wrap from top?"
                if not forward:
                    prompt = "Beginning of document; wrap from bottom?"
                keep_going = messagebox.askyesno("Find Markup", prompt)
                if keep_going:
                    if forward:
                        self.logger.debug("starting over at the top")
                        del_range.MoveToDocumentStart()
                        ins_range.MoveToDocumentStart()
                    else:
                        self.logger.debug("starting over at the bottom")
                        del_range.MoveToDocumentEnd()
                        ins_range.MoveToDocumentEnd()
                else:
                    self.logger.debug("user says we're done")

    def _find_or_create_child(self, selection, name):
        """Find or create a node in the selection.

        Required positional arguments:
            selection - Range object from XMetaL's API
            name - string for the desired element's tag

        Return:
            Range object for the found or created element
        """

        # See if the element we want is already there.
        selection.SelectContainerContents()
        child = selection.Duplicate
        child.Collapse(self.XM_COLLAPSE_START)
        if child.MoveToElement(name, True):
            if selection.Contains(child, False):
                return child

        # Didn't find the desired element, so we create one.
        selection.Collapse(self.XM_COLLAPSE_START)
        if selection.FindInsertLocation(name, True):
            selection.InsertElement(name)
            return selection.Duplicate

        # That didn't work either.
        return None

    def _get_blob_extension(self, root):
        """Find the file extension for the active document's blob.

        Required positional argument:
            root - top of the parsed XML tree for the document

        Return:
            string for the filename extension, including the period prefix
        """

        if root.tag == "Media":
            for medium in ("Image", "Video", "Sound"):
                for node in root.iter(f"{medium}Encoding"):
                    encoding = self.get_text(node)
                    self.logger.debug("%s encoding=%r", medium, encoding)
                    if encoding:
                        return f".{encoding.lower()}"
            return None
        elif root.tag != "SupplementaryInfo":
            return None
        for node in root.iter("MimeType"):
            mime_type = self.get_text(node)
            extension = self.MIME_TYPES.get(mime_type)
            args = mime_type, extension
            self.logger.debug("mimetype=%r extension=%e", *args)
            if extension:
                return f"{extension}"
        return None

    def _get_fragment_id(self):
        """Extract the CDR fragment ID for the enclosing block."""

        node = self.app.Selection.ContainerNode
        depth = 5
        while node:
            if depth < 1:
                return None
            depth -= 1
            if self._is_element(node):
                fragment_id = node.getAttribute("cdr:id")
                if fragment_id:
                    return fragment_id
            node = node.parentNode
        return None

    def _get_glossary_names_for_concept(self):
        """Find the GlossaryTermName documents for this concept document."""

        command_set = CommandSet(self, "CdrReport")
        command = command_set.command
        etree.SubElement(command, "ReportName").text = "Glossary Term Names"
        params = etree.SubElement(command, "ReportParams")
        param = etree.SubElement(params, "ReportParam")
        param.set("Name", "ConceptId")
        param.set("Value", self.cdr_id)
        response = command_set.send()
        names = {}
        for node in response.iter("GlossaryTermName"):
            names[node.get("ref")] = self.get_text(node)
        return names

    def _get_glossary_tree(self, **opts):
        """Find or construct the requested glossary tree.

        Uses a cache for performance.

        Optional keywork parameters:
            wrap - if True, wrap the glossary markup in an Insertion element
            dig - if True, recurse into Insertion/Deletion markup
            audience - optionally restrict to terms with this audience
            dictionary - optionally restrict to terms in this dictionary

        Return:
            Glossary object
        """

        language = "es" if self.is_spanish_summary else "en"
        dictionary = opts.get("dictionary")
        audience = opts.get("audience")
        key = f"{language}:{dictionary}:{audience}"
        if key not in self.glossary_trees:
            tree = Glossary(self, language, **opts)
            self.glossary_trees[key] = tree
            self.logger.info("Fetched %s glossary tree", key)
        else:
            tree = self.glossary_trees[key]
            tree.clear_flags()
        self.logger.debug("returning %s glossary tree", key)
        return tree

    def _get_object_link_id(self):
        """Get the document ID of the currently linked object."""

        # Likeliest is a link to a Media document.
        range = self.document.Range
        if self._move_selection_to(range, "MediaLink"):

            # Tricky because the actual link attribute is in a nested element.
            element = self._get_single_element("MediaID", range.ContainerNode)
            if not element:
                return None
            return element.getAttribute("cdr:ref")

        # SupplementaryInfoLink is more straightforward.
        if self._move_selection_to(range, "SupplementaryInfoLink"):
            return range.ContainerNode.getAttribute("cdr:ref")

        # Didn't find what we were looking for.
        return None

    def _get_save_parameters(self, blob_allowed, blocked=False):
        """Ask the user how the document should be saved.

        Required positional arguments:
            blob_allwoed - True if the current document type supports blobs
            blocked - True if the document is already blocked

        Return:
            object holding options specified by the user
        """

        def browse_for_blob(_event=None):
            """Open a second dialog window to pick a blob file to save."""

            title = "Select attachment file to be saved with this document."
            fileopts = dict(
                initialdir=self.blob_directory,
                title=title,
                filetypes=self.FILETYPES,
            )
            selected_file = filedialog.askopenfilename(**fileopts)
            if selected_file:
                path = pathlib.Path(selected_file)
                self.BLOB_BROWSE_DIRECTORY.write_text(str(path.parent))
                filename.delete(0, "end")
                filename.insert("end", path)
                self.logger.debug("filename is %s", path)

        def keep_comment_short(_event=None):
            value = comment.get("1.0", "end")
            if len(value) > 255:
                dialog.bell()
                comment.delete("1.0", "end")
                comment.insert("end", value[:255])

        def publishable_onclick(_event=None):
            """We need a valid version for publication."""

            if publishable.get():
                validate.set(True)
                version.set(True)

        def save_parameters_callback(_event=None):
            """Capture the user's save options."""

            dialog.values.confirmed = True
            dialog.values.validate = validate.get()
            dialog.values.unlock = unlock.get()
            dialog.values.version = version.get()
            dialog.values.publishable = publishable.get()
            dialog.values.comment = (comment.get("1.0", "end") or "").strip()
            dialog.values.path = filename.get() if blob_allowed else None
            dialog.values.block = block.get() if not blocked else False
            dialog.close()


        def validate_onclick(_event=None):
            """Prevent publication without validation."""

            if not validate.get():
                publishable.set(False)

        def version_onclick(_event=None):
            """Can't make a version publishable without creating a version."""

            if not version.get():
                publishable.set(False)

        # Create a dialog form with some option checkboxes.
        callback = save_parameters_callback
        dialog = DialogBox(self, "Save CDR Document")
        top_row = ttk.Frame(dialog.form)
        top_row.grid(row=0, column=0, padx=20, pady=(10, 20), sticky="w")
        checkboxes = ttk.LabelFrame(top_row, text="Options")
        checkboxes.grid(row=0, column=0)
        leftboxes = ttk.Frame(checkboxes)
        leftboxes.grid(row=0, column=0, padx=(15, 40), pady=(3, 10))
        box_opts = dict(frame=leftboxes, sticky="W")
        box_opts["command"] = validate_onclick
        validate = dialog.add_checkbox("Validate", 0, 0, **box_opts)
        box_opts["command"] = version_onclick
        version = dialog.add_checkbox("Create version", 1, 0, **box_opts)
        rightboxes = ttk.Frame(checkboxes)
        rightboxes.grid(row=0, column=1, padx=(0, 35), pady=(3, 10))
        box_opts = dict(frame=rightboxes, sticky="W")
        box_opts["command"] = publishable_onclick
        unlock = dialog.add_checkbox("Check in", 0, 0, **box_opts)
        label = "Make version publishable"
        publishable = dialog.add_checkbox(label, 1, 0, **box_opts)

        # Add some action buttons on the right.
        buttons = ttk.Frame(top_row)
        buttons.grid(row=0, column=1, padx=(33, 0))
        dialog.add_button("OK", callback, 0, 0, frame=buttons)
        dialog.add_button("Cancel", dialog.close, 1, 0, frame=buttons, pady=5)

        # Conditionally add a field for selecting the document's blob file.
        row = 1
        if blob_allowed:
            file_row = ttk.Frame(dialog.form)
            file_row.grid(row=row, column=0, padx=20, pady=(0, 20), sticky="w")
            label = ttk.Label(file_row, text="File Name", anchor="w", width=10)
            label.grid(row=0, column=0)
            filename = ttk.Entry(file_row, width=45)
            filename.grid(row=0, column=1, padx=(10, 31))
            dialog.add_button("Browse", browse_for_blob, 0, 2, frame=file_row)
            row += 1

        # Add a row for the comment field.
        comment_row = ttk.Frame(dialog.form)
        comment_row.grid(row=row, column=0, padx=20, pady=(0, 20), sticky="w")
        row += 1
        label = ttk.Label(comment_row, text="Comment")
        label.grid(row=0, column=0, padx=(0, 14))
        opts = dict(frame=comment_row, width=46, height=5)
        comment = dialog.add_textarea(0, 1, **opts)
        comment.bind("<KeyRelease>", keep_comment_short)

        # Conditionally add a row for a checkbox to block the document.
        if not blocked:
            label = "Block publication of any version of this document"
            block = dialog.add_checkbox(label, row, 0, pady=(0, 20))
        dialog.run()
        return dialog.values

    def _get_single_element(self, name, node=None, **attr):
        """Find a singly-occurring element under a specified node.

        Can also be used for multiply-occurring elements by specifying
        a target value for one of the element's attributes.

        Pass:
            name - name of element to be returned
            node - ancestor of desired element
            attr - optional attribute name -> value attribute map

        Return:
            element found, else None
        """

        node = node or self.document_element
        if not node:
            return None
        nodes = node.getElementsByTagName(name)
        attr, value = attr.popitem() if attr else None, None
        for i in range(nodes.length):
            node = nodes.item(i)
            if node.nodeType == self.DOM_NODE_TYPE_ELEMENT:
                # Documentation says getElementsByTagName returns DOMElements,
                # but it actually returns DOMNodes. BAD documentation!
                element = self.cast(node)
                if not attr or element.getAttribute(attr) == value:
                    return element
        return None

    def _get_text_content(self, element):
        """Extract the text content of an XMetaL DOMElement.

        Use CDR.get_text() for DOM object returned by lxml.etree.

        Pass:
            element - node whose text content we return

        Return:
            concatenated text node values
        """

        fragments = []
        child = element.firstChild
        while child:
            arg = child.nodeType
            self.logger.trace("_get_text_content(): nodeType=%d", arg)
            if child.nodeType == self.DOM_NODE_TYPE_TEXT:
                fragments.append(child.nodeValue)
            child = child.nextSibling
        return "".join(fragments)

    def _get_translated_doc_id(self, original_id):
        """Find the CDR ID of an English document's translation.

        Pass:
            original_id - CDR ID of the English document

        Return:
            string for the translated document's CDR ID
        """

        command_set = CommandSet(self, "CdrReport")
        command = command_set.command
        etree.SubElement(command, "ReportName").text = "Translated Document"
        params = etree.SubElement(command, "ReportParams")
        param = etree.SubElement(params, "ReportParam")
        param.set("Name", "EnglishDocId")
        param.set("Value", original_id)
        response = command_set.send(quiet=True)
        if response:
            for node in response.iter("TranslatedDocId"):
                return self.get_text(node)
        return None

    def _get_validation_parameters(self):
        """Let the user decide how to validate the current document.

        Return:
            object whose attributes store the user's validation choices
        """

        def validation_callback(_event=None):
            """Pack up the parameters."""

            validations = []
            for key in ("schema", "links"):
                if boxes[key].get():
                    validations.append(key.capitalize())
            if not validations:
                return self.app.Alert("No validation type selected.")
            dialog.values.validations = " ".join(validations)
            dialog.values.filter_level = self.REVISION_LEVEL_PUBLISHED
            if boxes["proposed"].get():
                dialog.values.filter_level = self.REVISION_LEVEL_PROPOSED
            elif boxes["approved"].get():
                dialog.values.filter_level = self.REVISION_LEVEL_APPROVED
            dialog.close()

        # Create a dialog form to get the validation parameters.
        dialog = DialogBox(self, "CDR Validation Options", validation_callback)
        buttons = ttk.Frame(dialog.form)
        buttons.grid(sticky="E", row=0, column=0)
        opts = dict(frame=buttons, focus=True, pady=4)
        ok = dialog.add_button("OK", validation_callback, 0, 0, **opts)
        dialog.add_button("Cancel", dialog.close, 1, 0, frame=buttons)
        checkbox_wrapper = ttk.Frame(dialog.form)
        opts = dict(sticky="W", row=1, column=0, padx=(30,20), pady=(0, 20))
        checkbox_wrapper.grid(**opts)
        box_values = (
            ("schema", "Schema Validation", True),
            ("links", "Link Validation", False),
            ("approved", "Include Approved markup", False),
            ("proposed", "Include approved and proposed markup", False),
        )
        boxes = {}
        for i, (key, name, checked) in enumerate(box_values):
            opts = dict(frame=checkbox_wrapper, checked=checked, sticky="W")
            boxes[key] = dialog.add_checkbox(name, i, 0, **opts)
        dialog.run(ok)
        return dialog.values

    def _is_contained_in(self, *names):
        """Determine whether the selection is inside any of a set of elements.

        Required positional arguments:
            names - sequence of strings for names of elements to check

        Return:
            True if the selection is contained in any of the named elements
        """

        selection = self.app.Selection
        for name in names:
            if selection.IsParentElement(name):
                return True
        return False

    def _is_element(self, node):
        """Determine whether the specified DOM node is an element.

        Required positional argument:
            node - reference to an XMetaL DOM node object

        Return:
            True if the node is an element, else False
        """

        return node and node.nodeType == self.DOM_NODE_TYPE_ELEMENT

    def _jump_before_element(self):
        """Move in front of the current element.

        Separated out so we can invoke it ourselves directly.
        """

        if self.document:
            range = self.document.Range
            if range:
                range.SelectBeforeContainer()
                range.Select()

    def _jump_past_element(self):
        """Move past the current element.

        Separated out so we can invoke it ourselves directly.
        """

        if self.document:
            range = self.document.Range
            if range:
                range.SelectAfterContainer()
                range.Select()

    def _load_menus(self):
        """Add our custom menus."""

        # Start with a clean slate.
        bars = self.app.CommandBars
        bar = bars.item("Menu bar")
        menus = bar.Controls
        i = menus.count
        while i > 0:
            control = menus.item(i)
            menu = self.cast(control, "CommandBarPopup")
            try:
                caption = menu.caption
                self.logger.trace("menu %d has caption %s", i, caption)
            except:
                caption = "<no caption>"
                self.logger.warning("menu %d has no caption", i)
            if not caption or "CDR" in caption or caption == "Repro":
                menu.Delete()
            i -= 1

        # Find the menu in front of which ours go.
        window_menu_position = menus.count
        while window_menu_position > 0:
            control = menus.item(window_menu_position)
            menu = self.cast(control, "CommandBarPopup")
            if "Window" in menu.caption:
                break
            window_menu_position -= 1
        self.logger.debug("window menu position is %d", window_menu_position)

        # Add our own menus.
        for values in reversed(cdrcontrols.menus):
            args = self.XM_CONTROL_TYPE_POPUP, None, window_menu_position
            control = menus.Add(*args)
            menu = self.cast(control, "CommandBarPopup")
            menu.caption = values["caption"]
            for item in values["items"]:
                self._add_menu_item(menu, item)
        self.logger.debug("XMetaL now has %d menus", menus.count)

    def _load_toolbars(self):
        """Ensure that the toolbars are as they should be."""

        # Start with a clean slate.
        bars = self.app.CommandBars
        i = bars.Count
        deleted = 0
        while i > 0:
            bar = bars.item(i)
            self.logger.trace("found bar %r", bar.name)
            if bar.name.startswith("CDR") or bar.name == "Repro":
                self.logger.trace("deleting bar %r", bar.name)
                bar.Delete()
                deleted += 1
            elif bar.name == "Whiteboard":
                bar.visible = False
            i -= 1

        # Add our own toolbars.
        for values in cdrcontrols.toolbars:
            name = values["name"]
            bar = bars.Add(name, self.XM_COMMAND_BAR_POSITION_TOP)
            if "doctype" in values:
                self.toolbars[name] = values["doctype"]
            try:
                bar.visible = False
            except BaseException as e:
                # @todo This only seems to happen when the "Restore last open
                #       documents" option is enabled. Why?
                message = f"Problem making toolbar {name} invisible: {e}"
                self.app.Alert(message)
            for button in values["buttons"]:
                self._add_toolbar_button(bar, button)
            if values["name"] == "CDR":
                bar.visible = True

    def _move_selection_to(self, range, name):
        """Make the range's container node be for the specified name.

        Required positional arguments:
            range - the selection object
            name - the name of the element to move to if not already there

        Return:
            True if we succeeded, otherwise False
        """

        if range.ElementName(0) == name:
            return True
        if not range.IsParentElement(name):
            return False
        return range.MoveToElement(name, False)

    def _move_to_location_id(self, location_id, node):
        """Restore the user's position after a document save.

        Invoked recursively by CCommands::save() crawling down from the top
        of the document until we find the matching cdr:id representing where
        the user's cursor was prior to the save. We have to do it like this,
        because our DTD doesn't use "ID" as the type of the cdr:id attribute.

        See https://tracker.nci.nih.gov/browse/OCECDR-4933.

        Required positional parameters:
            location_id - cdr:id attribute value for the saved position
            node - candidate node to examine (recursively)

        Return:
            True if we found the target location and moved there, else False
        """

        if node.nodeType == self.DOM_NODE_TYPE_ELEMENT:
            element = self.cast(node)
            if element.getAttribute("cdr:id") == location_id:
                self.app.Selection.SelectNodeContents(node)
                self.app.Selection.MoveLeft(self.XM_MOVE)
                return True
            child = node.firstChild
            while child:
                if self._move_to_location_id(location_id, child):
                    return True
                child = child.nextSibling
        return False


    def _on_document_open_complete(self):
        """Conditionally adjust the initial position of a newly opened doc.

        See https://tracker.nci.nih.gov/browse/OCECDR-2090.

        Separated out so it can be invoked indirectly, to avoid an XMetaL
        bug (#00014812), which causes other applications to flicker.
        """

        # Record the firing of the event.
        self.logger.debug("_On_Document_Open_Complete macro fired")

        # Skip past the added control block unless it has important info.
        if not self.document_blocked and self.doctype_name != "macros":
            self.app.Selection.GotoNext(self.XM_ELEMENT)
            self.app.Selection.GotoNext(self.XM_ELEMENT)
            self.app.Selection.SelectContainerContents()

    def _open_doc(self, response, doc_id, **opts):
        """Extract the doc from the response and open it in XMetaL.

        Required positional arguments:
            response - parsed response from the CDR server
            doc_id - identification of the CDR document to be opened

        Optional keyword arguments:
            version - identification of a specific document version to open
            checkout - True if the document has been locked for editing
        """

        # Make sure we have a response.
        if not response:
            self.logger.warning("_open_doc(%s, %s): no response", doc_id, opts)
            return

        # Pull out the optional argument values.
        version = opts.get("version")
        checkout = opts.get("checkout") and not version
        version_suffix = f"-V{version}" if version else ""

        # Catch and log any exceptions from the CDRDocument constructor.
        try:
            doc = CDRDocument(response, checkout=checkout)
        except:
            opts = dict(encoding="unicode")
            arg = etree.tostring(response, **opts)
            self.logger.error("retrieve_doc response:\n%s", arg)
            raise

        self.logger.info("Opening document %s (%r)", doc.cdr_id, doc.title)
        filename = f"CDR{doc.doc_id}{version_suffix}.xml"
        directory = "Checkout" if checkout else "ReadOnly"
        path = pathlib.Path(self.path, "Cdr", directory, filename)
        if not path.parent.exists():
            path.parent.mkdir(parents=True)
        path.write_bytes(doc.xml)
        title = doc.title[:15]
        if len(title) < len(doc.title):
            title += "\u2026"
        ro = " [RO]" if not checkout else ""
        title = f"CDR{doc.doc_id}{version_suffix}{ro} - {title}"
        doc = self.app.Documents.Open(str(path), self.DEFAULT_VIEW_MODE)
        if doc:
            doc.Title = title

    def _paste_and_navigate(self, range, xml, navigate_to):
        """Paste XML into the current position and go to a specified element.

        Required positional arguments:
            range - target location for the new XML
            xml - markup to be inserted
            navigate_to - string tag identifying our move target
        """

        range.PasteString(xml)
        range.moveToElement(navigate_to, False)
        range.SelectElement()
        range.Collapse(self.XM_COLLAPSE_START)
        range.MoveRight()
        range.Select()

    def _pick_link_target(self, doctype, element, text):
        """Put up a listbox with link target candidates.

        Required positional argument:
            doctype - string name for the active document's type
            element - string identifying the current element
            text - content of the current element
        """

        def link_lookup_callback(_event=None):
            """Populate the list with matching link candidates."""

            fragment = (title.get() or "").strip()
            if not fragment:
                messagebox.showwarning(message="Title field is empty.")
            else:
                links = self._fetch_candidate_link_targets(doctype, element, fragment)
                dialog.values.links = links
                self.logger.debug("links=%r", links)
                if links:
                    box.delete(0, "end")
                    box.insert("end", *links)
                else:
                    message = "No documents match this title fragment."
                    messagebox.showwarning(message=message)

        def link_select_callback(_event=None):
            """Remember the link selected by the user."""

            selected = box.curselection()
            if selected and dialog.values.links:
                link = dialog.values.links[selected[0]].strip()
                self.logger.debug("selected link: %r", link)
                target = self.normalize_space(link)
                if doctype == "Person" and element == "OrganizationLocation":
                    self._pick_organization_location(dialog, target)
                else:
                    dialog.values.target = target
                    dialog.close()

        def link_view_callback(_event=None):
            """Open a browser to show the selected link's target document."""

            selected = box.curselection()
            if selected and dialog.values.links:
                link = dialog.values.links[selected[0]].strip()
                match = re.search(r"^\[([^]]+)\]", link) or None
                parms = f"Session={self.session}&DocId={match.group(1)}"
                url = f"{self.cgi_bin}/QcReport.py?{parms}"
                self.logger.debug("launched %s", url)
                self.browser.open_new_tab(url)
            else:
                self.app.Alert("No link selected.")
            print(f"link view callback")

        dialog = DialogBox(self, "Edit Linked CDR Element", link_lookup_callback)
        left = ttk.Frame(dialog.form)
        left.grid(row=0, column=0, padx=(12,0), pady=(0, 10))
        title_wrapper = ttk.Frame(left)
        title_wrapper.grid(row=0, column=0, pady=(10, 20), sticky="W")
        title_opts = dict(
            padx=(0, 0),
            frame=title_wrapper,
            width=94,
            focus=True,
            value=text,
            select=True,
        )
        title = dialog.add_text_field("Title", 0, 0, **title_opts)
        box_opts = dict(
            scrollbars="both",
            frame=left,
            width=100,
            height=12,
            command=link_select_callback,
        )
        box = dialog.add_listbox([], 1, 0, **box_opts)
        buttons = ttk.Frame(dialog.form)
        buttons.grid(row=0, column=1, padx=(30, 15), pady=4, sticky="N")
        button_opts = dict(pady=3, frame=buttons)
        dialog.add_button("Lookup", link_lookup_callback, 0, 0, **button_opts)
        dialog.add_button("Select", link_select_callback, 1, 0, **button_opts)
        dialog.add_button("View", link_view_callback, 2, 0, **button_opts)
        button_opts["pady"] = 40
        dialog.add_button("Cancel", dialog.close, 3, 0, **button_opts)
        dialog.run(title)
        target = dialog.values.target
        self.logger.debug("_pick_link_target() returning %r", target)
        return target

    def _pick_organization_location(self, root, link):
        """Add a fragment ID identifying which address to link to.

        Required positional arguments:
            root - dialog window used to select an organization
            link - string in the form "[doc ID] org doc title"
        """

        def organization_location_callback(_event=None):
            """Set the target link string with the address fragment ID."""

            root.values.target = None
            selected = box.curselection()
            if selected and locations:
                link = locations[selected[0]].strip()
                self.logger.debug("selected link: %r", link)
                link = self.normalize_space(link)
                match = re.search(r"^\[([^]]+)\]", link)
                id_with_fragment = match.group(1)
                root.values.target = f"[{id_with_fragment}] {display}"
                root.close()

        # Put up a second dialog window asking the user to choose an address.
        callback = organization_location_callback
        match = re.search(r"^\[([^]]+)\] (.*)", link)
        doc_id = match.group(1)
        display = match.group(2)
        locations = self._fetch_link_location_targets(doc_id)
        if locations:
            top = tkinter.Toplevel(root)
            top.title("Location Picklist")
            box_opts = dict(
                frame=top,
                scrollbars="both",
                width=100,
                height=5,
                command=callback,
                padx=15,
                pady=15,
            )
            box = root.add_listbox(locations, 0, 0, **box_opts)
            buttons = ttk.Frame(top)
            buttons.grid(row=0, column=1, padx=(10,30), pady=12, stick="N")
            button_opts = dict(pady=3, frame=buttons)
            root.add_button("OK", callback, 0, 0, **button_opts)
            root.add_button("Cancel", top.destroy, 1, 0, **button_opts)
            top.geometry(f"+{root.winfo_x()+100}+{root.winfo_y()+100}")
        else:
            self.app.Alert("No locations found.")

    def _pick_valid_value(self, name, values, value=None):
        """Select a valid value from a controlled list.

        Pass:
            name - element name string
            values - sequence of value strings
            value - optional string for selected value

        Return:
            selected valid value string or None
        """

        def pick_valid_values_callback(_event=None):
            selected = box.curselection()
            if selected:
                dialog.values.value = values[selected[0]]
            dialog.close()

        callback = pick_valid_values_callback
        dialog = DialogBox(self, f"Valid Values for Element {name}", callback)
        opts = dict(focus=True, command=callback, scrollbars="right")
        self.logger.debug("values=%s", values)
        box = dialog.add_listbox(values, 0, 0, value=value, **opts)
        buttons = ttk.Frame(dialog.form)
        buttons.grid(row=0, column=1, padx=(20, 15), sticky="N")
        dialog.add_button("OK", callback, 0, 0, pady=3, frame=buttons)
        dialog.add_button("Cancel", dialog.close, 1, 0, pady=3, frame=buttons)
        dialog.run(box)
        return dialog.values.value

    def _pick_version(self, root, doc_id, versions):
        """Allow the user to select which version of a document to open.

        Required positional arguments:
            root - dialog window used to select the document
            doc_id - unique CDR ID for the selected document
            versions - versions of the document available for selection
        """

        def pick_version_callback(_event=None):
            """Fetch and open the version of the doc selected by the user."""

            selected = box.curselection()
            self.logger.debug("pick_version_callback(): selected=%s", selected)
            if selected:
                selected_version = versions[selected[0]]
                self.logger.debug("selected version: %s", selected_version)
                match = re.search(r"^ \[(\d+)\] ", selected_version)
                opts = dict(version=int(match.group(1)))
                message = "calling _fetch_and_open_doc(%s) with opts %s"
                self.logger.debug(message, doc_id, opts)
                root.close()
                self._fetch_and_open_doc(doc_id, **opts)

        def pick_version_cancel(_event=None):
            """Restore z-order and close this second dialog window."""
            root.make_topmost()
            top.destroy()

        # Put up a second dialog window showing the available versions.
        root.make_not_topmost()
        callback = pick_version_callback
        top = tkinter.Toplevel(root)
        top.title("Versions")
        box_opts = dict(
            frame=top,
            scrollbars="right",
            width=100,
            height=6,
            command=callback,
            padx=25,
            pady=25,
            value=versions[0],
            focus=True,
        )
        box = root.add_listbox(versions, 0, 0, **box_opts)
        buttons = ttk.Frame(top)
        buttons.grid(row=0, column=1, padx=(10,30), pady=22, stick="N")
        button_opts = dict(pady=3, frame=buttons)
        root.add_button("Retrieve", callback, 0, 0, **button_opts)
        root.add_button("Cancel", pick_version_cancel, 1, 0, **button_opts)
        top.geometry(f"+{root.winfo_x()-100}+{root.winfo_y()+100}")
        self.logger.debug("pick version dialog created")

    def _prune_formatting_toolbar(self):
        """Remove List buttons from the Formatting toolbar."""

        bar = self.app.CommandBars.item("Formatting")
        if bar:
            i = bar.Controls.count
            while i > 0:
                item = bar.Controls.item(i)
                if item:
                    args = i, item.DescriptionText
                    self.logger.trace("checking formatter item %d (%r)", *args)
                    if "List" in item.DescriptionText:
                        item.Delete()
                i -= 1

    def _publish_preview(self, **opts):
        """Common code for Publish Preview reports.

        Optional keyword arguments:
            flavor - e.g., "Summary_Patient"
        """

        if not self.cdr_id:
            return self.app.Alert("Document not yet saved in the CDR.")
        session = self.session or "guest"
        version = self.document_version or "cwd"
        parms = [
            f"Session={session}",
            f"DocId={self.cdr_id}",
            f"Version={version}",
        ]
        flavor = opts.get("flavor")
        if flavor:
            parms.append(f"Flavor={flavor}")
        parms = "&".join(parms)
        url = f"{self.cgi_bin}/PublishPreview.py?{parms}"
        self.browser.open_new_tab(url)

    def _remove_doc(self, cdr_id):
        """Remove the editable document from the file system.

        Required positional argument:
            cdr_id - string with the canonical form of the CDR ID
        """

        int_id = self.extract_id(cdr_id)
        path = pathlib.Path(self.path, "Cdr", "Checkout", f"CDR{int_id:d}.xml")
        path.unlink(missing_ok=True)

    def _save_document(self, cdr_id, doctype, options):
        """Create the command to save the document and submit it.

        Required positional parameters:
            cdr_id - string for the document's CDR ID (if not new)
            doctype - string for the document's type
            options - options selected by the user for this save request

        Return:
            parsed XML for the server's response
        """

        # Create the CommandSet object.
        title = self.document_title
        command_set = CommandSet(self, "CdrRepDoc" if cdr_id else "CdrAddDoc")
        command = command_set.command

        # Add the basic options requested by the user.
        unlock = "Y" if options.unlock else "N"
        etree.SubElement(command, "CheckIn").text = unlock
        version = etree.SubElement(command, "Version")
        version.text = "Y" if options.version else "N"
        if options.version:
            version.set("Publishable", "Y" if options.publishable else "N")
        validate = etree.SubElement(command, "Validate")
        validate.text = "Y" if options.validate else "N"
        validate.set("ErrorLocators", "Y")
        etree.SubElement(command, "Echo").text = "Y"
        if options.comment:
            etree.SubElement(command, "Reason").text = options.comment
        cdr_doc = etree.SubElement(command, "CdrDoc")
        cdr_doc.set("Type", doctype)
        if cdr_id:
            cdr_doc.set("Id", cdr_id)
        control = etree.SubElement(cdr_doc, "CdrDocCtl")
        if cdr_id:
            etree.SubElement(control, "DocId").text = cdr_id
        etree.SubElement(control, "DocType").text = doctype
        etree.SubElement(control, "DocTitle").text = title
        if options.block:
            etree.SubElement(control, "DocActiveStatus").text = "I"
        if options.comment:
            etree.SubElement(control, "DocComment").text = options.comment

        # Create the DOM tree for the CDR document.
        root = etree.fromstring(self.document_element.xml)
        node = root.find("CdrDocCtl")
        if node is not None:
            root.remove(node)
        for node in root.xpath("//*[@readonly]"):
            self.logger.debug("removing readonly attribute from %s", node.tag)
            node.attrib.pop("readonly", None)

        # If we have a blob, make some possible tweaks to the tree.
        if options.path:
            path = pathlib.Path(options.path)
            blob_bytes = path.read_bytes()
            if doctype == "Media":
                self._adjust_media_document_values(root, blob_bytes)

        # Now that the document has any needed tweaks, we can add its XML.
        xml = etree.tostring(root, encoding="unicode").replace("\r", "")
        self.logger.trace("Document XML for save:\n%s", xml)
        etree.SubElement(cdr_doc, "CdrDocXml").text = etree.CDATA(xml)

        # Fold in the blob if we have one.
        if options.path:
            encoded = str(base64.b64encode(blob_bytes), "ascii")
            etree.SubElement(cdr_doc, "CdrDocBlob").text = encoded

        # Send the document to the CDR server.
        return command_set.send()

    def _send_client_log(self):
        """Pack up the client log, send it to the server, drop the file."""
        if self.LOGPATH.exists():
            log_data = self.LOGPATH.read_text(encoding="utf-8")
            if log_data:
                suffix = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
                new_path = pathlib.Path(f"{self.LOGPATH}-{suffix}")
                self.LOGPATH.rename(new_path)
                opts = dict(session="guest")
                command_set = CommandSet(self, "CdrSaveClientTraceLog", **opts)
                command = command_set.command
                etree.SubElement(command, "LogData").text = log_data
                etree.SubElement(command, "Session").text = self.session
                etree.SubElement(command, "User").text = self.user
                if command_set.send(quiet=True):
                    new_path.unlink(missing_ok=True)

    def _set_current_element_text(self, value):
        """Set the text content of the current element to the specified value.

        Required positional argument:
            value - string value to be assigned as the current element's text
        """

        self.app.Selection.SelectContainerContents()
        element = self.app.Selection.ContainerNode
        self.app.Selection.Delete()
        while element and not self._is_element(element):
            element = element.parentNode
        if element:
            new_node = self.document.createTextNode(value)
            element.appendChild(new_node)

    def _set_new_attribute_value(self, element_name, attribute_name, value):
        """Set selected attributes in the current selection to a new value.

        Pass:
            element_name - string name identifying the target elements
            attribute_name - string name identifying the attribute to be set
            value - string for the new value to be assigned

        Return:
            integer for the number of attributes which were assigned
        """

        selection = self.document.Range
        original_value = self.app.Selection.ReadOnlyContainer
        self.app.Selection.ReadOnlyContainer = False
        count = 0
        cursor = selection.Duplicate
        cursor.Collapse()
        moved = cursor.MoveToElement(element_name)
        while moved:
            if selection.Contains(cursor):
                count += 1
                node = cursor.ContainerNode
                node.setAttribute(attribute_name, value)
            moved = selection.MoveToElement(element_name)
        self.app.Selection.ReadOnlyContainer = original_value
        return count

    def _set_rev_markup_attrs(self, name, value):
        """Assign value to selected Insertion and Deletion element attributes.

        Pass:
            name - string identifying which attribute is to be set
            value - string for the attributes' new value

        Return:
            integer for the number of attributes which were set
        """

        return (
            self._set_new_attribute_value("Insertion", name, value) +
            self._set_new_attribute_value("Deletion", name, value)
        )

    def _set_title_bar(self):
        """Identify the application as the CDR editor on the selected tier."""
        win32gui.SetWindowText(self.app.WindowHandle,
                               f"CDR Editor ({self.tier})")

    def _set_view_mode(self, mode):
        """Put the currently active document in the specified view mode.

        Required position argument:
            mode - e.g., self.XM_VIEW_NORMAL
        """

        if self.document:
            self.document.ViewType = mode

    def _show_validation_certificate(self, cdr_id):
        """Let the user know that the document passed validation."""

        def callback(_event=None):
            dialog.close()
        dialog = DialogBox(self, f"Validation for {cdr_id}")
        top_row = ttk.Frame(dialog.form)
        top_row.grid()
        path = self.PATH / "certificate.png"
        image = Image.open(path)
        self.logger.debug("opened image %s from %s", image, path)
        photo_image = ImageTk.PhotoImage(image)#, master=dialog)
        image_label = ttk.Label(top_row, image=photo_image)
        image_label.grid(padx=(0, 150))
        message = ttk.Label(dialog.form, text="Document passes validation.")
        message.grid(row=1, pady=(5, 10))
        ok = dialog.add_button("OK", callback, 0, 1, frame=top_row, focus=True)
        ok.bind("<Return>", callback)
        dialog.run(ok)

    def _strip_cdr_id_attributes(self, node):
        """Recursively remove the cdr:id attributes from the document.

        This works with XMetaL DOM nodes.

        Pass:
            node - element from which to strip the attribute and recurse
        """

        name = node.nodeName
        self.logger.trace("_strip_cdr_id_attributes(%s)", name)
        if node.nodeType == self.DOM_NODE_TYPE_ELEMENT:
            element = self.cast(node)
            if element.hasAttribute("cdr:id"):
                self.logger.debug("removing cdr:id attribute from %s", name)
                element.removeAttribute("cdr:id")
            child = element.firstChild
            while child:
                self._strip_cdr_id_attributes(child)
                child = child.nextSibling


    ######################################################################
    #                   NON-INSTANCE UTILITY METHODS                     #
    ######################################################################

    @staticmethod
    def cast(base_class_object, name="DOMElement"):
        """Work around bug in XMetaL API."""
        return win32com.client.CastTo(base_class_object, name)

    @staticmethod
    def extract_id(arg):
        """Return CDR document ID as an integer (ignoring fragment suffixes).
        """

        if isinstance(arg, bytes):
            arg = arg.decode("utf-8")
        if isinstance(arg, str):
            return int(re.sub(r"[^\d]", "", arg.split("#")[0]))
        return int(arg)

    @staticmethod
    def get_text(node, default=None):
        """Assemble the concatenated text nodes for an element of a document.

        Used for nodes in an lxml.etree parsed tree. Use the instance method
        _get_text_content for extracting text from an XMetaL DOM node.

        Note that the call to node.itertext() must include the wildcard
        string argument to specify that we want to avoid recursing into
        nodes which are not elements. Otherwise we will get the content
        of processing instructions, and how ugly would that be?!?

        Pass:
            node - element node from an XML document parsed by the lxml package
            default - what to return if the node is None
        Return:
            default if node is None; otherwise concatenated string node
            descendants
        """

        if node is None:
            return default
        return "".join(node.itertext("*"))

    @staticmethod
    def normalize_space(string):
        """Convert sequences of whitespace to a single space character.

        Trims leading and trailing whitespace.

        Required positional argument:
            string - the value to be converted

        Return:
            the normalized string value
        """

        return re.sub(r"\s+", " ", (string or "").strip())

class CommandSet:
    """Object for communicating with the CDR API."""

    def __init__(self, cdr, name, **opts):
        """Create the common elements used by all commands.

        In this module each command set contains exactly one command.

        Pass:
            cdr - object with access to logging and API communication
            name - string naming the CDR command in the set
            session - optional override of self.session
        """

        self.cdr = cdr
        self.root = etree.Element("CdrCommandSet")
        session = opts.get("session", cdr.session)
        etree.SubElement(self.root, "SessionId").text = session
        wrapper = etree.SubElement(self.root, "CdrCommand")
        self.command = etree.SubElement(wrapper, name)

    def send(self, **opts):
        """Send the serialized command set to the CDR and parse the response.

        Failures are logged and the user is notified about the problem(s).

        Optional keyword argument:
            quiet - suppress popups for errors reported by the server

        Return:
            None if the command failed; otherwise the parsed XML response
        """

        self.cdr.logger.info("Sending CDR command %s", self.command.tag)
        xml = etree.tostring(self.root, encoding="utf-8")
        self.cdr.logger.setLevel(self.cdr.server_logging_level)
        self.cdr.logger.debug("request is %r", xml)
        url = f"https://{self.cdr.api_server}"
        self.cdr.app.SetCursor(CDR.XM_CURSOR_BUSY)
        response = requests.post(url, data=xml)
        xml = response.content
        self.cdr.logger.debug("response is %r", xml)
        self.cdr.logger.setLevel(self.cdr.client_logging_level)
        root = etree.fromstring(xml)
        self.cdr.app.SetCursor(CDR.XM_DEFAULT_CURSOR)
        for node in root.findall("CdrResponse"):
            if node.get("Status") != "success":
                err_nodes = node.findall("Errors/Err")
                if not err_nodes:
                    errors = [f"Unknown error for {self.command.tag}"]
                else:
                    errors = []
                    for err_node in err_nodes:
                        message = CDR.get_text(err_node)
                        errors.append(f"{self.command.tag}: {message}")
                for error in errors:
                    if opts.get("quiet"):
                        self.cdr.logger.debug(error)
                    else:
                        self.cdr.logger.warning(error)
                        self.cdr.app.Alert(error)
                return None
        return root


class CDRDocument:
    """CDR document extracted from the CDR server's response."""

    def __init__(self, response_set, **opts):
        """Prepare the document for saving to the file system.

        The caller will catch and log any exceptions we throw.

        Required positional argument:
            response_set - parsed response from the CDR server

        Optional keyword argument:
            checkout - True if the document is locked for editing
        """

        response = response_set.find("CdrResponse")
        if response is None:
            raise Exception("Unable to find CdrResponse element")
        status = response.get("Status")
        if status != "success":
            raise Exception(f"Response status is {status}")
        self.elapsed = response.get("Elapsed")
        doc = response.find("*/CdrDoc")
        if doc is None:
            raise Exception("Unable to find CdrDoc element")
        self.doctype = doc.get("Type")
        if not self.doctype:
            raise Exception("Missing Type attribute in CdrDoc element")
        self.cdr_id = doc.get("Id")
        self.doc_id = CDR.extract_id(self.cdr_id)
        doc_ctl = doc.find("CdrDocCtl")
        if doc_ctl is None:
            raise Exception("Missing CdrDocCtl element")
        node = doc_ctl.find("ReadyForReview")
        self.ready_for_review = CDR.get_text(node) == "Y"
        self.title = CDR.get_text(doc_ctl.find("DocTitle"))
        self.active_status = CDR.get_text(doc_ctl.find("DocActiveStatus"))
        self.val_status = CDR.get_text(doc_ctl.find("DocValStatus"))
        self.modified = CDR.get_text(doc_ctl.find("DocModified"))
        self.modifier = CDR.get_text(doc_ctl.find("DocModifier"))
        self.comment = CDR.get_text(doc_ctl.find("DocComment"))
        self.blocked = self.active_status == "I"
        doc_xml = doc.find("CdrDocXml")
        if doc_xml is None:
            raise Exception("Response has no CdrDocXml element")
        xml = CDR.get_text(doc_xml).strip()
        if not xml:
            raise Exception("Document XML is empty")
        self.root = etree.fromstring(xml.encode("utf-8"))
        if self.root.tag != self.doctype:
            message = f"Got {self.root.tag} document instead of {self.doctype}"
            raise Exception(message)
        if not opts.get("checkout"):
            self.root.set("readonly", "yes")
        doc_ctl = etree.Element("CdrDocCtl")
        doc_ctl.set("readyForReview", "Y" if self.ready_for_review else "N")
        doc_ctl.set("blocked", "Y" if self.blocked else "N")
        etree.SubElement(doc_ctl, "DocId").text = self.cdr_id
        etree.SubElement(doc_ctl, "DocTitle").text = self.title
        self.root.find("*").addprevious(doc_ctl)
        doctype = f'<!DOCTYPE {self.doctype} SYSTEM "{self.doctype}.dtd">'
        opts = dict(doctype=doctype, encoding="utf-8", xml_declaration=True)
        self.xml = etree.tostring(self.root, **opts)


class DialogBox(tkinter.Tk):
    """Customization for forms needed by the CDR XMetaL macros."""

    set_window_pos = ctypes.windll.user32.SetWindowPos
    set_window_long = ctypes.windll.user32.SetWindowLongPtrW
    get_window_long = ctypes.windll.user32.GetWindowLongPtrW
    get_parent = ctypes.windll.user32.GetParent

    GWL_STYLE = -16
    WS_MINIMIZEBOX = 131072
    WS_MAXIMIZEBOX = 65536
    CONTROLS_MASK = ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX
    SWP_NOZORDER = 4
    SWP_NOMOVE = 2
    SWP_NOSIZE = 1
    SWP_FRAMECHANGED = 32
    SWP_FLAGS = SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED

    class Values:
        """Bucket which defaults to None attributes which haven't been set."""
        def __getattr__(self, name):
            return None

    def __init__(self, cdr, title, default_action=None):
        """Customize the dialog window for the CDR XMetaL client.

        Required positional arguments:
            cdr - object with access to logging and the user's data path
            title - string displayed at the top of the dialog window

        Optional positional argument:
            default_action - invoked when the Return key is pressed
        """

        tkinter.Tk.__init__(self)
        self.attributes("-alpha", 0.0)
        self.cdr = cdr
        self.values = DialogBox.Values()
        self.closed = False
        self.title(title)
        self.focus_force()
        self.resizable(False, False)
        self.iconbitmap("")
        self.iconbitmap(default=f"{cdr.path}\\cdr.ico")
        if default_action:
            self.bind("<Return>", default_action)
        self.bind("<Escape>", self.close)
        self.form = ttk.Frame(self, padding=15)
        self.form.grid()

    def add_button(self, label, command, row, col, **opts):
        """Add an action button to the form.

        Required positional arguments:
            label - string displayed on the button
            command - action to be performed when the button is clicked
            row - vertical position on the grid
            col - horizontal position on the grid

        Optional keyword argument:
            pady - integer or two-integer tuple for vertical padding
            padx - integer or two-integer tuple for horizontal padding
            frame - override for self.form as enclosing wrapper
            focus - if True, the button is given the initial focus

        Return:
            reference to button widget
        """

        self.cdr.logger.trace("added %s button", label)
        def run_command_on_space_bar(event):
            if event.char == " ":
                self.cdr.logger.trace(f"running {command}")
                command()
                self.cdr.logger.trace(f"back from running {command.__name__}")
        frame = opts.get("frame") or self.form
        button = ttk.Button(frame, text=label, command=command)
        grid_opts = dict(row=row, column=col)
        if "pady" in opts:
            grid_opts["pady"] = opts.get("pady")
        if "padx" in opts:
            grid_opts["padx"] = opts.get("padx")
        button.grid(**grid_opts)
        if command:
            button.bind("<Key>", run_command_on_space_bar)
        if opts.get("focus"):
            button.focus()
        return button

    def add_checkbox(self, label, row, col, /, **opts):
        """Add a checkbox to the form.

        Required positional arguments:
            label - string displayed next to the checkbox
            row - vertical position on the grid
            col - horizontal position on the grid

        Optional keyword arguments:
            pady - integer or two-integer tuple for vertical padding
            padx - integer or two-integer tuple for horizontal padding
            frame - override for self.form as enclosing wrapper
            checked - if True box is initially checked
            sticky - which sides of the frame to gravitate towards

        Return:
            tkinter.BooleanVar object
        """

        # Callback to let the space bar toggle the field's value.
        def toggle_on_space_bar(event):
            if event.char == " ":
                field.set(not field.get())

        # Create and return the field.
        value = True if opts.get("checked") else False
        field = tkinter.BooleanVar(value=value)
        frame = opts.get("frame", self.form)
        widget_opts = dict(text=label, variable=field)
        if opts.get("command"):
            widget_opts["command"] = opts["command"]
        widget = ttk.Checkbutton(frame, **widget_opts)
        grid_opts = dict(row=row, column=col)
        if opts.get("padx"):
            grid_opts["padx"] = opts["padx"]
        if opts.get("pady"):
            grid_opts["pady"] = opts["pady"]
        if opts.get("sticky"):
            grid_opts["sticky"] = opts["sticky"]
        widget.grid(**grid_opts)
        widget.bind("<Key>", toggle_on_space_bar)
        #field.set(True if opts.get("checked") else False)
        return field

    def add_listbox(self, values, row, col, **opts):
        """Create a box with one line for each selectable option.

        Required positional arguments:
            values - sequence of string value options
            row - vertical position within the enclosing frame
            col - horizontal position within the enclosing frame

        Optional keyword arguments:
            frame - use this as the wrapper instead of this.form
            focus - set the initial focus to the frame if True
            value - value to be selected and made visibile at the start
            height - number of rows to be displayed
            width - horizontal size of the box in characters (approximate)
            command - callback executed on double-click of a selection
            scrollbars - right, bottom, both, or none
            pady - integer or two-integer tuple for vertical padding
            padx - integer or two-integer tuple for horizontal padding

        Return:
            ttk.Scrollbar
        """

        padx = opts.get("padx", 0)
        pady = opts.get("pady", 0)
        wrapper = ttk.Frame(opts.get("frame", self.form))
        wrapper_opts = dict(row=row, column=col, padx=padx, pady=pady)
        if opts.get("sticky"):
            wrapper_opts["sticky"] = opts["sticky"]
        wrapper.grid(**wrapper_opts)
        height = opts.get("height", 15)
        width = opts.get("width", 60)
        box_opts = dict(height=height, width=width, activestyle="none")
        box = tkinter.Listbox(wrapper, **box_opts)
        box["listvariable"] = tkinter.Variable(value=values)
        box.grid(row=0, column=0)
        if opts.get("command"):
            box.bind("<Double-1>", opts["command"])
        if opts.get("focus"):
            box.focus()
        scrollbars = opts.get("scrollbars", "right")
        if scrollbars in ("right", "both"):
            scrollbar_opts = dict(orient=tkinter.VERTICAL, command=box.yview)
            scrollbar = ttk.Scrollbar(wrapper, **scrollbar_opts)
            scrollbar.grid(row=0, column=1, sticky="NSW")
            box['yscrollcommand'] = scrollbar.set
        if scrollbars in ("bottom", "both"):
            scrollbar_opts = dict(orient=tkinter.HORIZONTAL, command=box.xview)
            scrollbar = ttk.Scrollbar(wrapper, **scrollbar_opts)
            scrollbar.grid(row=1, column=0, sticky="EWS")
            box['xscrollcommand'] = scrollbar.set
        value = opts.get("value")
        if value in values:
            index = values.index(value)
            box.activate(index)
            box.selection_set(index)
            box.see(index)
        box.config(exportselection=False)
        return box

    def add_radios(self, label, values, row, col, **opts):
        """Add a box with radio buttons to the form.

        Required positional arguments:
            label - string displayed at the top of the box
            values - sequence of value strings or label, value tuples
            row - integer for the vertical position on the grid
            col - integer for the horizontal position on the grid

        Optional keyword arguments:
            frame - override for self.form as enclosing wrapper
            default - string value for button which should start as selected
            width - sets the width of the buttons and their labels
            pady - integer or two-integer tuple for vertical padding
            padx - integer or two-integer tuple for horizontal padding
            sticky - adhere to which side(s) of the enclosing frame?

        Return:
            tkinter.StringVar object
        """

        padx = opts.get("padx", (40, 10))
        pady = opts.get("pady", (15, 25))
        box = ttk.LabelFrame(opts.get("frame") or self.form, text=label)
        box_opts = dict(row=row, column=col, padx=padx, pady=pady)
        if opts.get("sticky"):
            box_opts["sticky"] = opts["sticky"]
        box.grid(**box_opts)
        field = tkinter.StringVar()
        if opts.get("default"):
            field.set(opts["default"])
        row = 0
        width = opts.get("width", 30)
        b_opts = dict(width=width, variable=field)
        for i, value in enumerate(values, 1):
            pady = (1, 5) if i == len(values) else 1
            if isinstance(value, (tuple, list)):
                label, value = value
            else:
                label = value
            button = ttk.Radiobutton(box, text=label, value=value, **b_opts)
            button.grid(row=row, column=0, padx=(10, 0), pady=pady)
            row += 1
        return field

    def add_textarea(self, row, col, **opts):
        """Add a multi-column text editing widget to the form.

        Required positional arguments:
            row - vertical position on the grid
            col - horizontal position on the grid

        Optional keyword arguments:
            frame - override for self.form as enclosing wrapper
            width - width in characters (not pixels!) for the widget
            height - height in characters for the widget
            padx - horizontal padding around the text content of the widget
            pady - vertical padding around the text content of the widget
            wrap - set to "none" to turn off word wrapping
            undo - whether undo should be supported (defaults to True)
            value - the starting text value for the widget

        Return:
            ScrolledText object
        """

        frame = opts.get("frame", self.form)
        field_opts = dict(
            width=opts.get("width", 80),
            height=opts.get("height", 10),
            padx=opts.get("padx", 5),
            pady=opts.get("pady", 5),
            wrap=opts.get("wrap", "word"),
            undo=opts.get("undo", True)
        )
        field = ScrolledText(frame, **field_opts)
        field.grid(row=row, column=col)
        if opts.get("value"):
            field.insert("end", opts.get("value"))
        return field

    def add_text_field(self, label, row, col, **opts):
        """Add a text field to the form.

        Notes:
            - the widget goes in the column to the right of the label
            - the padding is applied to the entire field (label and widget)

        Required positional arguments:
            label - string identifying the field
            row - integer for the vertical position on the grid
            col - integer for the horizontal position on the grid

        Optional keyword arguments:
            frame - override the default parent of self.form
            padx - overrides padding left of the label, right of the widget
            pady - vertical padding
            value - string for the initial value for the field
            width - custom width for the text field
            focus - True if the field should be given the intial focus
            sticky - which edge(s) of the enclosing frame to inhabit

        Return:
            tkinter.Entry object
        """

        padx = opts.get("padx", (15, 20))
        if isinstance(padx, int):
            padx = padx, padx
        pady = opts.get("pady", 0)
        parent = opts.get("frame", self.form)
        label = ttk.Label(parent, text=label, anchor="e")
        label.grid(row=row, column=col, padx=(padx[0], 5), pady=pady)
        field_opts = {}
        if "width" in opts:
            field_opts["width"] = opts["width"]
        field = ttk.Entry(parent, **field_opts)
        grid_opts = dict(row=row, column=col+1, padx=(0, padx[1]))
        if opts.get("sticky"):
            grid_opts["sticky"] = opts["sticky"]
        field.grid(**grid_opts)
        if opts.get("focus"):
            field.focus()
        field.insert("end", opts.get("value", ""))
        if opts.get("select"):
            field.select_range(0, tkinter.END)
        return field

    def close(self, _event=None):
        """Make sure the Tk interpreter has stopped and the wiindow is gone.

        Note: the _event parameter is ignored.
        """

        self.cdr.logger.debug("Top of DialogBox.close()")
        self.quit()
        try:
            self.destroy()
            self.cdr.logger.debug("Back from DialogBox.destroy()")
        except:
            pass
        self.cdr.logger.debug("Bottom of DialogBox.close()")
        self.closed = True

    def make_not_topmost(self):
        """Allow another popup to display in front of this one."""
        self.attributes("-topmost", False)

    def make_topmost(self):
        """Ensure visibility of this dialog box."""
        self.attributes("-topmost", True)

    def run(self, focus_field=None):
        """Start the dialog's main processing loop.

        Optional argument:
            focus_field - field which should get the initial focus
        """

        try:
            self._center_and_style()
            self.make_topmost()
            if focus_field:
                focus_field.focus()
            self.mainloop()
        except:
            if not self.closed:
                self.close()
            raise

    def _center_and_style(self):
        """Set the position and styling for the dialog window."""

        self.update_idletasks()
        width = self.winfo_width()
        frame_width = self.winfo_rootx() - self.winfo_x()
        window_width = width + 2 * frame_width
        height = self.winfo_height()
        titlebar_height = self.winfo_rooty() - self.winfo_y()
        window_height = height + titlebar_height + frame_width
        hwnd = int(self.form.master.frame(), 16)
        old_style = DialogBox.get_window_long(hwnd, DialogBox.GWL_STYLE)
        new_style = old_style & self.CONTROLS_MASK
        DialogBox.set_window_long(hwnd, DialogBox.GWL_STYLE, new_style)
        left, top, right, bottom = self.cdr.window_rect
        x = int(left + (right - left) // 2 - window_width // 2)
        y = int(top + (bottom - top) // 2 - window_height // 2)
        self.cdr.logger.debug(f"DialogBox position: x={x} y={y}")
        DialogBox.set_window_pos(hwnd, 0, x, y, 0, 0, self.SWP_FLAGS)
        self.deiconify()
        self.attributes("-alpha", 1.0)


class ValidationErrors:
    """Remembers errors so they can be displayed later."""

    class Error:
        """Stores information about a single error."""

        def __init__(self, node):
            """Extract the information from the Error element.

            Required positional parameter:
                node - Error node containing information from thne server
            """

            self.message = CDR.get_text(node)
            self.eid = node.get("eref")
            self.elevel = node.get("elevel")

    def __init__(self, response):
        """Find all the problems reported for a document.

        Required positional parameter:
            response - parsed XML response from the CDR server
        """

        self.errors = []
        self.current_error = 0
        for node in response.xpath("//Errors/Err"):
            if node.get("etype") in ("validation", "link"):
                self.errors.append(self.Error(node))

    def __bool__(self):
        return True if self.errors else False

    def next(self):
        """Return the current error (if any) and move past it."""

        if self.current_error >= len(self.errors):
            return None
        error = self.errors[self.current_error]
        self.current_error += 1
        return error


class Glossifier:
    """Job to glossify the current document."""

    TAG_NAME = "GlossaryTermRef"
    ENDING_PUNCTUATION = ".;:,"

    def __init__(self, **opts):
        """Establish default property values.

        Optional keyword argument:
            dig - find SummarySection blocks wrapped in revision markup
        """
        self.current_chain = 0
        self.current_node = None
        self.range = None
        self.chains = []
        self.dig = opts.get("dig", False)

    def find_next_match(self, cdr, tree):
        """Look through the chains for the next glossification candidate.

        Required positional arguments:
            cdr - access to logging and the current document type
            tree - information about the glossary used for this job

        Return:
            tuple of strings, one for the glossary term, one for the phrase;
            or None if there are no more glossification candidate phrases
        """

        # We're done if there are no more word chains to look at.
        if self.current_chain >= len(self.chains):
            return None

        # Pick up where we left off in the current word chain from the doc.
        chain = self.chains[self.current_chain]

        # Remember the path in the glossary tree for the current phrase.
        phrase = []

        # Keep looking until we run out of word chains.
        while chain:

            # Start at the top of the tree.
            current_node_map = tree.nodes

            # If we're finished with the current chain, move to the next one.
            words_left = len(chain.words) - chain.current
            args = words_left, self.current_chain
            cdr.logger.trace("%d words left in chain %d", *args)
            while words_left < 1:
                self.current_chain += 1
                if self.current_chain >= len(self.chains):
                    return None
                chain = self.chains[self.current_chain]
                words_left = len(chain.words)
                if cdr.doctype_name == "Summary":
                    tree.clear_flags()

            # Build longest matching phrase we can from the current position.
            while len(phrase) < words_left:
                word = chain.words[chain.current + len(phrase)]
                if word.value not in current_node_map:
                    break
                node = current_node_map[word.value]
                cdr.logger.trace("adding %r to phrase", word.value)
                phrase.append(node)
                current_node_map = node.node_map

            # Look for a match with a complete glossary phrase.
            while phrase:

                # The last word has a doc ID if this is a complete phrase.
                # Skip over it if we've already marked it up for this chain.
                node = phrase[-1]
                if node.doc_id and not node.marked_up:

                    # Position the range object to include the phrase.
                    first_word = chain.words[chain.current]
                    last_word = chain.words[chain.current + len(phrase) - 1]
                    self.range = first_word.range.Duplicate
                    glossifiable = True
                    if not self.range.ExtendTo(last_word.range):
                        glossifiable = False

                    # Make sure the phrase can be marked up.
                    if glossifiable:
                        if not self.range.CanSurround(self.TAG_NAME):
                            glossifiable = False

                    # Populate the controls of the dialog box.
                    if glossifiable:
                        punct = self.ENDING_PUNCTUATION
                        phrase_text = self.range.Text

                        # Back up in front of trailing punctuation.
                        if phrase_text and phrase_text[-1] in punct:
                            end_point = last_word.range.Duplicate
                            end_point.Collapse(CDR.XM_COLLAPSE_END)
                            while phrase_text and phrase_text[--1] in punct:
                                phrase_text = phrase_text[:-1]
                                end_point.MoveLeft(CDR.XM_MOVE) # broken/XM bug
                            self.range = first_word.range.Duplicate
                            if not self.range.ExtendTo(end_point):
                                glossifiable = False
                            elif not self.range.CanSurround(self.TAG_NAME):
                                glossifiable = False

                        # If we make it here, we've got a markup candidate.
                        if glossifiable:
                            name = tree.names[node.doc_id]
                            term = f"CDR{node.doc_id:010d}; {name}"
                            self.range.Select()

                            # Skip past the current phrase.
                            chain.current += len(phrase)
                            self.current_node = node
                            cdr.logger.debug("found phrase", phrase_text)
                            return term, phrase_text

                # Shrink the phrase by one word.
                phrase.pop()

            # Can't use the current word in a glossary phrase; skip past it.
            chain.current += 1

        # Make the linter happy (but we'll never reach here).
        return None

    def find_chains(self, cdr):
        """Sequence of `WordChain` objects, one for each top SummarySection.

        Required positional argument:
            cdr - access to the current document and to logging

        Return:
            True if any chains were loaded; otherwise False
        """

        # Suppress display jiggling while we navigate the document.
        doc = cdr.document
        doc.FormattingUpdating = False

        # Collect a chain of words for each top-level summary section.
        self.chains = []
        node = cdr.document_element.firstChild
        while node:
            if node.nodeName == "SummarySection":
                cdr.logger.debug("found summary section")
                self.chains.append(self.WordChain(doc, node))
                n = len(self.chains)
                cdr.app.SetStatusText(f"Collected {n} word chains")
                time.sleep(.1)  # Otherwise the status bar isn't updated.
            elif self.dig and node.nodeName in CDR.REVISION_MARKUP:
                self._keep_digging(doc, node)
            node = node.nextSibling

        # Don't forget to turn display updates back on.
        doc.FormattingUpdating = True
        cdr.logger.debug("loaded %d chains", len(self.chains))
        return True if self.chains else False

    def _keep_digging(self, doc, node):
        """Recursively find SummarySection nodes buried in revision markup.

        See https://tracker.nci.nih.gov/browse/OCECDR-3815.

        Required positional argument:
            doc - the editor's active document
            node - an Insertion or Deletion element node
        """

        child = node.firstChild
        while child:
            name = child.nodeName
            if name == "SummarySection":
                self.chains.append(Glossifier.WordChain(doc, child))
            elif name in CDR.REVISION_MARKUP:
                self._keep_digging(doc, child)
            child = child.nextSibling


    class Word:
        """Normalized word extracted from the currently active document."""

        PUNCTUATION = re.compile("""['".,?!:;()\[\]{}<>\u201C\u201D]""")

        def __init__(self, range):
            """Remember the Selection object and normalize the text.

            Required positional argument:
                range - position of this word in the document
            """

            self.range = range
            self.value = self.normalize(range.Text)

        @classmethod
        def normalize(cls, word):
            return cls.PUNCTUATION.sub("", word).upper()


    class WordChain:
        """Sequence of `Glossifier.Word` objects from document section."""

        def __init__(self, doc, node):
            """Collect the sequence of normalized words from this node.

            Required positional arguments:
                doc - currently active doc, from which we create Range objects
                node - node from which to extract word tokens
            """

            # Create range objects for searching through the node's content.
            range = doc.Range
            end = doc.Range
            range.SelectBeforeNode(node)
            end.SelectAfterNode(node)

            # Use a `Find` object to identify our word tokens.
            self.words = []
            self.current = 0
            find = range.Find
            args = (
                "[^-\n\r\t ]+", # Custom pattern for a word token
                "",             # Unused replacement string
                "",             # Unused string for restricting elements
                True,           # Match case when searching
                False,          # Don't use XMetaL's word tokenizer
                True,           # Use regular expression pattern matching
                True,           # Search forward, not backward
                False,          # Don't wrap at the end of the document
                CDR.XM_FIND,    # Just find, don't replace
                False,          # Don't bring up a dialog box
            )
            while find.Execute(*args):
                if not range.IsLessThan(end, False):
                    break
                word = Glossifier.Word(range.Duplicate)
                if word.value:
                    self.words.append(word)


class Glossary:
    """Maps of information for a particular glossary.

    There are two properties in the object:
      names - map of CDR GlossaryTermName document IDs to name strings
      nodes - map of linked lists for all of the phrases in the glossary

    The key for each member of the `nodes` property is the normalized
    string for the first word appearing in any of the phrases in the
    glossary. The value for each member of this dictionary is a `Node`
    object, described in detail below.
    """

    def __init__(self, cdr, language, **opts):
        """Fetch the glossary information from the CDR server.

        Required positional arguments:
            cdr - access to the CDR server's API
            language - one of "en" or "es"

        Optional keyword arguments:
            audience - optionally restrict to terms with this audience
            dictionary - optionally restrict to terms in this dictionary
        """

        # Prepare and send the request to the CDR Server.
        cdr.logger.debug("fetching %s glossary tree; opts=%s", language, opts)
        spanish = "Spanish" if language == "es" else ""
        command_set = CommandSet(cdr, f"CdrGet{spanish}GlossaryMap")
        command = command_set.command
        if "dictionary" in opts:
            etree.SubElement(command, "Dictionary").text = opts["dictionary"]
        if "audience" in opts:
            etree.SubElement(command, "Audience").text = opts["audience"]
        response = command_set.send()

        # Extract the glossary information from the server's response.
        self.names = {}
        self.nodes = {}
        count = 0
        for node in response.iter("Term"):
            count += 1
            doc_id = CDR.extract_id(node.get("id"))
            name = CDR.get_text(node.find("Name"))
            self.names[doc_id] = name
            for child in node.findall("Phrase"):
                current_map = self.nodes
                current_node = None
                for word in CDR.get_text(child).split():
                    if word in current_map:
                        current_node = current_map[word]
                    else:
                        current_node = self.Node()
                        current_map[word] = current_node
                    current_map = current_node.node_map
                if current_node:
                    current_node.doc_id = doc_id
        cdr.logger.debug("fetched %d terms", count)

    def clear_flags(self):
        """Recursively clear the `marked_up` flags in the nodes."""

        for node in self.nodes.values():
            node.clear_flags()


    class Node:
        """A word found in one or more phrases in the glossary.

        A `None` represents a single word token found in all of the glossary
        term phrases which share the same N initial words, where this word
        is the Nth word in those phrases. If there are more words to come in
        any given phrase, the next word in the phrase will be found as a key
        in this node's node_map, so the phrases are represented by linked
        chains of `Node` objects. If a given word is the final (possibly only)
        word in a glossary term phrase, its Node object will have the `doc_id`
        member set to the `GlossaryTermName` document's CDR ID. Otherwise that
        member will be set to 0.

        For example, imagine glossary which contained only three terms:
          CDR12345 cancer
          CDR12346 cancer diagnosis
          CDR12346 cancer prevention

        The `nodes` member of the `Glossary` object for that glossary would
        have a single entry, indexed by the string "CANCER" (the name tokens
        tokens are normalized to ignore case). The `Node` value for that entry
        would have the `doc_id` member set to 12345 (because the first term's
        final (and only) normalized word is "CANCER"), and its own `node_map`
        would have two entries, indexed by "DIAGNOSIS" and "PREVENTION"
        respectively, with the `doc_id` of the `Node` values for those entries
        set to 12346 or 12347, representing the second and third terms in the
        glossary. The `node_map` members for those two entries would be empty.

        We also track whether a term has already been used to "glossify" a
        matching string in the section of a document being edited, so the user
        can have the software skip over subsequent occurrence of the term
        within that section of the document. When we move to the next section
        of the document, or to an entirely different document, we clear out
        those `marked_up` flags so we can start afresh.
        """

        def __init__(self):
            """Initialize the object's properties."""

            self.doc_id = None
            self.marked_up = False
            self.node_map = {}

        def clear_flags(self):
            """Recursively clear the `marked_up` flags in the nodes."""

            self.marked_up = False
            for node in self.node_map.values():
                node.clear_flags()
