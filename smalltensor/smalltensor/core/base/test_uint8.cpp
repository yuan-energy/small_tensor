#include <iostream>
#include <cstdint>
using namespace std;
int main(int argc, char const *argv[])
{
	// typedef unsigned char uint8;
	uint_fast16_t a ; 
	a = 1;
	cout<<"a = " << a <<endl;
	cout<<"a = " << int(a) <<endl;
	cout<<"a = " << 1 <<endl;
	cout<<"a ==1 " << (a==1) <<endl;
	cout<<"a ==1 " << (a==2) <<endl;
	return 0;
}