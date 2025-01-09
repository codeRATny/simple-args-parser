#ifndef _ARGS_ASSERT_HPP_
#define _ARGS_ASSERT_HPP_

#ifndef RELEASE_BUILD
#   include <assert.h>
#else
#   ifdef assert
#       undef assert
#   endif
#   define assert(x) void (0)
#endif

#endif
