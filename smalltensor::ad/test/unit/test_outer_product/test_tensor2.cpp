#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor1<ad_dual<double>, 3> obj1(GRAPH,0.);
	tensor2<ad_dual<double>, 3,3> obj2(GRAPH,0.);
	tensor3<ad_dual<double>, 3,3,3> obj3(GRAPH,0.);
	obj1(2) = ad_dual<double>(GRAPH,3.);
	obj2(2,2) = ad_dual<double>(GRAPH,2.);
	Ident<'i'> _i;
	Ident<'j'> _j;
	Ident<'k'> _k;
	obj3(_i,_j,_k) = obj2(_i,_j) * obj1(_k);
	obj3(_i,_j,_k) = obj1(_i) * obj2(_j,_k) ;
	// cout<<"obj3(2,2) = " << obj3(2,2) <<endl;
	ASSERT_MSG(obj3(2,2,2)== 6,"tensor2() outer product error");

	cout<<"Done execution. Exiting..." <<endl;


	return 0;
}