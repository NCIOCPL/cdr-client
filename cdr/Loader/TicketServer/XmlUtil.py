import string
import xml.dom.minidom

def GetTrimmedTagContents( element ):
    rc = ""
    #print "DB: " + `element`
    for node in element:
        #print "DB: " + `node`
        if node.nodeType == node.TEXT_NODE:
            rc = rc +  string.strip( node.data )
    return rc

