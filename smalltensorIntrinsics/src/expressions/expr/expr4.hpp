#pragma once

template <typename dat_t, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4> class tensor4;

template<typename dat_t, 
         std::size_t d1, std::size_t d2, 
         std::size_t d3, std::size_t d4, 
         char i1, char i2, char i3, char i4>
class expr4: public tensor4<dat_t, d1, d2, d3, d4>
{
public:
    typedef tensor4<dat_t, d1, d2, d3, d4> _tensor4;
    expr4():_tensor4(){} ;
    expr4(expr4 const& rhs_):_tensor4(rhs_){} ;
    expr4& operator=(expr4 const& rhs_){
    	_tensor4::operator=(rhs_);
    	return (*this);
    }
    expr4 operator=(expr4&& rhs_) noexcept{
    	_tensor4::operator=(std::move(rhs_));
    	return (*this);
    }
    
 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d1,d2,d4,d3,i1,i2,i4,i3> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d1,d3,d2,d4,i1,i3,i2,i4> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d1,d3,d4,d2,i1,i3,i4,i2> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d1,d4,d2,d3,i1,i4,i2,i3> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d1,d4,d3,d2,i1,i4,i3,i2> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d2,d1,d3,d4,i2,i1,i3,i4> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d2,d1,d4,d3,i2,i1,i4,i3> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d2,d3,d1,d4,i2,i3,i1,i4> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d2,d3,d4,d1,i2,i3,i4,i1> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d2,d4,d1,d3,i2,i4,i1,i3> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d2,d4,d3,d1,i2,i4,i3,i1> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d3,d1,d2,d4,i3,i1,i2,i4> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d3,d1,d4,d2,i3,i1,i4,i2> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d3,d2,d1,d4,i3,i2,i1,i4> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d3,d2,d4,d1,i3,i2,i4,i1> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d3,d4,d1,d2,i3,i4,i1,i2> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d3,d4,d2,d1,i3,i4,i2,i1> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d4,d1,d2,d3,i4,i1,i2,i3> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d4,d1,d3,d2,i4,i1,i3,i2> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d4,d2,d1,d3,i4,i2,i1,i3> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d4,d2,d3,d1,i4,i2,i3,i1> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d4,d3,d1,d2,i4,i3,i1,i2> const& RHS_);

 ST_ALWAYS_INLINE expr4<dat_t,d1,d2,d3,d4,i1,i2,i3,i4>&
 operator=(expr4<dat_t,d4,d3,d2,d1,i4,i3,i2,i1> const& RHS_);

 /*Done!*/
};



#include "expr4_equal.hpp"

