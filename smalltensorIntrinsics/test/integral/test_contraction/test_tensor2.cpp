#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor2<double, 3,3> obj3;

	obj2(2,2) = 2.;
	Index<'i'> i;
	Index<'j'> j;
	// Index<'k'> k;

	// Test 1
	obj1(2,2)= 1;
	obj3(i,j)=obj1(i,j) + obj2(i,j) * 3;
	obj3(i,j)=obj1(i,j) + 3 * obj2(i,j) ;
	ASSERT_MSG(obj3(2,2)==7,"tensor2(_i,_j) contraction1  operator error");
	
	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}