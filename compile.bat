@echo off

REM Check if cmake is installed
where cmake >nul 2>nul
if errorlevel 1 (
    echo cmake could not be found. Please install cmake and try again.
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
cmake --build

REM Wait until done compiling and then run tests
if errorlevel 0 (
    echo Compilation successful. Running tests...
    .\tests\unit_tests.exe
) else (
    echo Compilation failed.
    exit /b 1
)
