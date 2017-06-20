#include "libxsmm_base.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	libxsmmm_base base(3,3);
	cout<<"base(0,0)= " << base(0,0) <<endl;
	return 0;
}