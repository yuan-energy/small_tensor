#ifndef SMALL_TENSOR_INTRINSICS_CONTRACTION2_H_
#define SMALL_TENSOR_INTRINSICS_CONTRACTION2_H_

#include "intrinsics_ext.hpp"

template<typename T, size_t M, size_t N>
ST_ALWAYS_INLINE T _contraction_2(const T* ST_RESTRICT a, const T* ST_RESTRICT b) {
    // std::cerr << " hello1" << std::endl ; 
    T result = static_cast<T>(0);
    for (size_t i = 0; i < M*N ; ++i)    {
        result += a[i] * b[i] ; 
    }
    return result ; 
}

#ifdef __AVX__

template<>
ST_ALWAYS_INLINE float _contraction_2<float,3,3>(const float* ST_RESTRICT a, const float* ST_RESTRICT b) {
    // std::cerr << " hello2" << std::endl ; 
    float r1 = _st_mm256_hsum_ps(_mm256_mul_ps(_mm256_load_ps(a),_mm256_load_ps(b)));
    float r2 = _st_mm_hsum_ps(_mm_mul_ss(_mm_load_ss(a+8),_mm_load_ss(b+8)));
    return r1+r2;
}

template<>
ST_ALWAYS_INLINE double _contraction_2<double,3,3>(const double* ST_RESTRICT a, const double* ST_RESTRICT b) {
    // std::cerr << " hello3" << std::endl ; 
    __m256d r1 = _mm256_mul_pd(_mm256_load_pd(a),_mm256_load_pd(b));
    __m256d r2 = _mm256_mul_pd(_mm256_load_pd(a+4),_mm256_load_pd(b+4));
    __m128d r3 = _mm_mul_sd(_mm_load_sd(a+8),_mm_load_sd(b+8));
    __m128d r4 = _st_hadd_pd(_mm256_add_pd(r1,r2));
    __m128d result = _mm_add_pd(_st_hadd_pd(r3),r4);
    return _mm_cvtsd_f64(result);
}


// template<>
// ST_ALWAYS_INLINE float _contraction_2<float,2,2>(const float* ST_RESTRICT a, const float* ST_RESTRICT b) {
//     return _st_mm_hsum_ps(_mm_mul_ps(_mm_load_ps(a),_mm_load_ps(b)));
// }

// template<>
// ST_ALWAYS_INLINE double _contraction_2<double,2,2>(const double* ST_RESTRICT a, const double* ST_RESTRICT b) {
//     return _st_mm256_sum_pd(_mm256_mul_pd(_mm256_load_pd(a),_mm256_load_pd(b)));
// }


#endif // __AVX__







#endif // SMALL_TENSOR_INTRINSICS_CONTRACTION2_H_
