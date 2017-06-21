#include "xsmm_base.h"

#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	xsmm_base<double,2> base0;
	xsmm_base<double,2> base(3,3);
	xsmm_base<double,2> base2(3,3);
	xsmm_base<double,2> base3(3,3);
	base(1,2) = 1;
	base2(1,2) = 2;
	base3(1,2) = 3;
	cout<<"base(0,0)= " << base(0,0) <<endl;
	cout<<"base(1,0)= " << base(1,0) <<endl;
	cout<<"base(1,2)= " << base(1,2) <<endl;
	cout<<"base(1,3)= " << base(1,1) <<endl;

	xsmm_base<double,2> base4(base3) ;
	cout<<"base4(0,0)= " << base4(0,0) <<endl;
	cout<<"base4(1,0)= " << base4(1,0) <<endl;
	cout<<"base4(1,2)= " << base4(1,2) <<endl;
	cout<<"base4(1,3)= " << base4(1,1) <<endl;


	base3=base;
	cout<<"base3(0,0)= " << base3(0,0) <<endl;
	cout<<"base3(1,0)= " << base3(1,0) <<endl;
	cout<<"base3(1,2)= " << base3(1,2) <<endl;
	cout<<"base3(1,3)= " << base3(1,1) <<endl;

	xsmm_base<double,2> test_move = move(base2) ;
	cout<<"test_move(0,0)= " << test_move(0,0) <<endl;
	cout<<"test_move(1,0)= " << test_move(1,0) <<endl;
	cout<<"test_move(1,2)= " << test_move(1,2) <<endl;
	cout<<"test_move(1,3)= " << test_move(1,1) <<endl;
	test_move = move(base3) ;
	cout<<"test_move(0,0)= " << test_move(0,0) <<endl;
	cout<<"test_move(1,0)= " << test_move(1,0) <<endl;
	cout<<"test_move(1,2)= " << test_move(1,2) <<endl;
	cout<<"test_move(1,3)= " << test_move(1,1) <<endl;
	return 0;
}