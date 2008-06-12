@echo off
rem
rem File:    pc2judge.bat
rem Purpose: to start judge client
rem Revised: Tue Apr 19 20:13:36 PDT 2005
rem

start java -Djava.security.policy=policy.ini  pc2.judge.Judge %1 %2 %3 %4
