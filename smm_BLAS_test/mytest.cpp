#include <libxsmm.h>

int main()
{
  const libxsmm_gemm_prefetch_type prefetch = LIBXSMM_PREFETCH_AUTO;
  const double alpha = 1.0, beta = 1.0; /* accumulate C-matrix */
  const int m = 23, n = 23, k = 23;     /* some problem size */
  libxsmm_dmmfunction xmm = NULL;       /* function pointer */

  xmm = libxsmm_dmmdispatch(23, 23, 23, /* some problem size */
          NULL/*lda*/, NULL/*ldb*/, NULL/*ldc*/,
          &alpha, &beta, NULL/*flags*/,
          NULL/*&prefetch*/);
  double a = new double
  int nbatch = 100;
  if (xmm) { /* JiT'ted code has been generated */
    for (int i = 0; i < nbatch; ++i) {
      const double *const ai = a ;
      const double *const bi = b ;
      double *const ci = c ;
      xmm(ai, bi, ci);


    }
  }
}