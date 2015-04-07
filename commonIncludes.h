#ifndef COMMONINCLUDES_H
#define COMMONINCLUDES_H

//#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <iostream>
using namespace std;

// stole this part from: http://stackoverflow.com/questions/16692400/c11-adding-a-stream-output-operator-for-stdchronotime-point
namespace pretty_print {
  template<typename T>
  struct print_wrapper { // boost::noopy optional -- if so, use it with && as an argument
    T const& data;
    print_wrapper( T const& t ): data(t) {}
  };

  template<typename T>
  print_wrapper<T> format( T const& t ) { return {t}; }

  template<typename Clock, typename Duration>
  std::ostream &operator<<(std::ostream &stream, const print_wrapper<std::chrono::time_point<Clock, Duration>>&& time_point) {
	  const time_t time = Clock::to_time_t(time_point.data);
	#if __GNUC__ > 4 || ((__GNUC__ == 4) && __GNUC_MINOR__ > 8 && __GNUC_REVISION__ > 1)
	  // Maybe the put_time will be implemented later?
	  struct tm tm;
	  localtime_r(&time, &tm);
	  return stream << std::put_time(tm, "c");
	#else
	  char buffer[26];
	  ctime_r(&time, buffer);
	  buffer[24] = '\0';  // Removes the newline that is added
	  return stream << buffer;
	#endif
  }
}

#ifdef DEBUG
#include <boost/thread/mutex.hpp>

static boost::mutex commonIncludesMutex;

#define DEBUGCODE(X) do {\
	commonIncludesMutex.lock();\
	cerr << pretty_print::format(std::chrono::system_clock::now()) << ':' << __FILE__ << ':' << __LINE__ << ": " << endl;\
	{ X; };\
	commonIncludesMutex.unlock();\
	} while(0);
#define DEBUGPRINTLN(X) do {\
	commonIncludesMutex.lock();\
	cerr << pretty_print::format(std::chrono::system_clock::now()) << ':' << __FILE__ << ':' << __LINE__ << ": " << X << endl;\
	commonIncludesMutex.unlock();\
	} while(0);
#else
#define DEBUGCODE(X)
#define DEBUGPRINTLN(X)
#endif

#define UNUSED(expr) (void)(expr)

#endif
