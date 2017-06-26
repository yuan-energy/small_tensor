#include "../../src/app/smalltensor.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	tensor2<double, 3, 3> tensor;
	tensor(1,2) = 3;
	cout<<"tensor(0,0)= " << tensor(0,0) <<endl;
	cout<<"tensor(1,0)= " << tensor(1,0) <<endl;
	cout<<"tensor(1,2)= " << tensor(1,2) <<endl;
	cout<<"tensor(1,3)= " << tensor(1,1) <<endl;

	// tensor = 22;
	cout<<"Test direct assignment\n";
	cout<<"tensor(0,0)= " << tensor(0,0) <<endl;
	cout<<"tensor(1,0)= " << tensor(1,0) <<endl;
	cout<<"tensor(1,2)= " << tensor(1,2) <<endl;
	cout<<"tensor(1,3)= " << tensor(1,1) <<endl;


	tensor2<double, 3, 3> krocker_delta;
	cout<<"Test identity\n";
	cout<<"krocker_delta(0,0)= " << krocker_delta(0,0) <<endl;
	cout<<"krocker_delta(1,0)= " << krocker_delta(1,0) <<endl;
	cout<<"krocker_delta(1,2)= " << krocker_delta(1,2) <<endl;
	cout<<"krocker_delta(1,3)= " << krocker_delta(1,1) <<endl;



	tensor2<double, 3, 3> base0;
	tensor2<double, 3, 3> base;
	tensor2<double, 3, 3> base2;
	tensor2<double, 3, 3> base3;
	base(1,2) = 1;
	base2(1,2) = 2;
	base3(1,2) = 3;
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;

	tensor2<double, 3, 3> base4(base3) ;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;


	base3=base;
	cout<<"base3(0,0)= " << base3(0,0) <<endl;
	cout<<"base3(1,0)= " << base3(1,0) <<endl;
	cout<<"base3(1,2)= " << base3(1,2) <<endl;
	cout<<"base3(1,3)= " << base3(1,1) <<endl;

	tensor2<double, 3, 3> test_move = move(base2) ;
	cout<<"test_move(0,0)= " << test_move(0,0) <<endl;
	cout<<"test_move(1,0)= " << test_move(1,0) <<endl;
	cout<<"test_move(1,2)= " << test_move(1,2) <<endl;
	cout<<"test_move(1,3)= " << test_move(1,1) <<endl;
	test_move = move(base3) ;
	cout<<"test_move(0,0)= " << test_move(0,0) <<endl;
	cout<<"test_move(1,0)= " << test_move(1,0) <<endl;
	cout<<"test_move(1,2)= " << test_move(1,2) <<endl;
	cout<<"test_move(1,3)= " << test_move(1,1) <<endl;

	cout<<"\n New Test \n";
	Index<'i'> i;
	Index<'j'> j;
	base(i,j);


	Index<'k'> k;
	Index<'l'> l;
	base(k,l);

	base4(i,k) = base(i,k);
	base(1,0) = 42;
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;

	base4 = base;
	base(1,1) = 21;
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;

	tensor2<double, 3, 3> L;
	tensor2<double, 3, 3> R;
	L(0,0) = 9; R(0,0) = 2;
	double ret = L(i,j) * R(i,j);
	ret = L(i,j) * R(j,i);
	cout<<"ret = " <<ret <<endl;
	return 0;
}