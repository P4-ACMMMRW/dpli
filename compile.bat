@echo off

REM Check if cmake is installed
where cmake >nul 2>nul
if errorlevel 1 (
    echo cmake could not be found. Please install cmake and try again.
    exit /b 1
)

REM Check if make is installed
where make >nul 2>nul
if errorlevel 1 (
    echo make could not be found. Please install make and try again.
    exit /b 1
)

REM If build clean
if "%~1"=="clean" (
    if exist build rmdir /s /q build
)

REM Check if build directory exists
if not exist build mkdir build

cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make