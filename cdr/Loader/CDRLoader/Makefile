#----------------------------------------------------------------------
#
# $Id: Makefile,v 1.1 2002-12-17 20:11:06 bkline Exp $
#
# Rules for building and packing up CDR client files.
#
# $Log: not supported by cvs2svn $
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Fix this if it doesn't match the location of your Visual Studio installation
#----------------------------------------------------------------------
DEVENV=C:\Program Files\Microsoft Visual Studio .NET\Common7\IDE\devenv.exe
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
	zip CDRLoaderSetup.zip $(ARCHIVE_FILES)

CDRLoader.exe:
	rm -rf CDRLoader.exe
	"$(DEVENV)" CDRLoader.sln /build Release
	copy Release\CDRLoader.exe

clean:
	rm -rf CDRLoaderSetup.exe CDRLoaderSetup.zip CDRLoader.exe CDRLoader.ncb
