@echo off
rem
rem File:    pc2team.bat
rem Purpose: to start team client
rem Revised: Tue Apr 19 20:13:36 PDT 2005
rem

start java -Djava.security.policy=policy.ini pc2.team.Team %1 %2 %3 %4
