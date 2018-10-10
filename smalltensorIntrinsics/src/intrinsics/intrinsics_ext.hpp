#ifndef SMALL_TENSOR_INTRINSICS_EXT_H_
#define SMALL_TENSOR_INTRINSICS_EXT_H_


#include <x86intrin.h>
#include "../../utils/__utils.h"

ST_ALWAYS_INLINE __m128 _mm_load3_al_ps(const float *value) {
    //! Align load a vector into the first three elements of an xmm
    __m128i xy = _mm_loadl_epi64((const __m128i*)value);
    __m128 z = _mm_load_ss(&value[2]);
    return _mm_movelh_ps(_mm_castsi128_ps(xy), z);
}

ST_ALWAYS_INLINE __m128 _mm_load3_ul_ps(const float *value) {
    //! Unalign load a vector into the first three elements of an xmm
    __m128 x = _mm_load_ss(value);
    __m128 y = _mm_load_ss(&value[1]);
    __m128 z = _mm_load_ss(&value[2]);
    __m128 xy = _mm_movelh_ps(x, y);
    return _mm_shuffle_ps(xy, z, _MM_SHUFFLE(2, 0, 2, 0));
}

ST_ALWAYS_INLINE __m128 _mm_shift_1_ps(__m128 a) {
    return _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(a), 4));
}






#endif
