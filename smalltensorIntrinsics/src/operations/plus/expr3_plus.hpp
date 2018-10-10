#pragma once


template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, 
          char i1, char i2, char i3>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i1,i2,i3> operator+(
       expr3<val_type,d1,d2,d3,i1,i2,i3> const& Rijk_){
    typedef expr3<val_type,d1,d2,d3,i1,i2,i3> ret_type;
    ret_type ret_ijk;
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        for (std::size_t n2 = 0; n2 < d2; ++n2){
            for (std::size_t n3 = 0; n3 < d3; ++n3)
            {
                ret_ijk(n1,n2,n3) = + Rijk_(n1,n2,n3);
            }
        }
    }
    return ret_ijk;
}




