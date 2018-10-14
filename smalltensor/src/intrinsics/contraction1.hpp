#ifndef SMALL_TENSOR_INTRINSICS_CONTRACTION1_H_
#define SMALL_TENSOR_INTRINSICS_CONTRACTION1_H_


#include "intrinsics_ext.hpp"



template<typename T, size_t M, size_t K, size_t N>
ST_ALWAYS_INLINE
void _contraction_1(const T * ST_RESTRICT a, const T * ST_RESTRICT b, T * ST_RESTRICT out) {
    // memset(out, 0, sizeof(T)*M*K) ; 
    // std::cerr << " M = " << M << std::endl ;
    // std::cerr << " K = " << K << std::endl ;
    // std::cerr << " N = " << N << std::endl ;
    for (std::size_t n1 = 0; n1 < M; ++n1){
      for (std::size_t n2 = 0; n2 < K; ++n2){
        for (std::size_t n3 = 0; n3 < N; ++n3){
          out[n1*K+n2] += a[n1*N+n3] * b[n3*K+n2];
        }
      }
    }
}


#ifdef __AVX__

template<>
ST_ALWAYS_INLINE
void _contraction_1<float,3,3,3>(const float * ST_RESTRICT a, const float * ST_RESTRICT b, float * ST_RESTRICT out) {

    // Arithmetic: 27 scalar mul + 18 scalar add
    // Intrinsics: 9 AVX mul + 6 AVX add

    __m128 b_row0 = _st_mm_load3_al_ps(b);
    __m128 b_row1 = _st_mm_load3_ul_ps(b+3);
    __m128 b_row2 = _st_mm_load3_ul_ps(b+6);

    {
        __m128 ai0 = _mm_set1_ps(a[0]);
        __m128 ai1 = _mm_set1_ps(a[1]);
        __m128 ai2 = _mm_set1_ps(a[2]);

        ai0 = _mm_mul_ps(ai0,b_row0);
        ai1 = _mm_mul_ps(ai1,b_row1);
        ai2 = _mm_mul_ps(ai2,b_row2);
        _mm_store_ps(out,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
    }

    {
        __m128 ai0 = _mm_set1_ps(a[3]);
        __m128 ai1 = _mm_set1_ps(a[4]);
        __m128 ai2 = _mm_set1_ps(a[5]);

        ai0 = _mm_mul_ps(ai0,b_row0);
        ai1 = _mm_mul_ps(ai1,b_row1);
        ai2 = _mm_mul_ps(ai2,b_row2);
        _mm_storeu_ps(out+3,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
    }

    {
        __m128 ai0 = _mm_set1_ps(a[6]);
        __m128 ai1 = _mm_set1_ps(a[7]);
        __m128 ai2 = _mm_set1_ps(a[8]);

        ai0 = _mm_mul_ps(ai0,b_row0);
        ai1 = _mm_mul_ps(ai1,b_row1);
        ai2 = _mm_mul_ps(ai2,b_row2);
        _mm_storeu_ps(out+6,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
    }
}





template<>
ST_ALWAYS_INLINE
void _contraction_1<double,3,3,3>(const double * ST_RESTRICT a, const double * ST_RESTRICT b, double * ST_RESTRICT out) {

    __m256d b_row0 = _st_mm256_load3_al_pd(b);
    __m256d b_row1 = _st_mm256_load3_ul_pd(b+3);
    __m256d b_row2 = _st_mm256_load3_ul_pd(b+6);

    {
        __m256d ai0 = _mm256_set1_pd(a[0]);
        __m256d ai1 = _mm256_set1_pd(a[1]);
        __m256d ai2 = _mm256_set1_pd(a[2]);

        ai0 = _mm256_mul_pd(ai0,b_row0);
        ai1 = _mm256_mul_pd(ai1,b_row1);
        ai2 = _mm256_mul_pd(ai2,b_row2);
        _mm256_store_pd(out,_mm256_add_pd(ai0,_mm256_add_pd(ai1,ai2)));
    }

    {
        __m256d ai0 = _mm256_set1_pd(a[3]);
        __m256d ai1 = _mm256_set1_pd(a[4]);
        __m256d ai2 = _mm256_set1_pd(a[5]);

        ai0 = _mm256_mul_pd(ai0,b_row0);
        ai1 = _mm256_mul_pd(ai1,b_row1);
        ai2 = _mm256_mul_pd(ai2,b_row2);
        _mm256_storeu_pd(out+3,_mm256_add_pd(ai0,_mm256_add_pd(ai1,ai2)));
    }

    {
        __m256d ai0 = _mm256_set1_pd(a[6]);
        __m256d ai1 = _mm256_set1_pd(a[7]);
        __m256d ai2 = _mm256_set1_pd(a[8]);

        ai0 = _mm256_mul_pd(ai0,b_row0);
        ai1 = _mm256_mul_pd(ai1,b_row1);
        ai2 = _mm256_mul_pd(ai2,b_row2);
        _mm256_storeu_pd(out+6,_mm256_add_pd(ai0,_mm256_add_pd(ai1,ai2)));
    }
}


#endif // __AVX__


#endif // SMALL_TENSOR_INTRINSICS_CONTRACTION1_H_


