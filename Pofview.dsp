# Microsoft Developer Studio Project File - Name="Pofview" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Pofview - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Pofview.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Pofview.mak" CFG="Pofview - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Pofview - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Pofview - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Freespace2", ARCCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Pofview - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "PofViewRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /I "code\nebula" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /U "_DEBUG" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib msacm32.lib comctl32.lib wsock32.lib code.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /libpath:"release"

!ELSEIF  "$(CFG)" == "Pofview - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Pofview___Win32_Debug"
# PROP BASE Intermediate_Dir "Pofview___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "PofViewDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W4 /GX /Zi /Od /Ob2 /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /I "code\fred2" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib msacm32.lib comctl32.lib wsock32.lib code.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /out:"E:\games\freespace2\Pofview.exe" /pdbtype:sept /libpath:"debug"

!ENDIF 

# Begin Target

# Name "Pofview - Win32 Release"
# Name "Pofview - Win32 Debug"
# Begin Group "res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\pofview\res\PofView.ico
# End Source File
# Begin Source File

SOURCE=.\code\pofview\res\PofView.rc2
# End Source File
# Begin Source File

SOURCE=.\code\pofview\res\PofViewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\code\pofview\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\code\pofview\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\ObjectTree.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\ObjectTree.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofView.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofView.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofView.rc
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofViewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofViewDoc.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofViewStubs.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofViewView.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\PofViewView.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\resource.h
# End Source File
# Begin Source File

SOURCE=.\code\pofview\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\code\pofview\StdAfx.h
# End Source File
# End Target
# End Project
