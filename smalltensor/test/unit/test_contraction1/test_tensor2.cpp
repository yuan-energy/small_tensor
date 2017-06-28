#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor3<double, 3,3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor2<double, 3,3> obj3;
	tensor1<double, 3> obj4;
	tensor2<double, 3,3> obj5;

	obj2(2,2) = 2.;
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;

	// Test 1
	obj1(2,2,2)=1;
	obj4(2) = 3;
	obj2(i,j)=obj1(i,j,k)*obj4(k);
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj2(2,2)==3,"tensor2(_i,_j) contraction1  operator error");
	
	// Test 2
	obj3(1,1)=9; obj5(1,1) = 3;
	obj2(i,j)=obj3(i,k)*obj5(k,j);
	ASSERT_MSG(obj2(1,1)==27,"tensor2(_i,_j) contraction1  operator error");

	// Test 3
	obj1(0,0,0)=32;
	obj4(0) = 2;
	obj2(i,j)=obj4(k)*obj1(k,i,j);
	ASSERT_MSG(obj2(0,0)==64,"tensor2(_i,_j) contraction1  operator error");


	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}