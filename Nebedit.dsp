# Microsoft Developer Studio Project File - Name="Nebedit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Nebedit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Nebedit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Nebedit.mak" CFG="Nebedit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Nebedit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Nebedit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Freespace2", RQCCAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Nebedit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "NebeditRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /I "code\nebula" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /U "_DEBUG" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /libpath:"release"

!ELSEIF  "$(CFG)" == "Nebedit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Nebedit___Win32_Debug"
# PROP BASE Intermediate_Dir "Nebedit___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "NebEditDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W4 /GX /Zi /Od /Ob2 /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "NEBEDIT" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib msacm32.lib comctl32.lib wsock32.lib code.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /out:"E:\games\freespace2\Nebedit.exe" /pdbtype:sept /libpath:"debug"

!ENDIF 

# Begin Target

# Name "Nebedit - Win32 Release"
# Name "Nebedit - Win32 Debug"
# Begin Source File

SOURCE=.\code\nebedit\NebEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\code\nebedit\Nebstubs.cpp
# End Source File
# End Target
# End Project
