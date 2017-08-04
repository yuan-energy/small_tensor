#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor4<ad_dual<double>,3, 3,3,3> obj1(GRAPH,0.);
	tensor3<ad_dual<double>,3, 3,3> obj2(GRAPH,0.);
	tensor3<ad_dual<double>,3, 3,3> obj3(GRAPH,0.);
	tensor2<ad_dual<double>,3, 3> obj4(GRAPH,0.);
	tensor3<ad_dual<double>,3, 3,3> obj5(GRAPH,0.);
	tensor4<ad_dual<double>,3, 3,3,3> obj7(GRAPH,0.);

	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
	Index<'m'> m;

	// Test 1
	obj7(2,2,2,2)=ad_dual<double>(GRAPH,1);
	obj4(2,1) = ad_dual<double>(GRAPH,3);
	obj1(i,j,k,l)= 	obj7(i,j,k,m)*obj4(m,l);
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj1(2,2,2,1)==3,"tensor2(_i,_j) contraction1  operator error");
	
	// Test 2
	obj2(2,1,0)=ad_dual<double>(GRAPH,1);
	obj3(0,1,1) = ad_dual<double>(GRAPH,5);
	obj1(i,j,k,l)= 	obj2(i,j,m)*obj3(m,k,l);
	ASSERT_MSG(obj1(2,1,1,1)==5,"tensor2(_i,_j) contraction1  operator error");

	// Test 3
	obj7(1,2,2,2)=ad_dual<double>(GRAPH,1);
	obj4(2,1) = ad_dual<double>(GRAPH,91);
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