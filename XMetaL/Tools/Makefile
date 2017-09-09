#----------------------------------------------------------------------
# Rules for building standalone tools supporting the CDR XMetaL client.
#----------------------------------------------------------------------

all: InstallCDRClientFiles.exe PatchXMetaL9.exe

InstallCDRClientFiles.exe: InstallCDRClientFiles.c
	cl InstallCDRClientFiles.c

PatchXMetaL9.exe: PatchXMetaL9.c
	cl PatchXMetaL9.c

clean:
	rm -f *~ *.obj *.exe
