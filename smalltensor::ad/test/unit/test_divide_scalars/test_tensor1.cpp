#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor1<ad_dual<double>, 3> obj1(GRAPH,0.);
	tensor1<ad_dual<double>, 3> obj2(GRAPH,0.);
	tensor1<ad_dual<double>, 3> obj3(GRAPH,0.);
	obj1(2) = ad_dual<double>(GRAPH,3.);
	obj2(2) = ad_dual<double>(GRAPH,2.);
	Ident<'i'> _i;
	obj3(_i) = obj2(_i) / 2;
	ASSERT_MSG(obj3(2)== 1,"tensor1 obj3(_i) plus operator error");
	ASSERT_MSG(obj2(2)== 2,"tensor1 obj2(_i) plus operator error");
	ASSERT_MSG(obj1(2)== 3,"tensor1 obj1(_i) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;



	return 0;
}