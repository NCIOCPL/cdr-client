#----------------------------------------------------------------------
# Rules for building standalone tools supporting the CDR XMetaL client.
#----------------------------------------------------------------------

all: InstallCDRClientFiles.exe regcdrdll.exe

InstallCDRClientFiles.exe: InstallCDRClientFiles.c
	cl /EHsc InstallCDRClientFiles.c

regcdrdll.exe: regcdrdll.cpp
	cl /EHsc regcdrdll.cpp

clean:
	rm -f *~ *.obj *.exe
