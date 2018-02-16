all:
	devenv Cdr.sln /build "Unicode Release MinDependency"
launch-ie.exe: launch-ie.cpp
	cl /EHsc /MD launch-ie.cpp
clean:
	rm -rf cdr_p.c cdr.ncb ReleaseUMinDependency cdr.sdf ipch Cdr.vcxproj.user\
launch-ie.exe launch-ie.ilk launch-ie.pdb launch-ie.sln vc120.pdb Cdr.h \
Cdr.tlb Cdr_i.c dlldata.c
