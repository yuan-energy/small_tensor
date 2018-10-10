template <typename val_type, 
          std::size_t d1, std::size_t d2, 
          std::size_t d3, std::size_t d4, 
          char i1, char i2, char i3, char i4>
ST_ALWAYS_INLINE expr4<val_type,d1,d2,d3,d4,i1,i2,i3,i4>& 
expr4<val_type,d1,d2,d3,d4,i1,i2,i3,i4>::operator=(
      expr4<val_type,D1,D2,D3,D4,A,B,C,D>     const& RHS_)
{
	for (std::size_t n1 = 0; n1 < d1; ++n1){
		for (std::size_t n2 = 0; n2 < d2; ++n2){
			for (std::size_t n3 = 0; n3 < d3; ++n3){
			    for (std::size_t n4 = 0; n4 < d4; ++n4){
					(*this)(n1,n2,n3,n4) = RHS_(a,b,c,d);
				}
			}
		}
	}
	return (*this);
}
