/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <assert.h>

namespace NVis {

#ifndef ASSERT_CHECK
#    ifdef NDEBUG
#        define ASSERT_CHECK 0
#    else
#        define ASSERT_CHECK 1
#    endif
#endif

#if ASSERT_CHECK && defined(NDEBUG)
        extern "C" void __assert_fail(const char* __assertion, const char* __file,
                                      unsigned int __line, const char* __function)
        throw () __attribute__((__noreturn__));
#    define ASSERT(expr) do { if (unlikely(!(expr))) { __assert_fail(# expr, __FILE__, __LINE__, __FUNCTION__); } \
} \
    while (0)
#    define ENSURE(expr) ASSERT(expr)
#else
#    define ASSERT(expr) assert(expr)
#endif

}   // NVis
