#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;

int main(int argc, char const *argv[])
{
	tensor1<double, 3> obj1;
	tensor1<double, 3> obj2;
	obj1(2) = 3.;
	obj2(2) = 2.;
	eindex<'i'> _i;
	eindex<'j'> _j;
	double ret1 = obj2(_i) * obj1(_i);
	ASSERT_MSG(ret1==6,"tensor1 obj3(_i) contraction 1 operator error");
	ASSERT_MSG(obj2(2)== 2,"tensor1 obj2(_i) contraction 1 operator error");
	ASSERT_MSG(obj1(2)== 3,"tensor1 obj1(_i) contraction 1 operator error");

	tensor2<double, 3,3> obj3;
	obj3(2,2) = 20;
	obj1(_i) = obj3(_i,_j) * obj2(_j) ;  
	ASSERT_MSG(obj1(2)==40,"tensor1 obj3(_i,_j) * obj2(_j) contraction 1 operator error");


	obj1(_i) = obj2(_j) * obj3(_i,_j)  ; 
	ASSERT_MSG(obj1(2)==40,"tensor1 obj2(_j) * obj3(_i,_j) contraction 1 operator error");

	cout<<"Done execution. Exiting..." <<endl;


	return 0;
}