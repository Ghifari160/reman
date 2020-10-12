@echo off

echo Packaging...

set REMAN_PACKAGER_TARGET=%1\%2-v%3
set REMAN_PACKAGER_TARGET_ZIP=%REMAN_PACKAGER_TARGET%.zip
set REMAN_PACKAGER_TARGET_TGZ=%REMAN_PACKAGER_TARGET%.tar.gz
set REMAN_PACKAGER_TARGET_TBZ=%REMAN_PACKAGER_TARGET%.tar.bz2

if not exist %1 (
    mkdir %1
)

@REM Requires PowerShell 7 and Microsoft.PowerShell.Archive v1.2.3.0 or higher
pwsh -Command "Compress-Archive -Path . -DestinationPath $env:REMAN_PACKAGER_TARGET_ZIP"

@REM Requires Tar. Installed by default on Windows 10
tar --exclude="*.git*" -zcvf %REMAN_PACKAGER_TARGET_TGZ% .

@REM TODO: BZ2 is not installed by default.
@REM tar --exclude="*.git*" -jcvf %REMAN_PACKAGER_TARGET_TBZ% .
