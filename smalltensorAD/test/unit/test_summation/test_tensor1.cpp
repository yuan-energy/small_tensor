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
	obj3(_i) = obj2(_i) + obj1(_i);
	ASSERT_MSG(obj3(2)== 5,"tensor1 obj3(_i) plus operator error");
	ASSERT_MSG(obj2(2)== 2,"tensor1 obj2(_i) plus operator error");
	ASSERT_MSG(obj1(2)== 3,"tensor1 obj1(_i) plus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	// Ident<'i'> i;
	// Ident<'j'> j;

	// tensor1<ad_dual<double>, 3> L;
	// tensor1<ad_dual<double>, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// ad_dual<double> ret = L(i,j) * R(i,j);
	// ret = L(i,j) * R(j,i);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}