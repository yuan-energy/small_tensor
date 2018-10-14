#pragma once

namespace smalltensor{
    

template <typename val_type, typename scalar_type, std::size_t d1, std::size_t d2, std::size_t d3, char i, char j, char k>
ST_ALWAYS_INLINE expr3<val_type,d1,d2,d3,i,j,k> operator/(
       expr3<val_type,d1,d2,d3,i,j,k> const& Lijk_, 
       scalar_type                    const& scalar_){
    typedef expr3<val_type,d1,d2,d3,i,j,k> ret_type;
    ret_type ret_ijk;
    for (std::size_t n1 = 0; n1 < d1; ++n1){
        for (std::size_t n2 = 0; n2 < d2; ++n2){
            for (std::size_t n3 = 0; n3 < d3; ++n3)
            {
                ret_ijk(n1,n2,n3) = Lijk_(n1,n2,n3) / scalar_;
            }
        }
    }
    return ret_ijk;
}



}
