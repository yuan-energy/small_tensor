#pragma once


// template <typename val_type, std::size_t d1, std::size_t d2, 
//           char i, char j>
// inline expr2<val_type,d1,d2,i,j> operator/ (
//        expr1<val_type,d1,i> const& Li_,
//        expr1<val_type,d2,j> const& Rj_){
//     typedef expr2<val_type,d1,d2,i,j> ret_type;
//     ret_type ret_ij;
//     for (std::size_t N1 = 0; N1 < d1; ++N1){
//       for (std::size_t N2 = 0; N2 < d2; ++N2){
//         // ret_ij(N1,N2) = val_type(*(Rj_(0)._graph), 0.) ;
//         ret_ij(N1,N2) = val_type(*(Rj_(0)._graph),
//                             Rj_(0)._graph->get_derivative( Li_(N1) , Rj_(N2) ) ); 
//       }
//     }
//     return ret_ij;
// }




template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i, char j, char k, char l>
inline expr4<val_type,d1,d2,d3,d4,i,j,k,l> operator/(
       expr2<val_type,d1,d2,i,j> const& Lij_, 
       expr2<val_type,d3,d4,k,l> const& Rkl_) {
    typedef expr4<val_type,d1,d2,d3,d4,i,j,k,l> ret_type;
    ret_type ret_ijkl;
    for (std::size_t N1 = 0; N1 < d1; ++N1){
      for (std::size_t N2 = 0; N2 < d2; ++N2){
        for (std::size_t N3 = 0; N3 < d3; ++N3){
          for (std::size_t N4 = 0; N4 < d4; ++N4){
            ret_ijkl(N1,N2,N3,N4) = val_type(*(Rkl_(0,0)._graph),
                            Rkl_(0,0)._graph->get_derivative(Lij_(N1,N2), Rkl_(N3,N4)));
          }
        }
      }
    }
    return ret_ijkl;
}
