@echo off
setlocal enabledelayedexpansion

REM 获取工程目录

set ROOT_DIR=%~dp0
call :GetFullPath "%ROOT_DIR%\.." ROOT

if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
    set "PLATFORM=x64"
) else (
    set "PLATFORM=Win32"
)

set VSWHERE="false"
set VS_INSTALLER=

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    set VSWHERE="true"
    set VS_INSTALLER="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
    cd "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
) else if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" (
    set VSWHERE="true"
    set VS_INSTALLER="%ProgramFiles%\Microsoft Visual Studio\Installer"
    cd "%ProgramFiles%\Microsoft Visual Studio\Installer"
) else (
    echo "vswhere tool is not found"
)

set MSBUILD_BIN=
set VS_PATH=

if %VSWHERE% == "true" (
    for /f "usebackq tokens=*" %%i in (`vswhere -latest -products * -requires Microsoft.Component.MSBuild -property installationPath`) do (
       set VS_PATH=%%i
    )
    if exist "!VS_PATH!\MSBuild\14.0\Bin\MSBuild.exe" (
        set "MSBUILD_BIN=!VS_PATH!\MSBuild\14.0\Bin\MSBuild.exe"
    )
    if exist "!VS_PATH!\MSBuild\15.0\Bin\MSBuild.exe" (
        set "MSBUILD_BIN=!VS_PATH!\MSBuild\15.0\Bin\MSBuild.exe"
    )
    if exist "!VS_PATH!\MSBuild\Current\Bin\MSBuild.exe" ( 
        set "MSBUILD_BIN=!VS_PATH!\MSBuild\Current\Bin\MSBuild.exe"
    )
)

if "!MSBUILD_BIN!" == "" (
   if exist "C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" (
      set "MSBUILD_BIN=C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe"
      set "MSBUILD_VERSION=14 2015"
   )
   if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin\MSBuild.exe" (
      set "MSBUILD_BIN=C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin\MSBuild.exe"
      set "MSBUILD_VERSION=15 2017"
   )
   if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" (
      set "MSBUILD_BIN=C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
      set "MSBUILD_VERSION=15 2017"
   )
   if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe" (
      set "MSBUILD_BIN=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\MSBuild\15.0\Bin\MSBuild.exe"
      set "MSBUILD_VERSION=15 2017"
   )
) else (
   if not "!MSBUILD_BIN:2019=!"=="!MSBUILD_BIN!" set "MSBUILD_VERSION=16 2019"
   if not "!MSBUILD_BIN:2017=!"=="!MSBUILD_BIN!" set "MSBUILD_VERSION=15 2017"
   if not "!MSBUILD_BIN:2015=!"=="!MSBUILD_BIN!" set "MSBUILD_VERSION=14 2015"
)

if "!MSBUILD_BIN!" == "" (
   echo Build tools for Visual Studio 2015 / 2017 / 2019 cannot be found. If you use Visual Studio 2017 / 2019, please download and install build tools from https://www.visualstudio.com/downloads/#build-tools-for-visual-studio-2017
   GOTO errorHandling
)

REM 检查当前系统的平台cd ..

REM 代码目录
set "DEMO_USE01_CODE_DIR=%ROOT%\use01"

REM 编译目录
set "DEMO_USE01_BUILD_DIR=%ROOT%\build\use01"

echo ROOT_DIR=%ROOT_DIR%
echo DEMO_USE01_DIR=%DEMO_USE01_CODE_DIR%
echo ROOT=%ROOT%
echo VS_INSTALLER=%VS_INSTALLER%
echo PLATFORM=%PLATFORM%
echo MSBUILD_VERSION=%MSBUILD_VERSION%

REM 1.创建工程

echo Creating Visual Studio !MSBUILD_VERSION! %PLATFORM% files in %DEMO_USE01_BUILD_DIR%... && ^
if exist "%DEMO_USE01_BUILD_DIR%\CMakeCache.txt" del "%DEMO_USE01_BUILD_DIR%\CMakeCache.txt"
cd "%DEMO_USE01_CODE_DIR%" && cmake -E make_directory "%DEMO_USE01_BUILD_DIR%" && cd "%DEMO_USE01_BUILD_DIR%" && cmake -G "Visual Studio !MSBUILD_VERSION!" -A %PLATFORM% "%DEMO_USE01_CODE_DIR%"
if ERRORLEVEL 1 GOTO errorHandling

timeout 7

REM 2.编译
echo.
echo ###############^|^| Build use01 using MS Visual Studio (MSBuild.exe) ^|^|###############
echo.
timeout 3
echo "!MSBUILD_BIN!" use01.sln /p:Configuration=Release /t:use01 /clp:ErrorsOnly /m
"!MSBUILD_BIN!" use01.sln /p:Configuration=Release /t:use01 /clp:ErrorsOnly /m
if ERRORLEVEL 1 GOTO errorHandling

timeout 7

REM 3.执行

:runSample
echo.
echo ###############^|^| Run use01 demo ^|^|###############
echo.
timeout 3
cd "%DEMO_USE01_BUILD_DIR%\Release"
echo "%DEMO_USE01_BUILD_DIR%\Release\use01.exe"
use01.exe
if ERRORLEVEL 1 GOTO errorHandling

exit /B 0

:GetFullPath
SET %2=%~f1

GOTO :EOF

:errorHandling
echo Error
cd "%ROOT_DIR%"