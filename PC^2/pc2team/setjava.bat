@echo off
rem Purpose: This sets the PATH and CLASSPATH to run the system where
rem java is under c:\java
rem Author: pc2@ecs.csus.edu
rem Mon Apr 15 09:58:25 PDT 2002

set PC2=c:\pc2
set JAVA=c:\java

rem might need to set systemroot on win95/98/ME
rem set SYSTEMROOT=c:\windows

set CLASSPATH=%PC2%;%JAVA%\lib;.;%CLASSPATH%
set PATH=%JAVA%\bin;%SYSTEMROOT%;%SYSTEMROOT%\system32;%PATH%

rem eof setjava.bat
