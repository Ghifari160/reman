@echo off

set REMAN_INSTALL_DIR=%~dp0bin
set REMAN_DOWNLOAD_DIR=%~dp0temp

set REMAN_DOWNLOAD_PS7_URL=https://github.com/PowerShell/PowerShell/releases/download/v7.0.3/PowerShell-7.0.3-win-x86.msi
set REMAN_DOWNLOAD_PS7_TARGET=%REMAN_DOWNLOAD_DIR%\PowerShell-7.0.3-win-x86.msi
set REMAN_PS7_LOC="C:\Program Files (x86)\PowerShell\7\pwsh.exe"

if not exist %~dp0\temp (
    mkdir %~dp0\temp
)

if not exist %REMAN_PS7_LOC% (
    echo PowerShell 7 is not installed! Running installation

    powershell -Command "(New-Object Net.WebClient).DownloadFile($env:REMAN_DOWNLOAD_PS7_URL, $env:REMAN_DOWNLOAD_PS7_TARGET)"
    msiexec /i temp\PowerShell-7.0.3-win-x86.msi /passive REGISTER_MANIFEST=1
) else (
    echo PowerShell 7 is already installed! Skipping installation
)

echo Forcing installation of the latest PowerShell Archive module
pwsh -Command "Install-Module -Name Microsoft.PowerShell.Archive -RequiredVersion 1.2.3.0"

if not exist %REMAN_INSTALL_DIR% (
    mkdir %REMAN_INSTALL_DIR%
)

@REM Install packager as package
@REM Requires Developer Mode or Administrative Permissions to create symbolic links
if exist %REMAN_INSTALL_DIR%\package.cmd (
    del %REMAN_INSTALL_DIR%\package.cmd
)
mklink %REMAN_INSTALL_DIR%\package.cmd %~dp0\src\packager\packager.cmd

echo Cleaning up

if exist %REMAN_DOWNLOAD_DIR% (
    rmdir /s /q %REMAN_DOWNLOAD_DIR%
)


echo Don't forget to add the installation directory to your PATH!
echo Directory: %REMAN_INSTALL_DIR%
echo Some tools will not function unless REMAN_DIR is set!
echo Set REMAN_DIR=%~dp0
