@echo off
setlocal
PATH = C:\Program Files\Wolfram Research\Mathematica\11.3\;%PATH%
echo Launching wolfram
start wolfram -noprompt -initfile "C:\Users\George\Desktop\Script\Run.m"
endlocal