import sys
import string
import tempfile
import os
import win32ui
import xml.dom.minidom
import XmlUtil

class ManifestComparitor:

    def __init__( self ):
        self.manifest_list = {}
        self.manifest_seen = {}
        self.manifest_update = {}
        self.comparison_list = {}
        self.comparison_del = {}

        self.last_error = "";

        self.delta_dom = xml.dom.minidom.Document()
        
        self.MANIFEST_FILE_PATH = ".\\"

    ############################################################
        
    def SetManifestPath( self, path ):
        self.MANIFEST_FILE_PATH = path
        os.chdir( self.MANIFEST_FILE_PATH )

    ############################################################
        
    def ReadCurrentManifest( self ):
        # read the current manifest file
        manifest_dom = xml.dom.minidom.parse( 'CDR_MANIFEST.XML' )
        filelist = manifest_dom.getElementsByTagName( "FILELIST" )
        if ( filelist ):
            files = filelist[0].getElementsByTagName( "FILE" )
            for file in files:
                name_node = file.getElementsByTagName("NAME")
                time_node = file.getElementsByTagName("TIMESTAMP")
                name = XmlUtil.GetTrimmedTagContents( name_node[0].childNodes )
                time = XmlUtil.GetTrimmedTagContents( time_node[0].childNodes )
                self.manifest_list[ name ] = time
                self.manifest_seen[ name ] = 0

    ############################################################
        
    def LoadComparisonManifest( self, old_manifest ):
        # read the current manifest file
        try:
            manifest_dom = xml.dom.minidom.parseString( old_manifest )
            filelist = manifest_dom.getElementsByTagName( "FILELIST" )
            if ( filelist ):
                files = filelist[0].getElementsByTagName( "FILE" )
                for file in files:
                    try:
                        name_node = file.getElementsByTagName("NAME")
                        time_node = file.getElementsByTagName("TIMESTAMP")
                        name = XmlUtil.GetTrimmedTagContents( name_node[0].childNodes )
                        time = XmlUtil.GetTrimmedTagContents( time_node[0].childNodes )
                        self.comparison_list[ name ] = time
                    except:
                        ## missing data for a individual file, go on with rest of files
                        self.last_error = "Missing file data."
        except:
            ## missing the filelist - empty manifest leave dictionary blank
            self.last_error = "Empty Manifest"

    ############################################################
            
    def CompareManifests( self ):
        for old in self.comparison_list.keys():
            # check all the existing files
            cl_time = self.comparison_list[ old ]
            # if the file is listed in the manifest
            if ( self.manifest_list.has_key( old ) ):
                # note that we saw it
                self.manifest_seen[ old ] = 1
                ml_time = self.manifest_list[ old ]
                # and check to make sure the time stamps match
                if ( cl_time != ml_time ):
                    # if timestamps don't match
                    # we need to replace the file
                    self.manifest_update[ old ] = 'update'
            else:
                # if the file isn't in the manifest
                # it needs to be deleted
                self.comparison_del[ old ] = 'delete'
                
        for new in self.manifest_list.keys():
            # check the new files if it's in the client list it's already handled
            if ( not self.comparison_list.has_key( new ) ):
                # if it isn't in the client list then we
                # need to add a file to the list
                self.manifest_update[ new ] = 'update'
            ## else:
                #if it was in the client list we're done with it
            
    ############################################################

    def CreateDeltaList( self, zname ):
        #create the delta doc root
        top_level = self.delta_dom.createElement("DELTA")
        self.delta_dom.appendChild( top_level )

        #create the zip file tag
        # add items only if they exist, but add tag
        # regardless so we get the <ZIPFILE/> on the other end
        zip_item = self.delta_dom.createElement( "ZIPFILE" )
        if ( zname ):
            zip_text = self.delta_dom.createTextNode( zname )
            zip_item.appendChild( zip_text )
        top_level.appendChild( zip_item )

        # likewise add the update element
        # even if it ends up being empty
        update_level = self.delta_dom.createElement("UPDATE")
        if ( len(self.manifest_update) ):
            for add in self.manifest_update.keys():
                a_item = self.delta_dom.createElement( "FILE" )
                a_text = self.delta_dom.createTextNode( add )
                a_item.appendChild( a_text )
                update_level.appendChild( a_item )
        top_level.appendChild( update_level )

        # one more time, make sure there is an empty <DELETE/>
        # when we don't have anythign to put in it
        del_level = self.delta_dom.createElement("DELETE")
        if ( len( self.comparison_del ) ):
            for dd  in self.comparison_del.keys():
                d_item = self.delta_dom.createElement( "FILE" )
                d_text = self.delta_dom.createTextNode( dd )
                d_item.appendChild( d_text )
                del_level.appendChild( d_item )
        top_level.appendChild( del_level )

        #   We've built ourselves a delta doc

    ############################################################

    def GetDeltaXml( self ):
        result = "Error buidling delta XML"
        if ( self.delta_dom ):
            result = self.delta_dom.toxml()
        return result

    ############################################################

    def BuildDeltaZip( self ):
        fl_name = tempfile.mktemp()
        fl_file = open( fl_name, "w" )
        if ( len(self.manifest_update) ):
            for add in self.manifest_update.keys():
                #fl_file.write( self.MANIFEST_FILE_PATH )
                fl_file.write( add )
                fl_file.write( "\n" )
        fl_file.close()
        zip_name = tempfile.mktemp() + ".zip"
        cmd = "zip -@ " + zip_name + " < " + fl_name + ">" + zip_name + ".err"
        #print win32ui.FullPath( "." )
        #print os.getcwd()
        #print cmd
        #create the zip file
        os.system( cmd )
        #remove the list of files
        #os.unlink( fl_name )
        return zip_name

    ############################################################

    def HasManifestChanged( self, orig ):
        result = "NAK"
        self.ReadCurrentManifest()
        self.LoadComparisonManifest( orig )
        ##print "Manifest: ", manifest_list
        ##print "Query:    ", comparison_list
        self.CompareManifests()
        zname = ""
        if ( (len(self.manifest_update) + len(self.comparison_del)) > 0 ):
            result = "ACK"
            # and if we need to update, then we _MUST_ include
            # the latest copy of the manifest! force it now.
            self.manifest_update[ ".\\CDR_MANIFEST.XML" ] = 'update'

        if ( len(self.manifest_update) > 0 ):
            zname = self.BuildDeltaZip()
        self.CreateDeltaList( zname )
        # now if I've done this right, the only keys in update
        # and delete are the ones that require action,
        # if I've messed up then I need to actually look at the value
        ##print "Updates:  ", manifest_update
        ##print "Deletes:  ", comparison_del
        ##print "Comparison shows "  \
        ##            + repr(len(manifest_update)) \
        ##            + " updates and " \
        ##            + repr(len(comparison_del)) \
        ##            + " deletes required"
        return result

    ############################################################

    def EvaluateManifest( self, orig ):
        q = self.HasManifestChanged( orig )
        return self.GetDeltaXml()

    ############################################################
    
### End Class ManifestComparitor ###############################
    
# Main is used mainly for testing
def Main():
    test_manifest = ""
    w_dir = "."
    if ( len(sys.argv) > 2 ):
        w_dir = sys.argv[1]
        test_manifest = sys.argv[2]
    #print sys.argv
    #print test_manifest
    mc = ManifestComparitor()
    #mc.SetManifestPath( "C:\\WorkingDir\\CDRStuff\\ticket\\" )
    olddir = os.getcwd()
    print olddir
    mc.SetManifestPath( w_dir )
    print os.getcwd()
    result = mc.HasManifestChanged( test_manifest )
    print "Has manifest in ", mc.MANIFEST_FILE_PATH, " changed?"
    print result
    if ( result == "ACK" ):
        print mc.GetDeltaXml()
    os.chdir( olddir )

# determine if we are invoked standalone, if so invoke testing mode
if __name__ == "__main__":
    Main()
    