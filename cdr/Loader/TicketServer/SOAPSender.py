import sys
import string
import os
import httplib
import urllib
import xml
import XmlUtil
import traceback
import base64

class SOAPSender:
    
    def __init__( self ):
        self.DIRECTORY = ".\\"
        self.MessageFile = "message.xml"
        self.HTTP_SERVER = "mmdb2"
        self.CGI_CMD = "/cgi-bin/Ticket/TicketCgi.py?"

    def SetDirectory( self, dir ):
        self.DIRECTORY = dir

    def PostMessage( self, message )
        params = urllib.urlencode( message )
        h = httplib.HTTP( self.HTTP_SERVER )
        h.putrequest("POST", self.CGI_CMD )
        h.putheader("Content-type", "application/x-www-form-urlencoded")
        h.putheader("Content-length", "%d" % len(params))
        h.putheader('Accept', 'text/plain')
        h.putheader('Host', 'www.musi-cal.com')
        h.endheaders()
        h.send(params)
        reply, msg, hdrs = h.getreply()
        print reply # should be 200
        data = h.getfile().read() # get the raw HTML
        return data

    def GetLocalMessage( self ):
        tfile = open( self.DIRECTORY + self.MessageFile )
        tdata = tfile.read()
        tfile.close()
        return tdata
       

# Main is actually main in this case
def Main():
    argv[1]
    sxmt = SOAPSender()
    sxmt.MessageFile = argv[1] 
    sxmt.HTTP_SERVER = argv[2]
    sxmt.CGI_CMD = argv[3]
    msg = sxmt.GetLocalMessage()
    reply = sxmt.PostMessage( msg )
    print reply
    
    
# determine if we are invoked standalone, if so invoke testing mode
if __name__ == "__main__":
    Main()
