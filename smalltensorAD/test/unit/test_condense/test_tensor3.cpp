#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor3<ad_dual<double>, 3, 3, 3> obj1(GRAPH,0.);
	tensor1<ad_dual<double>, 3> obj2(GRAPH,0.);
	obj1(1,2,1) = ad_dual<double>(GRAPH,3);
	obj1(1,1,1) = ad_dual<double>(GRAPH,42);
	Ident<'i'> i;
	Ident<'j'> j;
	obj2(i) = obj1(i,j,j);
	ASSERT_MSG(obj2(1)==42,"tensor3(i,j,j) condense tensor error");

	return 0;
}