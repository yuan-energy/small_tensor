#pragma once

namespace smalltensor{

#define A i1
#define a n1
#define D1 d1
#define B i2
#define b n2
#define D2 d2
#include "expr2_subtractions_core.hpp"
#undef A
#undef a
#undef D1
#undef B
#undef b
#undef D2



#define A i2
#define a n2
#define D1 d2
#define B i1
#define b n1
#define D2 d1
#include "expr2_subtractions_core.hpp"
#undef A
#undef a
#undef D1
#undef B
#undef b
#undef D2



} // namespace smalltensor{