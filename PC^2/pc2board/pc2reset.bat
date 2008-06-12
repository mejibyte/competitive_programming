@echo off
rem
rem Completely reset and erase contest data
rem USE WITH EXTREME CAUTION 
rem Revised: Thu Jul 17 20:31:39 PDT 2003

echo Backing up settings to archive 

java pc2.ZipPC2

set RMCMD=rmdir /s /q
if %OS%. == . set RMCMD=deltree /y

%RMCMD% db
%RMCMD% OLD
del *.log

rem eof reset.bat
