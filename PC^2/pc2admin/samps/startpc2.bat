@echo off
rem Purpose: start pc2 Server and Client
rem Author : pc2@ecs.csus.edu
rem Revised: Wed Nov  2 15:20:29 PST 2005

start java -Djava.security.policy=policy.ini pc2.server.Server %1

pause

start java -Djava.security.policy=policy.ini pc2.client.Client

rem eof startpc2.bat  $Id: startpc2.bat,v 1.2 2005/11/02 23:21:51 boudreat Exp $
