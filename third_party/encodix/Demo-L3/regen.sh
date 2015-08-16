#!/bin/sh

# =========================================================
#  Generates code for the C-Only version
# =========================================================
mkdir gen
rm -f gen/*
../bin/codegenix ../Common/endec.tcl Demo-L3.src gen config=localconfig.tcl
