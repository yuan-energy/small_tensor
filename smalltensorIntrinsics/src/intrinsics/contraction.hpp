#ifndef SMALL_TENSOR_INTRINSICS_CONTRACTION_H_
#define SMALL_TENSOR_INTRINSICS_CONTRACTION_H_


#include "intrinsics_ext.hpp"



template<typename T, size_t M, size_t N, size_t K>
ST_ALWAYS_INLINE
void _mat_mul(const T * ST_RESTRICT a, const T * ST_RESTRICT b, T * ST_RESTRICT out) {
    memset(out, 0, sizeof(T)*M*K) ; 
    for (std::size_t N1 = 0; N1 < M; ++N1){
      for (std::size_t N2 = 0; N2 < K; ++N2){
        for (std::size_t n3 = 0; n3 < N; ++n3){
          out[N1*K+N2] += a[N1*N+n3] * b[n3*K+N2];
        }
      }
    }
}

template<>
ST_ALWAYS_INLINE
void _mat_mul<float,3,3,3>(const float * ST_RESTRICT a, const float * ST_RESTRICT b, float * ST_RESTRICT out) {

    // Arithmetic: 27 scalar mul + 18 scalar add
    // Intrinsics: 9 AVX mul + 6 AVX add

    __m128 brow0 = _mm_load3_al_ps(b);
    __m128 brow1 = _mm_load3_ul_ps(b+3);
    __m128 brow2 = _mm_load3_ul_ps(b+6);

    {
        __m128 ai0 = _mm_set1_ps(a[0]);
        __m128 ai1 = _mm_set1_ps(a[1]);
        __m128 ai2 = _mm_set1_ps(a[2]);

        ai0 = _mm_mul_ps(ai0,brow0);
        ai1 = _mm_mul_ps(ai1,brow1);
        ai2 = _mm_mul_ps(ai2,brow2);
        _mm_store_ps(out,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
    }

    {
        __m128 ai0 = _mm_set1_ps(a[3]);
        __m128 ai1 = _mm_set1_ps(a[4]);
        __m128 ai2 = _mm_set1_ps(a[5]);

        ai0 = _mm_mul_ps(ai0,brow0);
        ai1 = _mm_mul_ps(ai1,brow1);
        ai2 = _mm_mul_ps(ai2,brow2);
        _mm_storeu_ps(out+3,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
    }

    {
        __m128 ai0 = _mm_set1_ps(a[6]);
        __m128 ai1 = _mm_set1_ps(a[7]);
        __m128 ai2 = _mm_set1_ps(a[8]);

        ai0 = _mm_mul_ps(ai0,brow0);
        ai1 = _mm_mul_ps(ai1,brow1);
        ai2 = _mm_mul_ps(ai2,brow2);
        _mm_storeu_ps(out+6,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
    }
}








// template<>
// ST_ALWAYS_INLINE
// void _mat_mul<float,8,3,3>(const float * ST_RESTRICT a, const float * ST_RESTRICT b, float * ST_RESTRICT out) {

//     __m128 brow0 = _mm_load3_al_ps(b);
//     __m128 brow1 = _mm_load3_ul_ps(b+3);
//     __m128 brow2 = _mm_load3_ul_ps(b+6);

//     {
//         __m128 ai0 = _mm_set1_ps(a[0]);
//         __m128 ai1 = _mm_set1_ps(a[1]);
//         __m128 ai2 = _mm_set1_ps(a[2]);

//         ai0 = _mm_mul_ps(ai0,brow0);
//         ai1 = _mm_mul_ps(ai1,brow1);
//         ai2 = _mm_mul_ps(ai2,brow2);
//         _mm_store_ps(out,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
//     }

//     {
//         __m128 ai0 = _mm_set1_ps(a[3]);
//         __m128 ai1 = _mm_set1_ps(a[4]);
//         __m128 ai2 = _mm_set1_ps(a[5]);

//         ai0 = _mm_mul_ps(ai0,brow0);
//         ai1 = _mm_mul_ps(ai1,brow1);
//         ai2 = _mm_mul_ps(ai2,brow2);
//         _mm_storeu_ps(out+3,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
//     }

//     {
//         __m128 ai0 = _mm_set1_ps(a[6]);
//         __m128 ai1 = _mm_set1_ps(a[7]);
//         __m128 ai2 = _mm_set1_ps(a[8]);

//         ai0 = _mm_mul_ps(ai0,brow0);
//         ai1 = _mm_mul_ps(ai1,brow1);
//         ai2 = _mm_mul_ps(ai2,brow2);
//         _mm_storeu_ps(out+6,_mm_add_ps(ai0,_mm_add_ps(ai1,ai2)));
//     }
// }








#endif
