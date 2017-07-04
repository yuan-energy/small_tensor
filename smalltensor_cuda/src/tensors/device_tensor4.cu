#ifndef device_TENSOR4_HPP_
#define device_TENSOR4_HPP_
#include "../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename _d_dat_t, std::size_t _d_d1, std::size_t _d_d2, std::size_t _d_d3, std::size_t _d_d4>
class device_tensor4
{
public:
	_d_dat_t* __restrict__ d_data_;

	device_tensor4()
	// : d_data_{new _d_dat_t[_d_d1*_d_d2]}
	{

	}
	device_tensor4(device_tensor4 const& d_rhs_)
	// : d_data_{new _d_dat_t[_d_d1*_d_d2]}
	{
		cudaMalloc((void**) &d_data_, sizeof(_d_dat_t)*_d_d1*_d_d2*_d_d3*_d_d4);
		DEBUG_MSG("device_tensor4 copy constructor is called");
		// std::memcpy(d_data_, d_rhs_.d_data_, sizeof(d_data_)*_d_d1*_d_d2*_d_d3*_d_d4);
		cudaMemcpy(d_data_, d_rhs_.d_data_ , sizeof(d_data_)*_d_d1*_d_d2*_d_d3*_d_d4, cudaMemcpyDeviceToDevice);
	}
	device_tensor4& operator=(device_tensor4 const& d_rhs_){

		DEBUG_MSG("device_tensor4 copy assignment operator is called");
		if(this != &d_rhs_){
			cudaMemcpy(d_data_, d_rhs_.d_data_ , sizeof(d_data_)*_d_d1*_d_d2*_d_d3*_d_d4, cudaMemcpyDeviceToDevice);
		}
		return *this;
	}

    device_tensor4(device_tensor4&& d_rhs_) noexcept
    // : d_data_{new _d_dat_t[_d_d1*_d_d2*_d_d3*_d_d4]}
    {
    	cudaMalloc((void**) &d_data_, sizeof(_d_dat_t)*_d_d1*_d_d2*_d_d3*_d_d4);
    	std::swap(d_data_, d_rhs_.d_data_);
    	DEBUG_MSG("device_tensor4 move constructor is called");
    }
    device_tensor4& operator=(device_tensor4&& d_rhs_) noexcept{
    	if(this != &d_rhs_){
    		std::swap(d_data_, d_rhs_.d_data_);
    	}
    	DEBUG_MSG("device_tensor4 move assignment operator is called");
    	return *this;
    }
	~device_tensor4(){
		if (d_data_!=nullptr){
		    cudaFree(d_data_);
		    d_data_=nullptr;
		}
	}
	// device_tensor4(std::string const& other_):d_data_{new _d_dat_t[_d_d1*_d_d2*_d_d3]}{
	//     if (other_ == "identity")
	//     {
	//         ASSERT_MSG(_d_d1==_d_d2*_d_d3, "ERROR:device_tensor4 has different dimensions, cannot be identity.");
	//         for (std::size_t n1 = 0; n1 < _d_d1; ++n1)
	//         {
	//             (*this)(n1,n1) = 1;
	//         }
	//     }
	// }
	// inline _d_dat_t& operator()(std::size_t n1_, std::size_t n2_){
	// 	ASSERT_MSG(n1_< _d_d1 && n2_ < _d_d2*_d_d3, "device_tensor4() index out of bounds in lvalue. ");
	// 	return d_data_[ n1_ * _d_d2*_d_d3 + n2_];
	// }
	// inline _d_dat_t operator()(std::size_t n1_, std::size_t n2_)const{
	// 	ASSERT_MSG(n1_< _d_d1 && n2_ < _d_d2*_d_d3, "device_tensor4() index out of bounds in rvalue. ");
	// 	return d_data_[ n1_ * _d_d2*_d_d3 + n2_];
	// }
	// template <char i, char j>
	// inline expr2<_d_dat_t, _d_d1, _d_d2*_d_d3, i, j>& operator()(Index<i> i_, Index<j> j_){
 //        return static_cast<expr2<_d_dat_t, _d_d1, _d_d2*_d_d3, i, j>&>(*this);
	// }

	// template <char i, char j>
	// inline expr2<_d_dat_t, _d_d1, _d_d2, i, j> const& operator()(Index<i> i_, Index<j> j_)const{
 //        return static_cast<expr2<_d_dat_t, _d_d1, _d_d2, i, j>const&>(*this);
	// }

	// template <char i>
	// inline _d_dat_t operator()(Index<i> i_, Index<i/*same*/> j_){
	// 	ASSERT_MSG(_d_d1 == _d_d2, "Dimension size should be equal for dummy indices. ");
	// 	_d_dat_t ret=0;
	// 	for (std::size_t n1 = 0; n1 < _d_d1; ++n1){
	// 		ret += (*this)(n1,n1);
	// 	}
 //        return ret;
	// }

	// inline device_tensor4& operator*=(_d_dat_t const& scalar_){
	// 	for (std::size_t n1 = 0; n1 < _d_d1; ++n1){
	// 		for (std::size_t n2 = 0; n2 < _d_d2; ++n2){
	// 			(*this)(n1,n2) *= scalar_ ;
	// 		}
	// 	}
	// 	return (*this);
	// }
};

#endif