@echo off

cd ..
echo Building project...

cmake --build build --config Release

if %ERRORLEVEL% NEQ 0 (
    echo Build failed
	cd scripts
    exit /b %ERRORLEVEL%
)

echo Done!
cd scripts
pause