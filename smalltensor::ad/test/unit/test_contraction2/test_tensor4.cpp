#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor4<ad_dual<double>,3, 3,3,3> obj1(GRAPH,0.);
	tensor4<ad_dual<double>,3, 3,3,3> obj2(GRAPH,0.);
	tensor4<ad_dual<double>,3, 3,3,3> obj3(GRAPH,0.);

	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	Index<'l'> l;
	Index<'m'> m;
	Index<'n'> n;

	// Test 1
	obj1(1,2,2,2) = ad_dual<double>(GRAPH,1);
	obj2(2,2,1,2) = ad_dual<double>(GRAPH,3);
	obj3(i,j,k,l)= 	obj1(i,j,m,n)*obj2(m,n,k,l);
	ASSERT_MSG(obj3(1,2,1,2)==3,"expr4 contraction2 operator error: obj1(i,j,m,n)*obj2(m,n,k,l)");
	
	return 0;
}