#!/bin/sh

mkdir gen-c
# =========================================================
#  Generates code for the C-Only version
# =========================================================
../bin/codegenix ../Common/endec.tcl demo-c.src gen-c config=localconfig-c.tcl
