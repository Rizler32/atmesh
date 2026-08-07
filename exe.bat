@echo off

"%~dp0bin/atmesh-app.exe" %*

echo Exit code: %errorlevel%
if errorlevel 1 (
    exit /b %errorlevel%
)

exit /b 0
