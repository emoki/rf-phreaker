// dllmain.cpp : Defines the entry point for the DLL application.
#include "ipp.h"

auto status = ippInit();
status = ippSetFlushToZero(1, NULL);
