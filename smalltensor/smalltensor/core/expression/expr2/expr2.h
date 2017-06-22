#ifndef EXPR2_H_
#define EXPR2_H_
#include "../../../utils/__utils.h"
using namespace __small_tensor;

template < typename __tensor_type, typename __data_type, char __i , char __j>
class Expr2
{
	// typedef Expr2<__tensor_type, __data_type, __i, __j> expr2;
	typedef __data_type   value_type;
public:
	__tensor_type *p_tensor; 

public:
	Expr2 (__tensor_type & rhs_): p_tensor(&rhs_) {}
	Expr2(Expr2 const& rhs_): p_tensor(rhs_.p_tensor){}
	// Expr2& operator=(Expr2 const& rhs_){p_tensor=rhs_.p_tensor; cout<<"Expr2 copy assignment operator is called \n"; }
	Expr2(Expr2 && rhs_): p_tensor(std::move(rhs_.p_tensor)){}
	// Expr2& operator=(Expr2 && rhs_){p_tensor=std::move(rhs_.p_tensor); cout<<"Expr2 move assignment operator is called \n"; }
   
	inline value_type operator()(dimension_type d1_, dimension_type d2_) const
	{
		ASSERT_MSG(d1_ < get_dim1() && d2_ < get_dim2(), "Expr2 index out of bounds, rvalue. ") ;
		return (*p_tensor)(d1_, d2_) ; 
	}

	inline value_type& operator()(dimension_type d1_, dimension_type d2_)
	{
		ASSERT_MSG(d1_ < get_dim1() && d2_ < get_dim2(), "Expr2 index out of bounds, lvalue. ") ;
		return (*p_tensor)(d1_, d2_) ; 
	}

	inline dimension_type get_dim1() const {return p_tensor->get_dim1();}
	inline dimension_type get_dim2() const {return p_tensor->get_dim2();}



	inline Expr2 const&
	operator=(Expr2 const& rhs_);
	
	template < typename rhs_tensor_t, typename rhs_v_type>
	inline Expr2 const&
	operator=(Expr2<rhs_tensor_t,rhs_v_type,__i,__j> const& rhs_);

};

#endif