#pragma once

namespace smalltensor{

template<typename expr2,
         typename dat_type, 
         char i, char j>
class ij_to_ij
{
public:
  expr2 origin;
  expr2(expr2 const& old_):origin(old_){}

  dat_type& operator()(std::size_t n1, std::size_t n2){
  	return origin(n1,n2)
  }
  dat_type operator()(std::size_t n1, std::size_t n2) const{
  	return origin(n1,n2)
  }
};



template<typename expr2,
         typename dat_type, 
         char i, char j>
class ij_to_ji
{
public:
  expr2 origin;
  expr2(expr2 const& old_):origin(old_){}

  dat_type& operator()(std::size_t n1, std::size_t n2){
  	return origin(n2,n1)
  }
  dat_type operator()(std::size_t n1, std::size_t n2) const{
  	return origin(n2,n1)
  }
};

} // namespace smalltensor{
  