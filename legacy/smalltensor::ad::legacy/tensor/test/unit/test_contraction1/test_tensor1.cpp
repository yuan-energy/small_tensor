#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
// using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
	ad_graph<double> GRAPH;
	tensor1<ad_dual<double>, 3> obj1;
	tensor1<ad_dual<double>, 3> obj2;
	obj1(0) = ad_dual<double>(GRAPH,0.) ;
	obj1(1) = ad_dual<double>(GRAPH,0.) ;
	obj1(2) = ad_dual<double>(GRAPH,3.) ;

	obj2(0) = ad_dual<double>(GRAPH,0.) ;
	obj2(1) = ad_dual<double>(GRAPH,0.) ;
	obj2(2) = ad_dual<double>(GRAPH,2.) ;

	Index<'i'> _i;
	Index<'j'> _j;
	ad_dual<double> ret1 = obj2(_i) * obj1(_i);

	ASSERT_MSG(ret1.get_value()==6,"tensor1 obj3(_i) contraction 1 operator error");
	ASSERT_MSG(obj2(2).get_value()== 2,"tensor1 obj2(_i) contraction 1 operator error");
	ASSERT_MSG(obj1(2).get_value()== 3,"tensor1 obj1(_i) contraction 1 operator error");

	tensor2<ad_dual<double>, 3,3> obj3;
	obj3(2,2) = ad_dual<double>(GRAPH,20.) ;

	obj3(0,2) = ad_dual<double>(GRAPH,0.) ;
	obj3(1,2) = ad_dual<double>(GRAPH,0.) ;

	obj3(0,1) = ad_dual<double>(GRAPH,0.) ;
	obj3(1,1) = ad_dual<double>(GRAPH,0.) ;
	obj3(2,1) = ad_dual<double>(GRAPH,0.) ;

	obj3(0,0) = ad_dual<double>(GRAPH,0.) ;
	obj3(1,0) = ad_dual<double>(GRAPH,0.) ;
	obj3(2,0) = ad_dual<double>(GRAPH,0.) ;
	
	obj1(_i) = obj3(_i,_j) * obj2(_j) ;  
	ASSERT_MSG(obj1(2).get_value()==40,"tensor1 obj3(_i,_j) * obj2(_j) contraction 1 operator error");


	// obj1(_i) = obj2(_j) * obj3(_i,_j)  ; 
	// ASSERT_MSG(obj1(2).get_value()==40,"tensor1 obj2(_j) * obj3(_i,_j) contraction 1 operator error");

	// cout<<"Done execution. Exiting..." <<endl;


	return 0;
}