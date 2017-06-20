#ifndef LIBXSMM_BASE_H_
#define LIBXSMM_BASE_H_

#include <cstdio>   /* printf */
#include <cstdint> /* uint_fast8_t, uint_fast16_t */
#include <stdarg>  /* ..., va_list, va_start, va_arg, va_end */
#include <cassert> /* assert */
using namespace std;


#ifndef NDEBUG
#   define ASSERT_MSG(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": \n" << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT_MSG(condition, message) do { } while (false)
#endif


template <typename T>
inline void copy_vector(T* v1,T* v2,int n){
    for(int i=0;i<n;i++)
        v1[i]=v2[i];
    }

template <typename T1, typename T2>
inline void copy_vector(T1* v1,T2* v2,int n){
    for(int i=0;i<n;i++)
        v1[i]=static_cast<T1>(v2[i]);
    }


template <typename __data_type, uint_fast8_t __order>
class libxsmmm_base
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

	libxsmmm_base()
	{
		_data = nullptr;
		_data_count = 0;
		for (int i = 0; i < __order; ++i)
		{
			dimension[i] = 0;
		}
	}
	void clear()
	{
		if (_data != nullptr)
		{
			delete[] _data;
		}
		_data_count = 0 ; 
		for (int i = 0; i < __order; ++i)
		{
			dimension[i] = 0;
		}
	}
	virtual ~libxsmmm_base()
	{
		clear();
	}

	libxsmmm_base(uint_fast16_t dimension_)
	:_data_count(dimension_), 
	(_dimension[0])(dimension_)
	{
		init_data();
	}

	libxsmmm_base(uint_fast16_t dimension_)
	:_data_count(dimension_), 
	(_dimension[0])(dimension_)
	{
		init_data();
	}

	libxsmmm_base(uint_fast16_t dimension1_, uint_fast16_t dimension2_)
	:_data_count(dimension1_*dimension2_), 
	(_dimension[0])(dimension1_),
	(_dimension[1])(dimension2_)
	{
		init_data();
	}

	libxsmmm_base(uint_fast16_t dimension1_, uint_fast16_t dimension2_, uint_fast16_t dimension3_)
	:_data_count(dimension1_*dimension2_*dimension3_), 
	(_dimension[0])(dimension1_),
	(_dimension[1])(dimension2_),
	(_dimension[2])(dimension3_)
	{
		init_data();
	}
	libxsmmm_base(uint_fast16_t dimension1_, uint_fast16_t dimension2_, uint_fast16_t dimension3_, uint_fast16_t dimension4_)
	:_data_count(dimension1_*dimension2_*dimension3_*dimension4_), 
	(_dimension[0])(dimension1_),
	(_dimension[1])(dimension2_),
	(_dimension[2])(dimension3_),
	(_dimension[3])(dimension4_)
	{
		init_data();
	}

	inline void init_data()
	{
		if(_data_count == 0){
			_data = nullptr;
		}else{
			_data = new value_type[_data_count];
			_data = LIBXSMM_ALIGN(_data, LIBXSMM_ALIGNMENT);
		}

		_stride[0] = 1;
		for (int i = 1; i < __order; i++)
		{
			_stride[i] = _stride[i - 1] * _dimension[ __order - i];
		}
	};

	libxsmmm_base<value_type, __order>& operator=(libxsmmm_base<value_type, __order> const& rhs_)
	{
		if(rhs_._data == nullptr)
		{
			this->clear();
		}else{
			if(this->_data == nullptr)
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

	libxsmmm_base<value_type, __order>& operator=(libxsmmm_base<__rhs_type, __order> const& rhs_)
	{
		if(rhs_._data == nullptr)
		{
			this->clear();
		}else{
			if(this->_data == nullptr)
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


	void set_dimension(uint_fast16_t n_dim, ...)
	{
		va_list l;
		va_start(l, n_dim);
		_data_count = 1;
		for (int i = 0; i < n_dim; ++i)
		{
			_dimension[i] = va_arg(l, uint_fast16_t);
			_data_count *= _dimension[i];
		}
		va_end(l);

		init_data();
	}


	value_type operator[](counter_type n_)
	{
		ASSERT_MSG(n_ <  )
	}

}







#endif LIBXSMM_BASE_H_
