@echo off
rem
rem Purpose: start pc2 admin module
rem Author : pc2@ecs.csus.edu
rem Revised: Wed May  4 23:09:27 PDT 2005

start java -Djava.security.policy=policy.ini pc2.client.Client %1 %2 %3 %4

rem eof pc2admin.bat 
