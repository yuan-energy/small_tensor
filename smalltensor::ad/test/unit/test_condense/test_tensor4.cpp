#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor4<ad_dual<double>, 3, 3, 3, 3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.);
	obj1(1,2,1,2) = ad_dual<double>(GRAPH,9993);
	obj1(1,2,1,1) = ad_dual<double>(GRAPH,3);
	obj1(1,2,2,2) = ad_dual<double>(GRAPH,39);
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	obj2(i,j) = obj1(i,j,k,k);
	ASSERT_MSG(obj2(1,2)==42,"tensor4(i,j,k,k) condense tensor error");


	return 0;
}