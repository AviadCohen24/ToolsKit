@echo off
REM Run node-gyp configure
call node-gyp configure

REM Run node-gyp build
call node-gyp build

REM Copy the HardwareManagerAddon.node to the specified directory
copy .\build\Release\HardwareManagerAddon.node ..\electron\src\shared\hardware

echo Process completed.
pause
