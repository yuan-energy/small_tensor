#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3,3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.);
	tensor3<ad_dual<double>, 3,3,3> obj3(GRAPH,0.);
	obj1(2,0) = ad_dual<double>(GRAPH,3.);
	obj2(2,0) = ad_dual<double>(GRAPH,2.);
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	ad_dual<double> ret1 = obj2(i,j) * obj1(i,j);
	ASSERT_MSG(ret1==6,"tensor1 obj3(_i) contraction 2 operator error");

	obj3(2,2,0)=ad_dual<double>(GRAPH,7);
	tensor1<ad_dual<double>,3> check;
	check(i) = obj3(i,j,k) * obj1(j,k);
	ASSERT_MSG(check(2)==21,"obj3(i,j,k) * obj1(j,k) contraction 2 operator error");

	obj3(2,0,2)=ad_dual<double>(GRAPH,3);
	check(i) = 	obj1(j,k) * obj3(j,k,i) ;
	ASSERT_MSG(check(2)==9,"obj1(j,k) * obj3(j,k,i) contraction 2 operator error");

	return 0;
}