#!/usr/local/bin/python

import sys
import traceback
import cgi
import base64
import os
import string
import urllib
import re
import time

import ManifestComparitor
import TicketValidator
import NCISoapCgi

## Provide some global definitions of where
##  to find important files
global CGI_PATH, CDR_MANIFEST_PATH
CGI_PATH = "./"
CDR_MANIFEST_PATH = ".\\ClientFiles"

###########################################
##  Validate
##  Call the validator, send back it's result
###########################################
def Validate( payload ):
    tv = TicketValidator.TicketValidator()
    tv.SetManifestPath( CDR_MANIFEST_PATH )
    return tv.XMLValidateTicket( payload )
    
###########################################
##  Compare
##  Call the comparitor to determine if
##  we need to report a change
##  if so get the delta document and send that
##  if no change, send a empty/dummy delta
###########################################
def Compare( payload ):
    mc = ManifestComparitor.ManifestComparitor()
    mc.SetManifestPath( CDR_MANIFEST_PATH )
    mc.EvaluateManifest( payload )
    return mc.GetDeltaXml()

###########################################
##    SendZip
##  Yank specified zip file off the disk
##  and send it done the pipe as our response
###########################################
def SendZip( payload ):
    # ok this is a place where it makes sense
    # to just regex it rather than dom it
    prog = re.compile( "<ZIPREQ>(.*)</ZIPREQ>", re.S )
    mg = prog.search( payload )
    fname = mg.group(1);
    n = fname
    zf = open( n, "rb" )
    data = base64.encodestring( zf.read() )
    zf.close()
    output = """\
    <ZIPFILE>
    <FNAME>%s</FNAME>
    <DATA encoding="base64">%s</DATA>
    </ZIPFILE>
    """ % ( fname, data )
    # need to delete files once they're sent out
    os.unlink( fname )
    
    ### !DEBUG! dump b64 file for comparison
    #b64dumpf = open( "b64srvdump.txt", "wb" )
    #b64dumpf.write( data )
    #b64dumpf.close()
    return output
    


###########################################
##  main body
##
##  Gets the cgi params from the python cgi
##  module, checks the request type and
##  calls the worker function to get the
##  requested data.
##
##
##  History:
##
##  jAHOLMES 020418
##  Checked w/ BKline & found that he too had
##  problems with the CGI & POST got a code frag
##  from him that handles SOAP style messages
##  in a POST.  Revised to use that instead of cgi.py
##
###########################################


## find out where the cgi is living so we can use absolute paths
if ( os.environ.has_key( "PATH_TRANSLATED" ) ):
    CGI_PATH = string.replace( os.environ[ "PATH_TRANSLATED" ], "TicketCgi.py", "" )
    
ticket_serv_log = open( CGI_PATH + "TicketServer.Log", "a+" )
ticket_serv_log.write( "\n===========\n" );
ticket_serv_log.write( "CGI-BIN-START " )
ticket_serv_log.write( `time.time()` )
ticket_serv_log.write( " " + os.environ[ "REMOTE_HOST" ] + " " + os.environ[ "HTTP_USER_AGENT" ] )
ticket_serv_log.write( "\n---\n" );

## start by fetching the cgi parameters    
soap = NCISoapCgi.NCISoapCgi()
soap.SetLogFile( ticket_serv_log )
soap_doc = soap.ReadRequest()

ticket_serv_log.write( "INPUT " )
ticket_serv_log.write( `time.time()` )
ticket_serv_log.write( "\n...\n" );
ticket_serv_log.write( soap_doc )
ticket_serv_log.write( "\n---\n" );

## The location of CDR files & manifest list shoudl be known to the server
## if not, then maybe the caller provided it to us
## if that fails, use the current directory for the cgi script
if ( os.environ.has_key( "CDR_MANIFEST_PATH" ) ):
    CDR_MANIFEST_PATH = os.environ[ "CDR_MANIFEST_PATH" ]
else:
    CDR_MANIFEST_PATH = CGI_PATH + "ClientFiles\\"

db_output = "<DB_OUT>\n"

# extract the payload
# this should be part of the NCISoapCgi util but some
# impenetrable scoping problem keeps it from working.
prog = re.compile( "<env:Body>(.*)</env:Body>", re.S )
mg = prog.search( soap_doc )
payload = "<BADREQ/>"
if ( mg ):
    payload = mg.group(1)

#DB#print "mg payload is ", payload    

# the XML header is both unneeded and harmful for the minidom parser
# ie. it hides the document type 
prog1 = re.compile( "<\?.*\?>(.*)", re.S )
mg1 = prog1.search( payload )
if ( mg1 ):
    payload = mg1.group(1)

#DB#print "mg1 payload is ", payload    
db_output = db_output + "<PAYLOAD>\n" + payload + "\n</PAYLOAD>\n"

# we can tell what kind of request this is by the document root
prog2 = re.compile( "<([^>]*)>", re.S )
mg2 = prog2.search( payload )
doc_type = "NOTFND"
if ( mg2 ):
    doc_type = mg2.group(1)

#DB#print "mg2 payload is ", payload    
# if this is an empty doc type remove the trailing /
# also dispose of any extra whitespace so we get a proper match
doc_type = doc_type.replace( "/", "" )
doc_type = doc_type.strip()

db_output = db_output + "<DOCTYPE>\n" + doc_type + "\n</DOCTYPE>\n"

#print "Doc type is " + doc_type

if ( doc_type == "TEST" ):
    # handle test case here
    output = "<TEST/>\n"
if (( doc_type == "NOTFND" ) or ( doc_type == "BADREQ" )):
    # handle test case here
    output = "<ERROR>\n" + "Invalid document type" + "</ERROR>\n"
elif ( doc_type == "TICKET" ):
    # validate a ticket
    output = Validate( payload )
elif ( doc_type == "MANIFEST" ):
    # generate a file delta report
    output = Compare( payload )
elif ( doc_type == "ZIPREQ" ):
    # send the zip file
    output = SendZip( payload )
else:
    output = "<ERROR>\nUnknown request document type " + doc_type + "\n</ERROR>\n"
    
db_output = db_output + "</DB_OUT>\n"    
ticket_serv_log.write( "DEBUG " )
ticket_serv_log.write( `time.time()` )
ticket_serv_log.write( "\n...\n" );
ticket_serv_log.write( db_output )
ticket_serv_log.write( "\n===========\n" );
ticket_serv_log.flush()
ticket_serv_log.close()

soap.SendMessage( output )


