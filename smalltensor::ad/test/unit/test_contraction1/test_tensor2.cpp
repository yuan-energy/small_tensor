#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
	ad_graph<double> GRAPH;
	tensor3<ad_dual<double>, 3,3,3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.)  ;
	tensor2<ad_dual<double>, 3,3> obj3(GRAPH,0.)  ;
	tensor1<ad_dual<double>, 3> obj4(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj5(GRAPH,0.)  ;

	obj2(2,2) = ad_dual<double>(GRAPH, 2.);
	Ident<'i'> i;
	Ident<'j'> j;
	Ident<'k'> k;

	// // Test 1
	obj1(2,2,2)= ad_dual<double>(GRAPH,1) ;
	obj4(2) = ad_dual<double>(GRAPH,3);
	obj2(i,j)=obj1(i,j,k)*obj4(k);
	ASSERT_MSG(obj2(2,2).get_value()==3,"tensor2(_i,_j) contraction1  operator error");
	
	// Test 2
	obj3(1,1)=ad_dual<double>(GRAPH,9); obj5(1,1) = ad_dual<double>(GRAPH,3);
	obj2(i,j)=obj3(i,k)*obj5(k,j);
	ASSERT_MSG(obj2(1,1).get_value()==27,"tensor2(_i,_j) contraction1  operator error");
	ASSERT_MSG(obj2(1,1)==27,"tensor2(_i,_j) contraction1  operator error");

	// // Test 3
	obj1(0,0,0)=ad_dual<double>(GRAPH,32);
	obj4(0) = ad_dual<double>(GRAPH,2);
	obj2(i,j)=obj4(k)*obj1(k,i,j);
	ASSERT_MSG(obj2(0,0).get_value()==64,"tensor2(_i,_j) contraction1  operator error");
	ASSERT_MSG(obj2(0,0)==64,"tensor2(_i,_j) contraction1  operator error");
	// cout<<"obj2(0,0)            ="<<obj2(0,0)<<endl;
	// cout<<"obj2(0,0).get_value()="<<obj2(0,0).get_value()<<endl;


	cout<<"Done execution. Exiting..." <<endl;

	return 0;
}