#include "smalltensor.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include "test_utils.h"



using namespace smalltensor;

int main(int argc, char const *argv[])
{
	Test_Contraction_float<3,3,3>() ; 
	Test_Contraction_float<8,3,3>() ; 
	Test_Contraction_float<20,3,3>() ; 
	Test_Contraction_float<27,3,3>() ; 
	Test_Contraction_double<3,3,3>() ; 
	Test_Contraction_double<8,3,3>() ; 
	Test_Contraction_double<20,3,3>() ; 
	Test_Contraction_double<27,3,3>() ; 

	return 0;
}
