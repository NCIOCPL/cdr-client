#----------------------------------------------------------------------
# $Id$
# Rules for building standalone tools supporting the CDR XMetaL client.
#----------------------------------------------------------------------

all: ShowTimestamp.exe InstallCDRClientFiles.exe PatchXMetaL9.exe

ShowTimestamp.exe: ShowTimestamp.cpp
	cl /EHsc ShowTimestamp.cpp

InstallCDRClientFiles.exe: InstallCDRClientFiles.c
	cl InstallCDRClientFiles.c

PatchXMetaL9.exe: PatchXMetaL9.c
	cl PatchXMetaL9.c

clean:
	rm -f *~ *.obj *.exe
