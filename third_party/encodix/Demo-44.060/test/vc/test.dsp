# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "test - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "test - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".." /I "..\..\gen" /I "..\..\..\Common" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /Zm200 /c
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x410 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".." /I "..\..\gen" /I "..\..\..\Common" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /Zm200 /c
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\main.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ts44.060_support.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\ed_user.h
# End Source File
# End Group
# Begin Group "Generated"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\gen\CSN1DataTypes.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\CSN1DataTypes.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\Downlink_RLC_MAC.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\Downlink_RLC_MAC.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_access.cpp
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_access.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_dump.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_dump.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_known_ie.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_known_ie.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_recog.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\ed_c_recog.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\endec_configs.h
# End Source File
# Begin Source File

SOURCE=..\..\gen\Uplink_RLC_MAC.c
# End Source File
# Begin Source File

SOURCE=..\..\gen\Uplink_RLC_MAC.h
# End Source File
# End Group
# Begin Group "Encodix Libraries"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\Common\bitencode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\bitencode.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\csn1clib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\csn1clib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_access.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_access.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_access_class.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_access_data.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_access_util.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_dump.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_dump.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_dump_file.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_dump_file.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_dump_val.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_dump_val.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_lib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_lib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\Common\ed_tlv.h
# End Source File
# End Group
# End Target
# End Project
