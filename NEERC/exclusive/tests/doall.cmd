@echo off

for %%i in (*.t) do (
  copy %%i %%~ni > nul
)

call javac -cp . ExclusiveTestsGen.java
call java -cp . ExclusiveTestsGen
