#include "tensor2.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor2<double> tensor(3,3);
	tensor(1,2) = 3;
	cout<<"tensor(0,0)= " << tensor(0,0) <<endl;
	cout<<"tensor(1,0)= " << tensor(1,0) <<endl;
	cout<<"tensor(1,2)= " << tensor(1,2) <<endl;
	cout<<"tensor(1,3)= " << tensor(1,1) <<endl;

	tensor = 22;
	cout<<"Test direct assignment\n";
	cout<<"tensor(0,0)= " << tensor(0,0) <<endl;
	cout<<"tensor(1,0)= " << tensor(1,0) <<endl;
	cout<<"tensor(1,2)= " << tensor(1,2) <<endl;
	cout<<"tensor(1,3)= " << tensor(1,1) <<endl;


	tensor2<double> krocker_delta(3,3,"identity");
	cout<<"Test identity\n";
	cout<<"krocker_delta(0,0)= " << krocker_delta(0,0) <<endl;
	cout<<"krocker_delta(1,0)= " << krocker_delta(1,0) <<endl;
	cout<<"krocker_delta(1,2)= " << krocker_delta(1,2) <<endl;
	cout<<"krocker_delta(1,3)= " << krocker_delta(1,1) <<endl;

	return 0;
}