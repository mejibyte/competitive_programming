@echo off
copy ??.t ?? > nul
dcc32 -cc genTests.dpr
genTests.exe
