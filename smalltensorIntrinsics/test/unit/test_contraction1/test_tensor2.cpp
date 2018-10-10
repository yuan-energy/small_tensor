#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor3<float, 3,3,3> obj1;
	tensor2<float, 3,3> obj2;
	tensor2<float, 3,3> obj3;
	tensor1<float, 3> obj4;
	tensor2<float, 3,3> obj5;

	tensor2<float, 8,3> obj6;
	tensor2<float, 8,3> obj7;

	tensor2<float, 2,2> obj8;
	tensor2<float, 2,2> obj9;
	tensor2<float, 2,2> obj10;

	obj2(2,2) = 2.;
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;

	// Test 1
	obj1(2,2,2)=1;
	obj4(2) = 3;
	obj2(i,j)=obj1(i,j,k)*obj4(k);
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

	// Test 4
	obj7(i,j) = obj6(i,k) * obj3(k,j) ; 

	// Test 5
	obj8(0,0) = 1 ; obj8(0,1) = 2 ; 
	obj8(1,0) = 3 ; obj8(1,1) = 4 ; 
	obj9(0,0) = 11 ; obj9(0,1) = 12 ; 
	obj9(1,0) = 13 ; obj9(1,1) = 14 ; 
	obj10(i,j) = obj8(i,k) * obj9(k,j) ; 
	ASSERT_MSG(obj10(0,0)==37,"tensor2(_i,_j) contraction1  operator error");
	ASSERT_MSG(obj10(0,1)==40,"tensor2(_i,_j) contraction1  operator error");
	ASSERT_MSG(obj10(1,0)==85,"tensor2(_i,_j) contraction1  operator error");
	ASSERT_MSG(obj10(1,1)==92,"tensor2(_i,_j) contraction1  operator error");

	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}