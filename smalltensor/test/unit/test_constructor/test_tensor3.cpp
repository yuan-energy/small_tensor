#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor3<double, 3, 3, 3> obj1;
	obj1(1,2,1) = 3;

	ASSERT_MSG(obj1(1,2,1)==3,"tensor3(n1,n2,n3) assignment error");

	tensor3<double, 3, 3, 3> obj2(obj1) ;

	ASSERT_MSG(obj2(1,2,1)==3,"obj2(n1,n2,n3) copy constructor error");
	tensor3<double, 3, 3, 3> obj3;
	obj3 = obj1;
	ASSERT_MSG(obj3(1,2,1)==3,"obj3(n1,n2,n3) copy assignment operator error");

	tensor3<double, 3, 3, 3> obj4(std::move(obj2));
	ASSERT_MSG(obj4(1,2,1)==3,"obj4(n1,n2,n3) move constructor error");

	tensor3<double, 3, 3, 3> obj5 ;
	obj5 = std::move(obj3);
	ASSERT_MSG(obj5(1,2,1)==3,"obj5(n1,n2,n3) move assignment operator error");

	// eindex<'i'> i;
	// eindex<'j'> j;

	// tensor3<double, 3, 3, 3> L;
	// tensor3<double, 3, 3, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// double ret = L(i,j) * R(i,j);
	// ret = L(i,j) * R(j,i);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}