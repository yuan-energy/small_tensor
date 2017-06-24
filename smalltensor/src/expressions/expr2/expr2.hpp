#ifndef EXPR2_H_
#define EXPR2_H_

#include "../../tensors/tensor2.hpp"
template <typename __dat_t, std::size_t __d1, std::size_t __d2> class tensor2;
template<typename __dat_t, std::size_t __d1, std::size_t __d2, char __i, char __j>
class expr2: public tensor2<__dat_t, __d1, __d2>
{
public:
    typedef tensor2<__dat_t, __d1, __d2> _tensor2;
    expr2()=delete;
    expr2(expr2 const& rhs_)=delete;
    expr2& operator=(expr2 const& rhs_){
    	memcpy(_tensor2::_data, rhs_._tensor2::_data, __d1*__d2);
    	return (*this);
    }
    expr2 operator=(expr2&& rhs_) noexcept{
    	_tensor2::_data = std::move(rhs_._tensor2::_data);
    	return (*this);
    }
};





#endif
