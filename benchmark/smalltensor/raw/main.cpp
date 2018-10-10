// #include "tensor/vector3.h"
// #include "../log/logger.h"
// #include "../log/logstream.h"

#include <iostream>
#include <chrono>
#include "mat333.h"

// using namespace SimpleTensor ;
int main(int argc, char const *argv[])
{
	// Logger::set_global_logging_level(::Logger::kWarn);
	// Vector3 a(1,2,3) ; 
	// Vector3 b(4,5,6) ; 

	float __attribute__((aligned(0x20))) a[9] = {1,2,3,4,5,6,7,8,9} ; 
	float __attribute__((aligned(0x20))) b[9] = {1,2,3,4,5,6,7,8,9} ; 
	float __attribute__((aligned(0x20))) c[9] = {1,2,3,4,5,6,7,8,9} ; 

	// Vector3 c = a + b ; 
	auto start = std::chrono::system_clock::now();
	for (int i = 0; i < 1'000'000'0 ; ++i){
		_matmul<float, 3,3,3>(a, b, c) ; 
	}
	auto end = std::chrono::system_clock::now();
	auto elapsed =
    	std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
    std::cerr << " elapsed = " << elapsed << std::endl ; 

	std::cerr << " c = " 
		<< c[0] << ", "
		<< c[1] << ", "
		<< c[2] << ", "
		<< c[3] << ", "
		<< std::endl ; 
	  ;  

	return 0;
}