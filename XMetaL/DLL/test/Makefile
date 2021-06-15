CFLAGS=/D_UNICODE /DWIN32 /EHsc /D "_WIN32_WINNT=0x0600" /DTESTMAIN /I..
LFLAGS=/link msxml6.lib ole32.lib oleaut32.lib
tcdrdom.exe: tcdrdom.cpp cdrdom.obj
	cl $(CFLAGS) tcdrdom.cpp cdrdom.obj $(LFLAGS)
cdrdom.obj: ../cdrdom.cpp ../cdrdom.h
	cl $(CFLAGS) -c ../cdrdom.cpp
clean:
	rm -f *.obj *.pdb *~ *.exe *.ilk
