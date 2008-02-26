<?xml version="1.0"?>

<!-- 
     $Id: Cdr.mcr,v 1.175 2008-02-26 20:07:02 venglisc Exp $

     $Log: not supported by cvs2svn $
     Revision 1.174  2008/02/21 21:15:40  bkline
     Worked on macro to deal with private use Unicode characters.

     Revision 1.173  2008/01/29 15:13:38  bkline
     New macros for opening HP/Patient summaries.

     Revision 1.172  2008/01/23 22:46:22  venglisc
     Added new icon for dictionary/glossary term documents. (Bug 3699)

     Revision 1.171  2008/01/07 23:22:46  venglisc
     Modifying values passed for flavor in publishPreview to be consistant.
     (Bug 2002)

     Revision 1.170  2007/12/07 19:28:00  venglisc
     Modified GlossaryTerm Concept and GlossaryTerm Name icons. (Bug 3699)

     Revision 1.169  2007/10/11 14:23:52  bkline
     Made macro for inserting current date/time available for InScopeProtocol
     documents.

     Revision 1.168  2007/10/03 21:06:30  bkline
     Workaround for another XMetaL bug (see comments #12 and #13 on
     issue #3397).

     Revision 1.167  2007/10/03 16:32:33  bkline
     Added repro case for PI display bug.

     Revision 1.166  2007/09/27 12:08:57  bkline
     Rewrote code to clone InScopeProtocol information as Scientific doc.
     Added new cloneFor() function.  Reported bug with using that function's
     results to XMetaL (you have to turn off validation checking).

     Revision 1.165  2007/09/20 20:55:17  bkline
     Modified code which creates a new ScientificProtocolInfo doc from an
     InScopeProtocol doc to copy the missing information block.

     Revision 1.164  2007/09/12 20:51:52  bkline
     Macro modified to warn when Outcome is longer than 254 characters.

     Revision 1.163  2007/08/13 16:23:39  bkline
     Implemented macro to insert date/time (request #3493).

     Revision 1.162  2007/07/26 21:23:31  bkline
     Added new macros for Margaret (request #2861).

     Revision 1.161  2007/07/24 14:21:11  bkline
     Added new macro for creating a ScientificProtocolInfo document
     based on information in the active InScopeProtocol document.

     Revision 1.160  2007/07/13 19:19:18  bkline
     Added dynamic macro for inserting Diagnosis terms into protocol
     documents (see request #3140).

     Revision 1.159  2007/06/21 23:46:08  venglisc
     Added toolbar icon for Country QC Report. (Bug 3308)

     Revision 1.158  2007/06/15 23:07:36  bkline
     Tweaks to diagnosis macros at Sheri's request (#3333).

     Revision 1.157  2007/05/31 20:43:35  bkline
     Added audience attribute for new Comment macro.

     Revision 1.156  2007/05/31 19:35:59  bkline
     Added new "Insert Comment" macro (request #3138).

     Revision 1.155  2007/04/24 21:04:48  bkline
     Reordered diagnosis macros; fixed typo in one of the macros.

     Revision 1.154  2007/03/06 18:01:44  bkline
     Added new Diagnosis insertion macros.

     Revision 1.153  2007/03/01 18:52:46  bkline
     Changed link from http://www.abms.org to
     https://specialistsonline.abms.org/.

     Revision 1.152  2007/01/23 20:05:41  bkline
     Added macro to check (and warn) for over-long Outcome elements.

     Revision 1.151  2007/01/23 18:58:27  bkline
     Added support for issue #2730 (show blocked status in XMetaL).

     Revision 1.150  2006/07/11 20:46:25  venglisc
     Added Publish Preview button for DrugInfoSummary document type.
     (Bug 2310)

     Revision 1.149  2006/07/06 20:30:55  bkline
     Installed new cloning macros on the appropriate toolbars.

     Revision 1.148  2006/07/01 14:19:24  bkline
     Added macros for opening linked documents.

     Revision 1.147  2006/05/17 02:02:08  bkline
     Added 'recurrent breast cancer' to BMT macro.

     Revision 1.146  2006/05/16 20:41:41  venglisc
     Adding DrugInfoSummary toolbar (Bug 2053).

     Revision 1.145  2005/12/30 19:31:01  bkline
     Added macros/toolbar buttons for opening translated summaries and
     original English summaries (request #1918).

     Revision 1.144  2005/10/13 22:44:17  venglisc
     Added Redline/Strikeout toolbar button to GlossaryTerm toolbar.
     (Bug 1868)

     Revision 1.143  2005/09/21 21:30:42  bkline
     Fixed typo in one of the new diagnosis insertion macros.

     Revision 1.142  2005/09/21 15:41:46  bkline
     Finished all three diagnosis insertion macros.

     Revision 1.141  2005/09/19 21:57:38  bkline
     Added BMT macro.

     Revision 1.140  2005/06/30 20:54:47  bkline
     Plugged in new icon for Next External Site macro.

     Revision 1.139  2005/06/30 20:49:42  venglisc
     Adding new macro to add toolbar icon for Summary Patient BU Report.
     (Bug 1744)

     Revision 1.138  2005/06/30 18:36:23  bkline
     New macro ("Next External Site") added.

     Revision 1.137  2005/05/12 21:30:56  venglisc
     Added Media QC Report icon to media toolbar. (Bug 1659)

     Revision 1.135  2005/05/06 14:34:07  bkline
     Shifted newest toolbar to be created earlier, trying to work around
     bug in XMetaL which suppresses the ability to enable/disable more
     than a limited number of the toolbars.

     Revision 1.134  2005/05/05 15:49:58  bkline
     Added Supplementary Info Document toolbar.

     Revision 1.133  2005/03/18 17:24:01  bkline
     Added Media toolbar; modified site status adjustment macro for Sheri.

     Revision 1.132  2005/02/16 19:09:03  bkline
     Added code to set the title bar of the application.  Added new attribute
     ("Source") for Insertion and Deletion elements.  Added support for
     previewing mailers for specific summary document versions.  Added macro
     to invoke dialog window for reviewing all change markup.

     Revision 1.131  2004/11/03 22:11:35  bkline
     More modifications to the wording of the prompts in a new board member
     info block.

     Revision 1.130  2004/11/02 18:18:11  bkline
     Plugged in fix for toolbar bug (#963).

     Revision 1.129  2004/10/29 19:10:15  bkline
     Added macro to insert board manager information in org documents.

     Revision 1.128  2004/08/11 20:01:26  bkline
     Added command to create a new glossary term phrase mapping.

     Revision 1.127  2004/08/11 19:52:34  bkline
     Suppressed glossifier command for readonly documents.

     Revision 1.126  2004/08/10 19:45:28  bkline
     Dropped some more dead code.  Suppressed code to manipulate the
     ContainerStyle from the macros (leaving this to the CSS, so I can
     implement request #1213).

     Revision 1.125  2004/08/10 18:35:14  bkline
     Dropped dead buggy code from SoftQuad's original macros.  Added hooks
     for Glossify Document command.

     Revision 1.124  2004/06/03 15:24:04  bkline
     Plugged in workaround for toolbar visibility bug.

     Revision 1.122  2004/04/19 15:26:38  bkline
     Added support for copying/pasting fragment IDs.

     Revision 1.121  2004/04/09 17:05:15  bkline
     Adjusted the cdrIsReadOnly() function further, making sure that we prevent
     direct editing of the DocId and DocType elements.

     Revision 1.120  2004/04/09 16:46:25  bkline
     Implemented the behavior which the comment added for revision 1.75
     said we were going to use (we don't want to block direct editing of
     linking or value-list controlled elements because that disables
     things we want, such as adding a new instance of a repeatable
     element with the Enter key, or editing the attributes on the element.
     See comments in Bugzilla issue #1155.

     Revision 1.119  2004/04/08 20:14:49  bkline
     Dramatic simplification of deletion markup logic (request #1163).

     Revision 1.118  2004/04/08 19:56:09  bkline
     New function addPDQBoardMemberInfoToolbar().

     Revision 1.117  2004/03/22 21:54:40  bkline
     Removed Patient Publish Preview button from CTGov protocol toolbar
     (see request #1148).

     Revision 1.116  2004/03/22 21:51:52  bkline
     Added support for OverallContact element.

     Revision 1.115  2004/03/10 19:45:25  bkline
     Plugged in macro for pasting org address elements into new
     OverallContact element.

     Revision 1.114  2004/03/10 19:42:04  bkline
     Added "Go to Brief Summary" macro.

     Revision 1.113  2003/12/16 13:32:52  bkline
     Added macro to navigate to patient abstract.

     Revision 1.112  2003/12/03 20:26:52  bkline
     Plugged in Unicode for TM symbol.

     Revision 1.111  2003/12/01 21:17:04  bkline
     Added macro and toolbar buttons for Linked Docs Report.

     Revision 1.110  2003/12/01 20:06:25  bkline
     Fixed bug in CTGovProtocol Patient Publish Preview toolbar button
     (macro name in wrong place).

     Revision 1.109  2003/12/01 13:46:43  bkline
     Added another button for patient publish preview of CTGovProtocol
     documents.

     Revision 1.108  2003/11/29 13:18:48  bkline
     Added Publish Preview button to CTGovProtocol toolbar.

     Revision 1.107  2003/11/20 21:37:34  bkline
     Added toolbar button for CTGovProtocol QC report.

     Revision 1.106  2003/11/13 01:42:28  bkline
     Added CTGovProtocol toolbar.  Added macro to diff CWD against
     previous version.

     Revision 1.105  2003/09/24 22:26:31  bkline
     Plugged in named filter set for Protocol Admin QC report.

     Revision 1.104  2003/08/14 21:27:15  bkline
     Changed Style attribute from 'simple' to 'bullet' for Itemized List
     macro.

     Revision 1.102  2003/05/27 15:06:44  bkline
     Added dialog box for selecting markup levels in Accept All Changes macro.

     Revision 1.101  2003/05/13 15:51:34  bkline
     Modified Summary QC macros to take the user to the page which let's the
     user select revision markup level and document version number.

     Revision 1.100  2003/05/08 18:37:54  bkline
     Added macro to back out rejected change markup.  Modified Find Next and
     Find Prev macros to let the user specify the revision level of the
     markup to move to.

     Revision 1.99  2003/05/05 22:00:40  bkline
     Added support for Org address clipboard support.

     Revision 1.98  2003/03/04 16:47:42  bkline
     Modified macro Insert Participating Org as requested by enhancement #433.

     Revision 1.97  2003/03/04 16:08:16  bkline
     Added new macro Verify Specialties.

     Revision 1.96  2003/02/14 21:07:20  bkline
     Added Audit Trail Report.

     Revision 1.95  2003/02/14 20:47:40  bkline
     Added support for cdr:href link pasting; turned off warning for
     publish preview.

     Revision 1.94  2002/12/24 15:08:41  bkline
     Swapped in our own implementation of showPage() to replace SoftQuad's
     buggy version.

     Revision 1.93  2002/12/11 20:51:15  bkline
     Enhancements for issues #527 and #528.

     Revision 1.92  2002/11/21 12:54:35  bkline
     Moved Mailer History button from Summary to Protocol toolbar.

     Revision 1.91  2002/11/21 12:51:35  bkline
     Plugged in Mailer History toolbar buttons.

     Revision 1.90  2002/11/14 14:59:30  bkline
     Added Patient Summary Publish Preview macro.

     Revision 1.89  2002/11/14 14:49:17  bkline
     Added Mailer History macro.

     Revision 1.88  2002/11/14 13:20:40  bkline
     Fixed icon for mailer response button.

     Revision 1.87  2002/10/18 22:19:30  bkline
     Added macros for manipulating Public attribute.

     Revision 1.86  2002/10/15 13:48:32  bkline
     Renamed some macros (issue #406).

     Revision 1.85  2002/10/10 16:34:18  bkline
     Dropped cdr:id attribute from LeadOrgPersonnel in Insert Lead Org macro.

     Revision 1.84  2002/10/09 14:11:54  bkline
     Lifted read-only block for PUP.

     Revision 1.83  2002/10/07 11:45:17  bkline
     Eliminated more dead code.

     Revision 1.82  2002/09/26 15:30:51  bkline
     Eliminated dead code.

     Revision 1.81  2002/09/24 20:41:32  bkline
     Added Mailer toolbar/macro.

     Revision 1.80  2002/09/24 15:30:47  bkline
     Plugged in toolbar buttons for new macros.

     Revision 1.79  2002/09/23 20:17:21  bkline
     Added macro to move to next lead org block.

     Revision 1.78  2002/09/23 20:10:20  bkline
     Added macro to insert participating org.

     Revision 1.77  2002/09/23 19:58:25  bkline
     Added new org status change macro to popup menu.

     Revision 1.76  2002/09/23 19:51:21  bkline
     Added Change Participating Org Status macro.

     Revision 1.75  2002/08/27 18:45:56  bkline
     Added patient publish preview.  Moved publish preview commands from menus
     and from general CDR toolbar to protocol and summary toolbars.  Changed
     patient publish preview icon at Eileen's request.  Added comment
     explaining why readonly settings are not imposed on linking elements.

     Revision 1.74  2002/08/22 13:12:21  bkline
     Turned on Publish Preview.

     Revision 1.73  2002/07/26 16:29:09  bkline
     Removed DatedAction from Insert ProtocolAmendmentInformation (Issue #346).

     Revision 1.72  2002/07/26 16:20:01  bkline
     Removed dead code.  Added code to disable CDR Save macro for readonly
     documents.  Disabled extra On_Update_UI macro.  Added hotkey for CDR
     Save.

     Revision 1.71  2002/07/19 22:07:14  bkline
     Replaced buggy SoftQuad code for Accept/Reject Change macros.  Added
     hotkey for macro to insert current date.

     Revision 1.70  2002/07/17 13:55:19  bkline
     Fixed Move Next/Prev macros.

     Revision 1.69  2002/07/15 22:39:22  bkline
     Switched to Normal view before saving.

     Revision 1.68  2002/07/02 20:47:02  bkline
     Fixed icon number for doc version history report button.

     Revision 1.67  2002/07/02 19:52:06  bkline
     Added document history report macro.

     Revision 1.66  2002/06/26 21:48:37  bkline
     Modified Insertion macro to implement simpler logic as requested by users.

     Revision 1.65  2002/06/13 21:50:22  bkline
     Fixed Insert DateLastModified macro.

     Revision 1.64  2002/06/13 19:01:16  bkline
     Replaced hardcoded host name with COM property.

     Revision 1.63  2002/06/11 13:33:11  bkline
     Moved new NHL Text button.

     Revision 1.62  2002/06/11 13:26:30  bkline
     Plugged in new icon for NHL Text Macro button.

     Revision 1.61  2002/06/07 20:48:41  bkline
     Added NHL macro and button; replace some Filter.py URLs with QcReport.py.

     Revision 1.60  2002/06/06 14:57:37  bkline
     Unplugged Undo macro; added Bold/Underline QC report.

     Revision 1.59  2002/06/03 20:22:43  bkline
     Fixed CitationLink macro button; plugged in help index.

     Revision 1.58  2002/05/31 13:00:45  bkline
     Added published version report button and stub macro.

     Revision 1.57  2002/05/20 15:41:00  bkline
     Replaced SoftQuad macros for inserting lists with code that works all
     the time.  New macros and buttons for inserting various elements.

     Revision 1.56  2002/05/16 02:51:28  bkline
     Added macro for inserting protocol amendment elements.

     Revision 1.55  2002/05/13 19:49:07  bkline
     Removed value from StatusName element when adding new org status for
     protocol.

     Revision 1.54  2002/05/11 03:01:05  bkline
     Implemented several newly requested enhancements.

     Revision 1.53  2002/05/08 20:28:19  bkline
     Removed HTML Summary button.

     Revision 1.52  2002/05/08 20:04:38  bkline
     Renamed filters; rearranged buttons on Protocol toolbar.

     Revision 1.51  2002/05/06 18:55:28  bkline
     Turned on redline/strikeout report.

     Revision 1.50  2002/04/26 23:08:32  bkline
     Added MiscellaneousDocument toolbar.

     Revision 1.49  2002/04/24 23:53:00  bkline
     Replaced stub for Generate Mailers macro.

     Revision 1.48  2002/04/24 21:18:04  bkline
     Replaced some stubs for Protocol and Organization toolbar buttons.

     Revision 1.47  2002/04/24 19:57:14  bkline
     Plugged in Terminology hierarchy view.

     Revision 1.46  2002/04/24 17:40:28  bkline
     Plugged in filters for Protocol Admin QC Report.

     Revision 1.45  2002/04/22 13:42:18  bkline
     Shifted QC macros to the right buttons.  Brought toolbar code in line
     with Eileen's Access tables.

     Revision 1.44  2002/04/20 02:44:05  bkline
     Added readonly protection for selected Mailer document elements.

     Revision 1.43  2002/04/15 02:37:41  bkline
     Added code to switch from text-only view when validating.

     Revision 1.42  2002/04/12 01:34:09  bkline
     Replaced stub for QC button.

     Revision 1.41  2002/04/05 14:15:05  bkline
     Added toolbar button for Checked Out Docs report.

     Revision 1.40  2002/04/05 14:05:38  bkline
     Added separator to Person toolbar between first and second buttons.

     Revision 1.39  2002/04/03 20:44:51  bkline
     Plugged in the filters for the Summary Markup report.

     Revision 1.38  2002/03/26 21:48:06  bkline
     Replaced hardwired filter number with filter name for Summary revision
     markup.

     Revision 1.37  2002/03/21 13:20:10  bkline
     Added summary macros.

     Revision 1.36  2002/03/07 22:29:55  bkline
     Added macros for PatientCharacteristics and PriorConcurrentTherapy.

     Revision 1.35  2002/03/07 20:49:34  bkline
     Fixed icon for CDR Markup/View Original menu item.

     Revision 1.34  2002/03/02 14:08:40  bkline
     Added macro for report of checked-out documents.

     Revision 1.33  2002/03/01 21:29:38  bkline
     Adjusted CdrEdit function to remove XMetaL PIs earlier.

     Revision 1.32  2002/02/26 21:38:18  bkline
     Fixed bug in RevisionLevel default setting.

     Revision 1.31  2002/02/21 22:33:12  bkline
     Switched icons for Find Next and Find Previous macros.

     Revision 1.30  2002/02/21 22:28:56  bkline
     Changed RevisionLevel attribute default from proposed to approved.

     Revision 1.29  2002/02/21 02:24:07  bkline
     Added code to modify the standard toolbars.

     Revision 1.28  2002/02/20 18:32:27  bkline
     Added new toolbar buttons for Find Next Change, Accept Change, and
     Reject Change.

     Revision 1.27  2002/02/20 04:12:21  bkline
     Removed Get Org Address from main CDR toolbar.

     Revision 1.26  2002/02/19 23:15:41  bkline
     Enabled code to pull down Org postal address into person document.

     Revision 1.25  2002/02/19 13:36:01  bkline
     Disabled code to move to newly inserted table's Title element.  Fixed
     typo in macro name Show Original.

     Revision 1.24  2002/02/14 19:29:54  bkline
     Made macro for getting person address conditional on popup menu.
     Commented out macro for getting org address.

     Revision 1.23  2002/02/14 00:56:15  bkline
     Removed dialog box display from save function.

     Revision 1.22  2002/02/14 00:54:18  bkline
     Added Publish Preview macro.  Changed Advanced Search macro to invoke
     the URL directly, rather than having this done in the DLL.

     Revision 1.21  2002/02/12 20:12:50  bkline
     Added remaining toolbars.  Renamed doctype-specific toolbars.
     Added stubs for missing toolbar macros.

     Revision 1.20  2002/02/08 15:07:16  bkline
     Fixed protocol tag names in attempt to keep up with schema changes.

     Revision 1.19  2002/02/05 23:00:50  bkline
     Aligned Insert User ID command with Eileen's requirements.

     Revision 1.18  2002/02/05 18:52:52  bkline
     Added toolbar macro and hotkey for Insert User Name.

     Revision 1.17  2002/02/05 14:38:46  bkline
     Hooked in Org status change to context menu.

     Revision 1.16  2002/02/05 14:19:53  bkline
     Added New Current Org Status macro for protocols.

     Revision 1.15  2002/02/02 18:57:45  bkline
     Hooked in Insert Current Date macro to toolbar.

     Revision 1.14  2002/01/31 14:21:35  bkline
     Added enumerated valid values for RevisionLevel attribute.

     Revision 1.13  2002/01/31 13:51:36  bkline
     Issue #63: moved cursor to end of enumerated value instead of beginning.

     Revision 1.12  2002/01/23 19:02:41  bkline
     Added hotkey (Ctrl+Enter) for cdr field editing.

     Revision 1.11  2001/12/19 14:10:05  bkline
     Added macros for publish preview, jump before/after element, etc.

     Revision 1.10  2001/10/25 02:30:06  bkline
     Moved all custom menu and toolbar building into the macro file.

     Revision 1.9  2001/10/23 21:46:34  bkline
     Added code to remove XMetaL placeholder processing instructions.
     Folded in macros from Eileen.

     Revision 1.8  2001/10/23 13:55:01  bkline
     Added Insert Current Date macro.

     Revision 1.7  2001/10/23 13:47:52  bkline
     Added new macros:
        Insert Lead Org
        CDR Get OrgAddress
        CDR Persons Linking to Org Address Fragment
        CDR Terminology Hierarchy Display
        CDR Terminology Usage Report
        CDR Copy Fragment Link
        CDR Paste Fragment Link

     Revision 1.6  2001/09/20 14:44:40  bkline
     Snapshot before switch to new workstation. (Bob)
     Added macros for toolbar separator, itemized list, ordered list, and
     stubs. (Eileen)

     Revision 1.5  2001/08/27 19:09:43  bkline
     Added "CDR Advanced Search" macro.

     Revision 1.4  2001/08/17 14:27:03  bkline
     Added test for HTML data entry form; added Insertion/Deletion macros.

     Revision 1.3  2001/06/12 02:21:44  bkline
     Added code to check readonly status for entire document.

     Revision 1.2  2001/06/11 21:19:40  bkline
     Added call to isReadOnly().

     Revision 1.1  2000/10/17  14:46:55  bobk
     Initial revision
 
  -->

<!DOCTYPE MACROS SYSTEM "macros.dtd">
<MACROS> 

<MACRO  name="On_Macro_File_Load" 
        lang="JScript">
  <![CDATA[

    //------------------------------------------------------------------
    // GLOBAL VARIABLES
    //------------------------------------------------------------------
    var CdrWebServer = "http://mahler.nci.nih.gov";
    var CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
    
    var blobLinkElementNames = [
        "MediaLink",
        "SupplementaryInfo"
    ];

    //"Summary", "Person", "Organization",
    //                             "InScopeProtocol", "Term",
    //                             "Citation", "GlossaryTerm");

    // To be overridden by successful logon.
    var CdrUserName = "";
    var CdrSession  = "";
    try {
        if (cdrObj) {
            CdrUserName  = cdrObj.username;
            CdrSession   = cdrObj.session;
            if (cdrObj.hostname) {
                CdrWebServer = "http://" + cdrObj.hostname;
                CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
            }
        }
    }
    catch (ignoreMe) {}


    // Clipboard for CDR links.
    var CdrDocLinkClipboard = "";
    var CdrFragLinkClipboard = "";
    var CdrFragIdClipboard = "";
    var CdrOrgAddressClipboard = null;

    function padNumber(number, length, padChar) {
        var str = '' + number;
        while (str.length < length)
            str = padChar + str;
        return str;
    }

    /*
     * Find a singly-occurring element under a specified node.
     * Can also be used for multiply-occurring elements by
     * specifying a target value for one of the element's attributes.
     */
    function getSingleElement(node, name, attrName, attrValue) {
        var elems = node.getElementsByTagName(name);
        for (var i = 0; i < elems.length; ++i) {
            var elem = elems.item(0);
            if (!attrName || elem.getAttribute(attrName) == attrValue)
                return elem;
        }
        return null;
    }

    /*
     * Extracts the document ID from the current document.
     */
    function getDocId() {
        elem = getSingleElement(Application.ActiveDocument, 'DocId');
        if (!elem) return null;
        var val  = getTextContent(elem);
        if (val.length < 1) { return null; }
        return val;
    }

    /*
     * Clone an node from one document for use in another.
     * Typically you have to turn off validation checking to use the
     * results of this function (for examle, if only one instance of
     * a given element is allowed by the DTD/schema at a certain
     * location, and you're replacing the existing instance with
     * one cloned from another document using this function,
     * XMetaL's implementation of replaceChild() isn't intelligent
     * enough to know that the result of replacing one element node with
     * another element node of the same type will still be valid.
     */
    function cloneFor(newDoc, node) {

        // Clone element (recursively).
        var e = newDoc.createElement(node.nodeName);

        // Pop in the attributes from the source element.
        for (var i = 0; i < node.attributes.length; ++i) {
           var attr = node.attributes.item(i);
           if (attr.name != 'cdr:id')
               e.setAttribute(attr.name, attr.value)
        }

        // Copy in clones of the child nodes.
        var child = node.firstChild;
        while (child) {
            var clone = null;
            if (child.nodeType == 1)
                clone = cloneFor(newDoc, child)
            else if (child.nodeType == 3)
                clone = newDoc.createTextNode(child.nodeValue);
            else if (child.nodeType == 4)
                clone = newDoc.createCDATASection(child.nodeValue);
            else if (child.nodeType == 7)
                clone = newDoc.createProcessingInstruction(child.target,
                                                           child.data);
            else if (child.nodeType == 8)
                clone = newDoc.createComment(node.nodeValue);
            if (clone)
                e.appendChild(clone);
            child = child.nextSibling;
        }
        return e;
    }

    /*
     * Extracts the version number (if any) from the open document.
     */
    function getDocVersion() {
        if (!Application.ActiveDocument) { return null; }
        var name = Application.ActiveDocument.Name;
        var pos  = name.indexOf('-V');
        if (pos > 0) {
            var period = name.indexOf('.', pos + 2);
            var ver    = name.substring(pos + 2, period);
            if (ver) return ver;
        }
        return null;
    }

    /*
     * Returns boolean flag indicating whether document has been blocked.
     */
    function docIsBlocked() {
        var doc = Application.ActiveDocument;
        if (!doc)
            return false;
        var nodes = doc.getElementsByTagName("CdrDocCtl");
        if (nodes.length < 1)
            return false;
        var elem = nodes.item(0);
        return elem.getAttribute('blocked') == 'Y';
    }

    /*
     * Produce string containing current date as YYYY-MM-DD string.
     */
     function getCurDateString() {
        var d = new Date();
        var str = padNumber(d.getFullYear(), 4, '0') + '-'
                + padNumber(d.getMonth() + 1, 2, '0') + '-'
                + padNumber(d.getDate(), 2, '0');
        return str;
    }

    /*
     * Produce string containing current time as hh:mm:ss string.
     */
    function getCurTimeString() {
        var d = new Date();
        var str = padNumber(d.getHours(), 2, '0') + ':'
                + padNumber(d.getMinutes(), 2, '0') + ':'
                + padNumber(d.getSeconds(), 2, '0');
        return str;
    }
        
    /*
     * Produce string containing current date/time in XSD format.
     */
    function getCurDateTimeString() {
        var d = new Date();
        var str = padNumber(d.getFullYear(), 4, '0') + '-'
                + padNumber(d.getMonth() + 1, 2, '0') + '-'
                + padNumber(d.getDate(), 2, '0') + 'T'
                + padNumber(d.getHours(), 2, '0') + ':'
                + padNumber(d.getMinutes(), 2, '0') + ':'
                + padNumber(d.getSeconds(), 2, '0');
        return str;
    }
        
    /*
     * Utility function to extract the text content of an element.
     */
    function getTextContent(elem) {
        var textContent = "";
        var child = elem.firstChild;
        while (child) {
            if (child.nodeType == 3) { // Text node
                textContent += child.nodeValue;
            }
            child = child.nextSibling;
        }
        return textContent;
    }

    /*
     * Obtains account credentials from the user and submits them to the CDR
     * server to establish a logged in session.
     */
    function cdrLogon() {
        CdrUserName = "";
        cdrObj = new ActiveXObject("Cdr.Commands");
        if (cdrObj == null) {
            Application.Alert("Unable to find CDR DLL.");
        }
        else {
            //Application.Alert("Sorry, doing a little debugging here ...");
            cdrObj.logon();
            CdrUserName = cdrObj.username;
            CdrSession  = cdrObj.session;
            if (cdrObj.hostname) {
                CdrWebServer = "http://" + cdrObj.hostname;
                CdrCgiBin    = CdrWebServer + "/cgi-bin/cdr/";
            }
//if (CdrUserName == 'rmk')
//            Application.Alert("User Name is " + CdrUserName);
            cdrObj.setTitleBar();
        }
    }

    /*
     * Log the user out of the CDR server.
     */
    function cdrLogoff() {
        CdrUserName = "";
        CdrSession  = "";
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc  = cdrObj.logoff();
            if (rc == 0) {
                Application.Alert("Session successfully logged off.");
                cdrObj = null;
            }
        }
    }

    /*
     * Determine whether the document is read-only.
     */
    function cdrDocReadOnly() {
        if (ActiveDocument == null)                   { return 0; }
        if (ActiveDocument.documentElement == null)   { return 0; }
        if (ActiveDocument.documentElement.getAttribute("readonly") == "yes") 
                                                      { return 1; }
        return 0;
    }

    /*
     * Determine whether the current element should be read-only.
     */
    function cdrIsReadOnly() {
        if (gEditingCdrLink)                          { return 0; }
        if (ActiveDocument == null)                   { return 0; }
        if (ActiveDocument.documentElement == null)   { return 0; }
        if (ActiveDocument.documentElement.getAttribute("readonly") == "yes") 
                                                      { return 1; }
        if (ActiveDocument.doctype == null)           { return 0; }
        if (Selection.ContainerNode == null)          { return 0; }
        if (Selection.ContainerNode.nodeName == null) { return 0; }
        if (Selection == null)                        { return 0; }
        if (cdrObj == null)                           { return 0; }
        var dtName = ActiveDocument.doctype.name;
        var elName = Selection.ContainerNode.nodeName;
        if (elName == "DocId" || elName == "DocType") { return 1; }
        if (dtName == "Mailer") {
            if (elName == "Received" ||
                elName == "ChangesCategory" ||
                elName == "Response" ||
                elName == "Comment")
                return 0;
            return 1;
        }
        /*
         * XXX We cannot use the following DLL method to block
         *     editing of linking elements without disabling the
         *     feature of inserting a new occurrence of a repeating
         *     element by pressing the Enter key.  Lakshmi has
         *     agreed that it is preferable to keep the latter
         *     feature.
         */
        // return cdrObj.isReadOnly(dtName, elName);
        
        return 0;
    }

    function switchCSS(from, to) {
        try {
            var fso = new ActiveXObject("Scripting.FileSystemObject");
        }
        catch (exception) {
            Application.Alert("SwitchCSS Failure: " +
                    "\nFailed to invoke Scripting.FileSystemObject" +
                    "\nWindows Scripting Host needs to be installed.");
        }
        try {
            var xmPath   = Application.Path;
            var fromPath = xmPath + "/display/" + from;
            var toPath   = xmPath + "/display/" + to;
            if (fso.FileExists(fromPath)) {
                var sourceFile = fso.GetFile(fromPath);
                sourceFile.Copy(toPath);
                ActiveDocument.RefreshCssStyle();
            }
            else {
                Application.Alert("SwitchCSS Failure: " +
                        from + " does not exist");
            }
        }
        catch (exception) {
            Application.Alert("SwitchCSS Failure: " + exception +
                    "\nFailed to switch to " + from);
        }
    }

    /*
     * Allows the user to modify a linking element.
     */
    function cdrEdit() {
        if (cdrDocReadOnly()) {
            Application.Alert("Document retrieved as read-only.");
        }
        else if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {

            // Prevent On_Update_UI macro from blocking our editing.
            gEditingCdrLink = true;
            oldFlag = Selection.ReadOnlyContainer;
            Selection.ReadOnlyContainer = false;
            var rc  = cdrObj.edit();
            if (!rc) {
                dumpXmPis();
                Selection.SelectContainerContents();
                Selection.MoveRight(0);
            }
            Selection.ReadOnlyContainer = oldFlag;
            gEditingCdrLink = false;
        }
    }

    /*
     * Allows the user to abandon changes to the current document.
     */
    function cdrCheckIn() {
        if (cdrObj == null)
            Application.Alert("You are not logged on to the CDR");
        else
            cdrObj.checkIn();
    }

    /*
     * Remove any XMetaL processing instructions for placeholder data.
     */
    function dumpXmPis() {
        if (Selection) {
            if (Selection.ContainerNode) {
                var elem = Selection.ContainerNode;
                var child = elem.firstChild;
                while (child) {
                    var nextChild = child.nextSibling;
                    if (child.nodeType == 7) {
                        if (child.target == "xm-replace_text") {
                            elem.removeChild(child);
                        }
                    }
                    child = child.nextSibling;
                }
            }
        }
    }
    
    /*
     * Allows the user to pick a protocol update person.
     */
    function protUpdPerson() {
        if (cdrDocReadOnly()) {
            Application.Alert("Document retrieved as read-only.");
        }
        else if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {

            // Prevent On_Update_UI macro from blocking our editing.
            var whatItWas = Selection.ReadOnlyContainer;
            Selection.ReadOnlyContainer = false;
            gEditingCdrLink = true;
            var rc  = cdrObj.protUpdPerson();
            gEditingCdrLink = false;
            Selection.ReadOnlyContainer = whatItWas;
        }
    }
  
    function getMarkupStyle(element) {
        var docProps = ActiveDocument.CustomDocumentProperties;
        var highlighting = docProps.item("Highlighting").value;
        var style = "color:black;background-color:white";
        if (highlighting == "True") {
            if (element == "Insertion") {
                style =  "color:red;background-color:white";
            }
            else if (element == "Deletion") {
                style = "color:red;background-color:white;" +
                        "text-decoration:line-through";
            }
        }
        return (style);
    }

    function getElemRange(elemName) {

        // Find out where we are.
        var rng = ActiveDocument.Range;

        // Make sure what we find is an ancestor of the current element.
        if (!rng.IsParentElement(elemName))
            return null;

        // Move.
        if (!rng.MoveToElement(elemName, false))
            return null;
        else
            return rng;
    }

    function insertAnother(parentName, elemName, str) {
        var rng = getElemRange(parentName);
        if (!rng) { return false; }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation(elemName, false)) { return false; }
        if (!str) {
            str = "<" + elemName + "/>";
        }
        rng.PasteString(str);
        rng.MoveToElement(elemName, false);
        rng.SelectElement();
        rng.Collapse(1);
        rng.MoveRight();
        rng.Select();
        return true;
    }

    function publishPreview(flavor) {
        //Application.Alert("*** WARNING ***\n" +
        //                "This service is still under development.\n" +
        //                "Formatting and content may be significantly\n" +
        //                "different in final version of software.");
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "PublishPreview.py?Session="
                + CdrSession + "&DocId=" + docId;
        if (flavor)
            url += "&Flavor=" + flavor;
        var ver = getDocVersion();
        if (ver)
            url += "&Version=" + ver;
        else
            url += "&Version=cwd";
        cdrObj.showPage(url);
    }

    function insertDiagnoses(elemString) {

        // Move to the desired location.
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement('Diagnosis', false)) {
            if (!rng.MoveToElement('Gender', false)) {
                if (!rng.MoveToElement('AgeText', false)) {
                    Application.Alert('Unable to find location for ' +
                                      'insertion.');
                    return false;
                }
            }
        }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation("Diagnosis", true)) {
            Application.Alert("Unable to insert Diagnosis terms here.");
            return false;
        }
        rng.PasteString(elemString);
        rng.Select();
        return true;
    }

  ]]>
</MACRO>

<MACRO  name="On_Update_UI" 
        hide="true" 
        lang="JScript">
  <![CDATA[

    // This workaround is being used because SoftQuad is unable or 
    // unwilling to fix the bug which is wiping out our setting of
    // the Visible property of the document-specific toolbar in the
    // On_Document_Activate event.
    function adjustToolbars2() {
        var docType = ActiveDocument.doctype;
        if (toolbars[docType.name] != null) {
            toolbars[docType.name].Visible = true;
        }
    }
    if (Application.VersionNumber < 4.5)
        adjustToolbars2();

    // this will only work if no On_Update_UI macro is defined for the DTD
    if (Selection.IsInsertionPoint && ActiveDocument.ViewType == 1) {
        // this should only apply to the tags-on view, and allow selection 
        // of the top-level element
       if (Selection.ContainerNode == null) {
          Selection.MoveRight();
       }
       if (Selection.ContainerNode == null) {
          Selection.MoveLeft();
       }
    }

    if (Selection) {
        if (cdrIsReadOnly()) {
            Selection.ReadOnlyContainer = true;
        }
        else {
            Selection.ReadOnlyContainer = false;
        }
    }

    if (ActiveDocument == null
    ||  ActiveDocument.documentElement == null
    ||  ActiveDocument.documentElement.getAttribute("readonly") == "yes")
        Application.DisableMacro("Cdr Save");

    if (Documents.Count > 0 && cdrObj) cdrObj.setTitleBar();
  ]]>
</MACRO>

<MACRO  name="Refresh Macros" 
        key="Ctrl+Alt+R" 
        lang="JScript" 
        id="1270" 
        tooltip="" 
        desc="">
  <![CDATA[
    Application.RefreshMacros();
    Application.Alert("Macros have been refreshed");
  ]]>
</MACRO>

<MACRO  lang="JScript" 
        name="Open Document Macros" 
        id="1272">
  <![CDATA[
    var count = Application.Documents.Count;
    if (count == 0) {
        Application.Alert("No Open Document");
    }
    else {
        var mpath = ActiveDocument.MacroFile;
        Documents.Open(mpath, 1);  // open in tags on view
    }
  ]]>
</MACRO>

<MACRO  name="Open Application Macros" 
        lang="JScript" 
        id="1274">
  <![CDATA[
    var mpath = Application.MacroFile;
    Documents.Open(mpath, 1); // open in tags on view
  ]]>
</MACRO>

<MACRO  name="On_Application_Open" 
        hide="true" 
        lang="JScript">
    /*
     * Initialize global variables for CDR macros.
     */
    var gEditingCdrLink = false;
    var cdrObj = null;
    cdrLogon();
    //Application.DisablePlainTextView();
</MACRO>

<MACRO  name="On_Application_Open_Complete" 
        hide="true" 
        lang="JScript">
    turnOffStandardToolbars();
    if (cdrObj != null)
        cdrObj.setTitleBar();
</MACRO>

<MACRO  name="On_Application_Close" 
        hide="true" 
        lang="JScript">
    /*
     * Close the connection to the CDR Server.
     */
    if (cdrObj != null) {
        cdrObj.logoff();
    }
</MACRO>

<MACRO  name="On_Mouse_Over" 
        lang="JScript" 
        hide="true">
  <![CDATA[
    // Reset the Status Text and the Cursor in case a different 
    // document changed them and they are stuck.
    function OnMouseOver()
    {
        Application.SetStatusText("");
        Application.SetCursor(0);
    }
    OnMouseOver();
  ]]>
</MACRO>

<MACRO name="On_DTD_Open_Complete" 
       key="" 
       hide="false" 
       lang="JScript">
         <![CDATA[

    function doAddElements() {

        // In this macro the new document is not yet the active document,
        // so this is how we get to its document type.
        docType  = Application.NewDocumentType;
        rootElem = docType.name;

        // Add a new attribute for CDR issue #2730.
        docType.addEnumeratedAttribute("CdrDocCtl", "blocked",
            "Indicates whether the document has been marked 'Inactive'",
            9, // ordinary enumeration
            2, // default value is explicitly specified
            "N", "N", "Y");
        // Add the Deletion element.
        docType.addElement("Deletion", "Deletion", true , false);
        docType.addAttribute("Deletion", "UserName", "", 0, 0);
        docType.addAttribute("Deletion", "Time", "", 0, 0);
        docType.addEnumeratedAttribute("Deletion", "RevisionLevel",
            "Indicates status of proposed deletion", 9, // ordinary enumeration
            2, // default value is explicitly specified
            "approved", "approved", "proposed", "publish", "rejected");
        docType.addEnumeratedAttribute("Deletion", "Source",
            "Used to tag deletions submitted by an Advisory Board member",
            9, 0, // attribute is optional (#IMPLIED)
            "advisory-board", // this is ignored because attr-type is 0
            "advisory-board", "editorial-board");

        // Add the Insertion element.
        docType.addElement("Insertion", "Insertion", true , false);
        docType.addAttribute("Insertion", "UserName", "", 0, 0);
        docType.addAttribute("Insertion", "Time", "", 0, 0);
        docType.addEnumeratedAttribute("Insertion", "RevisionLevel",
            "Indicates status of proposed insertion", 9, //ordinary enumeration
            2, // default value is explicity specified
            "approved", "approved", "proposed", "publish", "rejected");
        docType.addEnumeratedAttribute("Insertion", "Source",
            "Used to tag insertions submitted by an Advisory Board member",
            9, 0, // attribute is optional (#IMPLIED)
            "advisory-board", // this is ignored because attr-type is 0
            "advisory-board", "editorial-board");

        // Add the element to markup up unwanted private use characters.
        docType.addElement("cdr:PrivateUseCharacter", "cdr:PrivateUseCharacter",
                           true, false);

        // Allow these elements anywhere.
        if (docType.hasElementType(rootElem)) {
            if (docType.hasElementType("Deletion")) {
                docType.addElementToInclusions("Deletion", rootElem);
            }
            if (docType.hasElementType("Insertion")) {
                docType.addElementToInclusions("Insertion", rootElem);
            }
            if (docType.hasElementType("cdr:PrivateUseCharacter")) {
                docType.addElementToInclusions("cdr:PrivateUseCharacter",
                                               rootElem);
            }
        }
    }

    doAddElements();

  ]]>
</MACRO>

<MACRO  name="On_Document_Open_Complete" 
        hide="true" 
        lang="JScript">
<![CDATA[
    //Application.Alert("entering On_Document_Open_Complete");

    /* Request #2730
     */
    if (!docIsBlocked()) {

    Selection.GotoNext(0);
    Selection.GotoNext(0);
    Selection.SelectContainerContents();

    /* } */
    }

    var docProps = ActiveDocument.CustomDocumentProperties;
    docProps.Add("Highlighting", true);
    docProps.Add("ShowOriginal", false);
    docProps.Add("InsNextPrev", false);
    docProps.Add("DelNextPrev", false);
    Application.Run("Init_JScript_Macros");
    //Application.Alert("leaving On_Document_Open_Complete");
]]>
</MACRO>

<MACRO  name="On_Context_Menu" 
        lang="JScript">
  <![CDATA[
 
    function addCdrSubmenu() {
        var acmControls = Application.ActiveContextMenu.Controls;
        var submenu = acmControls.Add(sqcbcTypePopup);
        submenu.Caption = "Insert Canned Diagnosis Set";
        submenu.BeginGroup = true;
        submenu.FaceId  = Application.MakeFaceId("Databases (Custom)", 4, 10);
        var menuItems = new Array(
            new CdrCmdItem("&Advanced Head and Neck",
                           "Insert Advanced Head And Neck Diagnoses",
                           "Advanced Head and Neck",
                           "Add canned list of diagnoses for " +
                           "Advanced Head and Neck",
                           "Databases (Custom)", 4, 10,
                           false),
            new CdrCmdItem("Advanced &Leukemia",
                           "Insert ALK Diagnoses",
                           "ALK",
                           "Insert Advanced Leukemia Diagnoses",
                           "Databases (Custom)", 4, 10,
                           false),
            new CdrCmdItem("Advanced L&ymphomas",
                           "Insert AL Diagnoses",
                           "AL",
                           "Insert Advanced Lymphoma Diagnoses",
                           "Databases (Custom)", 4, 10,
                           false),
            new CdrCmdItem("All &Head and Neck",
                           "Insert Head And Neck Diagnoses",
                           "Head and Neck",
                           "Add canned list of Head and Neck diagnoses",
                           "Databases (Custom)", 4, 10,
                           false),
            new CdrCmdItem("&Bone Marrow Transplant",
                           "Insert BMT Diagnoses",
                           "BMT",
                           "Insert Diagnoses Eligible for Bone Marrow " +
                           "Transplants",
                           "Databases (Custom)", 4, 10,
                           false),
            new CdrCmdItem("&Squamous Cell Carcinoma of the Head and Neck",
                           "Insert Squamous Cell Carcinoma Head And Neck " +
                           "Diagnoses",
                           "Squamous Cell Carcinoma of the Head and Neck",
                           "Add canned list of diagnoses for Squamous Cell " +
                           "Carcinoma of the Head and Neck",
                           "Databases (Custom)", 4, 10,
                           false)
        );

        //menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        //menu.Caption = "Test Submenu";

        // Add the menu items.
        var controls = submenu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    /*
     * Adds a menu option to the popup context menu for custom editing
     * of a link element.
     */
    var container = Selection.ContainerNode;
    var docType = ActiveDocument.doctype;
    var rng = ActiveDocument.Range;
    Application.AppendMacro("-", "");
    Application.AppendMacro("&Edit Element", "Cdr Edit");
    Application.AppendMacro("Copy Document Link", "Cdr Copy Document Link");
    Application.AppendMacro("Copy Fragment Link", "Cdr Copy Fragment Link");
    Application.AppendMacro("Paste Document Link", "Cdr Paste Document Link");
    Application.AppendMacro("Paste Fragment Link", "Cdr Paste Fragment Link");
    if (container && container.nodeType == 1) { // we're in an element?
        if (docType.hasAttribute(container.nodeName, "Public")) {
            if (container.getAttribute("Public") == "No")
                Application.AppendMacro("Remove Public=No", "Set Public");
            else
                Application.AppendMacro("Make Public=No", "Set Non-Public");
        }
        var linkId = container.getAttribute("cdr:ref");
        if (linkId && linkId.indexOf("CDR") >= 0) {
            Application.AppendMacro("Open &Link For Editing",
                                    "Open Linked Doc Edit Mode");
            Application.AppendMacro("Open Link &Readonly",
                                    "Open Linked Doc View Mode");
        }
    }
    if (docType.name == "InScopeProtocol") {
        Application.AppendMacro("-", "");
        Application.AppendMacro("Insert Lead Org", "Insert Lead Org");
        Application.AppendMacro("Prot Update Person", "Protocol Update Person");
        Application.AppendMacro("New Current Org Status", 
                                "New Current Org Status");
        Application.AppendMacro("Insert Grp POs", 
                                "CDR Participating Orgs");
        Application.AppendMacro("Retrieve Person Address", 
                                "CDR Get Person Address");
        if (rng.IsParentElement("ProtocolLeadOrg"))
            Application.AppendMacro("Change Site Statuses",
                    "Change Participating Site Statuses");
        if (CdrOrgAddressClipboard) {
            if (rng.IsParentElement("GenericPerson") ||
                rng.IsParentElement("OverallContact"))
            {
                Application.AppendMacro("Paste Org Address Elements",
                                        "Paste Org Address Elements");
            }
        }
    }
    if (docType.name == "InScopeProtocol" || docType.name == "Summary" ||
        docType.name == "ScientificProtocolInfo") {
        if (!cdrDocReadOnly())
            Application.AppendMacro("Glossify Document", "Glossify Document");
        if (Selection.IsParentElement("GlossaryTermRef"))
            Application.AppendMacro("Add Glossary Phrase",
                                    "Add Glossary Phrase");
    }
    if (docType.name == "Person") {
        Application.AppendMacro("Retrieve Org Postal Address", 
                                "CDR Get Org Postal Address");
        Application.AppendMacro("Copy Fragment ID", "Cdr Copy Fragment ID");
    }
    if (docType.name == "Organization") {
        if (Selection.IsParentElement("Location")) {
            Application.AppendMacro("Persons Linking to This Location",
                "CDR Persons Linking to Org Address Fragment");
            Application.AppendMacro("Remember Postal Address",
                                    "Remember Org Postal Address")
        }
    }
    if (docType.name == "PDQBoardMemberInfo") {
        if (rng.IsParentElement("PersonContactID")) {
            Application.AppendMacro("Paste Fragment ID",
                                    "Cdr Paste Fragment ID");
        }
    }
    for (var i in blobLinkElementNames) {
        if (rng.IsParentElement(blobLinkElementNames[i])) {
            Application.AppendMacro("Show Linked Object",
                                    "Show Linked Blob");
            break;
        }
    }
    //Application.AppendMacro("submenu test", "Test Submenu");
    if (docType.name == "InScopeProtocol" || docType.name == "CTGovProtocol" ||
        docType.name == "ScientificProtocolInfo") {
        if (!cdrDocReadOnly()) {
            Application.AppendMacro("-", "");
            // addCdrSubmenu();
            Application.AppendMacro("Insert Diagnosis Links",
                                    "Insert Diagnosis Links");
        }
    }
    if (rng.FindInsertLocation("Comment")) {
        Application.AppendMacro("Insert Comment", "Insert Comment");
    }
    if (docType.name == 'ScientificProtocolInfo' ||
        docType.name == 'InScopeProtocol') {
        if (!cdrDocReadOnly()) {
            Application.AppendMacro("Insert Current Date and Time",
                                    "Insert Current Date and Time");
        }
    }
  ]]>
</MACRO>

<MACRO  name="On_Default_CommandBars_Complete" 
        key="" 
        lang="JScript">
  <![CDATA[

    /*
     * Constructor for a custom menu or toolbar item.
     */
    function CdrCmdItem(label, action, tip, desc, iconSet, row, col, newGroup) 
    {
        this.label    = label;
        this.action   = action;
        this.tip      = tip;
        this.desc     = desc;
        this.row      = row;
        this.col      = col;
        this.iconSet  = iconSet;
        this.newGroup = newGroup;
    }
    
    function addCdrButton(ctrls, item) {

        // Create a new button.
        var newButton = ctrls.Add();

        // Set the new item's attributes.
        if (newButton != null) {
            newButton.OnAction         = item.action;
            newButton.TooltipText      = item.tip;
            newButton.Enabled          = true;
            newButton.DescriptionText  = item.desc;
            newButton.BeginGroup       = item.newGroup;
            if (item.iconSet != null) {
                newButton.FaceId       = Application.MakeFaceId(item.iconSet, 
                                                                item.row, 
                                                                item.col);
            }
        }
        else {
            Application.Alert("Unable to create \""+action+"\" button.");
        }
        /*
        var faceId = Application.MakeFaceId("CDR", row, col);
        var b = ctrls.add();
        if (sep) { b.BeginGroup = true; }
        b.TooltipText = tip;
        b.DescriptionText = desc;
        b.FaceId = faceId;
        b.OnAction = cmd;
        */
    }

    /*
     * Adds a single CDR menu choice.  Invoked by addCdrMenu() below.
     */
     function addCdrMenuItem(menuControls, item) {

        // Create a new menu item.
        var newItem = menuControls.Add(sqcbcTypePopup);

        // Set the new item's attributes.
        if (newItem != null) {
            newItem.OnAction        = item.action;
            newItem.TooltipText     = item.tip;
            newItem.DescriptionText = item.desc;
            newItem.Caption         = item.label;
            newItem.Enabled         = true;
            newItem.BeginGroup      = item.newGroup;
            if (item.iconSet  != null) {
                newItem.FaceId      = Application.MakeFaceId(item.iconSet, 
                                                             item.row, 
                                                             item.col);
            }
        }
        else {
            Application.Alert("Unable to create \""+action+"\" menu item.");
        }
    }

    /*
     * Drop any old versions of the menus.
     */
    function dropOldMenu(menuName) {

        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;

        // Get rid of the old menu.
        var menu = menuControls.item(menuName);
        while (menu != null) {
            Application.Alert("deleting menu [" + menuName + "]");
            menu.Delete();
            menu = menuBar.Controls.item(menuName);
        }
        Application.Alert("finished deleting all " + menuName + " menus");
    }

    /*
     * Add main CDR menu.
     */
    function addCdrMenu(menuControls, beforeThis) {

        var menuItems = new Array(
            new CdrCmdItem("&New CDR Document",         // Label.
                           "New CDR Document",          // Macro.
                           "Create New CDR Document",   // Tooltip.
                           "Create New CDR Document",   // Description.
                           "CDR", 3, 9,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem("&Retrieve",
                           "Cdr Retrieve",
                           "Retrieve",
                           "Retrieve an existing CDR document by document ID",
                           "CDR", 4, 7,
                           false),
            new CdrCmdItem("S&earch",
                           "Cdr Search",
                           "Search for CDR Document",
                           "Search for CDR Document",
                           "CDR", 3, 1,
                           false),
            new CdrCmdItem("&Advanced Search",
                           "CDR Advanced Search",
                           "Advanced Search",
                           "Launch browser-based CDR search form",
                           "CDR", 3, 2,
                           false),
            new CdrCmdItem("Prin&t",
                           "Print",
                           "Print",
                           "Print the current document",
                           "CDR", 1, 10,
                           true),
            /*
            new CdrCmdItem("&Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            */
            new CdrCmdItem("&Validate",
                           "Cdr Validate",
                           "Validate",
                           "Validate the current CDR document",
                           "CDR", 4, 1,
                           true),
            new CdrCmdItem("&Save",
                           "Cdr Save",
                           "Save",
                           "Save the current CDR document",
                           "CDR", 3, 10,
                           false),
            new CdrCmdItem("&Unlock",
                           "CDR Check In",
                           "Unlock",
                           "Unlock the current CDR document",
                           "CDR", 6, 6,
                           false),
            new CdrCmdItem("Ad&ministrative Subsystem",
                           "Administrative Subsystem",
                           "Administrative Subsystem",
                           "Invoke the web-based CDR Administration menu",
                           "Databases (Custom)", 2, 10,
                           true),
            new CdrCmdItem("CDR &Help",
                           "CDR Help",
                           "CDR Help",
                           "Launch the CDR Help System",
                           "CDR", 4, 2,
                           true)
        );

        var menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        menu.Caption = "&CDR";

        // Add the menu items.
        var controls = menu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    /*
     * Add CDR style menu.
     */
    function addCdrStyleMenu(menuControls, beforeThis) {

        var menuItems = new Array(
            new CdrCmdItem("&Insertion",                // Label.
                           "Insertion",                 // Macro.
                           "Insertion",                 // Tooltip.
                           "Add Insertion markup",      // Description.
                           "CDR", 1, 6,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem("&Deletion",
                           "Deletion",
                           "Deletion",
                           "Add Deletion markup",
                           "CDR", 1, 7,
                           false),
            new CdrCmdItem("Itemized &List",
                           "Itemized List",
                           "Itemized List",
                           "Insert itemized list",
                           "CDR", 6, 1,
                           true),
            new CdrCmdItem("&Ordered List",
                           "Ordered List",
                           "Ordered List",
                           "Insert ordered list",
                           "CDR", 6, 2,
                           false),
            new CdrCmdItem("&Table",
                           "Table",
                           "Table",
                           "Invoke XMetaL table wizard",
                           "CDR", 5, 9,
                           false),
            new CdrCmdItem("D&ate",
                           "Insert Current Date",
                           "Date",
                           "Insert current date",
                           "CDR", 6, 8,
                           false),
            new CdrCmdItem("&User",
                           "Insert User ID",
                           "User",
                           "Insert user ID",
                           "CDR", 5, 10,
                           false),
            new CdrCmdItem("D&rug Name",
                           "Insert DrugName Element",
                           "Drug Name",
                           "Add DrugName element tags to current selection",
                           null, 0, 0,
                           true),
            new CdrCmdItem("&Foreign Word",
                           "Insert ForeignWord Element",
                           "Foreign Word",
                           "Add ForeignWord element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("&Gene Name",
                           "Insert GeneName Element",
                           "Gene Name",
                           "Add GeneName element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("S&cientific Name",
                           "Insert ScientificName Element",
                           "Scientific Name",
                           "Add ScientificName tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("&Emphasis",
                           "Insert Emphasis Element",
                           "Emphasis",
                           "Add Emphasis element tags to current selection",
                           null, 0, 0,
                           true),
            new CdrCmdItem("&Strong",
                           "Insert Strong Element",
                           "Strong",
                           "Add Strong element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("Su&bscript",
                           "Insert Subscript Element",
                           "Subscript",
                           "Add Subscript element tags to current selection",
                           null, 0, 0,
                           false),
            new CdrCmdItem("Su&perscript",
                           "Insert Superscript Element",
                           "Superscript",
                           "Add Superscript element tags to current selection",
                           null, 0, 0,
                           false)
        );

        menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        menu.Caption = "CDR &Styles";

        // Add the menu items.
        var controls = menu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    /*
     * Add CDR markup menu.
     */
    function addCdrMarkupMenu(menuControls, beforeThis) {

        var menuItems = new Array(
            new CdrCmdItem("Find &Next Change",         // Label.
                           "Find Next",                 // Macro.
                           "Find Next Change",          // Tooltip.
                           "Find next markup change",   // Description.
                           "CDR", 1, 8,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem("Find &Previous Change",
                           "Find Prev",
                           "Find Previous Change",
                           "Find previous markup change",
                           "CDR", 1, 9,
                           false),
            new CdrCmdItem("&Accept Change",
                           "Accept Change",
                           "Accept Change",
                           "Accept current markup change",
                           "CDR", 2, 6,
                           true),
            new CdrCmdItem("A&ccept All Changes",
                           "Accept Changes",
                           "Accept All Changes",
                           "Accept all markup changes",
                           "CDR", 2, 7,
                           false),
            new CdrCmdItem("&Reject Change",
                           "Reject Change",
                           "Reject Change",
                           "Reject current markup change",
                           "CDR", 2, 8,
                           false),
            new CdrCmdItem("Re&ject All Changes",
                           "Reject Changes",
                           "Reject All Changes",
                           "Reject all markup changes",
                           "CDR", 2, 9,
                           false),
            new CdrCmdItem("&Back Out Rejected Changes",
                           "Back Out Rejected Markup",
                           "Back Out Rejected Changes",
                           "Back out rejected tracked changes",
                           "Design (Custom)", 4, 10,
                           false),
            new CdrCmdItem("R&eview All Changes",
                           "Review Markup",
                           "Review Markup",
                           "Accept or Reject Changes",
                           null, 0, 0,
                           false),
            new CdrCmdItem("Vie&w Changes With Highlighting",
                           "Show Changes With Highlighting",
                           "View Changes With Highlighting",
                           "View markup changes with highlighting",
                           "CDR", 2, 1,
                           true),
            new CdrCmdItem("View Changes With&out Highlighting",
                           "Show Changes Without Highlighting",
                           "View Changes Without Highlighting",
                           "View markup changes without highlighting",
                           "CDR", 2, 2,
                           false),
            new CdrCmdItem("&View Original",
                           "Show Original",
                           "View Original",
                           "View document before markup",
                           "CDR", 2, 10,
                           false)
        );

        menu = menuControls.Add(sqcbcTypePopup, null, beforeThis);
        menu.Caption = "CDR &Markup";

        // Add the menu items.
        var controls = menu.Controls;
        for (var i = 0; i < menuItems.length; ++i) {
            addCdrMenuItem(controls, menuItems[i]);
        }
    }

    function dropOldMenus() {
        // Prepare some local variables.
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var i = 1;
        while (i <= menuControls.Count) {
        //  Application.Alert("menu count: " + 
        //                    menuControls.Count + " i: " + i);
            var menu = menuControls.item(i);
            var caption = menu.Caption.toUpperCase();
            var pos = caption.indexOf("CDR");
            if (pos == 0 || pos == 1) {
                menu.Delete();
                //Application.Alert("Deleted " + caption);
            }
            else {
                ++i;
                // Application.Alert("Kept " + caption);
            }
        }
    }

    /*
     * Adds the CDR menus, first removing any old versions.
     */
    function addCdrMenus() {

        // Drop any old versions of the menus.
        //dropOldMenu("Cdr");
        //dropOldMenu("CDR");
        //dropOldMenu("CDR Style");
        //dropOldMenu("CDR Markup");
        dropOldMenus();

        // Prepare some local variables.
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;

        // Find the position of the Window menu
        var windMenu      = menuControls.item("Window");
        var windowMenuPos = menuControls.Count;
        while (windowMenuPos >= 1) {
            if (menuControls.item(windowMenuPos) == windMenu) {
                break;
            }
            windowMenuPos = windowMenuPos - 1;
        }
        if (windowMenuPos == 0) {
            windowMenuPos = menuControls.Count - 1;
        }

        // We have to insert these backwards to get them in the right order.
        addCdrMarkupMenu(menuControls, windowMenuPos);
        addCdrStyleMenu(menuControls, windowMenuPos);
        addCdrMenu(menuControls, windowMenuPos);
    }

    function addCdrToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "New CDR Document",          // Macro.
                           "New CDR Document",          // Tooltip.
                           "Create new CDR document",   // Description
                           "CDR", 3, 9,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Cdr Retrieve",
                           "Retrieve",
                           "Retrieve existing CDR document with document ID",
                           "CDR", 4, 7,
                           false),
            new CdrCmdItem(null,
                           "Cdr Search",
                           "Search",
                           "Search for an existing CDR document",
                           "CDR", 3, 1,
                           false),
            new CdrCmdItem(null,
                           "CDR Advanced Search",
                           "Advanced Search",
                           "Launch browser-based CDR search form",
                           "CDR", 3, 2,
                           false),
            new CdrCmdItem(null,
                           "Document History Report",
                           "Document History",
                           "Show Document History",
                           "CDR", 4, 8,
                           true),
            new CdrCmdItem(null,
                           "Audit Trail Report",
                           "Audit Trail",
                           "Show Audit Trail",
                           "Annotations (Custom)", 1, 6,
                           false),
            new CdrCmdItem(null,
                           "Show Checked Out Docs",
                           "Checked Out",
                           "Show Checked Out Docs",
                           "CDR", 1, 1,
                           false),
            new CdrCmdItem(null,
                           "Print",
                           "Print",
                           "Print the current document",
                           "CDR", 1, 10,
                           false),
            /*
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            */
            new CdrCmdItem(null,
                           "Cdr Validate",
                           "Validate",
                           "Validate the current CDR document",
                           "CDR", 4, 1,
                           false),
            new CdrCmdItem(null,
                           "Cdr Save",
                           "Save",
                           "Save the current document",
                           "CDR", 3, 10,
                           false),
            new CdrCmdItem(null,
                           "Administrative Subsystem",
                           "Administrative Subsystem",
                           "Invoke the web-based CDR Administration menu",
                           "Databases (Custom)", 2, 10,
                           false),
            new CdrCmdItem(null,
                           "Jump Before Element",
                           "Jump Before Element",
                           "Position cursor in front of current element's" +
                           " start tag",
                           "CDR", 6, 3,
                           true),
            new CdrCmdItem(null,
                           "Jump Past Element",
                           "Jump Past Element",
                           "Position cursor beyond current element's" +
                           " start tag",
                           "CDR", 6, 4,
                           false),
            /* Bug in XMetaL prevents this from working...
            new CdrCmdItem(null,
                           "Undo Last Edit",
                           "Undo",
                           "Undo Last Action",
                           "Standard", 2, 2,
                           true),
             */
            new CdrCmdItem(null,
                           "Insertion",
                           "Insertion",
                           "Add Insertion markup",
                           "CDR", 1, 6,
                           true),
            new CdrCmdItem(null,
                           "Deletion",
                           "Deletion",
                           "Add Deletion markup",
                           "CDR", 1, 7,
                           false),
            new CdrCmdItem(null,
                           "Find Next",
                           "Find Next",
                           "Find Next Change",
                           "CDR", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Accept Change",
                           "Accept Change",
                           "Accept Change",
                           "CDR", 2, 6,
                           false),
            new CdrCmdItem(null,
                           "Reject Change",
                           "Reject Change",
                           "Reject Change",
                           "CDR", 2, 8,
                           false),
            new CdrCmdItem(null,
                           "Itemized List",
                           "Itemized List",
                           "Insert itemized list",
                           "CDR", 6, 1,
                           true),
            new CdrCmdItem(null,
                           "Ordered List",
                           "Ordered List",
                           "Insert ordered list",
                           "CDR", 6, 2,
                           false),
            new CdrCmdItem(null,
                           "Insert Current Date",
                           "Current Date",
                           "Insert Current Date",
                           "CDR", 6, 8,
                           false),
            new CdrCmdItem(null,
                           "Insert User ID",
                           "User Name",
                           "Insert User ID",
                           "CDR", 5, 10,
                           false),
            new CdrCmdItem(null,
                           "CDR Help",
                           "CDR Help",
                           "Launch the CDR Help System",
                           "CDR", 4, 2,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        /*
        var i = 1;
        //Application.Alert("number of bars: " + cmdBars.count);
        while (i <= cmdBars.count) {
            //Application.Alert("looking at bar " + i);
            var bar = cmdBars.item(i);
            //Application.Alert("Found command bar: " + bar.name);
            try {
                if (bar.name == "CDR") {
                    bar.Delete();
                    Application.Alert("Deleted command bar " + bar.name);
                }
                else {
                    i++;
                }
            }
            catch (e) {
                Application.Alert("Failure deleting CDR bar: " + e);
                ++i;
            }
        }
        */
        
        
        try { cmdBar = cmdBars.item("CDR"); }
        catch (e) { 
            //Application.Alert(e.description);
            //Application.Alert("Error number: " + (e.number & 0xFFFF));
            //Application.Alert("Error description: " + e.description);
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR", 2);
        }
        catch (e) {
            Application.Alert("Failure adding CDR toolbar: " + e);
        }
        if (cmdBar) {
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addSymbolToolbar() {
        var buttons = new Array(
    new CdrCmdItem(null, "SC Up", "Up", "Up", "CDR", 7, 2, false),
    new CdrCmdItem(null, "SC Down", "Down", "Down", "CDR", 7, 3, false),
    new CdrCmdItem(null, "SC Right", "Right", "Right", "CDR", 7, 5, false),
    new CdrCmdItem(null, "SC Left", "Left", "Left", "CDR", 7, 4, false),
    new CdrCmdItem(null, "SC alpha", "alpha", "alpha", "CDR", 7, 6, false),
    new CdrCmdItem(null, "SC beta", "beta", "beta", "CDR", 7, 7, false),
    new CdrCmdItem(null, "SC gamma", "gamma", "gamma", "CDR", 7, 8, false),
    new CdrCmdItem(null, "SC delta", "delta", "delta", "CDR", 7, 9, false),
    new CdrCmdItem(null, "SC mu", "mu", "mu", "CDR", 7, 10, false),
    new CdrCmdItem(null, "SC le", "</=", "</=", "CDR", 8, 1, false),
    new CdrCmdItem(null, "SC ge", ">/=", ">/=", "CDR", 8, 2, false),
    new CdrCmdItem(null, "SC copy", "(C)", "(C)", "CDR", 8, 3, false),
    new CdrCmdItem(null, "SC reg", "(R)", "(R)", "CDR", 8, 4, false),
    new CdrCmdItem(null, "SC TM", "TM", "TM", "CDR", 8, 5, false),
    new CdrCmdItem(null, "SC deg", "Degree", "Degree", "CDR", 8, 6, false),
    new CdrCmdItem(null, "SC cross", "Dagger", "Dagger", "CDR", 8, 7, false),
    new CdrCmdItem(null, "SC dblx", "DDagger", "DDagger", "CDR", 8, 8, false),
    new CdrCmdItem(null, "SC mdash", "Em Dash", "Em dash", "CDR", 8, 9, false),
    new CdrCmdItem(null, "SC plusmin", "+/-", "+/-", "CDR", 8, 10, false),
    new CdrCmdItem(null, "SC lapos", "LApos", "LApos", "CDR2", 1, 1, false),
    new CdrCmdItem(null, "SC rapos", "RApos", "RApos", "CDR2", 1, 2, false),
    new CdrCmdItem(null, "SC lquot", "LQuot", "LQuot", "CDR2", 1, 3, false),
    new CdrCmdItem(null, "SC rquot", "RQuot", "RQuot", "CDR2", 1, 4, false),
    new CdrCmdItem(null, "SC quarter", "1/4", "1/4", "CDR2", 1, 5, false),
    new CdrCmdItem(null, "SC half", "1/2", "1/2", "CDR2", 1, 6, false),
    new CdrCmdItem(null, "SC 3quart", "3/4", "3/4", "CDR2", 1, 7, false),
    new CdrCmdItem(null, "SC nbsp", "NBSP", "NBSP", "CDR2", 1, 8, false)
        );
        
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        try { cmdBar = cmdBars.item("CDR Symbols"); }
        catch (e) { 
            //Application.Alert(e.description);
            //Application.Alert("Error number: " + (e.number & 0xFFFF));
            //Application.Alert("Error description: " + e.description);
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR symbols " +
                                  "toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Symbols", 4);
        }
        catch (e) {
            Application.Alert("Failure adding CDR Symbols toolbar: " + e);
        }
        if (cmdBar) {
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addSummaryToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "New Summary Section",       // Macro.
                           "New Section",               // Tooltip.
                           "Insert new SummarySection", //Description
                           "General (Custom)", 5, 8,    // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Next Summary Section",
                           "Next Section",
                           "Move to next SummarySection",
                           "CDR", 4, 4,
                           true),
            new CdrCmdItem(null,
                           "Previous Summary Section",
                           "Previous Section",
                           "Move to previous SummarySection",
                           "CDR", 4, 5,
                           false),
            new CdrCmdItem(null,
                           "Higher Summary Section",
                           "Higher Section",
                           "Move to higher SummarySection",
                           "CDR", 4, 6,
                           false),
            new CdrCmdItem(null,
                           "Insert CitationLink",
                           "Citation Link",
                           "Insert Citation Link",
                           "CDR", 6, 9,
                           true),
            new CdrCmdItem(null,
                           "Insert DateLastModified",
                           "DateLastModified",
                           "Insert DateLastModified",
                           "CDR", 5, 2,
                           false),
            new CdrCmdItem(null,
                           "Bold Underline Report",
                           "Bold Underline",
                           "Bold Underline Report",
                           "CDR", 2, 3,
                           true),
            new CdrCmdItem(null,
                           "Redline Strikeout Report",
                           "Redline Strikeout",
                           "Redline Strikeout Report",
                           "CDR", 2, 4,
                           false),
            /* Removed at Margaret's request 2003-06-05 (#755).
            new CdrCmdItem(null,
                           "Published Version Report",
                           "Published Version",
                           "Published Version Report",
                           "CDR", 5, 1,
                           false),
            */
            new CdrCmdItem(null,
                           "Patient Summary BU QC Report",
                           "Patient BU QC",
                           "Patient Summary BU QC Report",
                           "CDR2", 2, 1,
                           false),
            new CdrCmdItem(null,
                           "Patient Summary RS QC Report",
                           "Patient RS QC",
                           "Patient Summary RS QC Report",
                           "CDR", 3, 5,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
                           false),
            new CdrCmdItem(null,
                           "Preview Mailer",
                           "Preview Mailer",
                           "Preview Mailer",
                           "General (Custom)", 3, 3,
                           false),
            new CdrCmdItem(null,
                           "Back Out Rejected Markup",
                           "Back Out Rejected Changes",
                           "Back out rejected tracked changes",
                           "Design (Custom)", 4, 10,
                           true),
            new CdrCmdItem(null,
                           "Open Patient Summary",
                           "Patient",
                           "Open patient version of this summary",
                           "CDR2", 3, 1,
                           true),
            new CdrCmdItem(null,
                           "Open HP Summary",
                           "HP",
                           "Open health professional version of this summary",
                           "CDR2", 3, 2,
                           false),
            new CdrCmdItem(null,
                           "Open Original English Summary",
                           "English",
                           "Open original English summary of which this " +
                           "is a translation",
                           "CDR2", 2, 4,
                           true),
            new CdrCmdItem(null,
                           "Open Translated Summary",
                           "Spanish",
                           "Open Spanish translation of this summary",
                           "CDR2", 2, 3,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Summary"); }
        catch (e) { 
            //Application.Alert(e.description);
            //Application.Alert("Error number: " + (e.number & 0xFFFF));
            //Application.Alert("Error description: " + e.description);
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Summary Toolbar: " + e);
            }
            cmdBar = null; 
        }
        try { cmdBar = cmdBars.item("Summary"); }
        catch (e) { 
            // Do nothing.
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old Summary toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Summary", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Summary toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Summary"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addPersonToolbar() {

        var buttons = new Array(
            /*
            new CdrCmdItem(null,                        // Label.
                           "Reset Contact Information", // Macro.
                           "Reset Contact",             // Tooltip.
                           "Reset Contact Information", // Description
                           "CDR", 4, 9,                 // Icon set, row, col.
                           true),                       // Starts new group?
            */
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           false),
            new CdrCmdItem(null,
                           "Verify Specialties",
                           "Specialties",
                           "Link to American Board of Medical Specialties",
                           "Misc 1 (Custom)", 8, 6,
                           false),
            new CdrCmdItem(null,
                           "Mailer History",
                           "Mailer History",
                           "Mailer History",
                           "CDR", 7, 1,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
                           false),
            new CdrCmdItem(null,
                           "Linked Docs Report",
                           "Linked Docs",
                           "Launch Linked Docs Report",
                           "Integration (Custom)", 3, 9,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Person"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Person toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Person", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Person toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Person"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addOrganizationToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Mailer History",
                           "Mailer History",
                           "Mailer History",
                           "CDR", 7, 1,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
                           false),
            new CdrCmdItem(null,
                           "Linked Docs Report",
                           "Linked Docs",
                           "Launch Linked Docs Report",
                           "Integration (Custom)", 3, 9,
                           false),
            new CdrCmdItem(null,
                           "Insert PDQ Board Info",
                           "PDQ Board",
                           "Insert PDQ Board Info",
                           "Databases (Custom)", 7, 5,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Organization"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Organization toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Organization", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Organization toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Organization"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addProtocolToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Go To Admin Info Section",  // Macro.
                           "Admin Info",                // Tooltip.
                           "Go To Admin Info Section",  // Description
                           "General (Custom)", 7, 1,    // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Go To Scientific Info Section",
                           "Scientific Info",
                           "Go To Scientific Info Section",
                           "CDR", 6, 7,
                           false),
            new CdrCmdItem(null,
                           "Go To Patient Abstract",
                           "Patient Abstract",
                           "Navigate to Patient Abstract",
                           "CDR2", 1, 9,
                           false),
            new CdrCmdItem(null,
                           "Next Lead Org",
                           "Go To Next Lead Org",
                           "Go To Next Lead Org",
                           "CDR", 1, 4,
                           false),
            new CdrCmdItem(null,
                           "Next External Site",
                           "Go To Next External Site",
                           "Go To Next External Site",
                           "CDR2", 2, 2,
                           false),
            new CdrCmdItem(null,
                           "Insert PatientCharacteristics",
                           "Patient Characteristics",
                           "Patient Characteristics",
                           "CDR", 1, 2,
                           true),
            new CdrCmdItem(null,
                           "Insert PriorConcurrentTherapy",
                           "Prior Concurrent Therapy",
                           "Prior Concurrent Therapy",
                           "CDR", 1, 3,
                           false),
            new CdrCmdItem(null,
                           "NHL Text",
                           "NHL Text",
                           "NHL Text",
                           "CDR", 5, 7,
                           false),
            new CdrCmdItem(null,
                           "Insert ProtocolAmendmentInformation",
                           "Amendment",
                           "Insert ProtocolAmendmentInformation",
                           "CDR", 5, 4,
                           false),
            new CdrCmdItem(null,
                           "Insert Participating Org",
                           "Add POs",
                           "Add Participating Organizations",
                           "CDR", 5, 6,
                           false),
            new CdrCmdItem(null,
                           "Protocol Merge",
                           "Merge",
                           "Protocol Merge",
                           "Integration (Custom)", 8, 4,
                           true),
            new CdrCmdItem(null,
                           "New Current Org Status",
                           "New Current Org Status",
                           "Change Organization Status",
                           "CDR", 6, 10,
                           false),
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "Full QC",
                           "Full QC Report",
                           "CDR", 4, 3,
                           true),
            new CdrCmdItem(null,
                           "Protocol HP QC Report",
                           "Health Professional QC",
                           "Health Professional QC Report",
                           "CDR", 3, 6,
                           false),
            new CdrCmdItem(null,
                           "Protocol Patient QC Report",
                           "Patient QC",
                           "Patient QC Report",
                           "CDR", 3, 5,
                           false),
            new CdrCmdItem(null,
                           "Protocol Admin QC Report",
                           "Administrative QC",
                           "Administrative QC Report",
                           "CDR", 3, 7,
                           false),
            new CdrCmdItem(null,
                           "Protocol Citations QC Report",
                           "Citations QC",
                           "Citations QC Report",
                           "CDR", 3, 8,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Mailer History",
                           "Mailer History",
                           "Mailer History",
                           "CDR", 7, 1,
                           false),
            new CdrCmdItem(null,
                           "Patient Publish Preview",
                           "Patient Publish Preview",
                           "Patient Publish Preview",
                           "Structure (Custom)", 1, 9,
                           false),
            new CdrCmdItem(null,
                           "Generate Mailer",
                           "Mailer",
                           "Generate Mailer",
                           "CDR", 5, 8,
                           false),
            new CdrCmdItem(null,
                           "Make Scientific Protocol Doc",
                           "Create Scientific Doc",
                           "Make Scientific Protocol Info Document",
                           "CDR2", 2, 5,
                           false),
            new CdrCmdItem(null,
                           "Send Missing Protocol Info Mailer",
                           "Missing Info Mailer",
                           "Send Mailer for Missing Protocol Information",
                           "Misc 1 (Custom)", 7, 1,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Protocol"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old " + 
                    "CDR Protocol toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Protocol", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
        Application.Alert("Failure adding CDR Protocol toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["InScopeProtocol"] = cmdBar;
            toolbars["OutOfScopeProtocol"] = cmdBar;
            toolbars["ScientificProtocolInfo"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addTermToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Term Hierarchy",            // Macro.
                           "Hierarchy",                 // Tooltip.
                           "View Hierarchy",            // Description
                           "Databases (Custom)", 6, 3,  // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Term"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
            Application.Alert("Failure deleting old CDR Term toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Term", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Term toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Term"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addGlossaryToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Glossary RS Report",
                           "Redline Strikeout",
                           "Glossary Redline Strikeout Report",
                           "CDR", 2, 4,
                           false),
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,
                           "Glossary Phrase Search",
                           "Glossary Phrase Search",
                           "Report on matching GlossaryTerm phrases",
                           "CDR", 5, 3,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Glossary Term"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Glossary Term toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Glossary Term", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Glossary Term toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["GlossaryTerm"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addGlossaryTermConceptToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "GT Concept QC Report",      // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,                        // Label.
                           "Show Glossary Term Names",  //  Macro.
                           "Term Names",                // Tooltip.
                           "Show Glossary Term Names",  // Description
                           "Integration (Custom)", 7, 1,// Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Make Glossary Term Name Doc",
                           "Glossary Term",
                           "Create Term Name Document",
                           "CDR2", 2, 10,
                           false),
            new CdrCmdItem(null,
                           "View Glossary Term Name Docs",
                           "View GT Name Docs",
                           "View Term Name Documents",
                           "Integration (Custom)", 3, 9,
                           false),
            new CdrCmdItem(null,
                           "Edit Glossary Term Name Docs",
                           "Edit GT Name Docs",
                           "Edit Term Name Documents",
                           "CDR", 5, 3,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Glossary Term Concept"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert(
                   "Failure deleting old CDR Glossary Term Concept toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Glossary Term Concept", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert(
                "Failure adding CDR Glossary Term Concept toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["GlossaryTermConcept"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addGlossaryTermNameToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "GT Name QC Report",   // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,                        // Label.
               "View Linked Glossary Term Concept Doc", // Macro.
                           "View GT Concept",           // Tooltip.
                           "View Concept Document",     // Description
                           "Integration (Custom)", 3, 9,// Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Edit Linked Glossary Term Concept Doc",
                           "Edit GT Concept",     
                           "Edit Concept Document",
                           "CDR", 5, 3,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Glossary Term Name"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert(
                    "Failure deleting old CDR Glossary Term Name toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Glossary Term Name", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert(
                "Failure adding CDR Glossary Term Name toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["GlossaryTermName"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addDrugInfoToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Drug Info"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Drug Info toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        try {
            cmdBar = cmdBars.add("CDR Drug Info", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Drug Info toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["DrugInformationSummary"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }


    function addCountryToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                      // Label.
                           "Country QC Report",       // Macro.
                           "QC Report",               // Tooltip.
                           "Country QC Report",       // Description
                           "CDR", 3, 4,               // Icon set, row, col.
                           false)                     // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Country"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Drug Info toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        try {
            cmdBar = cmdBars.add("CDR Country", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Country toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Country"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }


    function addCitationToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Search PubMed",             // Macro.
                           "PubMed",                    // Tooltip.
                           "Search PubMed",             // Description
                           "CDR", 3, 3,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           true),
            new CdrCmdItem(null,
                           "Make Citation Supplementary Info Doc",
                           "Create SupplementaryInfo doc",
                           "Create SupplementaryInfo document",
                           "CDR2", 2, 6,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Citation"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Citation toolbar: "
                                + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Citation", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Citation toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Citation"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addMiscToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false)                       // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Miscellaneous Document"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Miscellaneous " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Miscellaneous Document", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Miscellaneous Document " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["MiscellaneousDocument"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addMailerToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Insert Mailer Response",    // Macro.
                           "Response",                  // Tooltip.
                           "Insert Mailer Response",    // Description
                           "CDR", 6, 5,                 // Icon set, row, col.
                           false)                       // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Mailer"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Mailer " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Mailer", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Mailer " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Mailer"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addCTGovToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Go To Brief Summary",       // Macro.
                           "Brief Summary",             // Tooltip.
                           "Move to Brief Summary element",// Description
                           "General (Custom)", 7, 2,    // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,                        // Label.
                           "CTGovProtocol Diff",        // Macro.
                           "Diff ",                     // Tooltip.
                           "Diff against prior version",// Description
                           // "CDR", 6, 5,                
                           "Databases (Custom)", 2, 9,  // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Publish Preview",
                           "Publish Preview",
                           "Publish Preview",
                           "Structure (Custom)", 1, 8,
                           false),
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Insert BMT Diagnoses",
                           "BMT",
                           "Insert Diagnoses Eligible for Bone Marrow " +
                           "Transplants",
                           "Databases (Custom)", 4, 10,
                           true),
            new CdrCmdItem(null,
                           "Insert AL Diagnoses",
                           "AL",
                           "Insert Advanced Lymphoma Diagnoses",
                           "Databases (Custom)", 4, 10,
                           false),
            new CdrCmdItem(null,
                           "Insert ALK Diagnoses",
                           "ALK",
                           "Insert Advanced Leukemia Diagnoses",
                           "Databases (Custom)", 4, 10,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR CTGovProtocol"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR CTGovProtocol " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR CTGovProtocol", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR CTGovProtocol " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["CTGovProtocol"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addTermSetToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Insert Term Set Members",   // Macro.
                           "Insert Terms",              // Tooltip.
                           "Insert Term Set Members",   // Description
                           "Databases (Custom)", 4, 10, // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "TermSet QC Report",
                           "QC Report",
                           "Generate QC Report",
                           "CDR", 3, 4,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR TermSet"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR TermSet " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR TermSet", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR TermSet " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["TermSet"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addPDQBoardMemberInfoToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Generate QC Report",        // Macro.
                           "QC Report",                 // Tooltip.
                           "Generate QC Report",        // Description
                           "CDR", 3, 4,                 // Icon set, row, col.
                           false)                       // Starts new group?
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR PDQBoardMemberInfo"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR PDQBoardMemberInfo toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR PDQBoardMemberInfo", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR PDQBoardMemberInfo toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["PDQBoardMemberInfo"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addMediaToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Show Doc Blob",             // Macro.
                           "Launch Media File",         // Tooltip.
                           "Launch Media File",         // Description
                           "Design (Custom)", 2, 3,     // Icon set, row, col.
                           false),                      // Starts new group?
            new CdrCmdItem(null,
                           "Generate QC Report",
                           "Media QC Report",
                           "Generate QC Report",
                           "CDR2", 1, 10,
                           false)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Media Document"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Media " +
                                  "Document toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Media Document", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Media Document " +
                              "toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["Media"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function addSupplementaryInfoToolbar() {

        var buttons = new Array(
            new CdrCmdItem(null,                        // Label.
                           "Show Doc Blob",             // Macro.
                           "Launch Object File",        // Tooltip.
                           "Launch Object File",        // Description
                           "Databases (Custom)", 2, 6,  // Icon set, row, col.
                           false),                       // Starts new group?
            new CdrCmdItem(null,
                           "Clone Doc",
                           "Clone Document",
                           "Clone SupplementaryInfo Document",
                           "CDR2", 2, 5,
                           true)
        );
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("CDR Supplementary Info Document"); }
        catch (e) { 
        }
        if (cmdBar) { 
            try {
                cmdBar.Delete(); 
            }
            catch (e) {
                Application.Alert("Failure deleting old CDR Supplementary " +
                                  "Info Document toolbar: " + e);
            }
            cmdBar = null; 
        }
        
        
        try {
            cmdBar = cmdBars.add("CDR Supplementary Info Document", 2);
            //cmdBar.Visible = false;
        }
        catch (e) {
            Application.Alert("Failure adding CDR Supplementary Info " +
                              "Document toolbar: " + e);
        }
        if (cmdBar) {
            toolbars["SupplementaryInfo"] = cmdBar;
            var ctrls = cmdBar.Controls;
            for (var i = 0; i < buttons.length; ++i) {
                addCdrButton(ctrls, buttons[i]);
            }
        }
    }

    function bugRepro() {
        var cmdBars = Application.CommandBars;
        var i       = 0;
        if (cmdBars) {
            Application.Alert("number of bars: " + cmdBars.count);
            while (i < cmdBars.count) {
                try {
                    var bar = cmdBars.item(i);
                    Application.Alert("Found command bar: " + bar.name);
                }
                catch (e) {
                    Application.Alert("Err number: " + e.number & 0xFFFF);
                    try {
                        Application.Alert("Description: " + e.description);
                    }
                    catch (e2) {
                        Application.Alert("e.description error: " + e2);
                    }
                }
                i++;
            }
        }
    }

    /*
     * Turn off all the document-specific toolbars.
     */
    function hideToolbars() {
        for (var i in toolbars) {
            if (toolbars[i] && toolbars[i].Visible)
                toolbars[i].Visible = false;
        }
    }

    function turnOffStandardToolbars() {
        var cmdBars = Application.CommandBars;
        var cmdBar  = null;
        
        try { cmdBar = cmdBars.item("Standard"); }
        catch (e) { }
        if (cmdBar) {
            cmdBar.Visible = false;
        }
        cmdBar = null;
        try { cmdBar = cmdBars.item("Formatting"); }
        catch (e) { }
        if (cmdBar) {
            cmdBar.Visible = true;
            var controls = cmdBar.Controls;
            for (var i = controls.count; i >= 1; --i) {
                try {
                    item = controls.item(i);
                    var str = item.DescriptionText;
                    if (str.indexOf("List") != -1) {
                        item.Delete();
                    }
                }
                catch (e) {}
            }
        }
    }

    /*
     * This workaround is needed because, as Softquad admits, there is no way
     * for us to customize our installation in a way which installs the CDR
     * menu as part of a customized default.tbr.
     */
    var toolbars = new Object();
    addCdrToolbar();
    addSupplementaryInfoToolbar();
    addSymbolToolbar();
    addSummaryToolbar();
    addPersonToolbar();
    addOrganizationToolbar();
    addProtocolToolbar();
    addTermToolbar();
    addGlossaryToolbar();
    addGlossaryTermConceptToolbar();
    addGlossaryTermNameToolbar();
    addDrugInfoToolbar();
    addCitationToolbar();
    addMiscToolbar();
    addCountryToolbar();
    addMailerToolbar();
    addCTGovToolbar();
    addTermSetToolbar();
    addPDQBoardMemberInfoToolbar();
    addMediaToolbar();
    addCdrMenus();
    hideToolbars();

  ]]>
</MACRO>

<MACRO  name="Cdr Logon" 
        key="" 
        lang="JScript" 
        tooltip="Log On To CDR" 
        id="1342">
  <![CDATA[

    cdrLogon();

  ]]>
</MACRO>

<MACRO  name="Cdr Retrieve" 
        key="" 
        lang="JScript" 
        tooltip="Retrieve Document From CDR" 
        id="1221">
  <![CDATA[

    /*
     * Retrieves a document from the CDR.  The user is prompted for a document
     * ID.
     */
    function cdrRetrieve() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc = cdrObj.retrieve();
        }
    }
    cdrRetrieve();

  ]]>
</MACRO>

<MACRO  name="Cdr Search" 
        key="" 
        lang="JScript" 
        tooltip="Search for Document in CDR" 
        id="20103">
  <![CDATA[

    /*
     * Searches the CDR repository and retrieves a selected document.
     */
    function cdrSearch() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            var rc  = cdrObj.search();
        }
    }
    cdrSearch();

  ]]>
</MACRO>

<MACRO  name="Cdr Validate" 
        key="" 
        lang="JScript" 
        tooltip="Ask CDR to Validate Document">
  <![CDATA[

    /*
     * Perform CDR validation (schema and/or links) on the currently active 
     * document.
     */
    function cdrValidate() {
        if (ActiveDocument.ViewType != sqViewNormal &&
            ActiveDocument.ViewType != sqViewTagsOn) {
            try {
                ActiveDocument.ViewType = sqViewNormal;
            }
            catch (e) { 
                Application.Alert("Switch to normal or tags-on view " +
                                  "to validate documents.");
                return;
            }
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
        }
        else {
            cdrObj.validate();
        }
    }
    cdrValidate();

  ]]>
</MACRO>

<MACRO  name="Cdr Save" 
        key="Ctrl+Shift+S"
        lang="JScript" 
        tooltip="Store Document in the CDR" 
        id="1365">
  <![CDATA[
  

    /*
     * Saves the currently active document in the CDR repository.
     */
    function cdrSave() {
        if (ActiveDocument.ViewType != sqViewNormal &&
            ActiveDocument.ViewType != sqViewTagsOn) {
            try {
                ActiveDocument.ViewType = sqViewNormal;
            }
            catch (e) { 
                Application.Alert("Switch to normal or tags-on view " +
                                  "to save documents.");
                return;
            }
        }
        if (cdrObj == null)
            Application.Alert("You are not logged on to the CDR");
        else {
            var answer = true;
            var docType = ActiveDocument.doctype;
            // Application.Alert(docType.name);
            if (docType && docType.name == "InScopeProtocol") {
                var doc = Application.ActiveDocument;
                var nodes = doc.getElementsByTagName("Outcome");
                // for (var node in nodes) {
                if (nodes.length > 0) {
                    var elem = nodes.item(0);
                    var val = getTextContent(elem);
                    //Application.Alert(val.length);
                    if (val.length > 254) {
                        var msg = "Outcome text has " + val.length
                                + " characters.\nSave anyway?"
                        answer = Application.Confirm(msg);
                   }
                }
            }
            if (answer)
                cdrObj.save();
        }
    }
    cdrSave();

  
  ]]>
</MACRO>

<MACRO  name="Cdr Logoff" 
        key="" 
        lang="JScript" 
        tooltip="Log out of the CDR" 
        id="20307">
  <![CDATA[
    cdrLogoff();
  ]]>
</MACRO>

<MACRO  name="Cdr Edit" 
        key="Ctrl+Enter"
        lang="JScript" 
        tooltip="Store Document in the CDR" 
        id="1919">
 <![CDATA[
    cdrEdit();
  ]]>
</MACRO>

<MACRO  name="Protocol Update Person" 
        key="" 
        lang="JScript" 
        tooltip="Pick a protocol update person" >
  <![CDATA[
    protUpdPerson();
  ]]>
</MACRO>

<MACRO  name="Cdr Copy Document Link"
        key="" 
        lang="JScript" 
        tooltip="Copy Document Link to CDR Clipboard">
  <![CDATA[
    function copyDocumentLink() {
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("This is a new document without a document ID.");
        }
        CdrDocLinkClipboard = docId;
    }
    copyDocumentLink();
  ]]>
</MACRO>

<MACRO  name="Cdr Copy Fragment Link"
        key="" 
        lang="JScript" 
        tooltip="Copy Fragment Link to CDR Clipboard">
  <![CDATA[
    function copyFragmentLink() {
        CdrFragLinkClipboard = "";
        var nodes = Application.ActiveDocument.getElementsByTagName("DocId");
        if (nodes.length < 1) {
            Application.Alert("This is a new document without a document ID.");
        }
        else {
            var docIdElem = nodes.item(0);
            var docId     = getTextContent(docIdElem);
            var node      = Selection.ContainerNode;
            var depth     = 5;
            var fragId    = "";
            while (node && !fragId) {
                if (depth-- < 1) {
                    Application.Alert("No fragment ID found");
                    return;
                }
                if (node.nodeType != 1) {
                    node = node.parentNode;
                    continue;
                }
                fragId = node.getAttribute("cdr:id");
                if (!fragId) {
                    node = node.parentNode;
                }
            }
            CdrFragLinkClipboard = docId + "#" + fragId;
            Application.Alert("CdrFragLinkClipboard=" + CdrFragLinkClipboard);
        }
    }
    copyFragmentLink();
  ]]>
</MACRO>

<MACRO  name="Cdr Copy Fragment ID"
        key="" 
        lang="JScript" 
        tooltip="Copy Fragment ID to CDR Clipboard">
  <![CDATA[
    function copyFragmentId() {
        CdrFragIdClipboard = "";
        var node           = Selection.ContainerNode;
        var depth          = 5;
        var fragId         = "";
        while (node && !fragId) {
            if (depth-- < 1)
                break;
            if (node.nodeType != 1)
                node = node.parentNode;
            else {
                fragId = node.getAttribute("cdr:id");
                if (!fragId)
                    node = node.parentNode;
            }
        }
        if (!fragId)
            Application.Alert("No fragment ID found");
        else {
            CdrFragIdClipboard = fragId;
            Application.Alert("CdrFragIdClipboard=" + CdrFragIdClipboard);
        }
    }
    copyFragmentId();
  ]]>
</MACRO>

<MACRO  name="Cdr Paste Document Link"
        key="" 
        lang="JScript" 
        tooltip="Paste Document Link From CDR Clipboard">
 <![CDATA[
    function pasteDocumentLink() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        if (CdrDocLinkClipboard == "") {
            Application.Alert("CDR Document Link Clipboard is empty");
            return;
        }
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "cdr:ref") &&
            !docType.hasAttribute(container.nodeName, "cdr:href")) {
            Application.Alert("Current element cannot accept links.");
            return;
        }
        
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        cdrObj.pasteDocLink(CdrDocLinkClipboard);
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = true;
    }

    pasteDocumentLink();
  ]]>
</MACRO>

<MACRO  name="Cdr Paste Fragment Link"
        key="" 
        lang="JScript" 
        tooltip="Paste Fragment Link From CDR Clipboard">
 <![CDATA[
    function pasteFragmentLink() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        if (CdrFragLinkClipboard == "") {
            Application.Alert("CDR Fragment Link Clipboard is empty");
            return;
        }
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "cdr:ref") && 
            !docType.hasAttribute(container.nodeName, "cdr:href")) {
            Application.Alert("Current element cannot accept links.");
            return;
        }
        
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        cdrObj.pasteDocLink(CdrFragLinkClipboard);
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = true;
    }

    pasteFragmentLink();
  ]]>
</MACRO>

<MACRO  name="Cdr Paste Fragment ID"
        key="" 
        lang="JScript" 
        tooltip="Paste Fragment ID From CDR Clipboard">
 <![CDATA[
    function pasteFragmentId() {
        if (CdrFragIdClipboard == "") {
            Application.Alert("CDR Fragment ID Clipboard is empty");
            return;
        }
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (docType.name != "PDQBoardMemberInfo") {
            Application.Alert("Wrong doctype for ID paste target");
            return;
        }
        if (container.nodeName != "PersonContactID") {
            Application.Alert("Current element is not PersonContactID");
            return;
        }
        Selection.SelectContainerContents();
        if (Selection.ReadOnly) {
            Application.Alert("Cannot modify current element");
            return;
        }
        Selection.Text = CdrFragIdClipboard;
    }

    pasteFragmentId();
  ]]>
</MACRO>

<MACRO  name="Test Schema Validation" 
        lang="JScript" 
        key="Ctrl+Alt+Shift+V">
  <![CDATA[

    /*
     * Launches external schema validation app.  This is likely to be used
     * by Aspen for validation of temporary documents created with XMetaL
     * before the CDR system has gone into production.
     */
    function testSchemaValidation() {
        Application.ActiveDocument.Save();
        var WSHShell = new ActiveXObject("WScript.Shell");
        WSHShell.run("macros\\tValidate.cmd \"" + 
                     Application.ActiveDocument.FullName + "\"", 1, 1);
    }
    testSchemaValidation();

  ]]>
</MACRO>


<MACRO  name="PrevElement"  
        key="Shift+Tab" 
        lang="JScript">
  <![CDATA[
    Selection.GotoPrevious(0);
    Selection.SelectContainerContents();
  ]]>
</MACRO>

<MACRO  name="NextElement" 
        key="Tab" 
        lang="JScript">
  <![CDATA[
    Selection.GotoNext(0);
    Selection.SelectContainerContents();
  ]]>
</MACRO>

<MACRO  name="ReloadCSS" 
        key="Ctrl+Alt+S" 
        lang="JScript">
  <![CDATA[
    ActiveDocument.RefreshCssStyle();
  ]]>
</MACRO>

<!--
<MACRO  name="On_Double_Click" 
        lang="JScript" 
        key="Ctrl+Shift+E">
  <![CDATA[
    cdrEdit();
  ]]>
</MACRO>
 -->

<!--
<MACRO  name="PersonNameInfo_OnInitialize" 
        hide="true" 
        lang="JScript">
<![CDATA[

    var ipeg = Application.ActiveInPlaceControl;
    var browser = ipeg.Control;
    var form    = Application.Path + "/Forms/PersonNameInfo.html";
    ipeg.Height = 200;
    ipeg.Width  = 580;
    browser.Navigate2(form, 2);

]]>
</MACRO>
-->

<MACRO name="On_View_Change"
       lang="JScript">
         <![CDATA[

    // refreshes the Insertion and Deletion element container styles on 
    // view change fromplain text to Normal or Tags on
/*
    function refreshStyles() {
        var docProps = ActiveDocument.CustomDocumentProperties;
        if (docProps.item("Highlighting").value == "True") {
            var rng = ActiveDocument.Range;
            rng.MoveToDocumentStart();
            while (rng.MoveToElement("Insertion")) {
                rng.ContainerStyle = "color:red";
            }
            rng.MoveToDocumentStart();
            while (rng.MoveToElement("Deletion")) {
                rng.ContainerStyle = "color:red; text-decoration:line-through";
            }
            rng = null;
        }
    }

    if ((ActiveDocument.ViewType==sqViewNormal ||
        ActiveDocument.ViewType==sqViewTagsOn) &&
        ActiveDocument.PreviousViewType==sqViewPlainText) {
            refreshStyles();
    }
*/
  ]]>
</MACRO>

<MACRO name="Deletion"
       key="Ctrl+Alt+F1"
       lang="JScript" id="1913"
       desc="Surround the selected text with Deletion element">
         <![CDATA[

    //------------------------------------------------------------------
    // Macro for Revision Control
    // Surrounds the selected text with Deletion element and sets the 
    // container style accordingly if highlighting  is true then the 
    // selected text color is red and style is strike through.  If the
    // selected text has an Deletion inside then it merges it with the
    // current parent.  If the selected text has an Insertion element
    // inside then it deletes the elemetn and its contents.
    //
    // NOTE: Logic drastically simplified in keeping with request #1163.
    //------------------------------------------------------------------
    function doDeletion() {

        // If some text is selected:
        if (!ActiveDocument.Range.IsInsertionPoint) {

            if (Selection.CanSurround("Deletion")) {
                var date = new Date();
                Selection.Surround("Deletion");
                //Selection.ContainerStyle = getMarkupStyle("Deletion");
                Selection.ContainerAttribute("UserName") = CdrUserName;
                Selection.ContainerAttribute("Time") = date.toLocaleString();
                Selection.ContainerAttribute("RevisionLevel") = "approved";
            }
            else
                Application.Alert("Deletion markup not allowed here.");
        }
        else
            Application.Alert("The current selection is empty.");
    }

    if (CanRunMacros()) {
        doDeletion();
    }
    
  ]]>
</MACRO>
 
<MACRO  name="Insertion"
        key="Ctrl+Alt+I"
        lang="JScript"
        id="1914"
        desc="Marks the Insertions">
  <![CDATA[

    //----------------------------------------------------------------------
    // Allows the users to track changes while inserting any text in the 
    // document.  If the user selects some text and clicks on insertion 
    // toolbar button the selected text is surrounded by deletion element
    //----------------------------------------------------------------------
    function simpleInsertion() {
        var date = new Date();
        if (!Selection.IsInsertionPoint) {
            if (!Selection.CanSurround("Insertion")) {
                Application.Alert("Unable to apply Insertion markup");
                return;
            }
            Selection.Surround("Insertion");
        }
        else {
            if (!Selection.CanInsert("Insertion")) {
                Application.Alert("Unable to apply Insertion markup");
                return;
            }
            Selection.InsertElement("Insertion");
            Selection.InsertReplaceableText("Insert text here");
        }
        Selection.ContainerAttribute("UserName") = CdrUserName;
        Selection.ContainerAttribute("Time") = date.toLocaleString();
        Selection.ContainerAttribute("RevisionLevel") = "approved";
        //Selection.ContainerStyle = getMarkupStyle("Insertion");
    }

    if (CanRunMacros()) {
        simpleInsertion();
    }

  ]]>
</MACRO>
 
<MACRO  name="Accept Changes"
        key=""
        lang="JScript"
        id="1912"
        desc="Includes all changes in the document">
  <![CDATA[

    //----------------------------------------------------------------------
    // Incorporates Reviewer's changes i.e deletes all text surrounded by
    // Deletion element including the tags and merges the contents of
    // Insertion element with the document.
    //----------------------------------------------------------------------
    function mergeChanges()
    {
        var frm = Application.Path + "/Forms/CDR/AcceptAllChanges.xft";
        var dlg = Application.CreateFormDlg(frm);
        dlg.ApprovedButton.Value = true;
        var rc = dlg.DoModal();
        if (rc != 1)
            return; // User cancelled.
        var levels = "";
        if (dlg.PublishButton.Value)
            levels = "[publish]";
        if (dlg.ApprovedButton.Value)
            levels += "[approved]";
        if (dlg.ProposedButton.Value)
            levels += "[proposed]";
        if (!levels) {
            Application.Alert("No levels selected.");
            return;
        }
        var r = Selection.Duplicate;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            var lvl = r.ContainerNode.getAttribute("RevisionLevel");
            //Application.Alert("revision level = " + lvl);
            if (levels.indexOf(lvl) != -1) {
                r.SelectContainerContents();
                r.Delete();
                r.RemoveContainerTags();
            }
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            var lvl = r.ContainerNode.getAttribute("RevisionLevel");
            //Application.Alert("revision level = " + lvl);
            if (levels.indexOf(lvl) != -1) {
                r.SelectContainerContents();
                if (r.Text == "<?xm-replace_text Insert text here?>") {
                    r.Delete();
                }
                r.RemoveContainerTags();
            }
        }
    }

    if (CanRunMacros()) {
        var confirm = true;/*
            Application.Confirm("Do you want to merge all changes " +
                                "without reviewing them?");*/
        if (confirm) {
            mergeChanges();
        }
    }
    
  ]]>
</MACRO>
 
<MACRO  name="Review Markup"
        lang="JScript"
        id="1948"
        key="Ctrl+Alt+A"
        desc="Accept or Reject Changes..."
        tooltip="Accept or Reject Changes... (Ctrl+Alt+A)">
  <![CDATA[
    if (cdrDocReadOnly())
        Application.Alert("Document is not checked out for editing.");
    else if (CanRunMacros())
        cdrObj.acceptOrRejectMarkup();
  ]]>
</MACRO>

<MACRO  name="Accept or Reject Changes"
        lang="JScript"
        id="1904"
        desc="Accept or Reject Changes..."
        tooltip="Accept or Reject Changes... (Ctrl+Alt+A)">
  <![CDATA[
        
    //----------------------------------------------------------------------
    // Enables the Reviewers to Incorporates the changes from a dialog box.
    //----------------------------------------------------------------------
    function doAcceptOrReject() {
        var Accept, Reject, AcceptAll, RejectAll, Undo,
            FindPrev, FindNext, Insertion_list, Deletion_list;
        Accept = true;
        Reject = true;
        AcceptAll = true;
        RejectAll = true;
        Undo = false;
        FindPrev = true;
        FindNext = true;
        var AcceptOrReject_Dlg = CreateFormDlg(Application.Path + 
                "\\Cdr\\AcceptOrReject.hhf");
        var rng = ActiveDocument.Range;
        Insertion_list = ActiveDocument.getElementsByTagName("Insertion");
        Deletion_list = ActiveDocument.getElementsByTagName("Deletion");
        if (Insertion_list.length == 0 && Deletion_list.length == 0) {
            Accept = false;
            Reject = false;
            AcceptAll = false;
            RejectAll = false;
            Undo = false;
            FindPrev = false;
            FindNext = false;
        }
        else if (!Selection.IsParentElement("Insertion") &&
                 !Selection.IsParentElement("Deletion")) {
            Accept = false;
            Reject = false;
        }

        AcceptOrReject_Dlg.cmdAccept.Enabled = Accept;
        AcceptOrReject_Dlg.cmdReject.Enabled = Reject;
        AcceptOrReject_Dlg.cmdAcceptAll.Enabled = AcceptAll;
        AcceptOrReject_Dlg.cmdRejectAll.Enabled = RejectAll;
        AcceptOrReject_Dlg.cmdUndo.Enabled = Undo;
        AcceptOrReject_Dlg.cmdFindPrev.Enabled = FindPrev;
        AcceptOrReject_Dlg.cmdFindNext.Enabled = FindNext;

        var docProps = ActiveDocument.CustomDocumentProperties;
        if (docProps.item("Highlighting").value == "True") {
            AcceptOrReject_Dlg.opt_ChangesWH.Value = true;
        }
        else if (docProps.item("ShowOriginal").value == "True") {
            AcceptOrReject_Dlg.opt_Original.Value = true;
        }
        else {
            AcceptOrReject_Dlg.opt_ChangesWOH.Value = true;
        }
        if (Selection.ContainerNode.nodeName == "Insertion") {
            AcceptOrReject_Dlg.lblUser.Caption =
                Selection.ContainerAttribute("UserName");
            AcceptOrReject_Dlg.lblAction.Caption = "Insertion";
            AcceptOrReject_Dlg.lblTime.Caption =
                Selection.ContainerAttribute("Time");
        }
        else if (Selection.ContainerNode.nodeName == "Deletion") {
            AcceptOrReject_Dlg.lblUser.Caption =
                Selection.ContainerAttribute("UserName");
                AcceptOrReject_Dlg.lblAction.Caption = "Deletion";
                AcceptOrReject_Dlg.lblTime.Caption =
                    Selection.ContainerAttribute("Time");
        }

        AcceptOrReject_Dlg.DoModal();
    }

    //if (CanRunMacros()) {
    //    doAcceptOrReject();
    //}

  ]]>
</MACRO>
 
<MACRO  name="Accept Change"
        key=""
        lang="JScript"
        id="1905"
        desc="Accept the current marked change">
  <![CDATA[

    //----------------------------------------------------------------------
    // Incorporates the current marked change i.e. if the selection is inside
    // an Insertion the contents are merged and if inside an Deletion the
    // contents are deleted.
    //----------------------------------------------------------------------

    //----------------------------------------------------------------------
    // Replacement for buggy SoftQuad code.
    //----------------------------------------------------------------------
    function doAcceptChangeWithoutSoftQuadBugs() {
        if (cdrDocReadOnly())
            Application.Alert("Document is not checked out for editing.");
        else if (Selection) {
            var elemName = Selection.ElementName(0);
            if (elemName == "Insertion")
                Selection.RemoveContainerTags();
            else if (elemName == "Deletion") {
                Selection.SelectContainerContents();
                Selection.Delete();
                Selection.RemoveContainerTags();
            }
            else
                Application.Alert("Accept Change can only be used " +
                                  "within Insertion or Deletion markup.");
        }
    }

    if (CanRunMacros())
        doAcceptChangeWithoutSoftQuadBugs();
    
  ]]>
</MACRO>
 
<MACRO  name="Reject Change" 
        key="" 
        lang="JScript" 
        id="1902" 
        desc="Rejects the current marked change">
  <![CDATA[
    //----------------------------------------------------------------------
    // Rejects the current marked change i.e. if the selection is inside an 
    // Insertion the contents are removed and if the contents are inside an 
    // Deletion they are merged back with the document.
    //----------------------------------------------------------------------
    //----------------------------------------------------------------------
    // Replacement for buggy SoftQuad code.
    //----------------------------------------------------------------------
    function doRejectChangeCorrectly() {
        if (cdrDocReadOnly())
            Application.Alert("Document is not checked out for editing.");
        else if (Selection) {
            var elemName = Selection.ElementName(0);
            if (elemName == "Deletion")
                Selection.RemoveContainerTags();
            else if (elemName == "Insertion") {
                Selection.SelectContainerContents();
                Selection.Delete();
                Selection.RemoveContainerTags();
            }
            else
                Application.Alert("Reject Change can only be used " +
                                  "within Insertion or Deletion markup.");
        }
    }

    if (CanRunMacros())
        doRejectChangeCorrectly();

  ]]>
</MACRO>
 
<MACRO  name="Reject Changes" 
        key="" 
        lang="JScript" 
        id="1909" 
        desc="Deletes all marked changes">
  <![CDATA[

    //----------------------------------------------------------------------
    // Drop marked changes.
    //----------------------------------------------------------------------
    function doRejectAllChanges()
    {
        var r = ActiveDocument.Range;
        r.MoveToDocumentStart();
        Selection.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            Selection.MoveToElement("Deletion");
            //Selection.RemoveContainerTags();
            var rng = r.Duplicate;
            doRejectDelChange(r);
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            r.SelectContainerContents();
            r.Delete();
            r.RemoveContainerTags();
        }
        r = null;
    }


    function doRejectDelChange(rng_reject) {
        rng_reject.SelectContainerContents();
        start = rng_reject.Duplicate;
        start.Collapse(1);  // set the starting boundary for the search
        end = rng_reject.Duplicate;
        end.Collapse(0);  // set the ending boundary for the search
        rng_reject.RemoveContainerTags();
        rng_reject = readtree(start, end);
        rng_reject= null;
        return;
    }

    function readtree(startRng, endRng) {  

        while (true) {  

            // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {
                // if it is with in the range of the selected parent
                if (startRng.IsLessThan(endRng)) {
                    // element = startRng.ContainerNode.nodeName;
                    // startRng.ContainerStyle = getMarkupStyle(element);
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return(endRng);
    }

    if (CanRunMacros()) {
        var confirm = Application.Confirm("Do you want to reject all " +
                                          "changes without reviewing them?");
        if (confirm) {
            doRejectAllChanges();
        }
    }

  ]]>
</MACRO>
 
<MACRO  name="Show Original" 
        key="" 
        lang="JScript" 
        id="20207" 
        desc="Displays the document without any marked changes">
  <![CDATA[

    //----------------------------------------------------------------------
    // Displays the original document (i.e., without any tracked changes).
    //----------------------------------------------------------------------
    function doShowOriginal()
    {
        var docProps = ActiveDocument.CustomDocumentProperties;
        docProps.item("Highlighting").value = false;
        docProps.item("ShowOriginal").value = true;
        var r = ActiveDocument.Range;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            //    r.HiddenContainer = false;
            r.ContainerStyle = "";

            //r.ReadOnlyContainer = false;
            //r.ContainerAttribute("display") = "showNormal";
            //r.ReadOnlyContainer = true;
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            if (!r.HiddenContainer) {
                r.HiddenContainer = true;
            }
        }
        r = null;
    }

    if (CanRunMacros()) {
        doShowOriginal();
    }

  ]]>
</MACRO>

<MACRO  name="Show Changes With Highlighting" 
        key="" 
        lang="JScript" 
        id="1908" 
        desc="Displays all marked changes with highlighting">
  <![CDATA[

    //----------------------------------------------------------------------
    // Highlights all the marked changes by setting the container style of all 
    // Insertion and Deletion Elements
    //----------------------------------------------------------------------
    function doShowChangesWithHL() {
        var docProps = ActiveDocument.CustomDocumentProperties;
        docProps.item("Highlighting").value = true;
        docProps.item("ShowOriginal").value = false;
        var rng_HL = ActiveDocument.Range;
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Insertion")) {
            rng_HL.HiddenContainer = false;
            //rng_HL.ContainerStyle = getMarkupStyle("Insertion");
            var rng2 = rng_HL.Duplicate;
            rng2.SelectElement();
            //txt = rng2.ContainerStyle;
            //rng2.ContainerStyle = txt;
            rng2 = null;
        }
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Deletion")) {
            rng_HL.SelectContainerContents();
            start = rng_HL.Duplicate;
            start.Collapse(1);  // set the starting boundary for the search
            end = rng_HL.Duplicate;
            end.Collapse(0);  // set the ending boundary for the search
            // rng_HL.ContainerStyle = getMarkupStyle("Deletion");
            rng_HL = readtree(start, end);
        }
        rng_HL= null;
    }

    function readtree(startRng, endRng) {

        while (true) {  

            // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {  
                // if it is with in the range of the selected parent
                if (startRng.IsLessThan(endRng)) {
                    element = startRng.ContainerNode.nodeName;
                    element = "Deletion";
                    //startRng.ContainerStyle = getMarkupStyle(element);
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return endRng;
    }

    // XXX This looks to be pretty buggy!
    var element;
    if (CanRunMacros()) {
        doShowChangesWithHL();
    }

  ]]>
</MACRO>

<MACRO  name="Show Changes Without Highlighting" 
        key="" 
        lang="JScript" 
        id="1907" 
        desc="Displays all marked changes without highlighting">
  <![CDATA[


    //----------------------------------------------------------------------
    // Displays the document with marked changes but without highlighting 
    //----------------------------------------------------------------------
    function doShowChangesWOH() {
        var docProps = ActiveDocument.CustomDocumentProperties;
        docProps.item("Highlighting").value = false;
        docProps.item("ShowOriginal").value = false;
        var rng_HL = ActiveDocument.Range;
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Insertion")) {
            rng_HL.HiddenContainer = false;
            // rng_HL.ContainerStyle = getMarkupStyle("Insertion");
            rng2 = null;  // clean up
        }
        rng_HL.MoveToDocumentStart();
        while (rng_HL.MoveToElement("Deletion")) {
            rng_HL.SelectContainerContents();
            start = rng_HL.Duplicate;
            start.Collapse(1);  // set the starting boundary for the search
            end = rng_HL.Duplicate;
            end.Collapse(0);  // set the ending boundary for the search
            // rng_HL.ContainerStyle = getMarkupStyle("Deletion");
            rng_HL = readtree(start, end);
        }
        rng_HL= null;
    }

    function readtree(startRng, endRng) {

        while (true) {

            // Move to next element
            var tempRng = startRng.Duplicate;
            startRng.GoToNext(0);
            if (tempRng.isEqual(startRng)) {
                tempRng = null;
                break;
            } 
            else {
                if (startRng.IsLessThan(endRng)) {  
                
                    // if it is with in the range of the selected parent
                    // startRng.ContainerStyle = getMarkupStyle("Deletion");
                } 
                else {
                    break;
                }
            }
        }
        startRng = null;
        return endRng;
    }

    if (CanRunMacros()) {
        doShowChangesWOH();
    }

  ]]>
</MACRO>

<MACRO  name="Find Next" 
        key="" 
        lang="JScript" 
        id="1911" 
        desc="Moves the selection to the next marked change if any" 
        tooltip="Find Next Change">
  <![CDATA[


    //----------------------------------------------------------------------
    // Moves the selection to the next Marked change in the document
    // If the end of the document is reached the search is resumed from 
    // the beginning of the document 
    // XXX This is SoftQuad's code.  Very complicated and impressive,
    //     but it doesn't work.  Replaced below.
    //----------------------------------------------------------------------
    function doFindNext() {

        var docProps = ActiveDocument.CustomDocumentProperties;
        var parentName = "";
        if (Selection.ContainerNode) {
            parentName = Selection.ContainerNode.parentNode.nodeName;
        }
        if (docProps.item("InsNextPrev").value == "True") {
            if (Selection.ContainerNode) {
                if (parentName == "Insertion") {
                    Application.Run("Find Prev");
                }
                else {
                    docProps.item("InsNextPrev").value = false;
                    doFindNext();
                }
            }
            docProps.item("InsNextPrev").value = false;
        }
        else {
            if (docProps.item("DelNextPrev").value == "True") {
                if (Selection.ContainerNode) {
                    if (parentName == "Deletion") {
                        Application.Run("Find Prev");
                    }
                    else {
                        docProps.item("DelNextPrev").value = false;
                        doFindNext();
                    }
                }
                docProps.item("DelNextPrev").value = false;
            }
            else {
                var rng1 = ActiveDocument.Range;
                var rng2 = rng1.Duplicate;
            
                var Insertion = rng1.MoveToElement("Insertion");
                var Deletion = rng2.MoveToElement("Deletion");
                if (Insertion && Deletion) {
                    if (rng1.IsLessThan(rng2)) {
                        if (hasChildren(rng1.Duplicate, "Insertion")) {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectAfterContainer();
                            docProps.item("InsNextPrev").value = true;
                            Application.Run("Find Prev");
                        }
                        else {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectContainerContents();
                        }
                    }
                    else {
                        if (hasChildren(rng1.Duplicate, "Deletion")) {
                            Selection.MoveToElement("Deletion");
                            Selection.SelectAfterContainer();
                            docProps.item("DelNextPrev").value = true;
                            Application.Run("Find Prev");
                        }
                        else {
                            Selection.MoveToElement("Deletion");
                            Selection.SelectContainerContents();
                        }
                    }
                }
                else {
                    if (Insertion) {
                        if (hasChildren(rng1.Duplicate, "Insertion")) {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectAfterContainer();
                            docProps.item("InsNextPrev").value = true;
                            Application.Run("Find Prev");
                        }
                        else {
                            Selection.MoveToElement("Insertion");
                            Selection.SelectContainerContents();
                        }
                    }
                    else {
                        if (Deletion) {
                            if (hasChildren(rng1.Duplicate, "Deletion")) {
                                Selection.MoveToElement("Deletion");
                                Selection.SelectAfterContainer();
                                docProps.item("DelNextPrev").value = true;
                                Application.Run("Find Prev");
                            }
                            else {
                                Selection.MoveToElement("Deletion");
                                Selection.SelectContainerContents();
                            }
                        }
                        else {
                            var ad = ActiveDocument;
                            var InsertionList = 
                                ad.getElementsByTagName("Insertion"); 
                            var DeletionList = 
                                ad.getElementsByTagName("Deletion"); 
                            if (InsertionList.length != 0 || 
                                DeletionList.length != 0) {
                                var search = Application.Confirm(
                                    "Reached the end of the Document.  " +
                                    "Do you want to continue searching " +
                                    "from the beginning of the document?");
                                if (search) {
                                    Selection.MoveToDocumentStart();
                                    var rng = ActiveDocument.Range;
                                    rng.MoveToDocumentStart();
                                    doFindNext();
                                }
                            }
                            else {
                                Application.Alert("Found no tracked changes");
                            }
                        }
                    }
                }
                rng1 = null;
                rng2 = null;
            }
        }
    }

    function hasChildren(rng_chld, elemName) {
        if (rng_chld.ContainerNode) {
            if (rng_chld.ContainerNode.hasChildNodes()) { 
                var children = rng_chld.ContainerNode.childNodes;
                for (var i=0; i < children.length; i++) {
                    if (children.item(i).nodeName == elemName) {
                        return true;
                    }
                }
                return false;
            }
            else {
                return false;
            }
        }
    }
  
    //----------------------------------------------------------------------
    // Rewritten to fix SoftQuad's buggy approach in response to CDR issue
    // report #330.
    //----------------------------------------------------------------------
    function findNextInsertionOrDeletion() {
        var delElem = ActiveDocument.Range;
        var insElem = ActiveDocument.Range;
        var keepGoing = true;
        var markupLevel = "";
        var dlg = Application.CreateFormDlg(Application.Path +
                                            "/Forms/CDR/FindNextMarkup.xft");
        dlg.MarkupLevel.Value = 2;
        if (dlg.DoModal() != 1)
            return;
        if (dlg.MarkupLevel.Value == 1) markupLevel = "proposed";
        else if (dlg.MarkupLevel.Value == 2) markupLevel = "approved";
        else if (dlg.MarkupLevel.Value == 3) markupLevel = "publish";
        while (keepGoing) {
            delElem.Collapse();
            insElem.Collapse();
            var foundDel = delElem.MoveToElement('Deletion', true);
            var foundIns = insElem.MoveToElement('Insertion', true);
            while (foundDel && markupLevel) {
                var lvl = delElem.ContainerNode.getAttribute("RevisionLevel");
                if (lvl == markupLevel)
                    break;
                delElem.Collapse();
                foundDel = delElem.MoveToElement('Deletion', true);
            }
            while (foundIns && markupLevel) {
                var lvl = insElem.ContainerNode.getAttribute("RevisionLevel");
                if (lvl == markupLevel)
                    break;
                insElem.Collapse();
                foundIns = insElem.MoveToElement('Insertion', true);
            }
            if (!foundDel && !foundIns) {
                keepGoing = Application.Confirm(
                    "Reached the end of the Document.  " +
                    "Do you want to continue searching " +
                    "from the beginning of the document?");
                if (keepGoing) {
                    delElem.MoveToDocumentStart();
                    insElem.MoveToDocumentStart();
                }
            }
            else {
                keepGoing = false;
                var whichRange = null;
                if (!foundDel)
                    whichRange = insElem;
                else if (!foundIns)
                    whichRange = delElem;
                else if (insElem.IsGreaterThan(delElem))
                    whichRange = delElem;
                else
                    whichRange = insElem;
                whichRange.SelectContainerContents();
                whichRange.Select();
            }
        }
    }

    if (CanRunMacros()) {
        //doFindNext();
        findNextInsertionOrDeletion();
    }

  ]]>
</MACRO>

<MACRO  name="Find Prev" 
        key="" 
        lang="JScript" 
        id="1910" 
        desc="Moves the selection to the previous marked change if any">
        <![CDATA[

    //----------------------------------------------------------------------
    // Moves the selection to the previous Marked change in the document
    // If the beginning of the document is reached the search is resumed 
    // from the end of the document 
    // XXX Buggy SoftQuad code.  See note on doFindNext() above.
    //----------------------------------------------------------------------
    function doFindPrev() {

        var rng1 = ActiveDocument.Range;
        var rng2 = rng1.Duplicate;

        var Insertion = rng1.MoveToElement("Insertion", false);
        var Deletion = rng2.MoveToElement("Deletion", false);
        if (Insertion && Deletion) {
            if (rng1.IsGreaterThan(rng2)) {
                Selection.MoveToElement("Insertion", false);
                Selection.SelectContainerContents();
            }
            else {
                Selection.MoveToElement("Deletion", false);
                Selection.SelectContainerContents();
            }
        } 
        else if (Insertion) {
            Selection.MoveToElement("Insertion", false);
            Selection.SelectContainerContents();
        } 
        else if (Deletion) {
            Selection.MoveToElement("Deletion", false);
            Selection.SelectContainerContents();
        } 
        else {
            var ad = ActiveDocument;
            var InsertionList = ad.getElementsByTagName("Insertion"); 
            var DeletionList = ad.getElementsByTagName("Deletion"); 
            if (InsertionList.length != 0 || DeletionList.length != 0) {
                var search = Application.Confirm(
                    "Reached the beginning of the Document.  " +
                    "Do you want to continue searching from the " +
                    "end of the document?");
                if (search) {
                    Selection.MoveToDocumentEnd();
                    doFindPrev();
                }
            }
            else {
                Application.Alert("Found no tracked changes");
            }
        }
        rng1 = null;
        rng2 = null;
    }

    //----------------------------------------------------------------------
    // Rewritten to fix SoftQuad's buggy approach in response to CDR issue
    // report #330.
    //----------------------------------------------------------------------
    function findPrevInsertionOrDeletion() {
        var delElem = ActiveDocument.Range;
        var insElem = ActiveDocument.Range;
        var keepGoing = true;
        var markupLevel = "";
        var dlg = Application.CreateFormDlg("Forms/CDR/FindNextMarkup.xft");
        dlg.MarkupLevel.Value = 2;
        dlg.TheFrame.Title = "Find Previous Revision Markup";
        if (dlg.DoModal() != 1)
            return;
        if (dlg.MarkupLevel.Value == 1) markupLevel = "proposed";
        else if (dlg.MarkupLevel.Value == 2) markupLevel = "approved";
        else if (dlg.MarkupLevel.Value == 3) markupLevel = "publish";
        while (keepGoing) {
            //delElem.Collapse();
            //insElem.Collapse();
            var foundDel = delElem.MoveToElement('Deletion', false);
            var foundIns = insElem.MoveToElement('Insertion', false);
            while (foundDel && markupLevel) {
                var lvl = delElem.ContainerNode.getAttribute("RevisionLevel");
                if (lvl == markupLevel)
                    break;
                foundDel = delElem.MoveToElement('Deletion', false);
            }
            while (foundIns && markupLevel) {
                var lvl = insElem.ContainerNode.getAttribute("RevisionLevel");
                if (lvl == markupLevel)
                    break;
                foundIns = insElem.MoveToElement('Insertion', false);
            }
            if (!foundDel && !foundIns) {
                keepGoing = Application.Confirm(
                    "Reached the beginning of the Document.  " +
                    "Do you want to continue searching " +
                    "from the end of the document?");
                if (keepGoing) {
                    delElem.MoveToDocumentEnd();
                    insElem.MoveToDocumentEnd();
                }
            }
            else {
                keepGoing = false;
                var whichRange = null;
                if (!foundDel)
                    whichRange = insElem;
                else if (!foundIns)
                    whichRange = delElem;
                else if (insElem.IsGreaterThan(delElem))
                    whichRange = insElem;
                else
                    whichRange = delElem;
                whichRange.SelectContainerContents();
                whichRange.Select();
            }
        }
    }

    if (CanRunMacros()) {
        //doFindPrev();
        findPrevInsertionOrDeletion();
    }

  ]]>
</MACRO>

<MACRO  name="Init_JScript_Macros" 
        lang="JScript" 
        desc="initialize JScript macros" 
        hide="true">
  <![CDATA[

    function CanRunMacros() {
        if (ActiveDocument.ViewType != sqViewNormal && 
            ActiveDocument.ViewType != sqViewTagsOn) {
            Application.Alert("Change to Tags On or Normal " + 
                              "view to run macros.");
            return false;
        }

        if (!ActiveDocument.IsXML) {
            Application.Alert("Cannot run macros because document " + 
                              "is not XML.");
            return false;
        }
        return true;
    }

  ]]>
</MACRO>

<MACRO  name="CDR Advanced Search"
        lang="JScript" 
        desc="Launch browser menu for advanced CDR searching" 
        hide="false">
  <![CDATA[

    function advancedSearch() {
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "AdvancedSearch.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    advancedSearch();

  ]]>
</MACRO>

<MACRO  name="Show Checked Out Docs"
        lang="JScript" 
        desc="Bring up report showing documents checked out by this user."
        hide="false">
  <![CDATA[

    function checkedOutDocs() {
        if (!CdrSession || !CdrUserName) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "CheckedOutDocs.py?Session=" + CdrSession
                            + "&User=" + CdrUserName;
        cdrObj.showPage(url);
    }
    checkedOutDocs();

  ]]>
</MACRO>

<MACRO name="Published Version Report" 
       lang="JScript">
  <![CDATA[
    Application.Alert("This report depends on the Publish Preview interface" +
                      "\nwith Cancer.Gov, which is still under development");
  ]]>
</MACRO>

<MACRO name="Publish Preview" 
       lang="JScript">
  <![CDATA[
    publishPreview("");
  ]]>
</MACRO>

<MACRO name="Patient Publish Preview" 
       lang="JScript">
  <![CDATA[
    publishPreview("Protocol_Patient");
  ]]>
</MACRO>

<MACRO name="Patient Summary Publish Preview" 
       lang="JScript">
  <![CDATA[
    publishPreview("Summary_Patient");
  ]]>
</MACRO>

<MACRO name="Patient CTGovProtocol Publish Preview" 
       lang="JScript">
  <![CDATA[
    publishPreview("CTGovProtocol_Patient");
  ]]>
</MACRO>

<MACRO  name="CDR Check In"
        lang="JScript" 
        desc="Releases CDR lock, abandoning any changes to current document."
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrCheckIn();
    }

  ]]>
</MACRO>

<MACRO  name="CDR Get Person Address"
        lang="JScript" 
        desc="Retrieve address from fragment link"
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrObj.getPersonAddress();
    }

  ]]>
</MACRO>

<MACRO  name="CDR Participating Orgs"
        lang="JScript" 
        desc="Select Participating Organizations for Protocol"
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrObj.particOrgs();
    }

  ]]>
</MACRO>

<MACRO  name="Insert Lead Org"
        lang="JScript" 
        desc="Insert new Protocol lead organization"
        hide="false">
  <![CDATA[

    if (!insertAnother("ProtocolAdminInfo", "ProtocolLeadOrg",
        "<ProtocolLeadOrg>" +
        "<LeadOrganizationID>Select Organization Here</LeadOrganizationID>" +
        "<LeadOrgRole/>" +
        "<LeadOrgProtocolID/>" +
        "<LeadOrgProtocolStatuses>" +
        "<CurrentOrgStatus>" +
        "<StatusName/>" +
        "<StatusDate/><EnteredBy/><EntryDate/>" +
        "</CurrentOrgStatus>" +
        "</LeadOrgProtocolStatuses>" +
        "<LeadOrgPersonnel>" +
        "<Person cdr:ref=''>Person Name Here</Person>" +
        "<PersonRole/>" +
        "</LeadOrgPersonnel>" +
        "</ProtocolLeadOrg>")) {
        Application.Alert("Unable to insert ProtocolLeadOrg");
    }
  ]]>
</MACRO>

<MACRO  name="Insert Participating Org"
        lang="JScript" 
        key="Ctrl+Alt+Z" 
        desc="Insert new Protocol participating organization"
        hide="false">
  <![CDATA[
    /*
     * Modified 2003-03-04 at Lakshmi's request (#433) to insert
     * the missing ProtocolSites parent element when the user
     * has failed to do so.
     */
    function insertParticipatingOrg() {
        var rng = getElemRange("ProtocolLeadOrg");
        if (!rng) {
            Application.Alert(
                "Current position is not within a lead organization");
            return;
        }
        leadOrg = rng.ContainerNode;
        protSites = leadOrg.getElementsByTagName("ProtocolSites");
        if (!protSites.length) {
            // Application.Alert("Inserting ProtocolSites element");
            if (!rng.FindInsertLocation("ProtocolSites", true)) {
                Application.Alert("Failure inserting ProtocolSites element");
                return;
            }
            rng.InsertElementWithRequired("ProtocolSites");
        }
        if (!rng.FindInsertLocation("OrgSite", true)) {
            Application.Alert("Can't insert OrgSite element");
            return; 
        }
        rng.InsertWithTemplate("OrgSite");
        rng.Select();
    }
    insertParticipatingOrg();
  ]]>
</MACRO>

<MACRO  name="Next Lead Org"
        lang="JScript" 
        desc="Move to the next lead organization in the protocol"
        hide="false">
  <![CDATA[
    function nextLeadOrg() {
        var rng = ActiveDocument.Range;
        if (!rng.MoveToElement("ProtocolLeadOrg", true)) {
            Application.Alert("No more ProtocolLeadOrg elements found.");
            return;
        }
        rng.Select();
    }
    nextLeadOrg();
  ]]>
</MACRO>

<MACRO  name="Next External Site"
        lang="JScript" 
        desc="Move to the next external site in the protocol"
        hide="false">
  <![CDATA[
    function nextExternalSite() {
        var rng = ActiveDocument.Range;
        if (!rng.MoveToElement("ExternalSite", true)) {
            Application.Alert("No more ExternalSite elements found.");
            return;
        }
        rng.Select();
    }
    nextExternalSite();
  ]]>
</MACRO>

<MACRO  name="CDR Get Org Postal Address"
        lang="JScript" 
        desc="Retrieve org address from fragment link"
        hide="false">
  <![CDATA[

    if (cdrObj == null) {
        Application.Alert("You are not logged on to the CDR");
    }
    else {
        cdrObj.getOrgAddress();
    }

  ]]>
</MACRO>

<MACRO  name="CDR Persons Linking to Org Address Fragment"
        lang="JScript" 
        desc="Finds Person documents linking to current Org location."
        hide="false">
  <![CDATA[

    function personsLinkingToOrgLoc() {
        var rng = ActiveDocument.Range
        var elem = rng.ContainerNode;
        if (elem) {
            if (elem.nodeName != "Location") {
                if (rng.IsParentElement("Location")) {
                    if (rng.MoveToElement("Location", false)) {
                        elem = rng.ContainerNode;
                    }
                }
            }
            if (elem.nodeName == "Location") {
                var id = elem.getAttribute("cdr:id");
                var nodes = 
                    Application.ActiveDocument.getElementsByTagName("DocId");
                if (nodes.length < 1) {
                    Application.Alert(
                        "This is a new document without a document ID.");
                    return;
                }
                else {
                    var elem = nodes.item(0);
                    var val  = getTextContent(elem);
                    var url = CdrCgiBin + "PersonOrgLocLinks.py?FragLink=" + 
                              val + "%23" + id;
                    cdrObj.showPage(url);
                }
            }
        }
    }

    personsLinkingToOrgLoc();

  ]]>
</MACRO>

<MACRO  name="Remember Org Postal Address"
        lang="JScript" 
        desc="Stores org postal address in an internal clipboard."
        hide="false">
  <![CDATA[

    function rememberOrgPostalAddress() {
        var rng = getElemRange("Location");
        if (!rng) {
            Application.Alert(
                "Current position is not within an org location.");
            return;
        }
        locElem = rng.ContainerNode;
        addrList = locElem.getElementsByTagName("PostalAddress");
        if (!addrList.length) {
            Application.Alert("No PostalAddress element found.");
            return;
        }
        //CdrOrgAddressClipboard = addrList.item(0);
        rng.MoveToElement("PostalAddress");
        rng.SelectElement();
        CdrOrgAddressClipboard = rng.Text;
        //Application.Alert("CB: " + CdrOrgAddressClipboard);
    }

    rememberOrgPostalAddress();

  ]]>
</MACRO>

<MACRO  name="Paste Org Address Elements"
        lang="JScript" 
        desc="Pastes org address elements from internal clipboard."
        hide="false">
  <![CDATA[

    /*
     * This is necessary because the DOM interface doesn't support
     * cloning elements for use in another document.
     *
     * XXX Doesn't work.  Another bug in XMetaL.
     */
    function cloneElementAcrossDocs(newDoc, oldElem) {
        if (!oldElem || !newDoc) return null;
        // Application.Alert("creating a new " + oldElem.nodeName);
        var newElem = newDoc.createElement(oldElem.nodeName);
        if (!newElem) return null;
        var attrs = oldElem.attributes;
        for (var i = 0; i < attrs.length; ++i) {
            var attr = attrs.item(i);
            newElem.setAttribute(attr.nodeName, attr.nodeValue);
        }
        var child = oldElem.firstChild;
        while (child) {
            if (child.nodeType == 1) { // DOMElement
                var newChild = cloneElementAcrossDocs(newDoc, child);
                newElem.appendChild(newChild);
            }
            else if (child.nodeType == 3) { // DOMText
                var textNode = newDoc.createTextNode(child.nodeValue);
                newElem.appendChild(textNode);
            }
            else if (child.nodeType == 7) { // DOMProcessingInstruction
                var piNode = newDoc.createProcessingInstruction(child.target,
                                                                child.data);
                newElem.appendChild(piNode);
            }
            else if (child.nodeType == 8) { // DOMComment
                var cmt = newDoc.createComment(child.data);
                newElem.appendChild(cmt);
            }
            else if (child.nodeType == 505) { // DOMCharacterReference
                Application.Alert("Please inform development staff that " +
                                  "a DOM character reference was found.");
            }
            child = child.nextSibling;
        }
        return newElem;
    }

    function pasteOrgAddressElements() {

        if (!CdrOrgAddressClipboard) {
            Application.Alert("Org address clipbard is empty!");
            return;
        }
        var rng = getElemRange("GenericPerson");
        if (!rng)
            rng = getElemRange("OverallContact");
        if (!rng) {
            Application.Alert(
                "Current position is not within a GenericPerson " +
                " or OverallContact element.");
            return;
        }

        var gpElem = rng.ContainerNode;
        var addrList = gpElem.getElementsByTagName("PostalAddress");
        if (!addrList.length) {
            if (!rng.FindInsertLocation("PostalAddress")) {
                Application.Alert("No PostalAddress element found.");
                return;
            }
            rng.Select();
        }
        else {
            rng.MoveToElement("PostalAddress");
            rng.SelectElement();
        }
        rng.Text = CdrOrgAddressClipboard;
        return;
        /*
         * Doesn't work: bug in XMetaL.
        var paElem = addrList.item(0);
        var cdElem = paElem.parentNode;
        var newNode = cloneElementAcrossDocs(ActiveDocument,
                                             CdrOrgAddressClipboard);
        if (!newNode) {
            Application.Alert("Failure cloning address node");
            return;
        }
        Application.Alert("Replacing " + paElem.nodeName +
                          " with " + newNode.nodeName);
        cdElem.replaceChild(newNode, paElem);
         */
    }

    pasteOrgAddressElements();

  ]]>
</MACRO>

<MACRO  name="Term Hierarchy"
        lang="JScript" 
        desc="Web interface for displaying Term document hierarchies"
        hide="false">
  <![CDATA[

    function termHierarchyDisplay() {
        var url = CdrCgiBin + "TermHierarchy.py";
        if (ActiveDocument && ActiveDocument.doctype.name == "Term") {
            var nodes = 
                Application.ActiveDocument.getElementsByTagName("DocId");
            if (nodes.length > 0) {
                var elem  = nodes.item(0);
                var docId = getTextContent(elem);
                url += "?DocId=" + docId;
            }
        }
        cdrObj.showPage(url);
    }

    termHierarchyDisplay();

  ]]>
</MACRO>

<MACRO  name="CDR Terminology Usage Report"
        lang="JScript" 
        desc="Report listing documents which are indexed by this term"
        hide="false">
  <![CDATA[

    function termUsageReport() {
        if (ActiveDocument && ActiveDocument.doctype.name == "Term") {
            var nodes = 
                Application.ActiveDocument.getElementsByTagName("DocId");
            if (nodes.length > 0) {
                var elem  = nodes.item(0);
                var docId = getTextContent(elem);
                var url = CdrCgiBin + "TermUsage.py?DocId=" + docId;
                cdrObj.showPage(url);
            }
            else {
                Application.Alert("This is a new document.");
            }
        }
        else {
            Application.Alert("No Term document found.");
        }
    }

    termUsageReport();

  ]]>
</MACRO>

<MACRO  name="Insert Current Date"
        lang="JScript" 
        key="Alt+D" 
        desc="Inserts the current date as text content of current elem"
        hide="false">
  <![CDATA[

    function insCurrentDate() {
        if (Selection != null) {
            // Selection.SelectContainerContents();
            str = getCurDateString();
            Selection.Text = str;
        }
    }
    insCurrentDate();

  ]]>
</MACRO>

<MACRO  name="Insert Current Date and Time"
        lang="JScript" 
        desc="Inserts the current date/time as text content of current elem"
        hide="false">
  <![CDATA[

    function insCurrentDateTime() {
        if (Selection != null) {
            // Selection.SelectContainerContents();
            str = getCurDateTimeString();
            Selection.Text = str;
        }
    }
    insCurrentDateTime();

  ]]>
</MACRO>

y<MACRO  name="Insert User ID"
        lang="JScript" 
        desc="Inserts the login name as text content of current elem"
        key="Alt+U" 
        hide="false">
  <![CDATA[

    function insUserName() {
        if (Selection != null) {
            Selection.Text = CdrUserName;
        }
    }
    insUserName();

  ]]>
</MACRO>

<MACRO  name="Insert DrugName Element"
        lang="JScript" 
        desc="Wraps the current selection with DrugName tags"
        hide="false">
    Selection.InsertElement("DrugName");
</MACRO>

<MACRO  name="Insert ForeignWord Element"
        lang="JScript" 
        desc="Wraps the current selection with ForeignWord tags"
        hide="false">
    Selection.InsertElement("ForeignWord");
</MACRO>

<MACRO  name="Insert GeneName Element"
        lang="JScript" 
        desc="Wraps the current selection with GeneName tags"
        hide="false">
    Selection.InsertElement("GeneName");
</MACRO>

<MACRO  name="Insert ScientificName Element"
        lang="JScript" 
        desc="Wraps the current selection with ScientificName tags"
        hide="false">
    Selection.InsertElement("ScientificName");
</MACRO>

<MACRO  name="Insert Emphasis Element"
        lang="JScript" 
        desc="Wraps the current selection with Emphasis tags"
        hide="false">
    Selection.InsertElement("Emphasis");
</MACRO>

<MACRO  name="Insert Strong Element"
        lang="JScript" 
        desc="Wraps the current selection with Strong tags"
        hide="false">
    Selection.InsertElement("Strong");
</MACRO>

<MACRO  name="Insert Subscript Element"
        lang="JScript" 
        desc="Wraps the current selection with Subscript tags"
        hide="false">
    Selection.InsertElement("Subscript");
</MACRO>

<MACRO  name="Insert Superscript Element"
        lang="JScript" 
        desc="Wraps the current selection with Superscript tags"
        hide="false">
    Selection.InsertElement("Superscript");
</MACRO>

<MACRO name="Administrative Subsystem" 
       lang="JScript" 
       id="1019">
  <![CDATA[
    function administrativeSubsystem() {
        
        var url = CdrCgiBin + "Admin.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    administrativeSubsystem();
  ]]>
</MACRO>

<MACRO name="New CDR Document" 
       lang="JScript" 
       id="2028">
  <![CDATA[
    Documents.Add();
  ]]>
</MACRO>

<MACRO name="Print" 
       lang="JScript" 
       id="2009">
  <![CDATA[
        // This didn't work
        //Application.RunKeyedMacro("Ctrl+P");
    function doPrint() {
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var fileMenu     = menuControls.item("File");
        var controls     = fileMenu.Controls;
        var printCtrl    = null;
        for (i = 1; i < controls.Count; ++i) {
            if (controls.item(i).TooltipText.indexOf("Ctrl+P") != -1) {
                printCtrl = controls.item(i);
                break;
            }
        }
        if (printCtrl) {
            Application.Alert("got a live one!");
            printCtrl.Execute();
        }
        return; 
    }
    // This doesn't work, either.  Confirmed by Derek of SoftQuad Technical
    // Support email 24 Oct 2001.  He has filed a bug report.
    // doPrint();
    Application.Alert("Sorry.  Due to a bug in XMetaL, you must invoke the\n"
        + "Print dialog box from the File menu or using Control+P.");
  ]]>
</MACRO>

<MACRO name="PubMed Browse" 
       lang="JScript" 
       id="2022">
  <![CDATA[
    function searchPubMed() {
        var url = "http://www.ncbi.nlm.nih.gov/entrez/";
        cdrObj.showPage(url);
    }
    searchPubMed();
  ]]>
</MACRO>

<MACRO name="Insert CitationLink" 
       lang="JScript" >
  <![CDATA[
    Selection.InsertWithTemplate("CitationLink")
  ]]>
</MACRO>

<MACRO name="Itemized List" 
       key="Alt+L" 
       lang="JScript" 
       id="20404">
  <![CDATA[
    Selection.InsertElement("ItemizedList");
    Selection.ElementAttribute("Style", "ItemizedList", 0) = "bullet";
    Selection.InsertWithTemplate("ListTitle");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Selection.MoveUp();
    Selection.MoveUp();
  ]]>
</MACRO>

<MACRO name="Ordered List" 
       key="Alt+O" 
       lang="JScript" 
       id="20412">
  <![CDATA[
    Selection.InsertElement("OrderedList");
    Selection.ElementAttribute("Style", "OrderedList", 0) = "Arabic";
    Selection.InsertWithTemplate("ListTitle");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Application.Run("Jump Past Element");
    Selection.InsertWithTemplate("ListItem");
    Selection.MoveUp();
    Selection.MoveUp();
  ]]>
</MACRO>

<MACRO name="Table"
       lang="JScript">
  <![CDATA[
    function doTable() {
        var cmdBars      = Application.CommandBars;
        var menuBar      = cmdBars.item("Menu bar");
        var menuControls = menuBar.Controls;
        var tableMenu    = menuControls.item("Table");
        var controls     = tableMenu.Controls;
        var tableWizard  = controls.item(1);
        tableWizard.Execute();
        /*
         * Don't do this, because the Execute() method above happens
         * asynchronously, which means that if there's already a Title
         * element somewhere above, the cursor will jump to it before
         * the table insertion has finished.
         *
         * if (ActiveDocument) {
         *     var rng = ActiveDocument.Range;
         *     if (rng) {
         *         rng.MoveToElement('Title', false);
         *         rng.Select();
         *     }
         * }
         */
    }
    doTable();
    //Application.Alert("Sorry.  Due to a bug in XMetaL, you must invoke the\n"
    //    + "Table Wizard from the Table menu.");
  ]]>
</MACRO>

<MACRO name="CDR Help" 
       lang="JScript">
  <![CDATA[
    cdrObj.showPage(CdrCgiBin + "Help.py")
  ]]>
</MACRO>

<MACRO name="Jump Past Element" 
       key="Ctrl+Alt+Shift+P"
       lang="JScript">
  <![CDATA[
    function jumpPastElement() {
        try {
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                if (rng) {
                    rng.SelectAfterContainer();
                    rng.Select();
                }
            }
        }
        catch (e) {}
    }
    jumpPastElement();
  ]]>
</MACRO>

<MACRO name="Jump Before Element" 
       key="Ctrl+Alt+Shift+B"
       lang="JScript">
  <![CDATA[
    function jumpBeforeElement() {
        try {
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                if (rng) {
                    rng.SelectBeforeContainer();
                    rng.Select();
                }
            }
        }
        catch (e) {}
    }
    jumpBeforeElement();
  ]]>
</MACRO>

<MACRO name="On_Document_Activate"
       lang="JScript">
  <![CDATA[
    function adjustToolbars() {
        hideToolbars();
        var docType = ActiveDocument.doctype;
        if (toolbars[docType.name] != null) {
            toolbars[docType.name].Visible = true;
        }
    }
    if (Application.VersionNumber < 4.5)
        adjustToolbars();
  ]]>
</MACRO>

<MACRO name="On_Document_Close"
       lang="JScript">
  <![CDATA[
    if (Application.VersionNumber < 4.5)
        hideToolbars();
    //cdrObj.setTitleBar();
  ]]>
</MACRO>

<MACRO name="On_Document_Open_View" 
       lang="JScript">
  <![CDATA[
    //Application.Alert("entering On_Document_Open_View");
    // Always open documents in Normal view
    if (ActiveDocument.ViewType != 0) {
        ActiveDocument.ViewType = 0;
    }
    //Application.Alert("leaving On_Document_Open_View");
  ]]>
</MACRO>

<MACRO name="New Current Org Status" 
       lang="JScript">
  <![CDATA[
    function newCurrentOrgStatus() {
        Selection.MoveRight();
        Selection.MoveLeft();
        var rng = ActiveDocument.Range;
        var savePos = ActiveDocument.Range;
        rng.SelectElement();
        var oldStatusElem = rng.ContainerNode;
        if (oldStatusElem.nodeName != "CurrentOrgStatus") {
            Application.Alert("Not in CurrentOrgStatus");
            return;
        }
        rng.SelectElement();
        elemText = rng.Text;
        elemText = elemText.replace("<CurrentOrgStatus", "<PreviousOrgStatus");
        elemText = elemText.replace("</CurrentOrgStatus>", 
                                    "</PreviousOrgStatus>");
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;
        var newElem = "<CurrentOrgStatus>"
                    + "<StatusName></StatusName>"
                    + "<StatusDate>" + getCurDateString() + "</StatusDate>"
                    + "<Comment>Your comment here ...</Comment>"
                    + "<EnteredBy>" + CdrUserName + "</EnteredBy>"
                    + "<EntryDate>" + getCurDateString() + "</EntryDate>"
                    + "</CurrentOrgStatus>";
        rng.PasteString(newElem + elemText);
        savePos.Select();
        Selection.MoveRight();
        Selection.MoveLeft();
        ActiveDocument.RulesChecking = rulesChecking;
    }
    newCurrentOrgStatus();
  ]]>
</MACRO>

<MACRO name="Insert PatientCharacteristics" 
       lang="JScript">
  <![CDATA[
    function insertPatientCharacteristics() {
        //Selection.MoveRight();
        //Selection.MoveLeft();
        var rng = ActiveDocument.Range;
        var savePos = ActiveDocument.Range;
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;
        var newElems = "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Age</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Performance status</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Life expectancy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Hematopoietic</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Hepatic</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Renal</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Cardiovascular</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Pulmonary</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Other</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>";
  
        rng.PasteString(newElems);
        savePos.Select();
        ActiveDocument.RulesChecking = rulesChecking;
    }
    insertPatientCharacteristics();
  ]]>
</MACRO>

<MACRO name="Insert PriorConcurrentTherapy" 
       lang="JScript">
  <![CDATA[
    function insertPriorConcurrentTherapy() {
        //Selection.MoveRight();
        //Selection.MoveLeft();
        var rng = ActiveDocument.Range;
        var savePos = ActiveDocument.Range;
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;
        var newElems = "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Biologic therapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Chemotherapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Endocrine therapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Radiotherapy</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Surgery</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>"
                     + "<ItemizedList Style='bullet'>"
                     + "<ListTitle>Other</ListTitle>"
                     + "<ListItem></ListItem>"
                     + "</ItemizedList>";
        rng.PasteString(newElems);
        savePos.Select();
        ActiveDocument.RulesChecking = rulesChecking;
    }
    insertPriorConcurrentTherapy();
  ]]>
</MACRO>

<MACRO name="Reset Contact Information" 
       lang="JScript">
  <![CDATA[
    Application.Alert("Stub for Reset Contact Information Macro");
  ]]>
</MACRO>

<MACRO name="Country QC Report" 
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId
                + "&Filter=name:Country QC Report Filter";
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="TermSet QC Report" 
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId
                + "&Filter=name:TermSet QC Report Filter";
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="Generate QC Report" 
       lang="JScript">
  <![CDATA[
    function qcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        cdrObj.showPage(url);
    }
    qcReport();
  ]]>
</MACRO>

<MACRO name="Protocol HP QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolHpQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "ProtocolHpQcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        cdrObj.showPage(url);
    }
    protocolHpQcReport();
  ]]>
</MACRO>

<MACRO name="Protocol Patient QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolPatientQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "ProtocolPatientQcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        cdrObj.showPage(url);
    }
    protocolPatientQcReport();
  ]]>
</MACRO>

<MACRO name="Protocol Admin QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolAdminQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId +
                "&Filter=set:QC InScopeProtocol Admin Set";
        cdrObj.showPage(url);
    }
    protocolAdminQcReport();
  ]]>
</MACRO>

<MACRO name="Protocol Citations QC Report" 
       lang="JScript">
  <![CDATA[
    function protocolCitationsQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "ProtocolCitationsQcReport.py?Session="
                + CdrSession + "&DocId=" + docId;
        cdrObj.showPage(url);
    }
    protocolCitationsQcReport();
  ]]>
</MACRO>

<MACRO name="Generate Mailer" 
       lang="JScript">
  <![CDATA[
    function generateMailer() {
        var url = CdrCgiBin + "Mailers.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    generateMailer();
  ]]>
</MACRO>

<MACRO name="Go To Admin Info Section"
       lang="JScript">
  <![CDATA[
    if (Selection != null) {
        Selection.MoveToDocumentStart();
        Selection.MoveToElement("CurrentProtocolStatus");
        Selection.SelectContainerContents();
    }
  ]]>
</MACRO>

<MACRO name="Go To Patient Abstract"
       lang="JScript">
  <![CDATA[
    if (Selection != null) {
        Selection.MoveToDocumentStart();
        Selection.MoveToElement("Patient");
        Selection.SelectContainerContents();
    }
  ]]>
</MACRO>

<MACRO name="Go To Scientific Info Section"
       lang="JScript">
  <![CDATA[
    if (Selection != null) {
        Selection.MoveToDocumentStart();
        Selection.MoveToElement("ProtocolAbstract");
    }
  ]]>
</MACRO>

<MACRO name="Go To Brief Summary"
       lang="JScript">
  <![CDATA[
    if (Selection != null) {
        Selection.MoveToDocumentStart();
        Selection.MoveToElement("BriefSummary");
    }
  ]]>
</MACRO>

<MACRO name="Protocol Merge" 
       lang="JScript">
  <![CDATA[
    function protocolMerge() {
        var url = CdrCgiBin + "MergeProt.py?Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    protocolMerge();
  ]]>
</MACRO>

<MACRO name="Search PubMed" 
       lang="JScript">
  <![CDATA[
    function searchPubMed() {
        var url = "http://www.ncbi.nlm.nih.gov/entrez/";
        cdrObj.showPage(url);
    }
    searchPubMed();
  ]]>
</MACRO>

<MACRO name="New Summary Section" 
       key ="" 
       lang="JScript" 
       id  ="1247">
  <![CDATA[
    function newSection() {
        try {
            if (!cdrObj) {
                Application.Alert("Not logged on to the CDR");
                return;
            }
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                var i = 0; // Safety measure...
                if (rng) { rng.Collapse(); }
                while (rng && i < 50) {
                    if (rng.CanInsert("SummarySection")) {
                        if (cdrIsReadOnly()) {
                            var msg = "Can't insert into readonly document";
                            Application.Alert(msg);
                            break;
                        }
                        rng.InsertWithTemplate("SummarySection");
                        rng.Select();
                        break;
                    }
                    if (!rng.ContainerNode) { 
                        var msg = "Can't find a place to insert Section";
                        Application.Alert(msg);
                        break; 
                    }
                    rng.SelectAfterContainer();
                    i++;
                }
            }
        }
        catch (e) { }
    }
    newSection();
  ]]>
</MACRO>

<MACRO name="Next Summary Section" 
       key ="Ctrl+Alt+N" 
       lang="JScript" 
       id  ="2033">
  <![CDATA[
    Selection.MoveToElement("SummarySection");
  ]]>
</MACRO>

<MACRO name="Previous Summary Section" 
       lang="JScript" 
       id  ="2034" 
       key ="Ctrl+Alt+P">
  <![CDATA[
    Selection.MoveToElement("SummarySection", false);
  ]]>
</MACRO>

<MACRO name="Higher Summary Section" 
       lang="JScript" 
       id  ="2035" 
       key ="Ctrl+Alt+H">
  <![CDATA[
    function higherSection() {
        try {
            if (ActiveDocument) {
                var rng = ActiveDocument.Range;
                var foundOne = false;
                var i = 0; // Safety measure...
                while (rng && i < 50) {
                    var node = rng.ContainerNode;
                    if (!node) { 
                        var msg = "Not inside a nested SummarySection";
                        Application.Alert(msg);
                        break; 
                    }
                    if (node.nodeName == "SummarySection") {
                        if (foundOne) {
                            rng.SelectBeforeContainer();
                            rng.Select();
                            break;
                        }
                        foundOne = true;
                    }
                    rng.SelectBeforeContainer();
                    i++;
                }
            }
        }
        catch (e) { }
    }
    higherSection();
  ]]>
</MACRO>

<MACRO name="Create Summary Markup Report" 
       lang="JScript">
  <![CDATA[
    function createSummaryMarkupReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    createSummaryMarkupReport();
  ]]>
</MACRO>

<MACRO name="Create HTML for Board" 
       lang="JScript">
  <![CDATA[
    function createHtmlForBoard() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "Filter.py?DocId=" + docId;
        cdrObj.showPage(url);
    }
    Application.Alert("Don't have filters for this command yet.");
    //createHtmlForBoard();
  ]]>
</MACRO>

<MACRO name="Bold Underline Report" 
       lang="JScript">
  <![CDATA[
    function boldUnderlineReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=bu&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    boldUnderlineReport();
  ]]>
</MACRO>

<MACRO name="Redline Strikeout Report" 
       lang="JScript">
  <![CDATA[
    function redlineStrikeoutReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=rs&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    redlineStrikeoutReport();
  ]]>
</MACRO>

<MACRO name="Glossary RS Report" 
       lang="JScript">
  <![CDATA[
    function glossaryRSReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Current document ID not found");
            return;
        }
        var url = CdrCgiBin + "QcReport.py?DocType=GlossaryTerm&DocId="
                            + docId
                            + "&ReportType=rs&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    glossaryRSReport();
  ]]>
</MACRO>
<MACRO name="Patient Summary RS QC Report" 
       lang="JScript">
  <![CDATA[
    function patientSummaryRsQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        /*
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId +
                "&Filter=name:Summary-Copy+XML+for+Patient+Summary+Report" +
                "&Filter1=name:Patient+Summary+QC+Report+Filter";
        */
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=pat&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    patientSummaryRsQcReport();
  ]]>
</MACRO>

<MACRO name="Patient Summary BU QC Report" 
       lang="JScript">
  <![CDATA[
    function patientSummaryBuQcReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        /*
        var url = CdrCgiBin + "Filter.py?Session="
                + CdrSession + "&DocId=" + docId +
                "&Filter=name:Summary-Copy+XML+for+Patient+Summary+Report" +
                "&Filter1=name:Patient+Summary+QC+Report+Filter";
        */
        var url = CdrCgiBin + "QcReport.py?DocType=Summary&DocId="
                            + docId
                            + "&ReportType=patbu&Session="
                            + CdrSession;
        cdrObj.showPage(url);
    }
    patientSummaryBuQcReport();
  ]]>
</MACRO>

<MACRO name="Generate Summary Mailers"
       lang="JScript">
  <![CDATA[
    function generateSummaryMailers() {
        var url = CdrCgiBin + "PDQMailerRequestForm.py?Session="
            + CdrSession;
        cdrObj.showPage(url);
    }
    generateSummaryMailers();
  ]]>
</MACRO>

<MACRO name="Document History Report"
       lang="JScript">
  <![CDATA[
    function documentHistoryReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "DocVersionHistory.py?Session="
                + CdrSession
                + "&DocId="
                + docId;
        cdrObj.showPage(url);
    }
    documentHistoryReport();
  ]]>
</MACRO>

<MACRO name="Insert DateLastModified" 
       lang="JScript" >
  <![CDATA[
    function insertDateLastModified() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement("DateLastModified", false)) {
            if (!rng.FindInsertLocation("DateLastModified", false)) {
                Application.Alert("Can't insert DateLastModified element");
                return; 
            }
            rng.InsertWithTemplate("DateLastModified");
        }
        rng.Select();
    }
    insertDateLastModified();
  ]]>
</MACRO>

<MACRO name="Insert ProtocolAmendmentInformation" 
       lang="JScript" >
  <![CDATA[
    function insertProtocolAmendmentInformation() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("ProtocolAmendmentInformation", false)) {
            Application.Alert(
                    "Can't insert ProtocolAmendmentInformation element");
                return; 
        }
        rng.InsertElement("ProtocolAmendmentInformation");
        rng.InsertWithTemplate("ProtocolAmendment");
        rng.Select();
    }
    insertProtocolAmendmentInformation();
  ]]>
</MACRO>

<MACRO name="Undo Last Edit" 
       lang="JScript" >
  <![CDATA[
    if (ActiveDocument)
        ActiveDocument.Undo();
  ]]>
</MACRO>

<MACRO name="NHL Text" 
       lang="JScript">
  <![CDATA[
    function nhlText() {
        var rng = ActiveDocument.Range;
        if (!rng.IsParentElement("DiseaseCharacteristics")) {
            Application.Alert("This macro can only be used within the "
                    + "DiseaseCharacteristics element");
            return;
        }
        if (!rng.FindInsertLocation("Para")) {
            Application.Alert("Unable to insert new Para element");
            return;
        }
        rng.InsertElement("Para");
        rng.InsertElement("Note");
        rng.Text = "A new classification scheme for adult non-Hodgkin's "
                 + "lymphoma has been adopted by PDQ.  The terminology "
                 + "of \"indolent\" or \"aggressive\" lymphoma will "
                 + "replace the former terminology of \"low\", "
                 + "\"intermediate\", or \"high\" grade lymphoma. "
                 + "However, this protocol uses the former terminology.";
    }
    nhlText();
  ]]>
</MACRO>

<MACRO name="Change Participating Site Statuses" 
       lang="JScript">
  <![CDATA[
    function changeSiteStatuses() {
        var rng = ActiveDocument.Range;
        if (!rng.IsParentElement("ProtocolLeadOrg")) {
            Application.Alert("This macro can only be used within a "
                    + "ProtocolLeadOrg element");
            return;
        }
        if (!rng.MoveToElement("ProtocolLeadOrg", false)) {
            Application.Alert("Can't find ProtocolLeadOrg element.");
            return;
        }
        var node = rng.ContainerNode;
        var elemList = node.getElementsByTagName("CurrentOrgStatus");
        if (!elemList || !elemList.length) {
            Application.Alert("Can't find CurrentOrgStatus element.");
            return;
        }
        elemList = elemList.item(0).getElementsByTagName("StatusName");
        if (!elemList || !elemList.length) {
            Application.Alert("Can't find StatusName element.");
            return;
        }
        var status = getTextContent(elemList.item(0));
        if (!status) {
            Application.Alert("Lead org status has not yet been set.");
            return;
        }
        var yes = 6;
        var no = 7;
        var response = no;
        var displayOkNoCancelButtons = 3;
        var useWarningQueryIcon = 32;
        var dlgConfig = displayOkNoCancelButtons + useWarningQueryIcon;
        var dlgMsg = "Set participating site statuses to " + status + "?";
        var dlgTitle = "Adjust Participating Site Statuses";
        response = Application.MessageBox(dlgMsg, dlgConfig, dlgTitle);
        if (response != yes)
            return;
        var sitesList = node.getElementsByTagName("ProtocolSites");
        if (!sitesList || !sitesList.length) {
            Application.Alert("Can't find ProtocolSites element.");
            return;
        }
        var numStatuses = 0;
        elemList = sitesList.item(0).getElementsByTagName("OrgSite");
        for (var i = 0; elemList && i < elemList.length; ++i) {
            var site = elemList.item(i);
            var statusList = site.getElementsByTagName("OrgSiteStatus");
            if (statusList && statusList.length) {
                var statusNode = statusList.item(0);
                rng.selectNodeContents(statusNode);
                var oldSetting = rng.WritePermittedContainer;
                rng.WritePermittedContainer = true;
                rng.PasteString(status);
                rng.WritePermittedContainer = oldSetting;
                numStatuses += 1;
            }
        }
        elemList = sitesList.item(0).getElementsByTagName(
                                                      "PrivatePracticeSite");
        for (var i = 0; elemList && i < elemList.length; ++i) {
            var site = elemList.item(i);
            var statusList = site.getElementsByTagName(
                                                "PrivatePracticeSiteStatus");
            if (statusList && statusList.length) {
                var statusNode = statusList.item(0);
                rng.selectNodeContents(statusNode);
                var oldSetting = rng.WritePermittedContainer;
                rng.WritePermittedContainer = true;
                rng.PasteString(status);
                rng.WritePermittedContainer = oldSetting;
                numStatuses += 1;
            }
        }
        Application.Alert("Status set for " + numStatuses + 
                " participating sites.");
    }
    changeSiteStatuses();
  ]]>
</MACRO>

<MACRO name="Insert Mailer Response" 
       lang="JScript" >
  <![CDATA[
    function insertMailerResponse() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("Response", false)) {
            Application.Alert(
                    "Can't insert Response element");
                return; 
        }
        rng.InsertWithTemplate("Response");
        rng.Select();
    }
    insertMailerResponse();
  ]]>
</MACRO>

<MACRO name="Insert PDQ Board Info" 
       lang="JScript" >
  <![CDATA[
    function insertPdqBoardInfo() {
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("PDQBoardInformation", false)) {
            Application.Alert(
                    "Can't insert PDQBoardInformation element");
                return; 
        }
        var newElems = "<PDQBoardInformation>"
                     + "<BoardManager>"
                     + "<?xm-replace_text {Enter Board Manager name} ?>"
                     + "</BoardManager>"
                     + "<BoardManagerPhone>"
                     + "<?xm-replace_text {Enter Board Manager phone} ?>"
                     + "</BoardManagerPhone>"
                     + "<BoardManagerEmail>"
                     + "<?xm-replace_text {Enter Board Manager e-mail} ?>"
                     + "</BoardManagerEmail>"
                     + "<BoardMeetingDate>"
                     + "<Year>"
                     + "<?xm-replace_text {Enter year for set of meeting "
                     + "dates} ?></Year>"
                     + "<Date>"
                     + "<?xm-replace_text {Enter each meeting date for the"
                     + " year as a separate occurrence} ?>"
                     + "</Date>"
                     + "<DayTime>"
                     + "<?xm-replace_text {Enter meeting day and time}"
                     + " ?></DayTime>"
                     + "</BoardMeetingDate>"
                     + "</PDQBoardInformation>";
        rng.PasteString(newElems);
        rng.Select();
    }
    insertPdqBoardInfo();
  ]]>
</MACRO>

<MACRO name="Set Non-Public" 
       lang="JScript" >
  <![CDATA[
    function setNonPublic() {
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "Public")) {
            Application.Alert(
                "Current element does not have a Public attribute.");
            return;
        }
        
        var holdFlag = Selection.ReadOnlyContainer;
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        container.setAttribute("Public", "No");
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = holdFlag;
    }
    setNonPublic();
  ]]>
</MACRO>

<MACRO name="Set Public" 
       lang="JScript" >
  <![CDATA[
    function setPublic() {
        var container = Selection.ContainerNode;
        if (!container || container.nodeType != 1) { // Look for element.
            Application.Alert("Can't find current element.");
            return;
        }
        docType = ActiveDocument.doctype;
        if (!docType.hasAttribute(container.nodeName, "Public")) {
            Application.Alert(
                "Current element does not have a Public attribute.");
            return;
        }
        
        var holdFlag = Selection.ReadOnlyContainer;
        Selection.ReadOnlyContainer = false;
        gEditingCdrLink = true;
        container.removeAttribute("Public");
        gEditingCdrLink = false;
        Selection.ReadOnlyContainer = holdFlag;
    }
    setPublic();
  ]]>
</MACRO>

<MACRO name="Mailer History" 
       lang="JScript" >
  <![CDATA[
    function mailerHistory() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "MailerHistory.py?Session="
                + CdrSession
                + "&DocId="
                + docId;
        cdrObj.showPage(url);
    }
    mailerHistory();
  ]]>
</MACRO>

<MACRO name="Linked Docs Report"
       lang="JScript" >
  <![CDATA[
    function linkedDocsReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "LinkedDocs.py?Session="
                + CdrSession
                + "&DocId="
                + docId
                + "&LinkingDocType=Any+Type";
        cdrObj.showPage(url);
    }
    linkedDocsReport();
  ]]>
</MACRO>

<MACRO name="Audit Trail Report" 
       lang="JScript" >
  <![CDATA[
    function auditTrailReport() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "AuditTrail.py?id=" + docId;
        cdrObj.showPage(url);
    }
    auditTrailReport();
  ]]>
</MACRO>

<MACRO name="Verify Specialties" 
       lang="JScript" >
    cdrObj.showPage("https://specialistsonline.abms.org/");
</MACRO>

<MACRO name="Back Out Rejected Markup" 
       lang="JScript" >
  <![CDATA[

    //----------------------------------------------------------------------
    // Drop marked changes.
    //----------------------------------------------------------------------
    function backOutRejectedMarkup()
    {
        var r = ActiveDocument.Range;
        r.MoveToDocumentStart();
        while (r.MoveToElement("Deletion")) {
            var elem = r.ContainerNode;
            var revLevel = elem.getAttribute("RevisionLevel");
            if (revLevel == "rejected")
                r.RemoveContainerTags();
        }
        r.MoveToDocumentStart();
        while (r.MoveToElement("Insertion")) {
            var elem = r.ContainerNode;
            var revLevel = elem.getAttribute("RevisionLevel");
            if (revLevel == "rejected") {
                r.SelectContainerContents();
                r.Delete();
                r.RemoveContainerTags();
            }
        }
        r = null;
    }

    if (CanRunMacros()) {
        var confirm = Application.Confirm("Do you want to back out all " +
                                          "rejected changes without " +
                                          "reviewing them?");
        if (confirm) {
            backOutRejectedMarkup();
        }
    }

  ]]>
</MACRO>

<MACRO name="CTGovProtocol Diff"
       lang="JScript" >
  <![CDATA[
    function ctGovDiff() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "DiffCTGovProtocol.py?DocId=" + docId;
        cdrObj.showPage(url);
    }
    ctGovDiff();
  ]]>
</MACRO>

<MACRO name="Glossary Phrase Search"
       lang="JScript" >
  <![CDATA[
    function glossaryPhraseSearch() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "GlossaryTermPhrases.py?Session="
                + CdrSession
                + "&Id=" + docId;
        cdrObj.showPage(url);
    }
    glossaryPhraseSearch();
  ]]>
</MACRO>

<MACRO name="Preview Mailer" 
       lang="JScript" >
  <![CDATA[
    function previewMailer() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "SummaryMailerPreview.py?DocId=" + docId;
        var ver = getDocVersion()
        if (ver)
            url += '&ver=' + ver;
        cdrObj.showPage(url);
    }
    previewMailer();
  ]]>
</MACRO>

<MACRO name="Send Missing Protocol Info Mailer" 
       lang="JScript" >
  <![CDATA[
    function sendMissingProtocolInfoMailer() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!CdrSession) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var url = CdrCgiBin + "MissingInfoMailer.py?id=" + docId
                + "&Session=" + CdrSession;
        cdrObj.showPage(url);
    }
    sendMissingProtocolInfoMailer();
  ]]>
</MACRO>

<MACRO name="Glossify Document" 
       lang="JScript" >
  <![CDATA[
    if (!cdrDocReadOnly()) {
        cdrObj.glossify();
        ActiveDocument.FormattingUpdating = true;
    }
  ]]>
</MACRO>

<MACRO name="Add Glossary Phrase" 
       lang="JScript" >
  <![CDATA[
    cdrObj.addGlossaryPhrase();
  ]]>
</MACRO>

<MACRO name="On_CommandBars_Activate"
       lang="JScript">
  <![CDATA[
    function showToolbarForDoctype() {
        var docType = ActiveDocument.doctype;
        if (docType) {
            var bar = toolbars[docType.name];
            if (bar != null && !bar.Visible) {
                bar.Visible = true;
            }
        }
    }
    try { showToolbarForDoctype(); }
    catch (e) {}
  ]]>
</MACRO>

<MACRO name="On_CommandBars_DeActivate"
       lang="JScript">
    try { hideToolbars(); }
    catch (e) {}
</MACRO>

<MACRO name="ShowCDRServer"
       lang="JScript">
    if (cdrObj)
        cdrObj.setTitleBar();
</MACRO>

<MACRO name="Show Doc Blob" 
       lang="JScript" >
  <![CDATA[
    function showDocBlob() {
        var docId  = getDocId();
        var docVer = getDocVersion();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        if (!cdrObj) {
            Application.Alert("Not logged into CDR");
            return;
        }
        cdrObj.launchBlob(docId, docVer ? docVer : "");
    }
    showDocBlob();
  ]]>
</MACRO>

<MACRO name="Show Linked Blob" 
       lang="JScript" >
  <![CDATA[
    function showLinkedBlob() {
        if (!cdrObj) {
            Application.Alert("Not logged into CDR");
            return;
        }
        var docId    = null;
        var elemName = null;
        var rng      = ActiveDocument.Range;
        for (var i in blobLinkElementNames) {
            if (rng.IsParentElement(blobLinkElementNames[i])) {
                elemName = elemNames[i];
                break;
            }
        }
        if (elemName) {
            if (rng.MoveToElement(elemName, false)) {
                var elem = rng.ContainerNode;
                docId = elem.GetAttribute("cdr:ref");
            }
        }
        if (docId)
            cdrObj.launchBlob(docId, "");
        else
            Application.Alert("No link found to a viewable object.");
    }
    showLinkedBlob();
  ]]>
</MACRO>

<MACRO name="Insert Term Set Members" 
       lang="JScript" >
  <![CDATA[
    function makeCdrIdString(cdrId) {
        var padding = "0000000000".substring(0, 10 - cdrId.length);
        return "CDR" + padding + cdrId;
    }
    function insertTermSetMembers() {

        // Get the term IDs from the system clipboard.
        var pieces = Application.Clipboard.Text.split(':');
        if (pieces.length != 2) {
            Application.Alert('Clipboard not ready.');
            return false;
        }
        var generatedFrom = pieces[0];
        if (isNaN(generatedFrom)) {
            Application.Alert('Malformed clipboard contents.');
            return false;
        }
        var termIds = pieces[1].split(' ');
        if (!termIds) {
            Application.Alert('No term IDs in clipboard.');
            return false;
        }

        // Sanity check.
        for (var i in termIds) {
            if (isNaN(termIds[i])) {
                Application.Alert('Clipboard does not contain document IDs.'
                                  + ': ' + termIds[i]);
                return false;
            }
        }

        // Move to the desired location.
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentStart();
        if (!rng.FindInsertLocation("GeneratedFrom")) {
            Application.Alert("Unable to insert GeneratedFrom element.");
            return false;
        }
        rng.PasteString("<GeneratedFrom cdr:ref='" +
                        makeCdrIdString(generatedFrom) +
                        "'/>");
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement('TermSetMember', false)) {
            if (!rng.MoveToElement('TermSetType', false)) {
                Application.Alert('Unable to find location for insertion.');
                return false;
            }
        }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation("TermSetMember", true)) {
            Application.Alert("Unable to insert TermSetMember terms here.");
            return false;
        }

        // Insert the new TermSetMember terms.
        var elemString = "\n";
        for (var i in termIds) {
            var termId = termIds[i];
            var padding = "0000000000".substring(0, 10 - termId.length);
            var idString = "CDR" + padding + termId;
            elemString += "<TermSetMember cdr:ref='" + idString + "'/>\n";
        }
        rng.PasteString(elemString);
        rng.Select();

        return true;
    }

    insertTermSetMembers();
  ]]>
</MACRO>

<MACRO name="Insert BMT Diagnoses" 
       lang="JScript" >
  <![CDATA[
    function insertBmtDiagnoses() {


        // Move to the desired location.
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement('Diagnosis', false)) {
            if (!rng.MoveToElement('AgeText', false)) {
                Application.Alert('Unable to find location for insertion.');
                return false;
            }
        }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation("Diagnosis", true)) {
            Application.Alert("Unable to insert Diagnosis terms here.");
            return false;
        }

        // Insert the new Dianosis terms.
        var elemString = "\n" +
            "<Diagnosis cdr:ref='CDR0000377661'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377660'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377664'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377659'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377655'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039070'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039084'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039083'/>\n" +
            "<Diagnosis cdr:ref='CDR0000335175'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039071'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039086'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039085'/>\n" +
            "<Diagnosis cdr:ref='CDR0000286994'/>\n" +
            "<Diagnosis cdr:ref='CDR0000276487'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039357'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040361'/>\n" +
            "<Diagnosis cdr:ref='CDR0000276485'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039069'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040812'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043711'/>\n" +
            "<Diagnosis cdr:ref='CDR0000372812'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038439'/>\n" +
            "<Diagnosis cdr:ref='CDR0000335177'/>\n" +
            "<Diagnosis cdr:ref='CDR0000372811'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042740'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042739'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042737'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042734'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042738'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042741'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042731'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042732'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042733'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042735'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371959'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371899'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040856'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043389'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041144'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038716'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038678'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040561'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042968'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040557'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040556'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040555'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040559'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040560'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039738'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040232'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042458'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038643'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042198'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038024'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043196'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042197'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038380'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040551'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040552'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040554'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042755'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371961'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038228'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043713'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043706'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040292'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040550'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038791'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037763'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038728'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040080'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041876'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038720'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040808'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041145'/>\n" +
            "<Diagnosis cdr:ref='CDR0000372809'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037801'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037810'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043703'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040535'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042483'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040531'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040530'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040529'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040533'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040534'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038490'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040525'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040526'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040528'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042744'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371902'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037811'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043704'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040524'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038780'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039180'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041974'/>\n" +
            "<Diagnosis cdr:ref='CDR0000340180'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040548'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042945'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040544'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040543'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040542'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040546'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040547'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039108'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038501'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040538'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040539'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040541'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042751'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371903'/>\n" +
            "<Diagnosis cdr:ref='CDR0000043705'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040537'/>\n";
        rng.PasteString(elemString);
        rng.Select();

        return true;
    }

    insertBmtDiagnoses();
  ]]>
</MACRO>

<MACRO name="Insert ALK Diagnoses" 
       lang="JScript" >
  <![CDATA[
    function insertAlkDiagnoses() {


        // Move to the desired location.
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement('Diagnosis', false)) {
            if (!rng.MoveToElement('AgeText', false)) {
                Application.Alert('Unable to find location for insertion.');
                return false;
            }
        }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation("Diagnosis", true)) {
            Application.Alert("Unable to insert Diagnosis terms here.");
            return false;
        }

        // Insert the new Dianosis terms.
        var elemString = "\n" +
            "<Diagnosis cdr:ref='CDR0000039070'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040510'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377661'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377660'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377664'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377659'/>\n" +
            "<Diagnosis cdr:ref='CDR0000377655'/>\n" +
            "<Diagnosis cdr:ref='CDR0000335175'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039071'/>\n" +
            "<Diagnosis cdr:ref='CDR0000276487'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039357'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040361'/>\n" +
            "<Diagnosis cdr:ref='CDR0000276485'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039069'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040812'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039361'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041865'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038439'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039072'/>\n" +
            "<Diagnosis cdr:ref='CDR0000335177'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039350'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041144'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041926'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040079'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041618'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038716'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038678'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040781'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038728'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040080'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041876'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038720'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040808'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041145'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040779'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038490'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037811'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040780'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038501'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039077'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039078'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040078'/>\n";
        rng.PasteString(elemString);
        rng.Select();

        return true;
    }

    insertAlkDiagnoses();
  ]]>
</MACRO>

<MACRO name="Insert AL Diagnoses" 
       lang="JScript" >
  <![CDATA[
    function insertAlDiagnoses() {


        // Move to the desired location.
        var rng = ActiveDocument.Range;
        rng.MoveToDocumentEnd();
        if (!rng.MoveToElement('Diagnosis', false)) {
            if (!rng.MoveToElement('AgeText', false)) {
                Application.Alert('Unable to find location for insertion.');
                return false;
            }
        }
        rng.SelectElement();
        rng.Collapse(0);
        if (!rng.FindInsertLocation("Diagnosis", true)) {
            Application.Alert("Unable to insert Diagnosis terms here.");
            return false;
        }

        // Insert the new Dianosis terms.
        var elemString = "\n" +
            "<Diagnosis cdr:ref='CDR0000041629'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041630'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042785'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042765'/>\n" +
            "<Diagnosis cdr:ref='CDR0000372812'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042137'/>\n" +
            "<Diagnosis cdr:ref='CDR0000372811'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042673'/>\n" +
            "<Diagnosis cdr:ref='CDR0000041199'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040561'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040557'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040556'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040555'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042968'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040559'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040560'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040781'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038380'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040551'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040552'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040554'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042755'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371961'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038228'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040550'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038745'/>\n" +
            "<Diagnosis cdr:ref='CDR0000372809'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040535'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040531'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040530'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040529'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042483'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040533'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040534'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040779'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037770'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040525'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040526'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040528'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042744'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371902'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038226'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040524'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040548'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040544'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040543'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040542'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042945'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040546'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040547'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040780'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037813'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040538'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040539'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040541'/>\n" +
            "<Diagnosis cdr:ref='CDR0000042751'/>\n" +
            "<Diagnosis cdr:ref='CDR0000371903'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038227'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040537'/>\n" +
            "<Diagnosis cdr:ref='CDR0000037790'/>\n";
        rng.PasteString(elemString);
        rng.Select();

        return true;
    }

    insertAlDiagnoses();
  ]]>
</MACRO>

<MACRO name="Open Translated Summary" 
       lang="JScript" >
  <![CDATA[
    function openTranslatedSummary() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        //Application.Alert("My ID: " + docId);
        var translatedSummaryId = cdrObj.getTranslatedDocId(docId);
        if (!translatedSummaryId)
            return;
        //Application.Alert("translation ID: " + translatedSummaryId);
        cdrObj.openCdrDoc(translatedSummaryId, "Current", false);
    }
    openTranslatedSummary();
  ]]>
</MACRO>

<MACRO name="Open Original English Summary" 
       lang="JScript" >
  <![CDATA[
    function openOriginalEnglishSummary() {
        if (!Application.ActiveDocument) { return null; }
        var name = "TranslationOf";
        var nodes = Application.ActiveDocument.getElementsByTagName(name);
        if (nodes.length < 1) {
            Application.Alert("TranslationOf element not found");
            return;
        }
        var elem = nodes.item(0);
        var originalId = elem.getAttribute("cdr:ref");
        if (!originalId) {
            Application.Alert("ID of original summary not found");
            return;
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.openCdrDoc(originalId, "Current", false);
    }
    openOriginalEnglishSummary();
  ]]>
</MACRO>

<MACRO name="Open Patient Summary" 
       lang="JScript" >
  <![CDATA[
    function openPatientSummary() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var patientSummaryId = cdrObj.getPatientDocId(docId);
        if (!patientSummaryId)
            return;
        cdrObj.openCdrDoc(patientSummaryId, "Current", false);
    }
    openPatientSummary();
  ]]>
</MACRO>

<MACRO name="Open HP Summary" 
       lang="JScript" >
  <![CDATA[
    function openHPSummary() {
        if (!Application.ActiveDocument) { return null; }
        var name = "PatientVersionOf";
        var nodes = Application.ActiveDocument.getElementsByTagName(name);
        if (nodes.length < 1) {
            Application.Alert("PatientVersionOf element not found");
            return;
        }
        var elem = nodes.item(0);
        var hpId = elem.getAttribute("cdr:ref");
        if (!hpId) {
            Application.Alert("ID of health professional summary not found");
            return;
        }
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        cdrObj.openCdrDoc(hpId, "Current", false);
    }
    openHPSummary();
  ]]>
</MACRO>

<MACRO name="Open Linked Doc Edit Mode"
       lang="JScript" >
  <![CDATA[
    function openLinkedDocEditMode() {
        var container = Selection.ContainerNode;
        var linkedDocId = container.getAttribute("cdr:ref");
        cdrObj.openCdrDoc(linkedDocId, "Current", true);
    }
    openLinkedDocEditMode();
  ]]>
</MACRO>

<MACRO name="Open Linked Doc View Mode"
       lang="JScript" >
  <![CDATA[
    function openLinkedDocViewMode() {
        var container = Selection.ContainerNode;
        var linkedDocId = container.getAttribute("cdr:ref");
        cdrObj.openCdrDoc(linkedDocId, "Current", false);
    }
    openLinkedDocViewMode();
  ]]>
</MACRO>

<MACRO name="View Linked Glossary Term Concept Doc"
       lang="JScript" >
  <![CDATA[
    function viewLinkedGlossaryTermConceptDoc() {
        var doc = Application.ActiveDocument;
        var conceptElems = doc.getElementsByTagName("GlossaryTermConcept");
        if (!conceptElems.length)
            Application.Alert("Can't find GlossaryTermConcept element");
        else {
            var conceptElem = conceptElems.item(0);
            var docId = conceptElem.getAttribute("cdr:ref");
            cdrObj.openCdrDoc(docId, "Current", false);
        }
    }
    viewLinkedGlossaryTermConceptDoc();
  ]]>
</MACRO>

<MACRO name="Edit Linked Glossary Term Concept Doc"
       lang="JScript" >
  <![CDATA[
    function editLinkedGlossaryTermConceptDoc() {
        var doc = Application.ActiveDocument;
        var conceptElems = doc.getElementsByTagName("GlossaryTermConcept");
        if (!conceptElems.length)
            Application.Alert("Can't find GlossaryTermConcept element");
        else {
            var conceptElem = conceptElems.item(0);
            var docId = conceptElem.getAttribute("cdr:ref");
            cdrObj.openCdrDoc(docId, "Current", true);
        }
    }
    editLinkedGlossaryTermConceptDoc();
  ]]>
</MACRO>

<MACRO name="Show Glossary Term Names" 
       lang="JScript" >
  <![CDATA[
    function showGlossaryTermNames() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var termNames = cdrObj.getGlossaryTermNames(docId);
        if (!termNames)
            Application.Alert("No term name documents found");
        else
            Application.Alert("Term names:\n" + termNames);
    }
    showGlossaryTermNames();
  ]]>
</MACRO>

<MACRO name="View Glossary Term Name Docs" 
       lang="JScript" >
  <![CDATA[
    function viewGlossaryTermNameDocs() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var termIds = cdrObj.getGlossaryTermNameIds(docId);
        if (!termIds)
            Application.Alert("No term name documents found");
        else {
            var pieces = termIds.split(' ');
            for (var i in pieces) {
                var termId = pieces[i];
                cdrObj.openCdrDoc(termId, "Current", false);
            }
        }
    }
    viewGlossaryTermNameDocs();
  ]]>
</MACRO>

<MACRO name="Edit Glossary Term Name Docs" 
       lang="JScript" >
  <![CDATA[
    function editGlossaryTermNameDocs() {
        if (cdrObj == null) {
            Application.Alert("You are not logged on to the CDR");
            return;
        }
        var docId  = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var termIds = cdrObj.getGlossaryTermNameIds(docId);
        if (!termIds)
            Application.Alert("No term name documents found");
        else {
            var pieces = termIds.split(' ');
            for (var i in pieces) {
                var termId = pieces[i];
                cdrObj.openCdrDoc(termId, "Current", true);
            }
        }
    }
    editGlossaryTermNameDocs();
  ]]>
</MACRO>

<MACRO name="Clone Doc"
       lang="JScript">
  <![CDATA[
    function stripCdrIdAttrs(elemNode) {
        if (elemNode.hasAttribute("cdr:id"))
            elemNode.removeAttribute("cdr:id");
        var child = elemNode.firstChild;
        while (child) {
            if (child.nodeType == 1) // DOMElement
                stripCdrIdAttrs(child);
            child = child.nextSibling;
        }
    }
    function stripDocId(docElem) {
        var target = "xm-replace_text";
        var data   = "{The document ID will be assigned automatically} ";
        var newPI  = ActiveDocument.createProcessingInstruction(target, data);
        var node   = docElem.firstChild;
        while (node) {
            if (node.nodeName == 'CdrDocCtl') {
                var child = node.firstChild;
                while (child) {
                    if (child.nodeName == 'DocId') {
                        gEditingCdrLink = true;
                        var grandchild = child.firstChild;
                        while (grandchild) {
                            var nextGrandchild = grandchild.nextSibling;
                            child.removeChild(grandchild);
                            grandchild = nextGrandchild;
                        }
                        grandchild.appendChild(newPI);
                        gEditingCdrLink = false;
                    }
                    child = child.nextSibling;
                }
            }
            node = node.nextSibling;
        }
    }
    function fixDocId(docText) {
        var docId = "<DocId><?xm-replace_text {The document ID will be "
                  + "assigned automatically} ?></DocId>";
        return docText.replace(/<DocId[^>]*>CDR\d+<\/DocId>/, docId);
    }
    function cloneDoc() {
        var docType = ActiveDocument.doctype;
        if (docType) {
            var rng = ActiveDocument.Range;
            rng.SelectAll();
            rng.Copy();
            var docText = fixDocId(Application.Clipboard.Text);
            var xmlText = "<?xml version='1.0'?>\n<!DOCTYPE "
                        + docType.name
                        + " SYSTEM '"
                        + docType.name
                        + ".dtd'>\n"
                        + docText;
            var doc = Application.Documents.OpenString(xmlText, 0,
                                                       "newdoc.xml",
                                                       true, true, false);
            var docElem = doc.documentElement;
            if (docElem.hasAttribute("readonly"))
                docElem.removeAttribute("readonly");
            stripCdrIdAttrs(docElem);
            // stripDocId(docElem);
        }
    }
    cloneDoc();
  ]]>
</MACRO>

<MACRO name="Make Citation Supplementary Info Doc"
       lang="JScript">
  <![CDATA[
    function stripCdrIdAttrs(elemNode) {
        if (elemNode.hasAttribute("cdr:id"))
            elemNode.removeAttribute("cdr:id");
        var child = elemNode.firstChild;
        while (child) {
            if (child.nodeType == 1) // DOMElement
                stripCdrIdAttrs(child);
            child = child.nextSibling;
        }
    }
    function getDocTitle() {
        var node = ActiveDocument.documentElement.firstChild;
        while (node) {
            if (node.nodeName == 'CdrDocCtl') {
                var child = node.firstChild;
                while (child) {
                    if (child.nodeName == 'DocTitle')
                        return getTextContent(child);
                    child = child.nextSibling;
                }
            }
            node = node.nextSibling;
        }
        return "*** DocTitle not found ***";
    }
    function insertCitationTitle(doc, title) {
        var nodes = doc.getElementsByTagName('Title');
        if (nodes.length < 1) {
            Application.Alert("Title element not found");
            return;
        }
        var elem = nodes.item(0);
        var child = elem.firstChild;
        while (child) {
            var nextChild = child.nextSibling;
            elem.removeChild(child);
            child = nextChild;
        }
        var textNode = doc.createTextNode(title);
        elem.appendChild(textNode);
    }
    function makeCitationSupplementaryInfoDoc() {

        var title = getDocTitle();
        var template = Application.Path
              + "\\Template\\Cdr\\CitationSupplementaryInfo.xml";
        var doc = Application.Documents.OpenTemplate(template);
        insertCitationTitle(doc, title);
    }
    makeCitationSupplementaryInfoDoc();
  ]]>
</MACRO>

<MACRO name="Make Scientific Protocol Doc"
       lang="JScript">
  <![CDATA[
    function OriginalProtocolDoc(doc, newDoc) {

        // Initialize object properties.
        this.docId       = null;
        this.primaryId   = null;
        this.title       = null;
        this.procInfo    = null;
        this.relDocs     = null;
        this.phases      = new Array();
        if (!doc)        { return; }

        // Get the CDR ID for the InScopeProtocol document.
        var docId = getSingleElement(doc, 'DocId');
        if (docId)
            this.docId = getTextContent(docId);

        // Extract a copy of the primary protocol ID element.
        var primaryId = getSingleElement(doc, 'PrimaryID');
        if (primaryId)
            this.primaryId = cloneFor(newDoc, primaryId);

        // Copy the original title element.
        var title = getSingleElement(doc, 'ProtocolTitle', 'Type', 'Original');
        if (title)
            this.title = cloneFor(newDoc, title);

        // Get the related documents block.
        var relDocs = getSingleElement(doc, 'RelatedDocuments');
        if (relDocs)
            this.relDocs = cloneFor(newDoc, relDocs);

        // Collect all the phase elements from the source document.
        var phases = doc.getElementsByTagName('ProtocolPhase');
        for (var i = 0; i < phases.length; ++i)
            this.phases.push(cloneFor(newDoc, phases.item(i)));

        // Clone the processing details block.
        var procInfo = getSingleElement(doc, 'ProtocolProcessingDetails');
        if (procInfo)
            this.procInfo = cloneFor(newDoc, procInfo);
    }

    function makeScientificProtocolDoc() {

        // Get a reference to the source document.
        var inScopeDoc = Application.ActiveDocument;

        // Create a new ScientificProtocolInfo document from the template.
        var templateLocation = "\\Template\\Cdr\\ScientificProtocolInfo.xml";
        var templatePath = Application.Path + templateLocation;
        var doc = Application.Documents.OpenTemplate(templatePath);
        var rulesChecking = ActiveDocument.RulesChecking;
        ActiveDocument.RulesChecking = false;

        // Extract the interesting bits from the source document.
        var oDoc = new OriginalProtocolDoc(inScopeDoc, doc);

        // Replace the empty primary ID element with the one from the source.
        if (oDoc.primaryId) {
            var primaryId = getSingleElement(doc, 'PrimaryID');
            if (!primaryId)
                Application.Alert("PrimaryID element missing from template");
            else
                primaryId.parentNode.replaceChild(oDoc.primaryId, primaryId);
        }

        // Replace the empty InScopeDocID element.
        var docId = getSingleElement(doc, 'InScopeDocID');
        if (!docId)
            Application.Alert("InScopeDocID element not found in template");
        else {
            var newElem = doc.createElement('InScopeDocID')
            newElem.setAttribute('cdr:ref', oDoc.docId);
            docId.parentNode.replaceChild(newElem, docId);
        }

        // Replace the single empty phase node with the in-scope phases.
        var phase = getSingleElement(doc, "ProtocolPhase");
        if (!phase)
            Application.Alert('ProtocolPhase element missing from template');
        else {
            for (var i = 0; i < oDoc.phases.length; ++i) {
                 var newElem = oDoc.phases[i];
                 if (i == oDoc.phases.length - 1)
                     phase.parentNode.replaceChild(newElem, phase);
                 else
                     phase.parentNode.insertBefore(newElem, phase);
            }
        }

        // Pop in the new RelatedDocuments block.
        if (oDoc.relDocs) {
            var relDocs = getSingleElement(doc, "RelatedDocuments");
            if (!relDocs)
                Application.Alert("RelatedDocuments missing from template");
            else
                relDocs.parentNode.replaceChild(oDoc.relDocs, relDocs);
        }

        // Insert the original title in front of the professional title.
        if (oDoc.title) {
            var title = getSingleElement(doc, 'ProtocolTitle');
            if (!title)
                Application.Alert("ProtocolTitle element not in template");
            else
                title.parentNode.insertBefore(oDoc.title, title);
        }

        // Last step: insert the processing information block.
        if (oDoc.procInfo) {
            var procInfo = getSingleElement(doc, "ProtocolProcessingDetails");
            if (!procInfo)
                Application.Alert("Template missing ProtocolProcessingDetails");
            else
                procInfo.parentNode.replaceChild(oDoc.procInfo, procInfo);
        }
        var rng = ActiveDocument.Range;
        rng.SelectAll();
        var docAsString = rng.Text;
        rng.Delete();
        rng.PasteString(docAsString);
        ActiveDocument.RulesChecking = rulesChecking;
    }
    makeScientificProtocolDoc();
  ]]>
</MACRO>

<MACRO name="PI Bug Repro"
       lang="JScript"
       key="Ctrl+Alt+O">
  <![CDATA[
    function piBugRepro() {

        // Create a new document.
        var xml = "<?xml version='1.0' ?>\n"
                + "<!DOCTYPE Article SYSTEM 'journalist.dtd'>\n"
                + "<Article>\n <Title>PI Bug Repro</Title>\n"
                + " <Para><?xm-replace_text { Riveting prose here }?></Para>\n"
                + "</Article>";
        var doc = Application.Documents.OpenString(xml);
        var elem = doc.createElement('Para');
        var prompt = '{ Boring stuff here }';
        var pi = doc.createProcessingInstruction('xm-replace_text', prompt);
        elem.appendChild(pi);
        doc.documentElement.appendChild(elem);
    }
    piBugRepro();
  ]]>
</MACRO>

<MACRO name="Make Glossary Term Name Doc"
       lang="JScript">
  <![CDATA[
    function makeGlossaryTermNameDoc() {
        var docId = getDocId();
        if (!docId) {
            Application.Alert("Document has not yet been saved in the CDR");
            return;
        }
        var template = Application.Path
                     + "\\Template\\Cdr\\GlossaryTermName.xml";
        var doc = Application.Documents.OpenTemplate(template);
        var docIdElems = doc.getElementsByTagName('GlossaryTermConcept');
        if (!docIdElems.length) {
            Application.Alert("InScopeDocID element not found");
            return;
        }
        var docIdElem = docIdElems.item(0);
        var child = docIdElem.firstChild;
        while (child) {
            var nextChild = child.nextSibling;
            docIdElem.removeChild(child);
            child = nextChild;
        }
        docIdElem.setAttribute("cdr:ref", docId);
    }
    makeGlossaryTermNameDoc();
  ]]>
</MACRO>

<MACRO name="Bug Repro" lang="JScript">
  <![CDATA[
    function bugRepro() {
        var elemName = Application.Prompt("Element to replace?");
        var doc      = Application.ActiveDocument;
        var newElem  = doc.createElement(elemName);
        var textNode = doc.createTextNode("foo");
        var oldElem  = doc.getElementsByTagName(elemName).item(0);
        newElem.appendChild(textNode);
        oldElem.parentNode.replaceChild(newElem, oldElem);
    }
    bugRepro();
  ]]>
</MACRO>

<MACRO name="Find Private Use Chars" lang="JScript" key="Alt+Z">
  <![CDATA[
    /*
     * We can't just use rng.MoveRight() repeatedly to check for private
     * use characters one at a time, because the XMetaL API skips over
     * the private use characters.  Shelving work on this, since it's a
     * lower-priority task than some of the other issues I'm working on
     * right now.  When we proceed with implementing this, use the new
     * 
     */
    function findPrivateUseChars() {
        var rng = ActiveDocument.Range;
        var found = false;
        rng.SelectAll()
        var text = rng.Text;
        var pos = text.search(/[\uE000-\uF8FF]/);
        while (pos != -1) {
            text = text.substring(0, pos)
                 + "<cdr:PrivateUseCharacter>U+"
                 + text.charCodeAt(pos).toString(16)
                 + "</cdr:PrivateUseCharacter>"
                 + text.substring(pos + 1);
            found = true;
            pos = text.search(/[\uE000-\uF8FF]/);
        }
        if (found) {
            Application.Alert("Replaced private use characters; text is now " +
                              text.length + " characters long");
            var rulesChecking = ActiveDocument.RulesChecking;
            ActiveDocument.RulesChecking = false;
            rng.Delete();
            ActiveDocument.RulesChecking = false;
            rng.PasteString(text);
            ActiveDocument.RulesChecking = rulesChecking;
            rng.MoveToDocumentStart();
            if (rng.MoveToElement("cdr:PrivateUseCharacter")) {
                rng.Select();
                rng.SelectElement();
            }
        }
        if (!found)
            Application.Alert("No private use characters found");
    }
    findPrivateUseChars();
  ]]>
</MACRO>

<MACRO name="Insert Comment"
       lang="JScript">
  <![CDATA[
    function insertComment() {
        var rng = ActiveDocument.Range;
        // rng.MoveToDocumentEnd();
        if (!rng.FindInsertLocation("Comment")) {
            Application.Alert("Can't insert Comment element " +
                              "under current position.");
            return; 
        }
        var newElem = "<Comment user='"
                    + CdrUserName
                    + "' audience='Internal' date='"
                    + getCurDateString()
                    + "'><?xm-replace_text {Your comment here} ?></Comment>";
        rng.PasteString(newElem);
        rng.MoveToElement("Comment", false);
        rng.SelectElement();
        rng.Collapse(1);
        rng.MoveRight();
        rng.Select();
    }
    insertComment();
  ]]>
</MACRO>

<MACRO name="SC Up"      lang="JScript">Selection.TypeText("&amp;#x2191;");</MACRO>
<MACRO name="SC Down"    lang="JScript">Selection.TypeText("&amp;#x2193;");</MACRO>
<MACRO name="SC Right"   lang="JScript">Selection.TypeText("&amp;#x2192;");</MACRO>
<MACRO name="SC Left"    lang="JScript">Selection.TypeText("&amp;#x2190;");</MACRO>
<MACRO name="SC alpha"   lang="JScript">Selection.TypeText("&amp;#x03B1;");</MACRO>
<MACRO name="SC beta"    lang="JScript">Selection.TypeText("&amp;#x03B2;");</MACRO>
<MACRO name="SC gamma"   lang="JScript">Selection.TypeText("&amp;#x03B3;");</MACRO>
<MACRO name="SC delta"   lang="JScript">Selection.TypeText("&amp;#x03B4;");</MACRO>
<MACRO name="SC mu"      lang="JScript">Selection.TypeText("&amp;#x03BC;");</MACRO>
<MACRO name="SC le"      lang="JScript">Selection.TypeText("&amp;#x2264;");</MACRO>
<MACRO name="SC ge"      lang="JScript">Selection.TypeText("&amp;#x2265;");</MACRO>
<MACRO name="SC copy"    lang="JScript">Selection.TypeText("&amp;#x00A9;");</MACRO>
<MACRO name="SC reg"     lang="JScript">Selection.TypeText("&amp;#x00AE;");</MACRO>
<MACRO name="SC TM"      lang="JScript">Selection.TypeText("&amp;#x2122;");</MACRO>
<MACRO name="SC deg"     lang="JScript">Selection.TypeText("&amp;#x00B0;");</MACRO>
<MACRO name="SC cross"   lang="JScript">Selection.TypeText("&amp;#x2020;");</MACRO>
<MACRO name="SC dblx"    lang="JScript">Selection.TypeText("&amp;#x2021;");</MACRO>
<MACRO name="SC mdash"   lang="JScript">Selection.TypeText("&amp;#x2014;");</MACRO>
<MACRO name="SC plusmin" lang="JScript">Selection.TypeText("&amp;#x00B1;");</MACRO>
<MACRO name="SC lquot"   lang="JScript">Selection.TypeText("&amp;#x201C;");</MACRO>
<MACRO name="SC rquot"   lang="JScript">Selection.TypeText("&amp;#x201D;");</MACRO>
<MACRO name="SC lapos"   lang="JScript">Selection.TypeText("&amp;#x2018;");</MACRO>
<MACRO name="SC rapos"   lang="JScript">Selection.TypeText("&amp;#x2019;");</MACRO>
<MACRO name="SC quarter" lang="JScript">Selection.TypeText("&amp;#x00BC;");</MACRO>
<MACRO name="SC half"    lang="JScript">Selection.TypeText("&amp;#x00BD;");</MACRO>
<MACRO name="SC 3quart"  lang="JScript">Selection.TypeText("&amp;#x00BE;");</MACRO>
<MACRO name="SC nbsp"    lang="JScript">Selection.TypeText("&amp;#x00A0;");</MACRO>

<MACRO name="Insert Diagnosis Links" 
       lang="JScript" >
  <![CDATA[
    function insertDiagnosisLinks() {
        var diagString = cdrObj.getDiagnosisSetTerms();
        if (!diagString)
            return;
        // Application.Alert(diagString);
        var elemString = "\n";
        var diags = diagString.split(' ');
        for (var i in diags) {
            elemString += "<Diagnosis cdr:ref='" + diags[i] + "'/>\n";
        }
        insertDiagnoses(elemString);
    }
    insertDiagnosisLinks();
  ]]>
</MACRO>

<MACRO name="Insert Head And Neck Diagnoses" 
       lang="JScript" >
  <![CDATA[
    function insertHeadAndNeckDiagnoses() {
        var diagString = cdrObj.getDiagnosisSetTerms();
        Application.Alert(diagString);
        return;

        // Create a string for the diagnosis link elements.
        var elemString = "\n" +
            "<Diagnosis cdr:ref='CDR0000038936'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040741'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040742'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040743'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040744'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040745'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038935'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040746'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040747'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040748'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040749'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040750'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040751'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040753'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040754'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040755'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040756'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039407'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040699'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040696'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040698'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040695'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040697'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040704'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040701'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040703'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040700'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040702'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040709'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040706'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040708'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040705'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040707'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040714'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040711'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040713'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040710'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040712'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040719'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040716'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040718'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040715'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040717'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039988'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039089'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039088'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038933'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040732'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040731'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040734'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040733'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040736'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040735'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040738'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040737'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040740'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040739'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038934'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040722'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040720'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040724'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040723'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040726'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040725'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040728'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040727'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040729'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040730'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038932'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040760'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040758'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040759'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040757'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040764'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040762'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040763'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040761'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040768'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040766'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040767'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040765'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040772'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040770'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040771'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040769'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040776'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040774'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040775'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040773'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040042'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040043'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040048'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040046'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040047'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040044'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039989'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040040'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040038'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038947'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038948'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038949'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038950'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038951'/>\n" +
            "";
        insertDiagnoses(elemString);
    }
    insertHeadAndNeckDiagnoses();
  ]]>
</MACRO>

<MACRO name="Insert Squamous Cell Carcinoma Head And Neck Diagnoses" 
       lang="JScript" >
  <![CDATA[
    function insertSquamousCellCarcinomaHeadAndNeckDiagnoses() {

        // Create a string for the diagnosis link elements.
        var elemString = "\n" +
            "<Diagnosis cdr:ref='CDR0000040741'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040742'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040743'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040744'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040745'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040746'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040747'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040748'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040749'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040750'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040751'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040753'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040754'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040755'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040756'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040695'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040700'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040705'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040710'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040715'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040697'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040702'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040707'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040712'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040717'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039988'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039089'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039088'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040731'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040733'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040735'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040737'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040739'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040720'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040723'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040725'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040727'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040729'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040757'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040761'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040765'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040769'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040773'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039989'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038947'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038948'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038949'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038950'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038951'/>\n" +
            "";
        insertDiagnoses(elemString);
    }
    insertSquamousCellCarcinomaHeadAndNeckDiagnoses();
  ]]>
</MACRO>

<MACRO name="Insert Advanced Head And Neck Diagnoses" 
       lang="JScript" >
  <![CDATA[
    function insertAdvancedHeadAndNeckDiagnoses() {

        // Create a string for the diagnosis link elements.
        var elemString = "\n" +
            "<Diagnosis cdr:ref='CDR0000040743'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040744'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040745'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040750'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040751'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040753'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040754'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040755'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040756'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040709'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040706'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040708'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040705'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040707'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040714'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040711'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040713'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040710'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040712'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040719'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040716'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040718'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040715'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040717'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039988'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039089'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039088'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040736'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040735'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040738'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040737'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040740'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040739'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040726'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040725'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040728'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040727'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040729'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040730'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040768'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040766'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040767'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040765'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040772'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040770'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040771'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040769'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040776'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040774'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040775'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040773'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040042'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040043'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040048'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040046'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040047'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040044'/>\n" +
            "<Diagnosis cdr:ref='CDR0000039989'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040040'/>\n" +
            "<Diagnosis cdr:ref='CDR0000040038'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038949'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038950'/>\n" +
            "<Diagnosis cdr:ref='CDR0000038951'/>\n" +
            "";
        insertDiagnoses(elemString);
    }
    insertAdvancedHeadAndNeckDiagnoses();
  ]]>
</MACRO>

</MACROS>
