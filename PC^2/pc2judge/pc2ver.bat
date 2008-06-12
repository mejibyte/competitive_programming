@echo off

rem
rem File:    pc2ver
rem Purpose: prints version info for pc2
rem Author:  pc2
rem E-mail:  mailto:pc2@ecs.csus.edu
rem Revised: Tue Jan 25 22:09:17 PST 2005
rem
rem Send e-mail to us if you have questions.. thanks.
rem

java pc2.SystemRevisionInfo

if .%1 == .-a goto :allver
goto :end

:allver
java pc2.admin.VersionInfo | find "Version"
java pc2.board.VersionInfo | find "Version"
java pc2.client.VersionInfo | find "Version"
java pc2.ex.VersionInfo | find "Version"
java pc2.judge.VersionInfo | find "Version"
java pc2.judge.aj.VersionInfo | find "Version"
java pc2.server.VersionInfo | find "Version"
java pc2.team.VersionInfo | find "Version"

:end
rem eof pc2ver
