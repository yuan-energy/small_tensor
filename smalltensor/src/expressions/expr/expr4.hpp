#ifndef EXPR4_HPP_
#define EXPR4_HPP_

template <typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3, std::size_t __d4> class tensor4;
template<typename __dat_t, std::size_t __d1, std::size_t __d2, std::size_t __d3, std::size_t __d4, char __i, char __j, char __k, char __l>
class expr4: public tensor4<__dat_t, __d1, __d2, __d3, __d4>
{
public:
    typedef tensor4<__dat_t, __d1, __d2, __d3, __d4> _tensor4;
    expr4()=delete;
    expr4(expr4 const& rhs_)=delete;
    expr4& operator=(expr4 const& rhs_){
    	memcpy(_tensor4::_data, rhs_._tensor4::_data, __d1*__d2*__d3*__d4);
    	return (*this);
    }
    expr4 operator=(expr4&& rhs_) noexcept{
    	_tensor4::_data = std::move(rhs_._tensor4::_data);
    	return (*this);
    }
};





#endif
