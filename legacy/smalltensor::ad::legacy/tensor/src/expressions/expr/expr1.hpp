#pragma once

template <typename __dat_t, std::size_t __d1> class tensor1;
template<typename __dat_t, std::size_t __d1, char __i>
class expr1: public tensor1<__dat_t, __d1>
{
public:
    typedef tensor1<__dat_t, __d1> _tensor1;
    expr1():_tensor1(){}
    expr1(expr1 const& rhs_):_tensor1(rhs_){} ;
    expr1& operator=(expr1 const& rhs_){
    	_tensor1::operator=(rhs_);
    	return (*this);
    }
    expr1 operator=(expr1&& rhs_) noexcept{
    	_tensor1::operator=(std::move(rhs_));
    	return (*this);
    }
};





