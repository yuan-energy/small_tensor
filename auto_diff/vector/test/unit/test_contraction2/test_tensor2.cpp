#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor4<double, 3,3,3,3> obj3;
	obj1(2,0) = 3.;
	obj3(1,0,2,0) = 7;
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
	obj2(i,j) = obj3(i,j,k,l) * obj1(k,l);
	ASSERT_MSG(obj2(1,0)==21,"tensor1 obj3(_i) contraction 2 operator error");

	tensor3<double,3,3,3> obj4;
	tensor3<double,3,3,3> obj5;
	obj4(1,1,0)=2;
	obj5(1,0,2)=3;
	obj2(i,j) =obj4(i,k,l)*obj5(k,l,j);
	ASSERT_MSG(obj2(1,2)==6,"tensor1 obj3(_i) contraction 2 operator error");

	obj1(1,0)=11;
	obj2(i,j) =  obj1(k,l) * obj3(k,l,i,j);
	ASSERT_MSG(obj2(2,0)==77,"tensor1 obj3(_i) contraction 2 operator error");

	return 0;
}