# Microsoft Developer Studio Project File - Name="HelpEd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HelpEd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HelpEd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HelpEd.mak" CFG="HelpEd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HelpEd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HelpEd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Freespace2", WSSCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HelpEd - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "HelpEd - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "HelpEd___Win32_Debug"
# PROP BASE Intermediate_Dir "HelpEd___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "HelpEdDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W4 /Gm- /GX /Zi /Od /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FD /GZ /c
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
# ADD LINK32 winmm.lib /nologo /subsystem:windows /incremental:no /debug /debugtype:both /machine:I386 /nodefaultlib:"libcd" /nodefaultlib:"libc" /pdbtype:sept /libpath:"debug"

!ENDIF 

# Begin Target

# Name "HelpEd - Win32 Release"
# Name "HelpEd - Win32 Debug"
# Begin Group "res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\HelpEd\res\HelpEd.ico
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\res\HelpEd.rc2
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\res\HelpEdDoc.ico
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\code\HelpEd\HelpEd.cpp
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEd.h
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEd.rc
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEdDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEdDoc.h
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEdLine.cpp
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEdLine.h
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEdView.cpp
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\HelpEdView.h
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\Resource.h
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\code\HelpEd\StdAfx.h
# End Source File
# End Target
# End Project
