#include "ltensor/LTensor.h"
#include <chrono>
#include <iostream>

Index<'I'> I;
Index<'J'> J;
Index<'K'> K;

void write_to_file(int m, int n, int k , double duration, std::string const& prefix=""){
	std::cerr << " m n k = " << m << ", " << n << ", " << k << "\n" ; 
	std::cerr << " duration = " << duration << std::endl ; 

	std::ofstream myfile ; 
	std::string out_file_name = prefix + "time" + std::to_string(m) + "x" + std::to_string(n) + "x" + std::to_string(k) + ".txt" ;
	myfile.open(out_file_name) ; 
	myfile << duration << std::endl ;
	myfile.close(); 
}

void initi_tensor(FTensor2& t, int Nrow, int Ncol, int start=0){
	for (int i = 0; i < Nrow; ++i)	{
		for (int j = 0; j < Ncol; ++j){
			t(i,j) = start++ ; 
		}
	}
}
void initi_tensor(DTensor2& t, int Nrow, int Ncol, int start=0){
	for (int i = 0; i < Nrow; ++i)	{
		for (int j = 0; j < Ncol; ++j){
			t(i,j) = start++ ; 
		}
	}
}
void Test_Contraction_float(int m, int n, int k ){
	FTensor2 a(m,n,0.0) ; 
	FTensor2 b(n,k,0.0) ; 
	FTensor2 c(m,k,0.0) ; 
	initi_tensor(a, m, n, 0) ;
	initi_tensor(b, n, k, 1) ;
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
void Test_Contraction_double(int m, int n, int k ){
	DTensor2 a(m,n,0.0) ; 
	DTensor2 b(n,k,0.0) ; 
	DTensor2 c(m,k,0.0) ; 
	initi_tensor(a, m, n, 0) ;
	initi_tensor(b, n, k, 1) ;
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
	write_to_file(m,n,k,duration,"double_") ; 
}


int main(int argc, char const *argv[])
{

	Test_Contraction_float(3,3,3) ; 
	Test_Contraction_float(8,3,3) ; 
	Test_Contraction_float(20,3,3) ; 
	Test_Contraction_float(27,3,3) ; 
	Test_Contraction_double(3,3,3) ; 
	Test_Contraction_double(8,3,3) ; 
	Test_Contraction_double(20,3,3) ; 
	Test_Contraction_double(27,3,3) ; 


	return 0;
}