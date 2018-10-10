#include "libxsmm_source.h"
#include <vector>
#include <iostream>
#include <fstream>
using std::vector; 

#include <chrono>

void write_to_file(int m, int n, int k , double duration, std::string const& prefix=""){
  std::cerr << " m n k = " << m << ", " << n << ", " << k << "\n" ; 
  std::cerr << " duration = " << duration << std::endl ; 

  std::ofstream myfile ; 
  std::string out_file_name = prefix + "time" + std::to_string(m) + "x" + std::to_string(n) + "x" + std::to_string(k) + ".txt" ;
  myfile.open(out_file_name) ; 
  myfile << duration << std::endl ;
  myfile.close(); 
}

void Test_Contraction_float( int my_m, int my_n, int my_k ){
  const libxsmm_mmfunction<float> my_xmm(my_m, my_n, my_k);
  int nbatch = 10'000'000;
  size_t a_len = my_m * my_n ;
  size_t b_len = my_n * my_k ;
  size_t c_len = my_m * my_k ;
  vector<float> a(a_len*nbatch,1.);
  vector<float> b(b_len*nbatch,1.);
  vector<float> c(c_len*nbatch,1.);

  auto start = std::chrono::system_clock::now();
  if (my_xmm) { /* JiT'ted code has been generated */
    for (int i = 0; i < nbatch; ++i) {
      my_xmm( &a[i*a_len] , &b[i*b_len] , &c[i*c_len] );
    }
  }
  auto end = std::chrono::system_clock::now();

  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;

  write_to_file(my_m, my_n, my_k, elapsed, "float_") ; 
}
void Test_Contraction_double( int my_m, int my_n, int my_k ){
  // const int my_m = 3, my_n = 3, my_k = 3;     /* some problem size */
  // libxsmm_dmmfunction xmm = NULL;       /* function pointer */
  // xmm = libxsmm_dmmdispatch(23, 23, 23, /* some problem size */
  //         NULL/*lda*/, NULL/*ldb*/, NULL/*ldc*/,
  //         &alpha, &beta, NULL/*flags*/,
  //         NULL/*&prefetch*/);
  // double a = new double
  const libxsmm_mmfunction<double> my_xmm(my_m, my_n, my_k);
  int nbatch = 10'000'000;
  size_t a_len = my_m * my_n ;
  size_t b_len = my_n * my_k ;
  size_t c_len = my_m * my_k ;
  vector<double> a(a_len*nbatch,1.);
  vector<double> b(b_len*nbatch,1.);
  vector<double> c(c_len*nbatch,1.);

  auto start = std::chrono::system_clock::now();
  if (my_xmm) { /* JiT'ted code has been generated */
    for (int i = 0; i < nbatch; ++i) {
      // const float *const ai = a ;
      // const float *const bi = b ;
      // float *const ci = c ;
      my_xmm( &a[i*a_len] , &b[i*b_len] , &c[i*c_len] );
      // my_xmm( &a[i] , &b[i] , &c[i] );
    }
  }
  auto end = std::chrono::system_clock::now();

  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;

  write_to_file(my_m, my_n, my_k, elapsed, "double_") ; 
}

int main()
{
  libxsmm_init();

  Test_Contraction_float(3,3,3) ; 
  Test_Contraction_float(8,3,3) ; 
  Test_Contraction_float(27,3,3) ; 
  Test_Contraction_double(3,3,3) ; 
  Test_Contraction_double(8,3,3) ; 
  Test_Contraction_double(27,3,3) ; 

  libxsmm_finalize();
  fprintf(stdout, "Finished\n");
  return(0);
}