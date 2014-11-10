/** ==========================================================================
 * 2012 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
 * with no warranties. This code is yours to share, use and modify with no
 * strings attached and no restrictions or obligations.
 * 
 * For more information see g3log/LICENSE or refer refer to http://unlicense.org
 * ============================================================================
 * Filename:g2loglevels.hpp  Part of Framework for Logging and Design By Contract
 * Created: 2012 by Kjell Hedström
 *
 * PUBLIC DOMAIN and Not copywrited. First published at KjellKod.cc
 * ********************************************* */

#pragma once

#define G2_DYNAMIC_LOGGING 1

#include <string>

// Levels for logging, made so that it would be easy to change, remove, add levels -- KjellKod
struct LEVELS {
   // force internal copy of the const char*. This is a simple safeguard for when g3log is used in a
   // "dynamic, runtime loading of shared libraries"

   LEVELS(const LEVELS& other)
   : value(other.value), text(other.text.c_str()) {}

   LEVELS(int id, const char* idtext) : value(id), text(idtext) {}
   const int value;
   const std::string text;
};

const LEVELS LVERBOSE{0, {"VERBOSE"}}, 
LDEBUG{LVERBOSE.value + 1, {"DEBUG"}}, 
LINFO{LDEBUG.value + 1, {"INFO"}},
LWARNING{LINFO.value + 1, {"WARNING"}}, 
LERROR{LWARNING.value + 1, {"ERROR"}},
// Insert here *any* extra logging levels that is needed
// 1) Remember to update the FATAL initialization below
// 2) Remember to update the initialization of "g2loglevels.cpp/g_log_level_status"
LFATAL{LERROR.value + 1, {"FATAL"}};


namespace g2 {
   namespace internal {
      const LEVELS CONTRACT{100, {"CONTRACT"}}, FATAL_SIGNAL{101, {"FATAL_SIGNAL"}};
      bool wasFatal(const LEVELS& level);
   }

#ifdef G2_DYNAMIC_LOGGING
   // Enable/Disable a log level {VERBOSE,DEBUG,INFO,WARNING,ERROR,FATAL}
   void setLogLevel(LEVELS level, bool enabled_status);
#endif
   bool logLevel(LEVELS level);
} // g2

