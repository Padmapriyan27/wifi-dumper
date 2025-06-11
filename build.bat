@echo off
setlocal

:: Set compiler (use full path if gcc is not in PATH)
set CC=gcc

:: Set output binary name
set OUT=wifi_dumper.exe

:: Set source files (add all your .c files here)
set SRC=src\interfaces.c src\autoconfig.c src\drivers.c src\dump_profiles.c src\execute.c src\filters.c src\hostednetwork.c src\networks.c src\profiles.c src\main.c

:: Set include directory
set INCLUDE=-Iinclude

:: Compile
echo Compiling...
%CC% %SRC% %INCLUDE% -o %OUT%

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Build successful!
    echo Output: %OUT%
) else (
    echo.
    echo ❌ Build failed!
)

endlocal
pause
