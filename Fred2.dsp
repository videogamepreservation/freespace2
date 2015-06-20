# Microsoft Developer Studio Project File - Name="fred2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=fred2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Fred2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fred2.mak" CFG="fred2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fred2 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "fred2 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Freespace2", RHWBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fred2 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G5 /MT /W4 /GX /Ot /Ow /Og /Oi /Oy /Ob2 /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /I "code\nebula" /FI"PSTypes.h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "FRED" /U "_DEBUG" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib vfw32.lib msacm32.lib code.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"nafxcwd.lib" /out:"E:\games\Freespace2\Fred2.exe" /libpath:"release"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "fred2 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "fred2___Win32_Debug"
# PROP BASE Intermediate_Dir "fred2___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "FredDebug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G5 /MDd /W4 /GX /ZI /Od /I "code\anim" /I "code\asteroid" /I "code\bmpman" /I "code\cfile" /I "code\cmdline" /I "code\cmeasure" /I "code\controlconfig" /I "code\cutscene" /I "code\debris" /I "code\debugconsole" /I "code\directx" /I "code\fireball" /I "code\gamehelp" /I "code\freespace2" /I "code\fs2launch" /I "code\fred" /I "code\gamesequence" /I "code\gamesnd" /I "code\glide" /I "code\globalincs" /I "code\graphics" /I "code\hud" /I "code\io" /I "code\jumpnode" /I "code\lighting" /I "code\math" /I "code\menuui" /I "code\mission" /I "code\missionui" /I "code\model" /I "code\movie" /I "code\network" /I "code\object" /I "code\observer" /I "code\osapi" /I "code\palman" /I "code\parse" /I "code\particle" /I "code\pcxutils" /I "code\physics" /I "code\playerman" /I "code\popup" /I "code\radar" /I "code\render" /I "code\ship" /I "code\sndman" /I "code\sound" /I "code\starfield" /I "code\stats" /I "code\testcode" /I "code\ui" /I "code\vcodec" /I "code\weapon" /I "code\localization" /I "code\nebula" /FI"PSTypes.h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /U "NDEBUG" /FR /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo "./FredDebug/*.sbr"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib vfw32.lib msacm32.lib wsock32.lib code.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"nafxcwd.lib" /out:"e:\games\freespace2\Fred2.exe" /pdbtype:sept /libpath:"debug"
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "fred2 - Win32 Release"
# Name "fred2 - Win32 Debug"
# Begin Group "res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\code\fred2\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\res\black_do.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\chained.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\chained_directive.bmp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\data.bmp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\res\FRED.ico
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FRED.rc
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\FRED.rc2
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\res\FREDDoc.ico
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\res\green_do.bmp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\resource.h
# End Source File
# Begin Source File

SOURCE=.\code\fred2\resource.hm
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\root.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\root_directive.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\res\variable.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\code\FRED2\AddVariableDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\AddVariableDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\AdjustGridDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\AdjustGridDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\AsteroidEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\AsteroidEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\BgBitmapDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\BgBitmapDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\BriefingEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\BriefingEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignFilelistBox.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignFilelistBox.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignTreeView.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignTreeWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CampaignTreeWnd.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CmdBrief.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CmdBrief.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CreateWingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\CreateWingDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\DebriefingEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\DebriefingEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\dialog1.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\dialog1.h
# End Source File
# Begin Source File

SOURCE=.\code\fred2\DumpStats.cpp
# End Source File
# Begin Source File

SOURCE=.\code\fred2\DumpStats.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\editor.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\EventEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\EventEditor.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FRED.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FRED.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FREDDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FREDDoc.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FredRender.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FredRender.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FredStubs.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FREDView.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\FREDView.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\Grid.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\Grid.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\IgnoreOrdersDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\IgnoreOrdersDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\InitialShips.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\InitialShips.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\InitialStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\InitialStatus.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\Management.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\Management.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MessageEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MessageEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MissionGoalsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MissionGoalsDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MissionNotesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MissionNotesDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MissionSave.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\MissionSave.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ModifyVariableDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ModifyVariableDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\OperatorArgTypeSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\OperatorArgTypeSelect.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\OrientEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\OrientEditor.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\PlayerStartEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\PlayerStartEditor.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\PrefsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\PrefsDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ReinforcementEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ReinforcementEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\Sexp_tree.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\Sexp_tree.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShieldSysDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShieldSysDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ship_select.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ship_select.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipCheckListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipCheckListBox.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipClassEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipClassEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipFlagsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipFlagsDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipGoalsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipGoalsDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipSpecialDamage.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\ShipSpecialDamage.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\StarfieldEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\StarfieldEditor.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\TextViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\TextViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\WaypointPathDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\WaypointPathDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\WeaponEditorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\WeaponEditorDlg.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\wing.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\wing.h
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\wing_editor.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FRED2\wing_editor.h
# End Source File
# End Target
# End Project
