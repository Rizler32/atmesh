@echo off
setlocal enabledelayedexpansion

pushd "%~dp0" >nul 2>&1 || exit /b 1

set platform_specific_libs=
set compilerFlags=-latmesh
set defines=
set asm=atmesh-app

if not "%1"=="--rls" (
    echo Building %asm% in debug mode
    set defines=!defines! -D_DEBUG
) else (
    echo Building %asm% in release mode
)

set includeDir=%~dp0include
set srcDir=%~dp0src
set binDir=%~dp0..\bin

set atmeshIncludeDir=%~dp0../atmesh/include
set atmeshLibDir=%~dp0../bin

set libIncludeFlags=-I"C:\Dev\C++\lib\glfw-3.4\include" ^
                    -I"C:\Dev\C++\lib\atil-1.0.0\include" ^
                    -I"C:\Dev\C++\lib\glad\include" ^
                    -I"C:\Dev\C++\lib\nuklear\include" ^
                    -I"C:\Dev\C++\lib\libstl\include" ^
                    -I"C:\Dev\C++\lib\tinyobjloader-c\include"

set libBinFlags=-L"C:\Dev\C++\lib\glfw-3.4\lib-mingw-w64" ^
                -L"C:\Dev\C++\lib\atil-1.0.0\bin" ^
                -L"C:\Dev\C++\lib\glad\lib-mingw-w64" ^
                -L"C:\Dev\C++\lib\nuklear\bin" ^
                -L"C:\Dev\C++\lib\libstl\bin" ^
                -L"C:\Dev\C++\lib\tinyobjloader-c\bin"

set libFlags=-lglad -lnk_glfw_gl3 -lnuklear -lglfw3dll -lopengl32 -lgdi32 -latil_sys -lcomdlg32 -llibstl -ltinyobjloaderc

if not exist "%bindir%" mkdir "%bindir%"

echo Building atmesh-app

REM ---------------------------------------------------------
REM 1. Raccogli tutti i .c da src/ e include/
REM ---------------------------------------------------------
set "sources="

for /r "%srcDir%" %%f in (*.c) do (
    set "sources=!sources! "%%f""
)

REM Aggiungi main.c dell'app se esiste
if exist "main.c" (
    set "sources=!sources! main.c"
) else (
    echo WARNING: main.c not found in app directory.
)

REM ---------------------------------------------------------
REM 2. Compila tutto in un colpo solo
REM ---------------------------------------------------------
gcc %sources% ^
    %defines% %compilerFlags% ^
    %platform_specific_libs% ^
    %libIncludeFlags% %libBinFlags% %libFlags% ^
    -I"%includeDir%" -I"%srcDir%" ^
    -I"%atmeshIncludeDir%" -L"%atmeshLibDir%" ^
    -o "%binDir%\atmesh-app.exe"

if errorlevel 1 (
    echo ERROR: compilation failed.
    exit /b 1
)

popd >nul 2>&1

echo Build complete.
