#----------------------------------------------------------------------
#
# $Id: Makefile,v 1.3 2002-12-17 20:50:04 bkline Exp $
#
# Rules for building and packing up CDR client files.
#
# $Log: not supported by cvs2svn $
# Revision 1.2  2002/12/17 20:47:12  bkline
# Made zip archive store the files in a subdirectory.
#
# Revision 1.1  2002/12/17 20:11:06  bkline
# New script for building and packing CDR client files.
#
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Fix this if it doesn't match the location of your Visual Studio installation
#----------------------------------------------------------------------
DRV=d:
DEVENV=$(DRV)\Program Files\Microsoft Visual Studio .NET\Common7\IDE\devenv.exe
ARCHIVE_FILES=CDRLoader.exe unzip.exe CDRLoader.ini CDRLoader.lnk \
SetupCDRLoader.cmd CDRLoader.cmd

#----------------------------------------------------------------------
# Main target.
#----------------------------------------------------------------------
CDRLoaderSetup.exe: CDRLoaderSetup.zip unzipsfx.exe
	rm -rf CDRLoaderSetup.exe
	copy /b unzipsfx.exe+CDRLoaderSetup.zip CDRLoaderSetup.exe
	zip -A CDRLoaderSetup.exe

CDRLoaderSetup.zip: $(ARCHIVE_FILES)
	rm -rf CDRLoaderSetup.zip
	rm -rf CDRLoaderSetup
	mkdir CDRLoaderSetup
	cp -p $(ARCHIVE_FILES) CDRLoaderSetup
	zip -rm CDRLoaderSetup.zip CDRLoaderSetup

CDRLoader.exe:
	rm -rf CDRLoader.exe
	"$(DEVENV)" CDRLoader.sln /build Release
	copy Release\CDRLoader.exe

clean:
	rm -rf CDRLoaderSetup.exe CDRLoaderSetup.zip CDRLoader.exe CDRLoader.ncb
	rm -rf CDRLoaderSetup
