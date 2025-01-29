@echo off
REM Set build directory and paths
set BUILD_DIR=.\build
set EXECUTABLE_MAIN=%BUILD_DIR%\Release\Heroes_AI.exe
set EXECUTABLE_TESTS=%BUILD_DIR%\Release\UnitTests.exe
set VCPKG=D:\path\to\vcpkg\vcpkg.cmake

REM Display usage if no arguments are provided
if "%~1"=="" (
    echo Usage: %0 {build|main|tests|debug}
    goto :eof
)

REM Build the project
if /I "%~1"=="build" (
    echo Building the project...
    if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
    cd "%BUILD_DIR%"
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG% -DCMAKE_BUILD_TYPE=Release
    cmake --build . --config Release
    cd ..
    echo Build completed.
    goto :eof
)

REM Run the main program
if /I "%~1"=="main" (
    if exist "%EXECUTABLE_MAIN%" (
        echo Running the main program...
        "%EXECUTABLE_MAIN%"
    ) else (
        echo Main executable not found. Building the project first...
        call %0 build
        "%EXECUTABLE_MAIN%"
    )
    goto :eof
)

REM Build and run the project
if /I "%~1"=="build-run" (
    call %0 build
    "%EXECUTABLE_MAIN%"
    goto :eof
)

REM Run all unit tests
if /I "%~1"=="tests" (
    echo Running unit tests...

    if not exist "%EXECUTABLE_TESTS%" (
        echo Unit test executable not found. Building the project first...
        call %0 build
    )

    REM Run the main unit test suite
    if exist "%EXECUTABLE_TESTS%" (
        "%EXECUTABLE_TESTS%"
    ) else (
        echo UnitTests.exe not found in %BUILD_DIR%\Debug\.
    )

    REM Run all individual test executables
    for %%T in (
        HexTests HexMapTests HealthTests StatisticTests 
        UnitClassTests FieldUnitTests FieldArmyTests InitiativeQueueTests
    ) do (
        if exist "%BUILD_DIR%\Release\%%T.exe" (
            echo Running %%T.exe...
            "%BUILD_DIR%\Release\%%T.exe"
        ) else (
            echo Warning: %%T.exe not found!
        )
    )

    goto :eof
)

echo Usage: %0 {build|main|tests}
