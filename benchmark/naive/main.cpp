#include <iostream>
#include "contraction.h"
#include <chrono>

int main(int argc, char const *argv[])
{
		
	float a[9] = {1,2,3,4,5,6,7,8,9};
	float b[9] = {2,3,4,4,6,7,8,9,10};
	float c[9] = {0,0,0,0,0,0,0,0,0};

	size_t m = 3 ; 
	size_t n = 3 ; 
	size_t k = 3 ; 

	size_t Nrepeat = 1'000'000'0 ; 

	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < Nrepeat ; ++i){
		Order2Contraction(a,b,c,m,n,k) ; 
	}
	auto end = std::chrono::system_clock::now();

	// auto duration = std::chrono::duration_cast<std::chrono::microseconds>
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(end-start).count();

	std::cerr << " c = \n" 
		<< c[0] << " " << c[1] << " " << c[2] << "\n"
		<< c[3] << " " << c[4] << " " << c[5] << "\n"
		<< c[6] << " " << c[7] << " " << c[8] << "\n"
		;

	std::cerr << " duration = \n" ; 
	std::cerr << duration << std::endl ; 

	return 0;
}