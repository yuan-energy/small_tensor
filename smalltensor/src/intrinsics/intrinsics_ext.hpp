#ifndef SMALL_TENSOR_INTRINSICS_EXT_H_
#define SMALL_TENSOR_INTRINSICS_EXT_H_


#include <x86intrin.h>
#include "../../utils/__utils.h"

namespace smalltensor{

#ifdef __AVX__

ST_ALWAYS_INLINE __m128 _st_mm_load3_al_ps(const float *value) {
    // Align load a vector into the first three elements 
    __m128i xy = _mm_loadl_epi64((const __m128i*)value);
    __m128 z = _mm_load_ss(&value[2]);
    return _mm_movelh_ps(_mm_castsi128_ps(xy), z);
}

ST_ALWAYS_INLINE __m128 _st_mm_load3_ul_ps(const float *value) {
    // Unalign load a vector into the first three elements 
    __m128 x = _mm_load_ss(value);
    __m128 y = _mm_load_ss(&value[1]);
    __m128 z = _mm_load_ss(&value[2]);
    __m128 xy = _mm_movelh_ps(x, y);
    return _mm_shuffle_ps(xy, z, _MM_SHUFFLE(2, 0, 2, 0));
}

ST_ALWAYS_INLINE __m128 _st_mm_shift_1_ps(__m128 a) {
    return _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(a), 4));
}


ST_ALWAYS_INLINE __m256d _st_mm256_load3_al_pd(const double *value) {
    // Align load a vector into the first three elements 
    __m128d xy   = _mm_load_pd(value);
    __m128d z    = _mm_load_sd(&value[2]);
    __m256d vec  = _mm256_castpd128_pd256(xy);
    return _mm256_insertf128_pd(vec, z,0x1);
}

ST_ALWAYS_INLINE __m256d _st_mm256_load3_ul_pd(const double *value) {
    // Align load a vector into the first three elements 
    __m256i mask = _mm256_set_epi64x(0,-1,-1,-1);
    return _mm256_maskload_pd(value,(__m256i) mask);
}


ST_ALWAYS_INLINE float _st_mm256_hsum_ps(__m256 a) {
    __m256 sum = _mm256_hadd_ps(a, a);
    sum = _mm256_hadd_ps(sum, sum);
    __m128 sum_high = _mm256_extractf128_ps(sum, 0x1);
    __m128 result = _mm_add_ps(sum_high, _mm256_castps256_ps128(sum));
    return _mm_cvtss_f32(result);
}

ST_ALWAYS_INLINE float _st_mm_hsum_ps(__m128 a) {
    __m128 shuf = _mm_movehdup_ps(a);
    __m128 sums = _mm_add_ps(a, shuf);
    shuf        = _mm_movehl_ps(shuf, sums);
    sums        = _mm_add_ss(sums, shuf);
    return        _mm_cvtss_f32(sums);
}

ST_ALWAYS_INLINE double _st_mm_hsum_pd(__m128d a) {
    __m128 shuftmp= _mm_movehl_ps(_mm_set1_ps(0.f), _mm_castpd_ps(a));
    __m128d shuf  = _mm_castps_pd(shuftmp);
    return  _mm_cvtsd_f64(_mm_add_sd(a, shuf));
}

static ST_ALWAYS_INLINE __m128d _st_hadd_pd(__m128d a) {
    __m128 shuftmp= _mm_movehl_ps(_mm_set1_ps(0.f), _mm_castpd_ps(a));
    __m128d shuf  = _mm_castps_pd(shuftmp);
    return  _mm_add_sd(a, shuf);
}

static ST_ALWAYS_INLINE __m128d _st_hadd_pd(__m256d a) {
    __m256d sum_low = _mm256_hadd_pd(a, a);
    __m128d sum_high = _mm256_extractf128_pd(sum_low, 0x1);
    return _mm_add_pd(sum_high, _mm256_castpd256_pd128(sum_low));
}

ST_ALWAYS_INLINE double _st_mm256_sum_pd(__m256d a) {
    __m256d sum = _mm256_add_pd(a, _mm256_shuffle_pd(a,a,0x5));
    __m128d sum_high = _mm256_extractf128_pd(sum, 0x1);
    __m128d result = _mm_add_sd(sum_high, _mm256_castpd256_pd128(sum));
    return _mm_cvtsd_f64(result);
}

#endif // __AVX__

} // namespace smalltensor

#endif
