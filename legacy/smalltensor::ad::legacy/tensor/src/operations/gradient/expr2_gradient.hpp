#pragma once


template <typename val_type, std::size_t d1, std::size_t d2, 
          char i, char j>
inline expr2<val_type,d1,d2,i,j> operator/ (
       expr1<val_type,d1,i> const& Li_,
       expr1<val_type,d2,j> const& Rj_){
    typedef expr2<val_type,d1,d2,i,j> ret_type;
    ret_type ret_ij;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        // ret_ij(N1,N2) = val_type(*(Rj_(0)._graph), 0.) ;
        ret_ij(N1,N2) = val_type(*(Rj_(0)._graph),
                            Rj_(0)._graph->get_derivative( Li_(N1) , Rj_(N2) ) ); 
      }
    }
    return ret_ij;
}



