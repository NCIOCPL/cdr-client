#!/usr/bin/env python3

"""Ensure that the CDR client files are up-to-date, then launch XMetaL.
"""

from argparse import ArgumentParser
from base64 import b64decode
from functools import cached_property
from hashlib import md5
from json import dump, load
from logging import getLogger, FileHandler, Formatter, INFO
from os import getenv, putenv
from pathlib import Path
from subprocess import Popen, run
from sys import executable
from zipfile import ZipFile

from lxml import etree
from psutil import process_iter
from requests import get, post
from requests.auth import HTTPDigestAuth
from tkinter import Tk, Label, Entry, StringVar, messagebox
from tkinter import ttk


class Control:
    """Logic driver for the program."""

    FORMAT = "%(asctime)s [%(levelname)s] %(message)s"
    LOGFILE = "cdr-loader.log"
    PATH = Path(__file__).parent.resolve()
    LOGDIR = PATH / "logs"
    LOGPATH = LOGDIR / LOGFILE
    SETTINGS = PATH / "cdr-settings.json"
    BITMAP = PATH / "xm17.ico"
    BITMAP = PATH / "cdr.ico"
    TIERS = "PROD", "STAGE", "QA", "DEV"
    DEFAULT_TIER = "DEV" # for now
    LOGGING_LEVELS = ["ERROR", "WARNING", "INFO", "DEBUG", "TRACE"]
    DEFAULT_LOGGING_LEVEL = "INFO"
    LOGGING_LEVEL_LOCATIONS = "client", "server"
    COMMAND_TRIES = 3
    CLIENT_REFRESH = "/cgi-bin/cdr/ClientRefresh.py"
    CLIENT_FILES = "CdrClientFiles.zip"

    def run(self):
        """Main entry point for execution."""

        # Get the user's choices, unless we already have them.
        if not self.opts.only_refresh and not self.session:
             self.window.mainloop()
             if self.cancelled:
                exit(0)

        # Make sure we've got the latest and greatest client files.
        self._clear_caches()
        if not self.opts.skip_refresh and not self.opts.restarted:
            checksum = self.checksum
            self._refresh_client_files()

            # If this script was replaced, we need to restart it.
            if checksum != self.checksum:
                self._restart()

        # If the user didn't cancel or opt out, launch XMetaL.
        if not self.opts.only_refresh:
            self._launch_xmetal()


    ######################################################################
    #                              PROPERTIES                            #
    ######################################################################

    @property
    def api_server(self):
        """DNS name for the server used for CDR API requests."""
        return self.servers["api"]

    @property
    def checksum(self):
        """Calculate the checksum of this script.

        This is calculated fresh each time.
        """

        checksum = md5(Path(__file__).read_bytes()).hexdigest()
        self.logger.info("checksum for %s is %s", __file__, checksum)
        return checksum

    @property
    def client_logging_level(self):
        """How verbose should client-side logging be?"""

        key = "client_logging_level"
        return self.settings.get(key, self.DEFAULT_LOGGING_LEVEL)

    @cached_property
    def gui(self):
        """True if we're running under the windowing version of Python."""
        return "pythonw" in executable.lower()

    @cached_property
    def logger(self):
        """Record what we do."""

        self.LOGDIR.mkdir(parents=True, exist_ok=True)
        logger = getLogger(__name__)
        handler = FileHandler(self.LOGPATH, encoding="utf-8")
        handler.setFormatter(Formatter(self.FORMAT))
        logger.addHandler(handler)
        logger.setLevel(self.opts.logging_level)
        return logger

    @cached_property
    def opts(self):
        """Command-line options."""

        parser = ArgumentParser()
        group = parser.add_mutually_exclusive_group()
        group.add_argument("--skip-refresh", action="store_true")
        group.add_argument("--only-refresh", action="store_true")
        parser.add_argument("--tier", choices=self.TIERS)
        parser.add_argument("--restarted", action="store_true")
        parser.add_argument("--session")
        levels = "ERROR", "WARNING", "INFO", "DEBUG"
        parser.add_argument("--logging-level", default="INFO", choices=levels)
        opts = parser.parse_args()
        return opts

    @cached_property
    def password(self):
        """Can be overridden with the dialog box field."""

        path = self.PATH / "pwd"
        if path.exists():
            return path.read_text().strip()
        return None

    @property
    def server_logging_level(self):
        """How verbose should server logging be?"""

        key = "server_logging_level"
        return self.settings.get(key, self.DEFAULT_LOGGING_LEVEL)

    @property
    def servers(self):
        """Dictionary with names of web and API servers."""
        return self.settings["servers"][self.tier]

    @cached_property
    def session(self):
        """Login session used for communicating with the CDR."""
        return self.opts.session or getenv("CDR_SESSION")

    @cached_property
    def settings(self):
        """Load the current user settings.

        Most likely they'll be on the disk. But we have fallback measures.
        """

        # If we have a JSON settings file, we're done
        path = self.PATH / "cdr-settings.json"
        if self.SETTINGS.exists():
            try:
                return load(self.SETTINGS.open())
            except:
                self.logger.exception("loading settings file")

        # Create default values.
        settings = dict(
            user="",
            tier=self.DEFAULT_TIER,
            client_logging_level="INFO",
            server_logging_level="INFO",
            servers={},
        )
        for name in self.TIERS:
            suffix = "" if name == "PROD" else f"-{name.lower()}"
            settings["servers"][name] = dict(
                web=f"cdr{suffix}.cancer.gov",
                api=f"cdrapi{suffix}.cancer.gov",
            )

        # If we have a legacy settings file, load its values.
        # Won't need to keep this code forever.
        path = self.PATH / "CdrTiers.xml"
        if path.exists():
            root = etree.parse(path)
            user = self.get_text(root.find("CurrentUser"), "").strip()
            if user:
                settings["user"] = user
            tier = self.get_text(root.find("CurrentGroup"), "").strip()
            if tier:
                settings["tier"] = tier
            for node in root.findall("ServerGroup"):
                name = node.get("Name")
                if name in settings["servers"]:
                    web = self.get_text(node.find("CDRServer"), "").strip()
                    if web:
                        settings["servers"][name]["web"] = web
                    api = self.get_text(node.find("APIServer"), "").strip()
                    if api:
                        settings["servers"][name]["api"] = api

        return settings

    @property
    def tier(self):
        """Name of the CDR tier to which we will connect (e.g., "PROD")."""
        return self.opts.tier or self.settings.get("tier")

    @property
    def url(self):
        """URL for CDR client-server commands."""
        return f"https://{self.web_server}{self.CLIENT_REFRESH}"

    @property
    def user(self):
        """CDR user name string."""
        return self.settings.get("user")

    @property
    def web_server(self):
        """DNS name for the web server used for refreshing client files."""
        return self.servers["web"]

    @cached_property
    def window(self):
        """Dialog window where the user chooses how to use XMetaL."""

        def on_ok(event=None):
            """Capture the values from the form."""

            self.cancelled = False
            value = password.get()
            if value:
                self.password = value
            settings = dict(
                user=user.get(),
                tier=tier.get(),
                servers={},
            )
            for name in self.LOGGING_LEVEL_LOCATIONS:
                key = f"{name}_logging_level"
                settings[key] = logging_levels[key].get()
            for name in self.TIERS:
                settings["servers"][name] = dict(
                    web=servers[name][0].get(),
                    api=servers[name][1].get(),
                )
            with self.SETTINGS.open("w", encoding="utf-8") as fp:
                dump(settings, fp, indent=2)
            self.settings = settings
            window.quit()
            try:
                window.destroy()
            except:
                pass

        # Create the root window.
        window = Tk()
        window.eval("tk::PlaceWindow . center")
        window.bind("<Return>", on_ok)
        window.bind("<Escape>", lambda _: window.quit())
        window.title("CDR Client")
        if self.opts.skip_refresh:
            window.title("CDR Client (skipping refresh of client files)")
        window.iconbitmap(default=self.BITMAP)
        window.resizable(0, 0)

        # Add the left column.
        column = ttk.Frame(window)
        column.grid(row=0, column=0, padx=(10, 0))

        # Put the credentials field group in that column.
        group = FieldGroup(column, "Credentials", 0, 0)
        user = group.add_text_field("User ID", self.user)
        password = group.add_text_field("Password", bottom=15)
        if not self.user:
            user.focus()
        else:
            password.focus()

        # Add the buttons now (to get the tabbing order we want).
        frame = ttk.Frame(column)
        frame.grid(row=2, column=0, padx=10, pady=(5,20))
        button = ttk.Button(frame, text="OK", command=on_ok)
        button.grid(row=0, column=0, padx=5)
        button = ttk.Button(frame, text="Cancel", command=window.quit)
        button.grid(row=0, column=1, padx=5)

        # Now add the options group (between credentials group and buttons).
        group = FieldGroup(column, "Options", 1, 0)
        value = self.tier
        value = value if value in self.TIERS else self.DEFAULT_TIER
        tier = group.add_dropdown("Tier", self.TIERS, value)
        logging_levels = {}
        opts = dict(bottom=5)
        for name in self.LOGGING_LEVEL_LOCATIONS:
            label = f"{name.capitalize()} Logging Level"
            key = f"{name}_logging_level"
            level = getattr(self, key)
            if level not in self.LOGGING_LEVELS:
                level = self.DEFAULT_LOGGING_LEVEL
            field = group.add_dropdown(label, self.LOGGING_LEVELS, level)
            logging_levels[key] = field
            opts = dict(bottom=15)

        # Create the right-side column.
        column = ttk.Frame(window)
        column.grid(row=0, column=1, padx=(0, 10))

        # Add a wrapper frame for the server groups.
        wrapper = ttk.LabelFrame(column, text="Server Names")
        wrapper.grid(row=0, column=0, padx=10, pady=(0, 12))
        servers = {}
        row, col = 0, 0
        for name in self.TIERS:
            label = name
            if name == "PROD":
                label = "Production"
            elif name == "STAGE":
                label = "Stage"
            pady = (15, 30) if row else 15
            frame = FieldGroup(wrapper, label, row, col, pady=pady)
            opts = dict(width=15)
            names = self.settings["servers"][name]
            web = frame.add_text_field("CDR Server", names["web"], **opts)
            opts["bottom"] = 15
            api = frame.add_text_field("API Server", names["api"], **opts)
            servers[name] = web, api
            row += 1
            if row > 1:
                row, col = 0, 1

        # This will be cleared when the OK button is clicked.
        self.cancelled = True
        return window

    @cached_property
    def xmetal(self):
        """Path the the XMetaL executable."""

        names = "ProgramFiles(x86)", "ProgramFiles", "ProgramW6432"
        for name in names:
            value = getenv(name)
            if value:
                path = Path(value, "XMetaL 17.0", "Author", "xmetal.exe")
                if path.exists():
                    return path
        return None


    ######################################################################
    #                      INTERNAL HELPER METHODS                       #
    ######################################################################

    def _check_for_running_instance(self):
        """Ensure that we don't already have a running instance of XMetaL.

        See https://tracker.nci.nih.gov/browse/OCECDR-5006.
        """

        username = getenv("USERNAME").lower()
        message= "Checking to see if %r is already running XMetaL"
        self.logger.info(message, username)
        xmetal_processes = [
            process
            for process in process_iter(["name", "username"])
            if process.name() == "xmetal.exe"
        ]
        for process in xmetal_processes:
            try:
                process_username = process.username()
            except:
                # We don't always have permission to see other user's names.
                continue
            if process_username:
                self.logger.info("%r is running XMetaL", process_username)
                if "\\" in process_username:
                    process_username = process_username.split("\\")[1]
                if process_username.lower() == username:
                    raise Exception("XMetaL is already running")

    def _clear_caches(self):
        """Remove unwanted cached files.

        First, we clear out any cached media so we don't fill up the user's
        disk with unwanted bulk. Second, we avoid stepping into some nasty
        XMetaL bugs. XMetaL does not behave correctly when we install changed
        DTDs for our document types, even though the file timestamps for the
        DTDs are more recent than the dates on XMetaL's compiled RLX files
        for these DTDs. Sometimes XMetaL ignores our changes; at other times
        XMetaL simply crashes. We eliminate these problems by clearing out
        XMetaL's compiled RLX files. We have to do this recursively, because
        sometimes XMetaL changes the location of those files. Confirmed that
        the bug is still present in XMetaL 17 (as of 2023-01-05).
        """

        for path in Path(self.PATH, "Cdr", "Media").glob("*"):
            try:
                path.unlink()
            except:
                self.logger.exception("Failure removing %s", path)
        for path in self.PATH.rglob("*.rlx"):
            try:
                path.unlink()
            except:
                self.logger.exception("Failure removing %s", path)

    def _get_new_files(self, zip_bytes):
        """Unpack and validate the new and/or changed files.

        Mismatches can happen for a variety of reasons:

          (1) Sometimes a new or changed file is added to the set on the
              server, and the account under which the client refresh server
              is running does not have sufficient permission to read the
              file when it tries to add it to the compressed archive.
              This condition should be addressed by enhancements to the
              software which builds the manifest on the server, to ensure
              at manifest build time that the client refresh server can
              read all of the files represented on the manifest. Of
              course, this would not completely eliminate this class of
              problem, as it is possible for systems administrators to
              make changes to permission settings, or for bugs to surface
              in the operating system, changing the way permissions are
              granted or denied. We might address this problem by having
              a periodic job run to confirm that permissions needed by
              the server are intact, with email alerts sent to appropriate
              persons whenever this assumption is violated. It is possible
              that moving the client refresh servers from Windows to an
              operating system with a less Byzantine authentication /
              permission system would dramatically reduce or eliminate
              this class of problem.

          (2) The copy of a file on the client machine can have settings
              which deny the current user permission to overwrite that
              file with a new version. This can happen, for example,
              if an administrator logs onto the machine and runs the
              CDR client, resulting in files for which only the administrator
              has sufficient permissions for removal or replacement.
              Or the systems support staff can change the account with which
              the user logs onto the machine (e.g., different domain).
              There isn't much we can do about this problem, beyond
              educating users (or at least, lead users responsible for
              troubleshooting failures) about the need to check the
              the logs for error messages and ensure that the user has
              adequate permissions for changing all of the files
              represented in the manifest.

          (3) A file can be added to (changed in, deleted from) the set
              of current client files without rebuilding the manifest.
              One solution might be to have a scheduled job run periodically
              to verify that the manifest is in sync with the set of current
              files, with email alerts when problems are detected. A more
              elaborate approach would be to set up a mechanism for
              managing the client file set (adding new files, removing
              or replacing existing files) exclusively through an interface
              designed for this purpose. This would eliminate the window
              for failures allowed by the first approach to dealing with
              this type of problem. For example, a web interface might
              be used with the file upload feature of CGI for submitting
              new or changed files. The web interface would also allow
              for removing files from the client set. An additional
              benefit from this technique would be the ability to capture
              information about who installed the most recent version of
              a file (or deleted a file), and any reasons for the change.
              Another side benefit of the web interface would be easier
              upload of files from the user's workstation, which is currently
              made more difficult by the inability to map drives locally
              to the CDR Servers.

              A command-line version of the interface might also be useful,
              to allow developers or lead users to install or delete files
              from a telnet or ssh connection, where a browser cannot be
              used for installing files from the remote server's filesystem.

              An even more elaborate, but more reliable approach (and one
              providing richer functionality), would be to store the client
              file set in tables of a DBMS.

          (4) Transmission errors. Theoretically possible, but should be
              eliminated by the error-correction facilities provided by
              TCP/IP, over which the connections communicate.

          (5) Bugs in the libraries for calculating checksums. So far we
              haven't yet encountered such bugs.

        In the past, bugs in how the operating system reported file time
        stamps also caused bogus discrepancies. This class of problem has
        been eliminated by switching to the use of checksums for detecting
        file changes.

        The zipfile is saved in the current working directory under the
        name CdrClientFiles.zip. We could just unpack the archive from the
        bytes in memory, but it's better to have the archive in the file
        system for diagnostic troubleshooting in the event of failure.
        """

        # Save the zipfile to the current working directory.
        try:
            with open(self.CLIENT_FILES, "wb") as fp:
                fp.write(zip_bytes)
        except:
            self.logger.exception("writing client zipfile")
            raise Exception(f"Failure writing {self.CLIENT_FILES}")

        # Unpack the archive.
        self.logger.info("Unpacking updated files from the server")
        try:
            with ZipFile(self.CLIENT_FILES) as zf:
                zf.extractall(self.PATH)
        except:
            self.logger.exception("unpacking zipfile")
            raise Exception("Failure unpacking new files from server")

        # Verify that the manifest and files match each other.
        try:
            manifest = Manifest()
            message = "Verifying the new manifest against our local files"
            self.logger.info(message)
            mismatch = manifest.validate(self.logger)
        except:
            raise Exception("Missing or corrupted server manifest")
        if mismatch:
            raise Exception(mismatch)

    def _post_command(self, command):
        """Post an XML command to the CDR web server.

        Required positional argument:
            command - serialized XML for the command

        Return:
            string for the server's response
        """

        headers = {
            "Content-type": "text/xml; charset=utf-8",
            "X-Debug-Level": "1",
        }
        opts = dict(data=command.encode("utf-8"), headers=headers)

        # This fails occasionally; give the server a few chances.
        tries = self.COMMAND_TRIES
        while tries > 0:
            try:
                self.logger.info("Posting to %s", self.url)
                response = post(self.url, **opts)
            except:
                self.logger.exception("posting command")
                tries -= 1
                continue
            code = response.status_code
            if code != 200:
                raise Exception(f"HTTP status code from server: {code}")
            return response
        raise Exception("Failure submitting request to update server")

    def _refresh_client_files(self):
        """Ensure that the user's CDR client files match what's on the server.

        This is where we do the work for which this program was principally
        created: make sure all of the files needed by the CDR client are
        up to date. This is accomplished by communicating via the network
        with a server which has a set of the current version of all of
        these files, as well as a list of all of those files (the "Manifest")
        with pathname and checksum for each file, as well as a header (called
        a "Ticket" below) identifying the server on which the manifest was
        generated, as well as a cumulative checksum for the client files.

        The first time this program connects to the client refresh server,
        it sends a stub version of the manifest to the server, asking it
        to send a complete set of the client files. The server does so and
        the client installs these files locally. A copy of the manifest
        document is included in the set.

        For subsequent invocations of this program, the client first asks
        the client refresh server if any changes have been made to the file
        set since the previous session. It does this by extracting the
        header ("Ticket") from the stored manifest document and sending it
        to the server. If the server name and checksum match those in
        the server's copy of the manifest, the response "<Current>Y</Current>"
        is returned to the client, and no further work needs to be done.

        In the event that we detect tampering with the local client files
        (we check to ensure that all of the files in our local copy of the
        manifest are present, with checksums which match those in the
        manifest exactly), then we discard the manifest and get a complete
        new set, as if this were the first time we had connected to the
        server. A possible side effect is that the client might retain a
        file which has been removed from the complete set of client files,
        and which the server would have asked to be deleted, had it received
        the manifest listing that file. This is extremely unlikely to present
        a problem.

        If the server determines that changes have occurred, it returns the
        response "<Current>N</Current>" and the client sends a copy of its
        complete manifest file to the server. The server compares its own
        copy of the manifest with the copy from the client and builds two
        lists: one for files which the client currently has but are no longer
        in the set of files needed by the client, and a second list of files
        which the client does not yet have, or for which the client's copy
        differs from that on the server. If the second list is not empty,
        the server creates a compressed archive containing the files
        represented by this list. An XML document ("Updates") is sent back
        to the client with a ZipFile child element containing the bytes
        for the archive containing the new and updated client files, and
        an optional "Delete" element with one or more child "File" elements.
        If the ZipFile element is present and non-empty, its contents are
        installed locally on the client machine. If there are any files to
        be removed, they are then deleted.

        For additional information about the structure of the XML responses
        returned by the server, see the interface documentation for the
        Manifest and Updates types.

        In summary, the following sequence of exchanges would take place
        if the client's files are not completely up to date, and the
        refresh process is successful:

             1. Client sends <Ticket>...</Ticket> document.
             2. Server responds with <Current>N</Current>.
             3. Client sends <Manifest>...</Manifest> document.
             4. Server responds with <Updates>...</Updates> document.
        """

        # Start out with stubs for the manifest document and ticket header.
        manifest_xml = "<Manifest/>"
        ticket_xml = ""

        # Parse the local copy of the manifest if it exists.
        try:

            # Make sure no one has manually changed any of the client files.
            manifest = Manifest()
            if not manifest.validate(self.logger):
                manifest_xml = manifest.xml
                ticket_xml = manifest.ticket_xml

        except:

            # Errors are not fatal; log them and use the stub manifest.
            self.logger.exception("Parsing local manifest")

        # If we found a valid manifest, ask the server if it's current.
        if ticket_xml:
            server = self.web_server
            self.logger.info("Asking %s if any files have changed", server)
            response = self._post_command(ticket_xml)
            ticket_validation = TicketValidation(response, self.logger)
            if ticket_validation.current:
                self.logger.info("Local files are up to date")
                return
        else:
            self.logger.info("No local ticket available; refresh forced")

        # There are changes; find out what they are. May take some time.
        message = "Some files have changed; sending manifest for local files"
        self.logger.info(message)
        updates = Updates(self._post_command(manifest_xml), self.logger)

        # If there are new or changed files, retrieve and unpack them.
        if updates.zipfile_bytes:
            self._get_new_files(updates.zipfile_bytes)

        # If we've been asked to delete any files, do so here.
        for path in updates.deletions:
            if "cdr-loader.pyw" in str(path).lower():
                self.logger.info("Not removing %s", path)
                continue
            self.logger.info("Removing %s on instructions from server", path)
            try:
                path.unlink()
            except:
                self.logger.exception("unlinking %s", path)

        # We're done.
        self.logger.info("Refresh of local files complete")

    def _restart(self):
        """Run this script again, because it has changed."""

        self._export_environment()
        args = [executable, __file__, "--restarted"]
        pid = Popen(args).pid
        self.logger.info("launched %s with process ID %d", " ".join(args), pid)
        exit()

    def _login(self):
        """Get a valid CDR session ID from the server."""

        auth = HTTPDigestAuth(self.user, self.password)
        url = f"https://{self.web_server}/cgi-bin/secure/login.py"
        self.logger.info("connecting to %s", url)
        response = get(url, auth=auth)
        if response.status_code != 200:
            reason = response.reason or "unknown error"
            raise Exception(f"Failure logging into CDR {self.tier}: {reason}")
        session = response.text.strip()
        if not session:
            raise Exception("CDR server returned empty session ID")
        return session

    def _export_environment(self):
        """Make the current settings visible to other processes."""

        putenv("CDR_SESSION", self.session or self._login())
        putenv("CDR_HOST", self.web_server)
        putenv("CDR_API_HOST", self.api_server)
        putenv("CDR_USER", self.user)
        putenv("CDR_TIER", self.tier)
        putenv("CDR_PATH", str(self.PATH))
        putenv("CDR_CLIENT_LOGGING_LEVEL", self.client_logging_level)
        putenv("CDR_SERVER_LOGGING_LEVEL", self.server_logging_level)

    def _launch_xmetal(self):
        """We're ready for XMetaL to take over."""

        # Make sure we don't already have an instance running.
        self._check_for_running_instance()

        # Give the other process the values it needs.
        self._export_environment()

        # Replace this process with the new one.
        pid = Popen([str(self.xmetal)]).pid
        self.logger.info("launched XMetaL with process ID %d", pid)
        exit()


    ######################################################################
    #                   NON-INSTANCE UTILITY METHODS                     #
    ######################################################################

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


class FieldGroup(ttk.LabelFrame):
    """Custom labeled frame with convenience methods for adding fields."""

    def __init__(self, frame, label, row, col, **opts):
        """Create the empty field group.

        Required positional arguments:
            frame - enclosing frame for the column in which the group appears
            label - string identifying which group this is
            row - where the group is positioned vertically within the frame
            col - where the group is placed horizontally in the frame

        Optionalal keyword argument:
            pady - override for the vertical padding around the group
        """

        ttk.LabelFrame.__init__(self, frame, text=label)
        self.grid(row=row, column=col, padx=10, pady=opts.get("pady", 10))
        self.next_row = 0

    def add_text_field(self, label, value=None, **opts):
        row = self.next_row
        self.next_row += 1
        show = "*" if label == "Password" else None
        width = opts.get("width", 20)
        pady = (3, opts.get("bottom", 3))
        label = ttk.Label(self, text=label, anchor="e", width=width)
        label.grid(row=row, column=0, pady=pady)
        field = ttk.Entry(self, show=show, width=23)
        field.grid(row=row, column=1, pady=pady, padx=(5, 10))
        if value:
            field.insert(0, value)
        return field

    def add_dropdown(self, label, values, value, **opts):
        row = self.next_row
        self.next_row += 1
        width = opts.get("width", 20)
        pady = (5, opts.get("bottom", 5))
        label = ttk.Label(self, text=label, anchor="e", width=width)
        label.grid(row=row, column=0, pady=pady)
        field = StringVar()
        field.set(value)
        box = ttk.Combobox(self, values=values, textvariable=field)
        box.grid(row=row, column=1, pady=pady, padx=(5, 10))
        return field


class Manifest:
    """
    CDR client files catalog.

    Contains a list of all of the current CDR client files which should
    be installed on the user's machine, as well as a header ("ticket")
    used to determine whether the client machine's copy of the manifest
    is current. The validate() method walks through the list of files
    in the manifest to ensure that the correct version of each file is
    present on the user's disk.

    The structure for the manifest file looks like this:

        Manifest
            Ticket
                Application [string] - name of program which built the manifest
                Host [string] - DNS name of the server with the client files
                Author [string] - name of user who ran the program
                Checksum [string] - MD5 checksum for the entire set of files
            FileList
                File [multiple]
                    Name [string] - relative path for the file
                    Checksum [string] - MD5 checksum for the file
    """

    def __init__(self):
        """Load the manifest information from the disk."""

        path = Control.PATH / "CdrManifest.xml"
        if not path.exists():
            raise Exception("User has no local manifest file")
        try:
            self.xml = path.read_text(encoding="utf-8")
            root = etree.fromstring(self.xml.encode("utf-8"))
        except:
            raise Exception("Manifest file is corrupt")
        if root.tag != "Manifest":
            raise Exception(f"Expected Manifest element; got {root.tag}")
        node = root.find("Ticket")
        if node is None:
            raise Exception("Manifest file contains no Ticket")
        self.ticket_xml = etree.tostring(node, encoding="unicode")
        self.ticket = Ticket(node)
        self.files = []
        for node in root.findall("FileList/File"):
            self.files.append(File(node))

    def validate(self, logger):
        """Compare the manifest with the files on the local disk.

        Make sure they're all present and have matching checksums.

        Required positional argument:
            logger - for recording mismatches

        Return:
            string describing the first discrepancy found, if any; else None
        """

        for file in self.files:
            if not file.manifest_checksum:
                continue
            if file.manifest_checksum != file.client_checksum:
                args = file.name, file.client_checksum
                logger.warning("client checksum for %s: %s", *args)
                args = file.name, file.manifest_checksum
                logger.warning("server checksum for %s: %s", *args)
                messagebox.showwarning("CDR", f"{file.name}: checksum mismatch")
                return f"{file.name} mismatch"
        return None


class Ticket:
    """Representation of the files on the client machine.

    This object represents the header from a manifest document identifying
    the current set of client files we should have. We send this to the
    client refresh server so that it can determined whether any changes
    have taken place since the last time we checked, without sending the
    entire manifest file. Since in most cases, no such changes have
    occurred, this saves significant time and network bandwidth. The
    header records the name of the machine on which the manifest was
    created, a cumulative checksum for the client files, who ran the
    program to create it, and what application was used to create it.
    Only the host name and manifest checksum are used in the determination
    of whether changes have taken place since the client's copy of the
    manifest was created. See documentation above for the `Manifest` class
    for the header's XML structure.
    """

    def __init__(self, node):
        """Parse out the values for the client's ticket.

        Required positional argument:
            node - wrapper containing the text-content elements
        """

        self.application = Control.get_text(node.find("Application"))
        self.host = Control.get_text(node.find("Host"))
        self.author = Control.get_text(node.find("Author"))
        self.checksum = Control.get_text(node.find("Checksum"))


class File:
    """Path name and checksum for one of the files listed in the manifest."""

    def __init__(self, node):
        """Extract the file values.

        Required positional argument:
            node - wrapper containing the text-content elements
        """

        self.name = Control.get_text(node.find("Name"))
        self.manifest_checksum = Control.get_text(node.find("Checksum"))

    @cached_property
    def client_checksum(self):
        """Calculated MD5 checksum for this file.

        We're calculating the value from the bytes on the user's disk,
        rather than returning the value we got for the file from the
        manifest, to which we'll compare this calculated value.
        """

        path = Path(self.name)
        hash = md5(path.read_bytes())
        return hash.hexdigest()


class TicketValidation:
    """Answer to our question about whether our manifest is out of date.

    The XML document for the server's response consists of only a single
    text-content element named Current. We convert that text content
    ("Y" or "N") to the Boolean `current` property.
    """

    def __init__(self, response, logger):
        """Parse the response to get the answer.

        Required positional argument:
            response - what we got back from the CDR server
        """

        try:
            root = etree.fromstring(response.content)
            self.current = Control.get_text(root) == "Y"
        except:
            logger.exception("parsing ticket validation")
            raise Exception("Failure parsing ticket validation")


class Updates:
    """Deltas between the server's manifest file and the client's.

    This object will have a list of files that we said we have but are
    no longer on the server's manifest, and should therefore be deleted,
    as well as the bytes for a zipfile containing all the new or changed
    files (if any) the server needs to send us.

    The server's response has the following structure:

        Updates
            ZipFile [string, optional]
                @encoding [='base64']
            Delete [optional]
                File [string, multiple]
    """

    def __init__(self, response, logger):
        """Extract the zipfile bytes and the list of files to delete.

        Extracts and decodes the bytes for the compressed archive containing
        new and/or modified files.

        Required positional argument:
            response - what we got back from the CDR server
            logger - so we can record failures

        Throws:
            `Exception` if the response is not parseable or the bytes
            cannot be decoded from their base 64 representation
        """

        # Parse the response.
        try:
            root = etree.fromstring(response.content)
        except:
            logger.exception("parsing updates response")
            raise Exception("Failure parsing server updates response")
        if root.tag == "ERROR":
            message = Control.get_text(root)
            messagebox.showerror("CDR", message)
            raise Exception("Failure assembling update package")

        # Extract the zipfile bytes.
        self.zipfile_bytes = None
        node = root.find("ZipFile")
        if node is not None:
            encoding = node.get("encoding")
            if encoding != "base64":
                message = f"Unsupported encoding {encoding!r} for zipfile"
                raise Exception(message)
            encoded = Control.get_text(node)
            self.zipfile_bytes = b64decode(encoded)

        # Find out which files need to be removed.
        self.deletions = []
        for node in root.findall("Delete/File"):
            self.deletions.append(Path(Control.get_text(node)))


if __name__ == "__main__":
    """Don't execute if we're loaded as a module."""

    # Make sure we can create a Control instance.
    try:
        control = Control()
    except Exception as e:
        messagebox.showerror("CDR", f"Failure starting up: {e}")
        exit(1)

    # Handle any uncaught exceptions.
    try:
        control.run()
    except Exception as e:
        control.logger.exception("Run failed")
        messagebox.showerror("CDR", f"Loader failure: {e}")
