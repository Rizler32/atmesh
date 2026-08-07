@echo off
SetLocal EnableDelayedExpansion

set cfiles=
for /R "%~dp0src" %%f in (*.c) do (
    set cfiles=!cfiles! "%%f"
)

set asm=atmesh
set compilerFlags=
set libIncludeFlags=-I"C:\Dev\C++\lib\atil-1.0.0\include"
set libBinFlags=-L"C:\Dev\C++\lib\atil-1.0.0\bin"
set libFlags=-latil_sys
set includeFlags=-I"%~dp0include" -I"%~dp0src"
set defines=

if not "%1"=="--rls" (
    echo Building %asm% in debug mode
    set defines=!defines! -D_DEBUG
) else (
    echo Building %asm% in release mode
)

set "bindir=%~dp0..\bin"
if not exist "%bindir%" mkdir "%bindir%"

rem --- compile the .c files into .o files ---
set ofiles=
for %%f in (!cfiles!) do (
    set "ofile=%%~nf.o"
    gcc -c "%%~f" -o "!ofile!" %compilerFlags% %libIncludeFlags% %libBinFlags% %libFlags% %defines% %includeFlags%
    if errorlevel 1 (
        echo Compilation failed for %%~f
        exit /b %errorlevel%
    )
    set ofiles=!ofiles! "!ofile!"
)

rem --- create the static library ---
ar rcs "%bindir%\lib%asm%.a" %ofiles%

if errorlevel 0 (
    echo Built successfully
) else (
    echo Built with %errorlevel% exit code
)

rem --- clean up ---
del *.o
