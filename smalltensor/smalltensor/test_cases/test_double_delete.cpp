#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	if (NULL!=NULL){
		cout<<"NULL is not equal to NULL" <<endl;
	}else{
		cout<<"NULL is equal to NULL" <<endl;
	}

	if (nullptr!=nullptr){
		cout<<"nullptr is not equal to nullptr" <<endl;
	}else{
		cout<<"nullptr is equal to nullptr" <<endl;
	}

	if (NULL!=nullptr){
		cout<<"NULL is not equal to nullptr" <<endl;
	}else{
		cout<<"NULL is equal to nullptr" <<endl;
	}

	int* pa= new int[10];
	int* pb= pa;

	pb = pa;
	cout<<"================\n Done set pointers" <<endl;
	// =========BAD=============
	delete[] pa;
	pa=NULL;
	// =========GOOD=============
	// delete[] pb;
	// pb=NULL;
	// ===========================
	cout<<"deleted first time" <<endl;
	if (NULL!=pb){
		cout<<"Trying to deleted second time." <<endl;
		delete[] pb;
		cout<<"deleted second time." <<endl;
		pb=NULL;
	}
	




	cout<<"All done!" <<endl;

	return 0;
}