#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3, 3> obj1(GRAPH,0.);
	obj1(1,2) = ad_dual<double>(GRAPH,3);
	obj1(1,1) = ad_dual<double>(GRAPH,42);
	Index<'i'> i;
	ASSERT_MSG(obj1(i,i)==42,"tensor2(n1,n1) condense tensor error");

	return 0;
}