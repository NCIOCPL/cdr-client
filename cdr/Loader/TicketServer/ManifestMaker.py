#!/usr/local/bin/python

###########################################
##
##  ManifestMaker.py
##
##  Looks at the contents of the current directory 
##  and wirtes a new CDR_MANIFEST.xml file
##
##
##  History:
##
##  Created jAHOLMES 020514
##
###########################################

import sys
import xml.dom.minidom
import XmlUtil
import time
import socket
import os

IGNORE_DIR_LIST = ( "CVS", )
IGNORE_FILE_LIST = ()  ## add .cvsignore later

###########################################
##
##
##
###########################################
def CreateNewManifest():
    global manifest_dom, top_level, ticket, filelist
    # create our xml document
    manifest_dom = xml.dom.minidom.Document()

    # create the critical elements, so they'll be there
    # even if they turn out to be empty

    #MANIFEST top level
    top_level = manifest_dom.createElement("MANIFEST")
    manifest_dom.appendChild( top_level )

    #TICKET
    ticket = manifest_dom.createElement("TICKET")
    top_level.appendChild( ticket )

    #FILELIST    
    filelist = manifest_dom.createElement("FILELIST")
    top_level.appendChild( filelist )

###########################################
##
##
##
###########################################
def AddTicket( ):
    global manifest_dom, top_level, ticket, filelist
    # add ticket info to document
    app = manifest_dom.createElement("APPLICATION")
    el_text = manifest_dom.createTextNode( "CDR MakeManifest Utility" )
    app.appendChild( el_text )
    ticket.appendChild( app )
    
    tstamp = manifest_dom.createElement( "TIMESTAMP" )
    ts = `time.time()`
    el_text = manifest_dom.createTextNode( ts )
    tstamp.appendChild( el_text )
    ticket.appendChild( tstamp )
    
    host = manifest_dom.createElement("HOST")
    hname = socket.gethostname()
    el_text = manifest_dom.createTextNode( hname )
    host.appendChild( el_text )
    ticket.appendChild( host )

    user = manifest_dom.createElement("AUTHOR")
    uname = os.environ['USERNAME']
    el_text = manifest_dom.createTextNode( uname )
    user.appendChild( el_text )
    ticket.appendChild( user )


 
###########################################
##
##
##
###########################################
def AddFiles( start_dir ):
    global manifest_dom, top_level, ticket, filelist
    # insert files into document
    dir_contents = os.listdir( start_dir )
    for c_item in dir_contents:
        c_fullname = start_dir + "\\" + c_item
        if ( os.path.isdir( c_fullname ) ):
            if ( not c_item in IGNORE_DIR_LIST ):
                AddFiles( c_fullname )
                
        file_item = manifest_dom.createElement("FILE")
        
        f_name = manifest_dom.createElement("NAME")
        el_text = manifest_dom.createTextNode( c_fullname )
        f_name.appendChild( el_text )
        file_item.appendChild( f_name )
        
        f_ts = manifest_dom.createElement("TIMESTAMP")
        el_text = manifest_dom.createTextNode( `os.path.getmtime( c_fullname )` )
        f_ts.appendChild( el_text )
        file_item.appendChild( f_ts )

        filelist.appendChild( file_item )               

###########################################
##
##
##
###########################################
def WriteFile( filename ):
    global manifest_dom, top_level, ticket, filelist
    #output xml manifest
    result = manifest_dom.toxml()
    fullname = root_path + "\\" + filename
    fl_file = open( fullname, "w" )
    fl_file.write( result )
    fl_file.close()
     

###########################################
##
##
##
###########################################
def Main():
    global manifest_dom, top_level, ticket, filelist, root_path
    root_path = sys.argv[1]

    print os.getcwd()
    print root_path
    
    CreateNewManifest()
    AddTicket( )
    AddFiles( root_path )
    WriteFile( "CDR_MANIFEST.XML" )

# determine if we are invoked standalone, if so invoke testing mode
if __name__ == "__main__":
    Main()
