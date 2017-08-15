#include "../include_small_tensor.h"

#include <iostream>
using namespace std;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
ad_graph<double> GRAPH;
	tensor1<ad_dual<double>, 3> obj1(GRAPH,0.);
	tensor3<ad_dual<double>, 3,3,3> obj2(GRAPH,0.);
	tensor4<ad_dual<double>, 3,3,3,3> obj3(GRAPH,0.);
	obj1(2) = ad_dual<double>(GRAPH,3.);
	obj2(2,1,2) = ad_dual<double>(GRAPH,2.);
	Ident<'i'> _i;
	Ident<'j'> _j;
	Ident<'k'> _k;
	Ident<'l'> _l;
	obj3(_i,_j,_k,_l) = obj1(_i) * obj2(_j,_k,_l);
	ASSERT_MSG(obj3(2,2,1,2)==6,"tensor3(_i,_j,_k,_l) outer product  error");

	cout<<"Done execution. Exiting..." <<endl;


	return 0;
}