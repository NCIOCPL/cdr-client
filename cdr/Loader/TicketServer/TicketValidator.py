import sys
import string
import xml.dom.minidom
import XmlUtil
import traceback

class TicketValidator:

    def __init__( self ):
        self.gerr = ""
        self.MANIFEST_FILE_PATH = ".\\"

    def SetManifestPath( self, path ):
        self.MANIFEST_FILE_PATH = path

    def CompareTicket( self, t ):
        # be pessamistic, assume failure
        valid = 0

        #print "CGI PATH " + self.MANIFEST_FILE_PATH + "\n"
        #print "CGI ticket in " + t + "\n"
       
        #first fetch our ticket from the file
        #   we could I suppose read this once and hold it in memory,
        #   but then we'd have to restart whenever a new ticket
        #   was written
        cur_ticket_dom =  xml.dom.minidom.parse( self.MANIFEST_FILE_PATH + 'CDR_MANIFEST.xml' )
        cur_t_time = cur_ticket_dom.getElementsByTagName("TIMESTAMP")
        cur_t_host = cur_ticket_dom.getElementsByTagName("HOST")
        file_time = XmlUtil.GetTrimmedTagContents( cur_t_time[0].childNodes )
        file_host = XmlUtil.GetTrimmedTagContents( cur_t_host[0].childNodes )

        #now evaluate the incoming ticket
        try:
            #print "testing ", t
            test_ticket_dom = xml.dom.minidom.parseString( t )
            test_t_time = test_ticket_dom.getElementsByTagName("TIMESTAMP")
            test_t_host = test_ticket_dom.getElementsByTagName("HOST")
            test_time = XmlUtil.GetTrimmedTagContents( test_t_time[0].childNodes )
            test_host = XmlUtil.GetTrimmedTagContents( test_t_host[0].childNodes )
        except:
            ( ty, v, b ) = sys.exc_info() 
            tb = traceback.format_exception( ty, v, b )
            self.gerr = "<Error>\n\t<Message>\n\t\tAttempt to test invalid ticket\n\t</Message>\n\t<Input>\n\t\t" + t + "\n\t</Input>\n\t<EXCEPTION>\n\t\t"
            for tbs in tb:
                self.gerr += tbs
            self.gerr += "\n\t</EXCEPTION>\n</Error>"
            test_time = "INVALID"
            test_host = "INVALID"

        if (( test_host == file_host ) and ( test_time == file_time )):
            valid = 1
        return valid


    #determine if this ticket is current/valid
    def ValidateTicket( self, ticket ):
        valid = 0
        #did we receive anything?
        if ( ticket != "" ):
            # yes compare ti to file contents
            valid = self.CompareTicket( ticket )
        return valid
            
    def XMLValidateTicket( self, ticket ):
        xmlout = "<TicketValidation>\n"
        result = self.ValidateTicket( ticket )
        if ( result != 0 ):
            xmlout += "<Response>ACK</Response>\n"
        else:
            xmlout += "<Response>NAK</Response>\n"
        xmlout += self.gerr
        xmlout += "</TicketValidation>\n"
        return xmlout

# Main is used mainly for testing
def Main():
    test_ticket = ""
    if ( len(sys.argv) > 1 ):
        test_ticket = sys.argv[1]
    #print sys.argv
    #print test_ticket
    tv = TicketValidator()
    tv.SetManifestPath( "C:\\WorkingDir\\CDRStuff\\ticket\\" )
    print tv.XMLValidateTicket( test_ticket )

# determine if we are invoked standalone, if so invoke testing mode
if __name__ == "__main__":
    Main()