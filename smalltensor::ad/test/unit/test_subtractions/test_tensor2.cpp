#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3,3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj3(GRAPH,0.);
	obj1(2,2) = ad_dual<double>(GRAPH,3.);
	obj2(2,2) = ad_dual<double>(GRAPH,2.);
	Index<'i'> _i;
	Index<'j'> _j;
	obj3(_i,_j) = obj2(_i,_j) - obj1(_i,_j);
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj3(2,2)==-1,"tensor2(_i,_j) minus operator error");

	cout<<"Done execution. Exiting..." <<endl;

	// Index<'i'> i;
	// Index<'j'> j;

	// tensor1<ad_dual<double>, 3> L;
	// tensor1<ad_dual<double>, 3> R;
	// L(0,0) = 9; R(0,0) = 2;
	// ad_dual<double> ret = L(i,j) * R(i,j);
	// ret = L(i,j) * R(j,i);
	// ASSERT_MSG(ret==18,"expr2 tensor2 contraction error");


	return 0;
}