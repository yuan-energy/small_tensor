#pragma once

template <typename dat_t, std::size_t d1, std::size_t d2, std::size_t d3> class tensor3;
template<typename dat_t, std::size_t d1, std::size_t d2, std::size_t d3, char i1, char i2, char i3>
class expr3: public tensor3<dat_t, d1, d2, d3>
{
public:
    typedef tensor3<dat_t, d1, d2, d3> _tensor3;
    expr3():_tensor3(){} ;
    expr3(expr3 const& rhs_):_tensor3(rhs_){} ;
    expr3& operator=(expr3 const& rhs_){
    	_tensor3::operator=(rhs_);
    	return (*this);
    }
    expr3 operator=(expr3&& rhs_) noexcept{
    	_tensor3::operator=(std::move(rhs_));
    	return (*this);
    }

    ST_ALWAYS_INLINE expr3<dat_t,d1,d2,d3,i1,i2,i3>&
    operator=(expr3<dat_t,d1,d3,d2,i1,i3,i2> const& RHS_);

    ST_ALWAYS_INLINE expr3<dat_t,d1,d2,d3,i1,i2,i3>&
    operator=(expr3<dat_t,d2,d1,d3,i2,i1,i3> const& RHS_);

    ST_ALWAYS_INLINE expr3<dat_t,d1,d2,d3,i1,i2,i3>&
    operator=(expr3<dat_t,d2,d3,d1,i2,i3,i1> const& RHS_);

    ST_ALWAYS_INLINE expr3<dat_t,d1,d2,d3,i1,i2,i3>&
    operator=(expr3<dat_t,d3,d1,d2,i3,i1,i2> const& RHS_);

    ST_ALWAYS_INLINE expr3<dat_t,d1,d2,d3,i1,i2,i3>&
    operator=(expr3<dat_t,d3,d2,d1,i3,i2,i1> const& RHS_);

    /*Done!*/
};

#include "expr3_equal.hpp"



