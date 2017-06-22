#include "index_basic.h"
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	

	Index<'i'> _a;

	cout<<"sizeof(a)= " << sizeof(_a) <<endl;

	constexpr char _b ='i' ;
	cout<<"sizeof(b)= " << sizeof(_b) <<endl;


	return 0;
}