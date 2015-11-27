#ifndef IRCBOT_ASSERT_HPP
#define IRCBOT_ASSERT_HPP

#include <assert.h>
#include <iostream>
#include <cstdlib>

#ifndef NDEBUG
#  define ASSERT(condition, message)					\
  do {									\
    if (! (condition)) {                                                \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__	\
                << " line " << __LINE__ << ": " << message << std::endl; \
      std::exit(-1);                                                    \
    }                                                                   \
  } while (false)
#else
#  define ASSERT(condition, message) do { } while (false)
#endif

#ifndef NDEBUG
#  define PRINT(message)                       \
  std::cout << message << std::endl;
#else
#  define PRINT(message) do { } while (false)
#endif

#ifndef NDEBUG
#  define ERROR(message)                       \
  std::cerr << message << std::endl;
#else
#  define ERROR(message) do { } while (false)
#endif


#endif
