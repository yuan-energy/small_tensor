#include "libxsmm_source.h"
#include <vector>
#include <iostream>
using std::vector; 

#include <chrono>

int main()
{
  libxsmm_init();
  // const libxsmm_gemm_prefetch_type prefetch = LIBXSMM_PREFETCH_AUTO;
  // const double alpha = 1.0, beta = 1.0; /* accumulate C-matrix */
  const int my_m = 3, my_n = 3, my_k = 3;     /* some problem size */
  // libxsmm_dmmfunction xmm = NULL;       /* function pointer */

  // xmm = libxsmm_dmmdispatch(23, 23, 23, /* some problem size */
  //         NULL/*lda*/, NULL/*ldb*/, NULL/*ldc*/,
  //         &alpha, &beta, NULL/*flags*/,
  //         NULL/*&prefetch*/);
  // double a = new double
  const libxsmm_mmfunction<double> my_xmm(my_m, my_n, my_k);
  int nbatch = 1'000'000'0;
  size_t a_len = my_m * my_n ;
  size_t b_len = my_n * my_k ;
  size_t c_len = my_m * my_k ;
  static vector<double> a(a_len*nbatch,1.);
  static vector<double> b(b_len*nbatch,1.);
  static vector<double> c(c_len*nbatch,1.);

  auto start = std::chrono::system_clock::now();

  if (my_xmm) { /* JiT'ted code has been generated */
    for (int i = 0; i < nbatch; ++i) {
      // const double *const ai = a ;
      // const double *const bi = b ;
      // double *const ci = c ;
      // my_xmm( &a[i*a_len] , &b[i*b_len] , &c[i*c_len] );
      my_xmm( &a[i] , &b[i] , &c[i] );
    }
  }

  
  auto end = std::chrono::system_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
    std::cerr << " elapsed = " << elapsed << std::endl ; 

  std::cout<<" c = " ; 
  for(int i = 0 ; i < 10; i ++ ){
    std::cout << c[i] << "\t";
  }
  std::cout << std::endl;

  libxsmm_finalize();
  fprintf(stdout, "Finished\n");
  return(0);
}