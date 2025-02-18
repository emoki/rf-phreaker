/** ==========================================================================
 * 2013 by KjellKod.cc. This is PUBLIC DOMAIN to use at your own risk and comes
 * with no warranties. This code is yours to share, use and modify with no
 * strings attached and no restrictions or obligations.
 * 
 * For more information see g3log/LICENSE or refer refer to http://unlicense.org
 * ============================================================================*/

#include "g2filesink.hpp"
#include "g2filesinkhelper.ipp"
#include <cassert>

namespace g2 {
using namespace internal;


FileSink::FileSink(const std::string& log_prefix, const std::string& log_directory)
: _log_file_with_path(log_directory)
, _log_prefix_backup(log_prefix)
, _outptr(new std::ofstream)
{
   _log_prefix_backup = prefixSanityFix(log_prefix);
   if (!isValidFilename(_log_prefix_backup)) {
      std::cerr << "g2log: forced abort due to illegal log prefix [" << log_prefix << "]" << std::endl;
      abort();
   }

   std::string file_name = createLogFileName(_log_prefix_backup);
   _log_file_with_path = pathSanityFix(_log_file_with_path, file_name);
   _outptr = createLogFile(_log_file_with_path);

   if (!_outptr) {
      std::cerr << "Cannot write log file to location, attempting current directory" << std::endl;
      _log_file_with_path = "./" + file_name;
      _outptr = createLogFile(_log_file_with_path);
   }
   assert(_outptr && "cannot open log file at startup");
   //addLogFileHeader();
}


FileSink::~FileSink() {
   std::string exit_msg{"\ng2log g2FileSink shutdown at: "};
   exit_msg.append(localtime_formatted(systemtime_now(), internal::time_formatted));
   filestream() << exit_msg << std::flush;

   exit_msg.append({"\nLog file at: ["}).append(_log_file_with_path).append({"]\n\n"});
   std::cerr << exit_msg << std::flush;
}

// The actual log receiving function
void FileSink::fileWrite(LogMessageMover message) {
   std::ofstream& out(filestream());
   out << message.get().toString() << std::flush;
}

std::string FileSink::changeLogFile(const std::string& directory) {

   auto now = g2::systemtime_now();
   auto now_formatted = g2::localtime_formatted(now, {internal::date_formatted + " " + internal::time_formatted});
   
   std::string file_name = createLogFileName(_log_prefix_backup);
   std::string prospect_log = directory + file_name;
   std::unique_ptr<std::ofstream> log_stream = createLogFile(prospect_log);
   if (nullptr == log_stream) {
      filestream() << "\n" << now_formatted << " Unable to change log file. Illegal filename or busy? Unsuccessful log name was: " << prospect_log;
      return {}; // no success
   }

   addLogFileHeader();
   std::ostringstream ss_change;
   ss_change << "\n\tChanging log file from : " << _log_file_with_path;
   ss_change << "\n\tto new location: " << prospect_log << "\n";
   filestream() << now_formatted << ss_change.str();
   ss_change.str("");

   std::string old_log = _log_file_with_path;
   _log_file_with_path = prospect_log;
   _outptr = std::move(log_stream);
   ss_change << "\n\tNew log file. The previous log file was at: ";
   ss_change << old_log;
   filestream() << now_formatted << ss_change.str();
   return _log_file_with_path;
}
std::string FileSink::fileName() {
   return _log_file_with_path;
}
void FileSink::addLogFileHeader() {
   filestream() << header();
}

} // g2
