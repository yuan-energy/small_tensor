#ifndef TENSOR1_HPP_
#define TENSOR1_HPP_
#include "../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1>
class tensor1
{
public:
	__dat_t* __restrict__ _data;

	tensor1(): _data{new __dat_t[__d1]}{}
	tensor1(tensor1 const& rhs_): _data{new __dat_t[__d1]}{
		DEBUG_MSG("tensor1 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(_data)*__d1);
	}
	tensor1& operator=(tensor1 const& rhs_){
		DEBUG_MSG("tensor1 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(_data)*__d1);		
		}
		return *this;
	}
    tensor1(tensor1&& rhs_) noexcept    
    : _data{new __dat_t[__d1]}
    {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor1 move constructor is called");

    }
    tensor1& operator=(tensor1&& rhs_) noexcept{
    	DEBUG_MSG("tensor1 move assignment operator is called");
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	return *this;
    }
	~tensor1(){
		if (_data!=nullptr){
		    delete[] _data;
		    _data=nullptr;
		}
	}

	inline __dat_t& operator()(std::size_t n1_){
		ASSERT_MSG(n1_< __d1 , "tensor1() index out of bounds in lvalue. ");
		return _data[ n1_ ];
	}
	inline __dat_t operator()(std::size_t n1_)const{
		ASSERT_MSG(n1_< __d1 , "tensor1() index out of bounds in rvalue. ");
		return _data[ n1_ ];
	}
	template <char i>
	inline expr1<__dat_t, __d1, i>& operator()(Index<i> i_){
        return static_cast<expr1<__dat_t, __d1, i>&>(*this);
	}
	template <char i>
	inline expr1<__dat_t, __d1, i> const& operator()(Index<i> i_)const{
        return static_cast<expr1<__dat_t, __d1, i>const&>(*this);
	}
	inline tensor1& operator*=(__dat_t const& scalar_){
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			(*this)(n1) *= scalar_ ;
		}
		return (*this);
	}
};

#endif