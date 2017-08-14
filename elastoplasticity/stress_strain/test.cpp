#include "../../smalltensor::ad/app/smalltensor.h"
#include "stress3D.h"	
#include <iostream>
using namespace std ;
using namespace smalltensor::ad ;
int main(int argc, char const *argv[])
{
	ad_graph<double> GRAPH;
	tensor2<ad_dual<double>, 3,3> obj1(GRAPH, 0.) ;
	obj1(1,1).set_value(3);
	auto mean = obj1.getI1();
	cout<<"mean = " <<mean.get_value()<<endl;



	return 0;
}