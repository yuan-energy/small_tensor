#include "ltensor/LTensor.h"
#include <chrono>
#include <iostream>

int main(int argc, char const *argv[])
{
	FTensor2 a(3,3,0.0) ; 
	FTensor2 b(3,3,0.0) ; 
	FTensor2 c(3,3,0.0) ; 

	int count = 0 ; 

	for (int i = 0; i < 3; ++i)	{
		for (int j = 0; j < 3; ++j){
			a(i,j) = count ; 
			b(i,j) = count++ ; 
		}
	}

	Index<'I'> I;
	Index<'J'> J;
	Index<'K'> K;

	size_t Nrepeat = 1'000'000'0 ; 

	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < Nrepeat; ++i)	{
		c(I,K) = a(I,J) * b(J,K) ; 
	}
	auto end = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count();

	std::cerr << " c = \n" 
		<< c(0,0) << " " << c(0,1) << " " << c(0,2) << "\n"
		<< c(1,0) << " " << c(1,1) << " " << c(1,2) << "\n"
		<< c(2,0) << " " << c(2,1) << " " << c(2,2) << "\n"
		;

	std::cerr << " duration = \n" ; 
	std::cerr << duration << std::endl ; 

	return 0;
}