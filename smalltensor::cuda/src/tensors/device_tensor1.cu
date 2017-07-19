#pragma once
#include "../utils/__utils.h"
// #include "../expressions/expressions.h"

using namespace std;
template <typename _d_dat_t, std::size_t _d_d1>
class device_tensor1
{
public:
	_d_dat_t* __restrict__ d_data_;

	device_tensor1()
	// : d_data_{new _d_dat_t[_d_d1]}
	{
		// cudaMalloc((void**) &(this.d_data_), sizeof(_d_dat_t)*_d_d1);
	}
	device_tensor1(device_tensor1 const& d_rhs_)
	// : d_data_{new _d_dat_t[_d_d1]}
	{
		cudaMalloc((void**) &d_data_, sizeof(_d_dat_t)*_d_d1);
		DEBUG_MSG("device_tensor1 copy constructor is called");
		// std::memcpy(d_data_, rhs_.d_data_, sizeof(d_data_)*_d_d1);
		cudaMemcpy(d_data_, d_rhs_.d_data_ , sizeof(d_data_)*_d_d1, cudaMemcpyDeviceToDevice);
	}
	device_tensor1& operator=(device_tensor1 const& d_rhs_){
		DEBUG_MSG("device_tensor1 copy assignment operator is called");
		if(this != &d_rhs_){
	        // std::memcpy(d_data_, rhs_.d_data_, sizeof(d_data_)*_d_d1);		
			cudaMemcpy(d_data_, d_rhs_.d_data_ , sizeof(d_data_)*_d_d1, cudaMemcpyDeviceToDevice);
		}
		return *this;
	}
    device_tensor1(device_tensor1&& d_rhs_) noexcept    
    // : d_data_{new _d_dat_t[_d_d1]}
    {
		cudaMalloc((void**) &d_data_, sizeof(_d_dat_t)*_d_d1);
    	std::swap(d_data_, d_rhs_.d_data_);
    	DEBUG_MSG("device_tensor1 move constructor is called");

    }
    device_tensor1& operator=(device_tensor1&& d_rhs_) noexcept{
    	DEBUG_MSG("device_tensor1 move assignment operator is called");
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

	// __global__ inline _d_dat_t& operator()(std::size_t n1_){
	// 	ASSERT_MSG(n1_< _d_d1 , "device_tensor1() index out of bounds in lvalue. ");
	// 	return d_data_[ n1_ ];
	// }
	// __global__ inline _d_dat_t operator()(std::size_t n1_)const{
	// 	ASSERT_MSG(n1_< _d_d1 , "device_tensor1() index out of bounds in rvalue. ");
	// 	return d_data_[ n1_ ];
	// }
	// template <char i>
	// inline expr1<_d_dat_t, _d_d1, i>& operator()(Index<i> i_){
 //        return static_cast<expr1<_d_dat_t, _d_d1, i>&>(*this);
	// }
	// template <char i>
	// inline expr1<_d_dat_t, _d_d1, i> const& operator()(Index<i> i_)const{
 //        return static_cast<expr1<_d_dat_t, _d_d1, i>const&>(*this);
	// }
	// inline device_tensor1& operator*=(_d_dat_t const& scalar_){
	// 	for (std::size_t n1 = 0; n1 < _d_d1; ++n1){
	// 		(*this)(n1) *= scalar_ ;
	// 	}
	// 	return (*this);
	// }

};

