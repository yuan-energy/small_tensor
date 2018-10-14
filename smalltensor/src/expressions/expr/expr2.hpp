#pragma once

namespace smalltensor{
    

template <typename dat_t, std::size_t d1, std::size_t d2> class tensor2;
template<typename dat_t, std::size_t d1, std::size_t d2, char i1, char i2>
class expr2: public tensor2<dat_t, d1, d2>
{
public:
    typedef tensor2<dat_t, d1, d2> _tensor2;
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

    ST_ALWAYS_INLINE expr2<dat_t,d1,d2,i1,i2>& 
    operator=(expr2<dat_t,d2,d1,i2,i1> const& RHS_){
        for (std::size_t n1 = 0; n1 < d1; ++n1){
            for (std::size_t n2 = 0; n2 < d2; ++n2){
                (*this)(n1,n2) = RHS_(n2,n1);
            }
        }
        return (*this);
    }


};





}
