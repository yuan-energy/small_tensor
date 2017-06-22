#ifndef TENSOR2_H_
#define TENSOR2_H_

// template < typename tensor_order2, typename __data_type, char i>  class Expr1;
// template < typename tensor_order2, typename __data_type, char i, char j> class Expr2;
#include "../base/xsmm_base.h"
#include "../expression/expr2/expr2s.h"
#include "../expression/index_basic.h"
#include <string>
#include <iostream>
using namespace __small_tensor;
template <typename __data_type> class tensor2;

template <typename __data_type>
class tensor2: public xsmm_base< __data_type, 2 >
{
    typedef __data_type   value_type;
    typedef xsmm_base< __data_type, 2 > base2;
public:

    tensor2():
    base2()
    {
    }

    tensor2 (tensor2 const& rhs_):
    base2(rhs_)
    {
    }

    tensor2& operator=(tensor2 const& rhs_)
    {
        cout<<"tensor2 copy assignment operator is called." <<endl;
        base2::operator=(rhs_); 
        return *this;
    }

    tensor2 (tensor2&& rhs_):
    base2(std::move(rhs_))
    {
    }

    tensor2& operator=(tensor2&& rhs_)
    {
        cout<<"tensor2 move assignment operator is called." <<endl;
        base2::operator=(std::move(rhs_)); 
        return *this;
    }

    tensor2(dimension_type d1_, dimension_type d2_)
    :base2(d1_, d2_)
    {
        for (dimension_type i = 0; i < get_dim1(); i++)
            for (dimension_type j = 0; j < get_dim2(); j++){
                (*this)(i, j) = (value_type)(0.) ;
            }
    }

    tensor2(dimension_type d1_, dimension_type d2_, __data_type val_)
    :base2(d1_, d2_)
    {
        for (dimension_type i = 0; i < get_dim1(); i++)
            for (dimension_type j = 0; j < get_dim2(); j++){
                 (*this)(i, j) = (value_type)(val_);
            }
    }

    tensor2(dimension_type d1_, dimension_type d2_, std::string val_)
    :base2(d1_, d2_)
    {
        if(val_ == "identity"){
            for (dimension_type i = 0; i < get_dim1(); i++){
                (*this)(i, i) = (value_type)(1.);
            }
        }else{
            std:cerr << "tensor2 -- unknown string "<< val_<<endl;
        }
    }


    template <class __rhs_scale_type>
    inline tensor2 & operator=(__rhs_scale_type const& rhs_)
    {
        for ( dimension_type i = 0; i < get_dim1(); i++)
        {
            (*this)(i, i) = (value_type)rhs_;
        }
        return *this;
    }

    inline dimension_type get_dim1(){return base2::_dimension[0];}
    inline dimension_type get_dim2(){return base2::_dimension[1];}
    inline value_type& operator() (dimension_type d1_, dimension_type d2_){return base2::operator()(d1_,d2_);}
    inline value_type operator() (dimension_type d1_, dimension_type d2_)const{return base2::operator()(d1_,d2_);}

    template <char i, char j>
    inline Expr2<tensor2, value_type, i, j> operator()(Index<i> i_, Index<j> j_){
        return Expr2<tensor2, value_type, i, j>(*this) ;
    }

    template <char i, char j>
    inline Expr2<tensor2, value_type, i, j> operator()(Index<i> i_, Index<j> j_) const{
        return Expr2<tensor2, value_type, i, j>(*this) ;
    }
};











#endif /*TENSOR2_H_*/
