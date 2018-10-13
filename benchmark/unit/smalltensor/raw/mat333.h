#include <x86intrin.h>


inline __attribute__((always_inline)) __m128 _st_mm_load3_al_ps(const float *value) {
    //! Align load a vector into the first three elements of an xmm
    __m128i xy = _mm_loadl_epi64((const __m128i*)value);
    __m128 z = _mm_load_ss(&value[2]);
    return _mm_movelh_ps(_mm_castsi128_ps(xy), z);
}

inline __attribute__((always_inline)) __m128 _st_mm_load3_ul_ps(const float *value) {
    //! Unalign load a vector into the first three elements of an xmm
    __m128 x = _mm_load_ss(value);
    __m128 y = _mm_load_ss(&value[1]);
    __m128 z = _mm_load_ss(&value[2]);
    __m128 xy = _mm_movelh_ps(x, y);
    return _mm_shuffle_ps(xy, z, _MM_SHUFFLE(2, 0, 2, 0));
}



template<typename T, size_t M, size_t K, size_t N>
void _matmul(const float * __restrict__ a, const float * __restrict__ b, float * __restrict__ out) ; 

template<>
inline __attribute__((always_inline))
void _matmul<float,3,3,3>(const float * __restrict__ a, const float * __restrict__ b, float * __restrict__ out) {
    // 63 OPS + 3 OPS
    // This is a completely vectorised approach that reduces
    // (27 scalar mul + 18 scalar add) to (9 SSE mul + 6 SEE add)

    __m128 brow0 = _st_mm_load3_al_ps(b);
    __m128 brow1 = _st_mm_load3_ul_ps(b+3);
    __m128 brow2 = _st_mm_load3_ul_ps(b+6);

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
