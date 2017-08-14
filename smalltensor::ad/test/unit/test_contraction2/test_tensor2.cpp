#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3,3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.);
	tensor4<ad_dual<double>, 3,3,3,3> obj3(GRAPH,0.);
	obj1(2,0) = ad_dual<double>(GRAPH,3.);
	obj3(1,0,2,0) = ad_dual<double>(GRAPH,7);
	Ident<'i'> i;
	Ident<'j'> j;
	Ident<'k'> k;
	Ident<'l'> l;
	obj2(i,j) = obj3(i,j,k,l) * obj1(k,l);
	ASSERT_MSG(obj2(1,0)==21,"tensor1 obj3(_i) contraction 2 operator error");

	tensor3<ad_dual<double>,3,3,3> obj4(GRAPH,0.);
	tensor3<ad_dual<double>,3,3,3> obj5(GRAPH,0.);
	obj4(1,1,0)=ad_dual<double>(GRAPH,2);
	obj5(1,0,2)=ad_dual<double>(GRAPH,3);
	obj2(i,j) =obj4(i,k,l)*obj5(k,l,j);
	ASSERT_MSG(obj2(1,2)==6,"tensor1 obj3(_i) contraction 2 operator error");

	obj1(1,0)=ad_dual<double>(GRAPH,11);
	obj2(i,j) =  obj1(k,l) * obj3(k,l,i,j);
	ASSERT_MSG(obj2(2,0)==77,"tensor1 obj3(_i) contraction 2 operator error");

	return 0;
}