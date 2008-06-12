@echo off
rem
rem File:    pc2board.bat
rem Purpose: to start board client
rem Revised: Tue Apr 19 20:13:36 PDT 2005

rem

start java -Djava.security.policy=policy.ini  pc2.board.Board %1 %2 %3 %4
