@echo off

del gen_Rel12\* /ysfx
md gen_Rel12
sleep 2
..\..\Encodix\bin\codegenix ..\..\Encodix\common\endec.tcl TS_44.018_Rel12.src gen_Rel12 config=localconfig.tcl
