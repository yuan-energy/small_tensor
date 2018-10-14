#include <chrono>
#include <iostream>
#include <fstream>
using namespace smalltensor;
eindex<'I'> I;
eindex<'J'> J;
eindex<'K'> K;


void write_to_file(int m, int n, int k , double duration, std::string const& prefix=""){
	std::cerr << " m n k = " << m << ", " << n << ", " << k << "\n" ; 
	std::cerr << " duration = " << duration << std::endl ; 

	std::ofstream myfile ; 
	std::string out_file_name = prefix + "time" + std::to_string(m) + "x" + std::to_string(n) + "x" + std::to_string(k) + ".txt" ;
	myfile.open(out_file_name) ; 
	myfile << duration << std::endl ;
	myfile.close(); 
}



template<size_t m, size_t n, size_t k>
void Test_Contraction_float(){
	tensor2<float,m,n> a ; 
	tensor2<float,n,k> b ; 
	tensor2<float,m,k> c ; 
	size_t Nrepeat = 10'000'000 ; 
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < Nrepeat; ++i)	{
		c(I,K) = a(I,J) * b(J,K) ; 
	}
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count();
	// std::cerr << " c = \n" 
	// 	<< c(0,0) << " " << c(0,1) << " " << c(0,2) << "\n"
	// 	<< c(1,0) << " " << c(1,1) << " " << c(1,2) << "\n"
	// 	<< c(2,0) << " " << c(2,1) << " " << c(2,2) << "\n"
	// 	;
	write_to_file(m,n,k, duration, "float_") ; 
}



template<size_t m, size_t n, size_t k>
void Test_Contraction_double(){
	tensor2<double,m,n> a ; 
	tensor2<double,n,k> b ; 
	tensor2<double,m,k> c ; 
	size_t Nrepeat = 10'000'000 ; 
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < Nrepeat; ++i)	{
		c(I,K) = a(I,J) * b(J,K) ; 
	}
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count();
	// std::cerr << " c = \n" 
	// 	<< c(0,0) << " " << c(0,1) << " " << c(0,2) << "\n"
	// 	<< c(1,0) << " " << c(1,1) << " " << c(1,2) << "\n"
	// 	<< c(2,0) << " " << c(2,1) << " " << c(2,2) << "\n"
	// 	;
	write_to_file(m,n,k, duration, "double_") ; 
}

