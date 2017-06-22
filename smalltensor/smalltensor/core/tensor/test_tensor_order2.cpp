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



	tensor2<double> base0;
	tensor2<double> base(3,3);
	tensor2<double> base2(3,3);
	tensor2<double> base3(3,3);
	base(1,2) = 1;
	base2(1,2) = 2;
	base3(1,2) = 3;
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;

	tensor2<double> base4(base3) ;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;


	base3=base;
	cout<<"base3(0,0)= " << base3(0,0) <<endl;
	cout<<"base3(1,0)= " << base3(1,0) <<endl;
	cout<<"base3(1,2)= " << base3(1,2) <<endl;
	cout<<"base3(1,3)= " << base3(1,1) <<endl;

	tensor2<double> test_move = move(base2) ;
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
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;
	
	base4 = base;
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;
	return 0;
}