#ifndef XSMM_BASE_H_
#define XSMM_BASE_H_

#include <cstdio>  /* printf */
#include <iostream>  /* cout */
#include <cstdint> /* uint_fast8_t, uint_fast16_t, uint_fast32_t */
#include <cstdarg>  /* ..., va_list, va_start, va_arg, va_end */
#include <cassert> /* assert */
#include <memory.h>
// #include "../../../third_party/libxsmm/include/libxsmm_source.h"
#include "../../utils/__utils.h"
// #include "../expression/index_basic.h"
using namespace std;
using namespace __small_tensor;


template <typename __data_type, uint_fast8_t __order>
class xsmm_base
{
public:
    typedef __data_type   value_type;


    // friend class index_basic;

    counter_type _data_count;
    value_type* __restrict__ _data;
    dimension_type _dimension[__order];
    stride_type _stride[__order];

    xsmm_base()
    {
    	// std::cout<<"default constructor is used!"<<std::endl;
        _data = nullptr;
        _data_count = 0;
        for (order_type i = 0; i < __order; ++i)
        {
            _dimension[i] = 0;
            _stride[i] = 0;
        }
    }

    xsmm_base(xsmm_base const& rhs_):
    _data_count {rhs_._data_count} ,
    _data {new value_type[rhs_._data_count]}
    {
    	// std::cout<<"copy constructor is used!"<<std::endl;
    	copy_vector<value_type>(_data, rhs_._data, _data_count);
    	memcpy(_dimension, rhs_._dimension, sizeof(rhs_._dimension));
    	memcpy(_stride, rhs_._stride, sizeof(rhs_._stride));
    }

    xsmm_base<value_type, __order>& operator=(xsmm_base<value_type, __order> const& rhs_)
    {
        // std::cout<<"copy assignment operator is used!"<<std::endl;
        if (this != &rhs_)
        {
        	clear();
            _data_count = rhs_._data_count ; 
            _data = new value_type[rhs_._data_count];
            copy_vector<value_type>(_data, rhs_._data, _data_count);
            memcpy(_dimension, rhs_._dimension, sizeof(rhs_._dimension));
            memcpy(_stride, rhs_._stride, sizeof(rhs_._stride));
        }

        return *this;
    }

    template< typename __rhs_type>
    xsmm_base<value_type, __order>& operator=(xsmm_base<__rhs_type, __order> const& rhs_)
    {
        if (this != &rhs_)
        {
        	clear();
            _data_count = rhs_._data_count ; 
            _data = new value_type[rhs_._data_count];
            copy_vector<value_type, __rhs_type>(_data, rhs_._data, _data_count);
            memcpy(_dimension, rhs_._dimension, sizeof(rhs_._dimension));
            memcpy(_stride, rhs_._stride, sizeof(rhs_._stride));
        }
        return *this;
    }

    xsmm_base(xsmm_base && rhs_) noexcept:
    _data_count{std::move(rhs_._data_count)},
    _data{std::move(rhs_._data)}
    {
        // std::cout<<"move constructor is used!"<<std::endl;
        memcpy(_dimension, rhs_._dimension, sizeof(rhs_._dimension));
        memcpy(_stride, rhs_._stride, sizeof(rhs_._stride));
        rhs_._data = nullptr ;
    }

    xsmm_base& operator=(xsmm_base && rhs_) noexcept
    {
        // std::cout<<"move assignment operator is used!"<<std::endl;
        if(this != &rhs_)
        {
            clear();
            _data_count = std::move(rhs_._data_count) ; 
            _data = std::move(rhs_._data);
            memcpy(_dimension, rhs_._dimension, sizeof(rhs_._dimension));
            memcpy(_stride, rhs_._stride, sizeof(rhs_._stride));
            rhs_._data  = nullptr ;
        }
        return *this;
    }

    void clear()
    {
        if (_data)
        {
            delete[] _data;
            _data=nullptr;
        }
        _data_count = 0 ; 
        for (order_type i = 0; i < __order; ++i)
        {
            _dimension[i] = 0;
            _stride[i] = 0;
        }
    }

    ~xsmm_base()
    {
    	// std::cout<<"destructor is used!"<<std::endl;
        clear();
    }

    xsmm_base(dimension_type dimension_)
    :_data_count{dimension_},
    _dimension{dimension_}
    {
        init_data();
    }

    xsmm_base(dimension_type dimension1_, dimension_type dimension2_)
    :_data_count{dimension1_*dimension2_}, 
    _dimension{dimension1_, dimension2_}
    {
        init_data();
    }

    xsmm_base(dimension_type dimension1_, dimension_type dimension2_, dimension_type dimension3_)
    :_data_count{dimension1_*dimension2_*dimension3_}, 
    _dimension{dimension1_, dimension2_, dimension3_}
    {
        init_data();
    }
    xsmm_base(dimension_type dimension1_, dimension_type dimension2_, dimension_type dimension3_, dimension_type dimension4_)
    :_data_count{dimension1_*dimension2_*dimension3_*dimension4_},
    _dimension{dimension1_, dimension2_, dimension3_, dimension4_}
    {
        init_data();
    }

    inline void init_data()
    {
        if(_data_count == 0){
            _data = nullptr;
        }else{
            // struct raii{
            //     value_type *raw;
            //     raii(counter_type raw_size): raw(new value_type[raw_size]){}
            //     ~raii(){delete[] raw;}
            // } buffer(_data_count);
            _data = new value_type[_data_count];
            // _data = LIBXSMM_ALIGN(_data, LIBXSMM_ALIGNMENT);
        }

        _stride[0] = 1;
        for (order_type i = 1; i < __order; i++)
        {
            _stride[i] = _stride[i - 1] * _dimension[ __order - i];
        }
    };



    /*va_arg do not accept cstdint */
    // void set_dimension(dimension_type n_dim, ...)
    // {
    //     va_list l;
    //     va_start(l, n_dim);
    //     _data_count = 1;
    //     for (dimension_type i = 0; i < n_dim; ++i)
    //     {
    //         _dimension[i] = va_arg(l, dimension_type);
    //         _data_count *= _dimension[i];
    //     }
    //     va_end(l);

    //     init_data();
    // }


    // value_type operator[](counter_type n_)
    // {
    //     ASSERT_MSG(n_ < _data_count, "tensor[] index out of bounds. " ) ; 
    //     return _data[n_];
    // }

    inline value_type operator()(dimension_type d1_)const{
        ASSERT_MSG(d1_ < _dimension[0], "small_tensor() index out of bounds, rvalue. ") ;
        return _data[d1_];
    }
    inline value_type& operator()(dimension_type d1_){
        ASSERT_MSG(d1_ < _dimension[0], "small_tensor() index out of bounds, lvalue. ") ;
        return _data[d1_];
    }
    
    inline value_type operator()(dimension_type d1_, dimension_type d2_)const{
        ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1], "small_tensor() index out of bounds, rvalue. ") ;
        return _data[d1_ * _stride[1] + d2_ * _stride[0]];
    }
    inline value_type& operator()(dimension_type d1_, dimension_type d2_){
        // std::cout<<"d1_= " << d1_<<endl;
        // std::cout<<"d2_= " << d2_<<endl;
        // std::cout<<"_dimension[0]= " << _dimension[0]<<endl;
        // std::cout<<"_dimension[1]= " << _dimension[1]<<endl;
        ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1], "small_tensor() index out of bounds, lvalue. ") ;
        return _data[d1_ * _stride[1] + d2_ * _stride[0]];
    }

    inline value_type operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_)const{
        ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2], "small_tensor() index out of bounds, rvalue. ") ;
        return _data[d1_ * _stride[2] + d2_ * _stride[1] + d3_ * _stride[0]];
    }
    inline value_type& operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_){
        ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2], "small_tensor() index out of bounds, lvalue. ") ;
        return _data[d1_ * _stride[2] + d2_ * _stride[1] + d3_ * _stride[0]];
    }

    inline value_type operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_, dimension_type d4_)const{
        ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2] && d4_ < _dimension[3], "small_tensor() index out of bounds, rvalue. ") ;
        return _data[d1_ * _stride[3] + d2_ * _stride[2] + d3_ * _stride[1] + d4_ * _stride[0]];
    }

    inline value_type& operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_, dimension_type d4_){
        ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2] && d4_ < _dimension[3], "small_tensor() index out of bounds, lvalue. ") ;
        return _data[d1_ * _stride[3] + d2_ * _stride[2] + d3_ * _stride[1] + d4_ * _stride[0]];
    }



};







#endif /*XSMM_BASE_H_*/
