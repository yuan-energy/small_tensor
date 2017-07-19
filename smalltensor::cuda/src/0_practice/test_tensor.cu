#pragma once
// #include "../utils/__utils.h"
// #include "../expressions/expressions.h"
#include <iostream>
using namespace std;
// template <typename val_type>
template <typename val_type, std::size_t dim>
class device_tensor1
{
public:
	val_type* d_data_;

	device_tensor1()
	// : d_data_{new val_type[dim]}
	{
		// cudaMalloc((void**) &(this.d_data_), sizeof(val_type)*dim);
	}
	device_tensor1(device_tensor1 const& d_rhs_)
	// : d_data_{new val_type[dim]}
	{
		cudaMalloc((void**) &d_data_, sizeof(val_type)*dim);
		// DEBUG_MSG("device_tensor1 copy constructor is called");
		// std::memcpy(d_data_, rhs_.d_data_, sizeof(d_data_)*dim);
		cudaMemcpy(d_data_, d_rhs_.d_data_ , dim, cudaMemcpyDeviceToDevice);
	}
	device_tensor1& operator=(device_tensor1 const& d_rhs_){
		// DEBUG_MSG("device_tensor1 copy assignment operator is called");
		if(this != &d_rhs_){
	        // std::memcpy(d_data_, rhs_.d_data_, sizeof(d_data_)*dim);		
			cudaMemcpy(d_data_, d_rhs_.d_data_ , dim, cudaMemcpyDeviceToDevice);
		}
		return *this;
	}
    device_tensor1(device_tensor1&& d_rhs_) noexcept    
    // : d_data_{new val_type[dim]}
    {
		cudaMalloc((void**) &d_data_, sizeof(val_type)*dim);
    	std::swap(d_data_, d_rhs_.d_data_);
    	// DEBUG_MSG("device_tensor1 move constructor is called");

    }
    device_tensor1& operator=(device_tensor1&& d_rhs_) noexcept{
    	// DEBUG_MSG("device_tensor1 move assignment operator is called");
    	if(this != &d_rhs_){
    		std::swap(d_data_, d_rhs_.d_data_);
    	}
    	return *this;
    }
	~device_tensor1(){
		if (d_data_!=nullptr){
		    cudaFree(d_data_);
		    d_data_=nullptr;
		}
	}


};

int main(int argc, char const *argv[])
{
	device_tensor1<float,3> test ;
	/* code */
	return 0;
}