#ifndef XSMM_BASE_H_
#define XSMM_BASE_H_

#include <cstdio>  /* printf */
#include <iostream>  /* cout */
#include <cstdint> /* uint_fast8_t, uint_fast16_t */
#include <cstdarg>  /* ..., va_list, va_start, va_arg, va_end */
#include <cassert> /* assert */
#include "../../../third_party/libxsmm/include/libxsmm_source.h"
#include "../../utils/__utils.h"
using namespace std;


template <typename __data_type, uint_fast8_t __order>
class xsmm_base
{
public:
	typedef __data_type   value_type;
	typedef uint_fast16_t dimension_type;
	typedef uint_fast16_t stride_type;
	typedef uint_fast32_t counter_type;

	counter_type _data_count;
	dimension_type _dimension[__order];
	value_type* __restrict__ _data;
	stride_type _stride[__order];

	xsmm_base()
	{
		_data = nullptr;
		_data_count = 0;
		for (int i = 0; i < __order; ++i)
		{
			_dimension[i] = 0;
		}
	}
	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data=nullptr;
		}
		_data_count = 0 ; 
		for (int i = 0; i < __order; ++i)
		{
			_dimension[i] = 0;
		}
	}
	~xsmm_base()
	{
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
			// 	value_type *raw;
			// 	raii(counter_type raw_size): raw(new value_type[raw_size]){}
			// 	~raii(){delete[] raw;}
			// } buffer(_data_count);
			_data = new value_type[_data_count];
			// _data = LIBXSMM_ALIGN(_data, LIBXSMM_ALIGNMENT);
		}

		_stride[0] = 1;
		for (int i = 1; i < __order; i++)
		{
			_stride[i] = _stride[i - 1] * _dimension[ __order - i];
		}
	};

	xsmm_base<value_type, __order>& operator=(xsmm_base<value_type, __order> const& rhs_)
	{
		if( nullptr == rhs_._data )
		{
			this->clear();
		}else{
			if( nullptr == this->_data )
			{
				this->_data = new value_type[rhs_._data_count];
			}else{
				if(this->_data_count != rhs_._data_count)
				{
					this->clear();
					this->_data = new value_type[rhs_._data_count];
				}
			}

			this->_data_count = rhs_._data_count ; 
			copy_vector<uint_fast16_t>(this->_dimension, rhs_._dimension, __order);
			copy_vector<value_type>(this->_data, rhs_._data, this->_data_count);
			copy_vector<int>(this->_stride, rhs_._stride, __order);
		}
		return *this;
	}

	template< typename __rhs_type>
	xsmm_base<value_type, __order>& operator=(xsmm_base<__rhs_type, __order> const& rhs_)
	{
		if( nullptr == rhs_._data )
		{
			this->clear();
		}else{
			if( nullptr == this->_data )
			{
				this->_data = new value_type[rhs_._data_count];
			}else{
				if(this->_data_count != rhs_._data_count)
				{
					this->clear();
					this->_data = new value_type[rhs_._data_count];
				}
			}

			this->_data_count = rhs_._data_count ; 
			copy_vector<uint_fast16_t>(this->_dimension, rhs_._dimension, __order);
			copy_vector<value_type, __rhs_type>(this->_data, rhs_._data, this->_data_count);
			copy_vector<int>(this->_stride, rhs_._stride, __order);
		}
		return *this;
	}


	// void set_dimension(uint_fast16_t n_dim, ...)
	// {
	// 	va_list l;
	// 	va_start(l, n_dim);
	// 	_data_count = 1;
	// 	for (int i = 0; i < n_dim; ++i)
	// 	{
	// 		_dimension[i] = va_arg(l, uint_fast16_t);
	// 		_data_count *= _dimension[i];
	// 	}
	// 	va_end(l);

	// 	init_data();
	// }


	// value_type operator[](counter_type n_)
	// {
	// 	ASSERT_MSG(n_ < _data_count, "tensor[] index out of bounds. " ) ; 
	// 	return _data[n_];
	// }

	inline value_type operator()(dimension_type d1_)const{
		ASSERT_MSG(d1_ < _dimension[0], "small_tensor() index out of bounds. ") ;
		return _data[d1_];
	}
	inline value_type& operator()(dimension_type d1_){
		ASSERT_MSG(d1_ < _dimension[0], "small_tensor() index out of bounds. ") ;
		return _data[d1_];
	}
	
	inline value_type operator()(dimension_type d1_, dimension_type d2_)const{
		ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1], "small_tensor() index out of bounds. ") ;
		return _data[d1_ * _stride[1] + d2_ * _stride[0]];
	}
	inline value_type& operator()(dimension_type d1_, dimension_type d2_){
		ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1], "small_tensor() index out of bounds. ") ;
		return _data[d1_ * _stride[1] + d2_ * _stride[0]];
	}

	inline value_type operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_)const{
		ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2], "small_tensor() index out of bounds. ") ;
		return _data[d1_ * _stride[2] + d2_ * _stride[1] + d3_ * _stride[0]];
	}
	inline value_type& operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_){
		ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2], "small_tensor() index out of bounds. ") ;
		return _data[d1_ * _stride[2] + d2_ * _stride[1] + d3_ * _stride[0]];
	}

	inline value_type operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_, dimension_type d4_)const{
		ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2] && d4_ < _dimension[3], "small_tensor() index out of bounds. ") ;
		return _data[d1_ * _stride[3] + d2_ * _stride[2] + d3_ * _stride[1] + d4_ * _stride[0]];
	}

	inline value_type& operator()(dimension_type d1_, dimension_type d2_, dimension_type d3_, dimension_type d4_){
		ASSERT_MSG(d1_ < _dimension[0] && d2_ < _dimension[1] && d3_ < _dimension[2] && d4_ < _dimension[3], "small_tensor() index out of bounds. ") ;
		return _data[d1_ * _stride[3] + d2_ * _stride[2] + d3_ * _stride[1] + d4_ * _stride[0]];
	}



};







#endif /*XSMM_BASE_H_*/
