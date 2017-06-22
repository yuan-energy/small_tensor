#include <iostream>


using namespace std;
class base
{
public:
	int *data;
	char array[100];
	int v1;
	int v2;
public:
	base(){
		data=new int[100];
		data[0] = 101;
	}
};

class hold_by_pointer
{
public:
	base * p;
public:
	hold_by_pointer();
	hold_by_pointer(hold_by_pointer const& rhs): p(rhs.p) {}
	hold_by_pointer& operator=(hold_by_pointer const& rhs) {p=(rhs.p);}
	hold_by_pointer(hold_by_pointer&& rhs) noexcept : p(std::move(rhs.p)) {}

	hold_by_pointer(base& rhs): p(&rhs) {}
};

class hold_by_copy
{
public:
	base copy_;
public:
	hold_by_copy(base& rhs): copy_(rhs) {
	}
};

int main(int argc, char const *argv[])
{
	base a;
	hold_by_pointer pointer(a) ;
	hold_by_copy   copy(a) ;
	cout<<"sizeof(base)   = " << sizeof(a) <<endl;
	cout<<"sizeof(pointer)= " << sizeof(pointer) <<endl;
	cout<<"sizeof(copy)   = " << sizeof(copy) <<endl;

    int* test_pointer = pointer.p->data ; 
	cout<<"test_pointer   = " << test_pointer[0] <<endl;
    
    int* test_refer = copy.copy_.data ;
	cout<<"test_refer     = " << test_refer[0] <<endl;

	return 0;
}