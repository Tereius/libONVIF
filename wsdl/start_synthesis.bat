@ECHO OFF
REM ------------------------change------------------------
set REL_PATH_TO_GSOAP_SRC_DIR=..\thirdparty\src\gsoap
set REL_PATH_TO_GSOAP_INSTALL_DIR=..\thirdparty\build\gsoap
set VS_COMNTOOLS_VAR=%VS120COMNTOOLS%
REM ------------------------------------------------------
SETLOCAL EnableDelayedExpansion
for /F "tokens=1,2 delims=#" %%a in ('"prompt #$H#$E# & echo on & for %%b in (1) do rem"') do (
  set "DEL=%%a"
)

call :ColorText 0d "This batch file does codesynthesis using gsoap."
ECHO.

:START
set CURRENT_DIR=%~dp0

%CURRENT_DIR%\%REL_PATH_TO_GSOAP_INSTALL_DIR%\bin\wsdl2h -c++11 -d -p -j -t typemap.dat -o rcx.h^
 http://www.onvif.org/onvif/ver10/analyticsdevice.wsdl^
 http://www.onvif.org/onvif/ver10/replay.wsdl^
 http://www.onvif.org/onvif/ver10/search.wsdl^
 http://www.onvif.org/onvif/ver10/recording.wsdl^
 http://www.onvif.org/onvif/ver10/receiver.wsdl^
 http://www.onvif.org/onvif/ver20/ptz/wsdl/ptz.wsdl^
 http://www.onvif.org/onvif/ver10/media/wsdl/media.wsdl^
 http://www.onvif.org/onvif/ver20/imaging/wsdl/imaging.wsdl^
 http://www.onvif.org/onvif/ver10/display.wsdl^
 http://www.onvif.org/onvif/ver10/events/wsdl/event.wsdl^
 http://www.onvif.org/onvif/ver10/device/wsdl/devicemgmt.wsdl^
 http://www.onvif.org/onvif/ver20/analytics/wsdl/analytics.wsdl
IF %errorlevel% neq 0 GOTO :ERROR
%CURRENT_DIR%\%REL_PATH_TO_GSOAP_INSTALL_DIR%\bin\soapcpp2 -Ed -Ec -c++11 -a -j -L -x -n -d %CURRENT_DIR%\..\src\generated -I %CURRENT_DIR%\%REL_PATH_TO_GSOAP_INSTALL_DIR%\share\gsoap;%CURRENT_DIR%\%REL_PATH_TO_GSOAP_INSTALL_DIR%\share\gsoap\import;%CURRENT_DIR%\..\src\gsoap rcx.h
IF %errorlevel% neq 0 GOTO :ERROR
GOTO :SUCCESS

:TRY
call :ColorText 0d "This batch file must be run from the Visual Studio command prompt. Will try to open it."
ECHO.
call "%VS_COMNTOOLS_VAR%VsDevCmd.bat"
IF errorlevel 1 (
	call :ColorText 0d "Couldn't open Visual Studio command prompt."
	ECHO.
	GOTO ERROR
)
GOTO :CONTINUE

:ERROR
call :ColorText 0c "Build failed"
ECHO.
PAUSE
GOTO :eof

:SUCCESS
call :ColorText 0a "Build succeeds"
ECHO.
PAUSE
GOTO :eof

:ColorText
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1 & echo.
GOTO :eof