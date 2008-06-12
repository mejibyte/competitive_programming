@echo off
rem Purpose: start pc2 Server 
rem Author : pc2@ecs.csus.edu
rem Revised: Tue Apr 19 20:13:36 PDT 2005

start java -Djava.security.policy=policy.ini pc2.server.Server %1 %2 %3 %4

rem eof pc2server.bat 
