
#include "smalltensor.h"
#include <chrono>
#include <iostream>

int main(int argc, char const *argv[])
{
	tensor2<float,3,3> a ; 
	tensor2<float,3,3> b ; 
	tensor2<float,3,3> c ; 
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

	std::cerr << " duration = \n" ; 
	std::cerr << duration << std::endl ;


	// tensor2<

	return 0;
}