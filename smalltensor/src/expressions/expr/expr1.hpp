#ifndef EXPR1_HPP_
#define EXPR1_HPP_

template <typename __dat_t, std::size_t __d1> class tensor1;
template<typename __dat_t, std::size_t __d1, char __i>
class expr1: public tensor1<__dat_t, __d1>
{
public:
    typedef tensor1<__dat_t, __d1> _tensor1;
    expr1()=delete;
    expr1(expr1 const& rhs_)=delete;
    expr1& operator=(expr1 const& rhs_){
    	memcpy(_tensor1::_data, rhs_._tensor1::_data, __d1);
    	return (*this);
    }
    expr1 operator=(expr1&& rhs_) noexcept{
    	_tensor1::_data = std::move(rhs_._tensor1::_data);
    	return (*this);
    }
};





#endif
