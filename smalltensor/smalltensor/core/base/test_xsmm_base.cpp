#include "xsmm_base.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	xsmm_base<double,2> base(3,3);
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,1)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;
	return 0;
}