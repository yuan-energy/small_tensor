#include "../include_small_tensor.h"

#include <iostream>
using namespace std; using namespace smalltensor;
int main(int argc, char const *argv[])
{
	tensor4<double,3, 3,3,3> obj1;
	tensor3<double,3, 3,3> obj2;
	tensor3<double,3, 3,3> obj3;
	tensor2<double,3, 3> obj4;
	tensor3<double,3, 3,3> obj5;
	tensor4<double,3, 3,3,3> obj7;

	eindex<'i'> i;
	eindex<'j'> j;
	eindex<'k'> k;
	eindex<'l'> l;
	eindex<'m'> m;

	// Test 1
	obj7(2,2,2,2)=1;
	obj4(2,1) = 3;
	obj1(i,j,k,l)= 	obj7(i,j,k,m)*obj4(m,l);
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj1(2,2,2,1)==3,"tensor2(_i,_j) contraction1  operator error");
	
	// Test 2
	obj2(2,1,0)=1;
	obj3(0,1,1) = 5;
	obj1(i,j,k,l)= 	obj2(i,j,m)*obj3(m,k,l);
	ASSERT_MSG(obj1(2,1,1,1)==5,"tensor2(_i,_j) contraction1  operator error");

	// Test 3
	obj7(1,2,2,2)=1;
	obj4(2,1) = 91;
	obj1(i,j,k,l)= 	obj4(i,m) * obj7(m,j,k,l);
	ASSERT_MSG(obj1(2,2,2,2)==91,"tensor2(_i,_j) contraction1  operator error");

	// // // Test 2
	// // obj1=obj1*0;  obj2=obj2*0;  obj7=obj7*0;
	// obj1(2,2,1) = 2; obj2(1,0)=4;
	// obj7(i,j,k)=obj1(i,j,l)*obj2(l,k);
	// ASSERT_MSG(obj7(2,2,0)==8,"tensor2(_i,_j) contraction1  operator error");

	// // // Test 3
	// obj1(2,2,1) = 2; obj2(1,2)=4;
	// obj7(i,j,k)=obj2(i,l) * obj1(l,j,k);
	// ASSERT_MSG(obj7(1,2,1)==8,"tensor2(_i,_j) contraction1  operator error");


	// // // Test 4
	// obj7(2,2,2,2)=7;
	// obj4(2) = 1;
	// obj1(i,j,k) = obj4(l)*obj7(l,i,j,k);
	// // cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	// ASSERT_MSG(obj1(2,2,2)==7,"tensor2(_i,_j) contraction1  operator error");



	return 0;
}