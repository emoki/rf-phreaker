@echo off
md gen-c 2>NUL:

REM =========================================================
REM  Generates code for the C-Only version
REM =========================================================
..\bin\codegenix ..\common\endec.tcl demo-c.src gen-c config=localconfig-c.tcl
