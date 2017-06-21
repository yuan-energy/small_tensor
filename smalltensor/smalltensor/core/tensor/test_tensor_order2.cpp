#include "tensor2.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor2<double> tensor(3,3);
	cout<<"tensor(0,0)= " << tensor(0,0) <<endl;
	return 0;
}