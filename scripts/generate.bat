@echo off

cd ..
echo Generating project...

cmake -S . -B build -G "Visual Studio 17 2022"

if %ERRORLEVEL% NEQ 0 (
    echo Generation failed
	cd scripts
    exit /b %ERRORLEVEL%
)

echo Done!
cd scripts
pause