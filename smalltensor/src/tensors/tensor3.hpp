#ifndef TENSOR3_HPP_
#define TENSOR3_HPP_
#include "../utils/__utils.h"
#include "../expressions/expressions.h"

using namespace std;
template <typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3>
class tensor3
{
public:
	__dat_t* __restrict__ _data;

	tensor3(): _data{new __dat_t[__d1*__d2*__d3]}{}
	tensor3(tensor3 const& rhs_): _data{new __dat_t[__d1*__d2*__d3]}{
		std::memcpy(_data, rhs_._data, sizeof(_data));
	}
	tensor3& operator=(tensor3 const& rhs_){
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(_data));		
		}
		return *this;
	}
    tensor3(tensor3&& rhs_) noexcept: _data{std::move(rhs_._data)}{}
    tensor3& operator=(tensor3&& rhs_) noexcept{
    	if(this != &rhs_){
    		_data = std::move(rhs_._data);
    	}
    	return *this;
    }
	~tensor3(){
		if (_data!=nullptr){
		    delete[] _data;
		    _data=nullptr;
		}
	}

	inline __dat_t& operator()(std::size_t n1_, std::size_t n2_, std::size_t n3_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_ < __d3, "tensor3() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 *__d3 + n2_ * __d3 + n3_];
	}
	inline __dat_t operator()(std::size_t n1_, std::size_t n2_, std::size_t n3_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2 && n3_ < __d3, "tensor3() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 *__d3 + n2_ * __d3 + n3_];
	}
	template <char i, char j, char k>
	inline expr3<__dat_t, __d1, __d2, __d3, i, j, k>& operator()(Index<i> i_, Index<j> j_, Index<k> k_){
        return static_cast<expr3<__dat_t, __d1, __d2, __d3, i, j, k>&>(*this);
	}
};

#endif