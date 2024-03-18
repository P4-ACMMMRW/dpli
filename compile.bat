@echo off

rem Check if cmake is installed
where cmake >nul 2>nul
if %errorlevel% neq 0 (
    echo cmake could not be found. Please install cmake and try again.
    exit /b 1
)

rem Check if mingw32-make is installed
where mingw32-make >nul 2>nul
if %errorlevel% neq 0 (
    echo mingw32-make could not be found. Please install MinGW and try again.
    exit /b 1
)

rem If ./compile.bat clean
if "%1" == "clean" (
    rd /s /q build
)

rem Check if build directory exists
if not exist build (
    mkdir build
)

cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
cmake --build .

rem Wait until done compiling and then run tests
if %errorlevel% equ 0 (
    echo Compilation successful. Running tests...
    tests\unit_tests.exe
) else (
    echo Compilation failed.
)