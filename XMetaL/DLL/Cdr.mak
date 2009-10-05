# Microsoft Developer Studio Generated NMAKE File, Based on Cdr.dsp
!IF "$(CFG)" == ""
CFG=Cdr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Cdr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Cdr - Win32 Debug" && "$(CFG)" != "Cdr - Win32 Unicode Debug" && "$(CFG)" != "Cdr - Win32 Release MinSize" && "$(CFG)" != "Cdr - Win32 Release MinDependency" && "$(CFG)" != "Cdr - Win32 Unicode Release MinSize" && "$(CFG)" != "Cdr - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Cdr.mak" CFG="Cdr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Cdr - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Cdr - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Cdr - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Cdr - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Cdr - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Cdr - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Cdr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Cdr.dll" ".\Cdr.tlb" ".\Cdr.h" ".\Cdr_i.c" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Cdr.obj"
	-@erase "$(INTDIR)\Cdr.pch"
	-@erase "$(INTDIR)\Cdr.res"
	-@erase "$(INTDIR)\CdrUtil.obj"
	-@erase "$(INTDIR)\CheckIn.obj"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\EditElement.obj"
	-@erase "$(INTDIR)\LogonDialog.obj"
	-@erase "$(INTDIR)\LogonProgress.obj"
	-@erase "$(INTDIR)\OrgLocs.obj"
	-@erase "$(INTDIR)\ParticOrgs.obj"
	-@erase "$(INTDIR)\PassedValidation.obj"
	-@erase "$(INTDIR)\PersonLocs.obj"
	-@erase "$(INTDIR)\ProtUpdPerson.obj"
	-@erase "$(INTDIR)\RetrieveDialog.obj"
	-@erase "$(INTDIR)\SaveDialog.obj"
	-@erase "$(INTDIR)\SchemaPicklist.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ValidateDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xmetal2.obj"
	-@erase "$(OUTDIR)\Cdr.dll"
	-@erase "$(OUTDIR)\Cdr.exp"
	-@erase "$(OUTDIR)\Cdr.ilk"
	-@erase "$(OUTDIR)\Cdr.lib"
	-@erase "$(OUTDIR)\Cdr.pdb"
	-@erase ".\Cdr.h"
	-@erase ".\Cdr.tlb"
	-@erase ".\Cdr_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Cdr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Cdr.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Cdr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Cdr.pdb" /debug /machine:I386 /def:".\Cdr.def" /out:"$(OUTDIR)\Cdr.dll" /implib:"$(OUTDIR)\Cdr.lib" /pdbtype:sept 
DEF_FILE= \
	".\Cdr.def"
LINK32_OBJS= \
	"$(INTDIR)\Cdr.obj" \
	"$(INTDIR)\CdrUtil.obj" \
	"$(INTDIR)\CheckIn.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\EditElement.obj" \
	"$(INTDIR)\LogonDialog.obj" \
	"$(INTDIR)\LogonProgress.obj" \
	"$(INTDIR)\OrgLocs.obj" \
	"$(INTDIR)\ParticOrgs.obj" \
	"$(INTDIR)\PassedValidation.obj" \
	"$(INTDIR)\PersonLocs.obj" \
	"$(INTDIR)\ProtUpdPerson.obj" \
	"$(INTDIR)\RetrieveDialog.obj" \
	"$(INTDIR)\SaveDialog.obj" \
	"$(INTDIR)\SchemaPicklist.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ValidateDialog.obj" \
	"$(INTDIR)\xmetal2.obj" \
	"$(INTDIR)\Cdr.res"

"$(OUTDIR)\Cdr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Cdr.dll
InputPath=.\Debug\Cdr.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\Cdr.dll" ".\Cdr.tlb" ".\Cdr.h" ".\Cdr_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Cdr.obj"
	-@erase "$(INTDIR)\Cdr.pch"
	-@erase "$(INTDIR)\Cdr.res"
	-@erase "$(INTDIR)\CdrUtil.obj"
	-@erase "$(INTDIR)\CheckIn.obj"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\EditElement.obj"
	-@erase "$(INTDIR)\LogonDialog.obj"
	-@erase "$(INTDIR)\LogonProgress.obj"
	-@erase "$(INTDIR)\OrgLocs.obj"
	-@erase "$(INTDIR)\ParticOrgs.obj"
	-@erase "$(INTDIR)\PassedValidation.obj"
	-@erase "$(INTDIR)\PersonLocs.obj"
	-@erase "$(INTDIR)\ProtUpdPerson.obj"
	-@erase "$(INTDIR)\RetrieveDialog.obj"
	-@erase "$(INTDIR)\SaveDialog.obj"
	-@erase "$(INTDIR)\SchemaPicklist.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ValidateDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xmetal2.obj"
	-@erase "$(OUTDIR)\Cdr.dll"
	-@erase "$(OUTDIR)\Cdr.exp"
	-@erase "$(OUTDIR)\Cdr.ilk"
	-@erase "$(OUTDIR)\Cdr.lib"
	-@erase "$(OUTDIR)\Cdr.pdb"
	-@erase ".\Cdr.h"
	-@erase ".\Cdr.tlb"
	-@erase ".\Cdr_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Cdr.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Cdr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Cdr.pdb" /debug /machine:I386 /def:".\Cdr.def" /out:"$(OUTDIR)\Cdr.dll" /implib:"$(OUTDIR)\Cdr.lib" /pdbtype:sept 
DEF_FILE= \
	".\Cdr.def"
LINK32_OBJS= \
	"$(INTDIR)\Cdr.obj" \
	"$(INTDIR)\CdrUtil.obj" \
	"$(INTDIR)\CheckIn.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\EditElement.obj" \
	"$(INTDIR)\LogonDialog.obj" \
	"$(INTDIR)\LogonProgress.obj" \
	"$(INTDIR)\OrgLocs.obj" \
	"$(INTDIR)\ParticOrgs.obj" \
	"$(INTDIR)\PassedValidation.obj" \
	"$(INTDIR)\PersonLocs.obj" \
	"$(INTDIR)\ProtUpdPerson.obj" \
	"$(INTDIR)\RetrieveDialog.obj" \
	"$(INTDIR)\SaveDialog.obj" \
	"$(INTDIR)\SchemaPicklist.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ValidateDialog.obj" \
	"$(INTDIR)\xmetal2.obj" \
	"$(INTDIR)\Cdr.res"

"$(OUTDIR)\Cdr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Cdr.dll
InputPath=.\DebugU\Cdr.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "Cdr - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\Cdr.dll" ".\Cdr.tlb" ".\Cdr.h" ".\Cdr_i.c" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Cdr.obj"
	-@erase "$(INTDIR)\Cdr.pch"
	-@erase "$(INTDIR)\Cdr.res"
	-@erase "$(INTDIR)\CdrUtil.obj"
	-@erase "$(INTDIR)\CheckIn.obj"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\EditElement.obj"
	-@erase "$(INTDIR)\LogonDialog.obj"
	-@erase "$(INTDIR)\LogonProgress.obj"
	-@erase "$(INTDIR)\OrgLocs.obj"
	-@erase "$(INTDIR)\ParticOrgs.obj"
	-@erase "$(INTDIR)\PassedValidation.obj"
	-@erase "$(INTDIR)\PersonLocs.obj"
	-@erase "$(INTDIR)\ProtUpdPerson.obj"
	-@erase "$(INTDIR)\RetrieveDialog.obj"
	-@erase "$(INTDIR)\SaveDialog.obj"
	-@erase "$(INTDIR)\SchemaPicklist.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ValidateDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xmetal2.obj"
	-@erase "$(OUTDIR)\Cdr.dll"
	-@erase "$(OUTDIR)\Cdr.exp"
	-@erase "$(OUTDIR)\Cdr.lib"
	-@erase ".\Cdr.h"
	-@erase ".\Cdr.tlb"
	-@erase ".\Cdr_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Cdr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Cdr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Cdr.pdb" /machine:I386 /def:".\Cdr.def" /out:"$(OUTDIR)\Cdr.dll" /implib:"$(OUTDIR)\Cdr.lib" 
DEF_FILE= \
	".\Cdr.def"
LINK32_OBJS= \
	"$(INTDIR)\Cdr.obj" \
	"$(INTDIR)\CdrUtil.obj" \
	"$(INTDIR)\CheckIn.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\EditElement.obj" \
	"$(INTDIR)\LogonDialog.obj" \
	"$(INTDIR)\LogonProgress.obj" \
	"$(INTDIR)\OrgLocs.obj" \
	"$(INTDIR)\ParticOrgs.obj" \
	"$(INTDIR)\PassedValidation.obj" \
	"$(INTDIR)\PersonLocs.obj" \
	"$(INTDIR)\ProtUpdPerson.obj" \
	"$(INTDIR)\RetrieveDialog.obj" \
	"$(INTDIR)\SaveDialog.obj" \
	"$(INTDIR)\SchemaPicklist.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ValidateDialog.obj" \
	"$(INTDIR)\xmetal2.obj" \
	"$(INTDIR)\Cdr.res"

"$(OUTDIR)\Cdr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Cdr.dll
InputPath=.\ReleaseMinSize\Cdr.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Cdr - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\Cdr.dll" ".\Cdr.tlb" ".\Cdr.h" ".\Cdr_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Cdr.obj"
	-@erase "$(INTDIR)\Cdr.pch"
	-@erase "$(INTDIR)\Cdr.res"
	-@erase "$(INTDIR)\CdrUtil.obj"
	-@erase "$(INTDIR)\CheckIn.obj"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\EditElement.obj"
	-@erase "$(INTDIR)\LogonDialog.obj"
	-@erase "$(INTDIR)\LogonProgress.obj"
	-@erase "$(INTDIR)\OrgLocs.obj"
	-@erase "$(INTDIR)\ParticOrgs.obj"
	-@erase "$(INTDIR)\PassedValidation.obj"
	-@erase "$(INTDIR)\PersonLocs.obj"
	-@erase "$(INTDIR)\ProtUpdPerson.obj"
	-@erase "$(INTDIR)\RetrieveDialog.obj"
	-@erase "$(INTDIR)\SaveDialog.obj"
	-@erase "$(INTDIR)\SchemaPicklist.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ValidateDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xmetal2.obj"
	-@erase "$(OUTDIR)\Cdr.dll"
	-@erase "$(OUTDIR)\Cdr.exp"
	-@erase "$(OUTDIR)\Cdr.lib"
	-@erase ".\Cdr.h"
	-@erase ".\Cdr.tlb"
	-@erase ".\Cdr_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Cdr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Cdr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Cdr.pdb" /machine:I386 /def:".\Cdr.def" /out:"$(OUTDIR)\Cdr.dll" /implib:"$(OUTDIR)\Cdr.lib" 
DEF_FILE= \
	".\Cdr.def"
LINK32_OBJS= \
	"$(INTDIR)\Cdr.obj" \
	"$(INTDIR)\CdrUtil.obj" \
	"$(INTDIR)\CheckIn.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\EditElement.obj" \
	"$(INTDIR)\LogonDialog.obj" \
	"$(INTDIR)\LogonProgress.obj" \
	"$(INTDIR)\OrgLocs.obj" \
	"$(INTDIR)\ParticOrgs.obj" \
	"$(INTDIR)\PassedValidation.obj" \
	"$(INTDIR)\PersonLocs.obj" \
	"$(INTDIR)\ProtUpdPerson.obj" \
	"$(INTDIR)\RetrieveDialog.obj" \
	"$(INTDIR)\SaveDialog.obj" \
	"$(INTDIR)\SchemaPicklist.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ValidateDialog.obj" \
	"$(INTDIR)\xmetal2.obj" \
	"$(INTDIR)\Cdr.res"

"$(OUTDIR)\Cdr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\Cdr.dll
InputPath=.\ReleaseMinDependency\Cdr.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\Cdr.dll" ".\Cdr.tlb" ".\Cdr.h" ".\Cdr_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Cdr.obj"
	-@erase "$(INTDIR)\Cdr.pch"
	-@erase "$(INTDIR)\Cdr.res"
	-@erase "$(INTDIR)\CdrUtil.obj"
	-@erase "$(INTDIR)\CheckIn.obj"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\EditElement.obj"
	-@erase "$(INTDIR)\LogonDialog.obj"
	-@erase "$(INTDIR)\LogonProgress.obj"
	-@erase "$(INTDIR)\OrgLocs.obj"
	-@erase "$(INTDIR)\ParticOrgs.obj"
	-@erase "$(INTDIR)\PassedValidation.obj"
	-@erase "$(INTDIR)\PersonLocs.obj"
	-@erase "$(INTDIR)\ProtUpdPerson.obj"
	-@erase "$(INTDIR)\RetrieveDialog.obj"
	-@erase "$(INTDIR)\SaveDialog.obj"
	-@erase "$(INTDIR)\SchemaPicklist.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ValidateDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xmetal2.obj"
	-@erase "$(OUTDIR)\Cdr.dll"
	-@erase "$(OUTDIR)\Cdr.exp"
	-@erase "$(OUTDIR)\Cdr.lib"
	-@erase ".\Cdr.h"
	-@erase ".\Cdr.tlb"
	-@erase ".\Cdr_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Cdr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Cdr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Cdr.pdb" /machine:I386 /def:".\Cdr.def" /out:"$(OUTDIR)\Cdr.dll" /implib:"$(OUTDIR)\Cdr.lib" 
DEF_FILE= \
	".\Cdr.def"
LINK32_OBJS= \
	"$(INTDIR)\Cdr.obj" \
	"$(INTDIR)\CdrUtil.obj" \
	"$(INTDIR)\CheckIn.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\EditElement.obj" \
	"$(INTDIR)\LogonDialog.obj" \
	"$(INTDIR)\LogonProgress.obj" \
	"$(INTDIR)\OrgLocs.obj" \
	"$(INTDIR)\ParticOrgs.obj" \
	"$(INTDIR)\PassedValidation.obj" \
	"$(INTDIR)\PersonLocs.obj" \
	"$(INTDIR)\ProtUpdPerson.obj" \
	"$(INTDIR)\RetrieveDialog.obj" \
	"$(INTDIR)\SaveDialog.obj" \
	"$(INTDIR)\SchemaPicklist.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ValidateDialog.obj" \
	"$(INTDIR)\xmetal2.obj" \
	"$(INTDIR)\Cdr.res"

"$(OUTDIR)\Cdr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Cdr.dll
InputPath=.\ReleaseUMinSize\Cdr.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\Cdr.dll" ".\Cdr.tlb" ".\Cdr.h" ".\Cdr_i.c" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\Cdr.obj"
	-@erase "$(INTDIR)\Cdr.pch"
	-@erase "$(INTDIR)\Cdr.res"
	-@erase "$(INTDIR)\CdrUtil.obj"
	-@erase "$(INTDIR)\CheckIn.obj"
	-@erase "$(INTDIR)\Commands.obj"
	-@erase "$(INTDIR)\EditElement.obj"
	-@erase "$(INTDIR)\LogonDialog.obj"
	-@erase "$(INTDIR)\LogonProgress.obj"
	-@erase "$(INTDIR)\OrgLocs.obj"
	-@erase "$(INTDIR)\ParticOrgs.obj"
	-@erase "$(INTDIR)\PassedValidation.obj"
	-@erase "$(INTDIR)\PersonLocs.obj"
	-@erase "$(INTDIR)\ProtUpdPerson.obj"
	-@erase "$(INTDIR)\RetrieveDialog.obj"
	-@erase "$(INTDIR)\SaveDialog.obj"
	-@erase "$(INTDIR)\SchemaPicklist.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\ValidateDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xmetal2.obj"
	-@erase "$(OUTDIR)\Cdr.dll"
	-@erase "$(OUTDIR)\Cdr.exp"
	-@erase "$(OUTDIR)\Cdr.lib"
	-@erase ".\Cdr.h"
	-@erase ".\Cdr.tlb"
	-@erase ".\Cdr_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Cdr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Cdr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Cdr.pdb" /machine:I386 /def:".\Cdr.def" /out:"$(OUTDIR)\Cdr.dll" /implib:"$(OUTDIR)\Cdr.lib" 
DEF_FILE= \
	".\Cdr.def"
LINK32_OBJS= \
	"$(INTDIR)\Cdr.obj" \
	"$(INTDIR)\CdrUtil.obj" \
	"$(INTDIR)\CheckIn.obj" \
	"$(INTDIR)\Commands.obj" \
	"$(INTDIR)\EditElement.obj" \
	"$(INTDIR)\LogonDialog.obj" \
	"$(INTDIR)\LogonProgress.obj" \
	"$(INTDIR)\OrgLocs.obj" \
	"$(INTDIR)\ParticOrgs.obj" \
	"$(INTDIR)\PassedValidation.obj" \
	"$(INTDIR)\PersonLocs.obj" \
	"$(INTDIR)\ProtUpdPerson.obj" \
	"$(INTDIR)\RetrieveDialog.obj" \
	"$(INTDIR)\SaveDialog.obj" \
	"$(INTDIR)\SchemaPicklist.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\ValidateDialog.obj" \
	"$(INTDIR)\xmetal2.obj" \
	"$(INTDIR)\Cdr.res"

"$(OUTDIR)\Cdr.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\Cdr.dll
InputPath=.\ReleaseUMinDependency\Cdr.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Cdr.dep")
!INCLUDE "Cdr.dep"
!ELSE 
!MESSAGE Warning: cannot find "Cdr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Cdr - Win32 Debug" || "$(CFG)" == "Cdr - Win32 Unicode Debug" || "$(CFG)" == "Cdr - Win32 Release MinSize" || "$(CFG)" == "Cdr - Win32 Release MinDependency" || "$(CFG)" == "Cdr - Win32 Unicode Release MinSize" || "$(CFG)" == "Cdr - Win32 Unicode Release MinDependency"
SOURCE=.\Cdr.cpp

"$(INTDIR)\Cdr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\Cdr.idl

!IF  "$(CFG)" == "Cdr - Win32 Debug"

MTL_SWITCHES=/tlb ".\Cdr.tlb" /h "Cdr.h" /iid "Cdr_i.c" /Oicf 

".\Cdr.tlb"	".\Cdr.h"	".\Cdr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Debug"

MTL_SWITCHES=/tlb ".\Cdr.tlb" /h "Cdr.h" /iid "Cdr_i.c" /Oicf 

".\Cdr.tlb"	".\Cdr.h"	".\Cdr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\Cdr.tlb" /h "Cdr.h" /iid "Cdr_i.c" /Oicf 

".\Cdr.tlb"	".\Cdr.h"	".\Cdr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Release MinDependency"

MTL_SWITCHES=/tlb ".\Cdr.tlb" /h "Cdr.h" /iid "Cdr_i.c" /Oicf 

".\Cdr.tlb"	".\Cdr.h"	".\Cdr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\Cdr.tlb" /h "Cdr.h" /iid "Cdr_i.c" /Oicf 

".\Cdr.tlb"	".\Cdr.h"	".\Cdr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Release MinDependency"

MTL_SWITCHES=/tlb ".\Cdr.tlb" /h "Cdr.h" /iid "Cdr_i.c" /Oicf 

".\Cdr.tlb"	".\Cdr.h"	".\Cdr_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Cdr.rc

"$(INTDIR)\Cdr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\CdrUtil.cpp

"$(INTDIR)\CdrUtil.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\CheckIn.cpp

"$(INTDIR)\CheckIn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\Commands.cpp

"$(INTDIR)\Commands.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\EditElement.cpp

"$(INTDIR)\EditElement.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\LogonDialog.cpp

"$(INTDIR)\LogonDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\LogonProgress.cpp

"$(INTDIR)\LogonProgress.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\OrgLocs.cpp

"$(INTDIR)\OrgLocs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\ParticOrgs.cpp

"$(INTDIR)\ParticOrgs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\PassedValidation.cpp

"$(INTDIR)\PassedValidation.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\PersonLocs.cpp

"$(INTDIR)\PersonLocs.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\ProtUpdPerson.cpp

"$(INTDIR)\ProtUpdPerson.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\RetrieveDialog.cpp

"$(INTDIR)\RetrieveDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\SaveDialog.cpp

"$(INTDIR)\SaveDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\SchemaPicklist.cpp

"$(INTDIR)\SchemaPicklist.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\SearchDialog.cpp

"$(INTDIR)\SearchDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Cdr - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Cdr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Cdr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Cdr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Cdr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Cdr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Cdr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Cdr - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_WINDLL" /Fp"$(INTDIR)\Cdr.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Cdr.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ValidateDialog.cpp

"$(INTDIR)\ValidateDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"


SOURCE=.\xmetal2.cpp

"$(INTDIR)\xmetal2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Cdr.pch"



!ENDIF 

