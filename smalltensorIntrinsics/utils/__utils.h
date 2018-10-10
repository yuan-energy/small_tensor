#pragma once
#include <iostream>  /* cout */
#include <cstring>  /* std::memcpy, std::memmove */
#include <cassert> /* assert */
#include <string> /* assert */

#include "__assert_msg.h"


#define ST_ALWAYS_INLINE inline __attribute__((always_inline))
#define ST_ALIGN32 __attribute__((aligned(32)))
#define ST_ALIGN16 __attribute__((aligned(16)))
#define ST_RESTRICT __restrict__

