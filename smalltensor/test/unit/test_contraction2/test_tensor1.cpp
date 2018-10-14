#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor2<double, 3,3> obj1;
	tensor2<double, 3,3> obj2;
	tensor3<double, 3,3,3> obj3;
	obj1(2,0) = 3.;
	obj2(2,0) = 2.;
	eindex<'i'> i;
	eindex<'j'> j;
	eindex<'k'> k;
	double ret1 = obj2(i,j) * obj1(i,j);
	ASSERT_MSG(ret1==6,"tensor1 obj3(_i) contraction 2 operator error");

	obj3(2,2,0)=7;
	tensor1<double,3> check;
	check(i) = obj3(i,j,k) * obj1(j,k);
	ASSERT_MSG(check(2)==21,"obj3(i,j,k) * obj1(j,k) contraction 2 operator error");

	obj3(2,0,2)=3;
	check(i) = 	obj1(j,k) * obj3(j,k,i) ;
	ASSERT_MSG(check(2)==9,"obj1(j,k) * obj3(j,k,i) contraction 2 operator error");


	// -------------------------------------------------------------------------------------
	tensor2<float, 3,3> obj4;
	tensor2<float, 3,3> obj5;
	obj4(0,0) = 1.; obj4(0,1) = 2.; obj4(0,2) = 3.;
	obj4(1,0) = 4.; obj4(1,1) = 5.; obj4(1,2) = 6.;
	obj4(2,0) = 7.; obj4(2,1) = 8.; obj4(2,2) = 9.;
	obj5(0,0) = 2 ; obj5(0,1) = 3 ; obj5(0,2) = 4 ;
	obj5(1,0) = 5 ; obj5(1,1) = 6 ; obj5(1,2) = 7 ;
	obj5(2,0) = 8 ; obj5(2,1) = 9 ; obj5(2,2) = 10 ;
	float sum = obj4(i,j) * obj5(i,j);
	ASSERT_MSG(sum==330,"tensor1 obj3(_i) contraction 2 operator error");

	// -------------------------------------------------------------------------------------
	tensor2<float, 2,3> obj6;
	tensor2<float, 2,3> obj7;
	obj6(0,0) = 1.; obj6(0,1) = 2.; obj6(0,2) = 3.;
	obj6(1,0) = 4.; obj6(1,1) = 5.; obj6(1,2) = 6.;
	obj7(0,0) = 2 ; obj7(0,1) = 3 ; obj7(0,2) = 4 ;
	obj7(1,0) = 5 ; obj7(1,1) = 6 ; obj7(1,2) = 7 ;
	float sum_ = obj6(i,j) * obj7(i,j);
	ASSERT_MSG(sum_==112,"tensor1 obj3(_i) contraction 2 operator error");



	return 0;
}