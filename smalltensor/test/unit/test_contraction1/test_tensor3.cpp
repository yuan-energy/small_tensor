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
	tensor4<double, 3,3,3,3> obj6;
	tensor3<double, 3,3,3> obj7;

	obj2(2,2) = 2.;
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;

	// Test 1
	obj6(2,2,2,2)=1;
	obj4(2) = 3;
	obj1(i,j,k)= 	obj6(i,j,k,l)*obj4(l);
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj1(2,2,2)==3,"tensor2(_i,_j) contraction1  operator error");
	
	// // Test 2
	// obj1=obj1*0;  obj2=obj2*0;  obj7=obj7*0;
	obj1(2,2,1) = 2; obj2(1,0)=4;
	obj7(i,j,k)=obj1(i,j,l)*obj2(l,k);
	ASSERT_MSG(obj7(2,2,0)==8,"tensor2(_i,_j) contraction1  operator error");

	// // Test 3
	obj1(2,2,1) = 2; obj2(1,2)=4;
	obj7(i,j,k)=obj2(i,l) * obj1(l,j,k);
	ASSERT_MSG(obj7(1,2,1)==8,"tensor2(_i,_j) contraction1  operator error");


	// // Test 4
	obj6(2,2,2,2)=7;
	obj4(2) = 1;
	obj1(i,j,k) = obj4(l)*obj6(l,i,j,k);
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj1(2,2,2)==7,"tensor2(_i,_j) contraction1  operator error");




	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}