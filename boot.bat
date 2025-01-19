@echo off
REM
REM

REM
set BUILD_DIR=.\build
set EXECUTABLE_MAIN=%BUILD_DIR%\Debug\Heroes_AI.exe
set EXECUTABLE_TESTS=%BUILD_DIR%\Debug\UnitTests.exe
set VCPKG=D:\vcpkg\scripts\buildsystems\vcpkg.cmake

REM
if "%~1"=="" (
    echo Usage: %0 {build|main|tests|debug}
    goto :eof
)

REM
if /I "%~1"=="build" (
    echo Building the project...
    if not exist "%BUILD_DIR%" (
        mkdir "%BUILD_DIR%"
    )
    cd "%BUILD_DIR%"
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG%
    cmake --build .
    cd ..
    echo Build completed.
    goto :eof
)

REM
if /I "%~1"=="main" (
    if exist "%EXECUTABLE_MAIN%" (
        echo Running the main program...
        "%EXECUTABLE_MAIN%"
    ) else (
        echo Main executable not found. Building the project first...
    )
    goto :eof
)

REM
if /I "%~1"=="build-run" (
    echo Building the project...
    if not exist "%BUILD_DIR%" (
        mkdir "%BUILD_DIR%"
    )
    cd "%BUILD_DIR%"
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG%
    cmake --build .
    cd ..
    "%EXECUTABLE_MAIN%"
    goto :eof
)

REM
if /I "%~1"=="tests" (
    if exist "%EXECUTABLE_TESTS%" (
        echo Running unit tests...
        "%EXECUTABLE_TESTS%"
    ) else (
        echo Unit tests executable not found. Building the project first...
    )
    goto :eof
)

REM
if /I "%~1"=="debug" (
    echo Building the project...
    if not exist "%BUILD_DIR%" (
        mkdir "%BUILD_DIR%"
    )
    cd "%BUILD_DIR%"
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG%
    cmake --build . --config Debug
    cd ..
    echo Build completed.
    goto :eof
)

REM
echo Usage: %0 {build|main|tests}
