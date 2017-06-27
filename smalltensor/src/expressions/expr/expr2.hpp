#ifndef EXPR2_HPP_
#define EXPR2_HPP_

template <typename __dat_t, std::size_t __d1, std::size_t __d2> class tensor2;
template<typename __dat_t, std::size_t __d1, std::size_t __d2, char __i, char __j>
class expr2: public tensor2<__dat_t, __d1, __d2>
{
public:
    typedef tensor2<__dat_t, __d1, __d2> _tensor2;
    expr2():_tensor2(){};
    expr2(expr2 const& rhs_):_tensor2(rhs_){};
    expr2& operator=(expr2 const& rhs_){
        _tensor2::operator=(rhs_);
    	return (*this);
    }
    expr2 operator=(expr2&& rhs_) noexcept{
        _tensor2::operator=(std::move(rhs_));
    	return (*this);
    }
};





#endif
