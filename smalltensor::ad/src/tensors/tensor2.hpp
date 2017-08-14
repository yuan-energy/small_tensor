#pragma once
#include "../expressions/expressions.h"

template <typename __dat_t, std::size_t __d1, std::size_t __d2>
class tensor2
{
public:
	__dat_t* __restrict__ _data;

	tensor2(): _data{new __dat_t[__d1*__d2]}{}
	tensor2(tensor2 const& rhs_): _data{new __dat_t[__d1*__d2]}{
		DEBUG_MSG("tensor2 copy constructor is called");
		std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2);
	}

	template <typename val_type>
	tensor2(ad_graph<val_type>& graph_, val_type value_)
	: _data{new __dat_t[__d1*__d2]}
	{
		DEBUG_MSG("tensor2 constructor with Graph is called");
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				(*this)(n1,n2) = __dat_t(graph_, value_) ; 
			}
		}
	}

	template <typename val_type>
	tensor2(ad_graph<val_type>& graph_, int value_)
	: _data{new __dat_t[__d1*__d2]}
	{
		DEBUG_MSG("tensor2 constructor with Graph is called");
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				(*this)(n1,n2) = __dat_t(graph_, value_) ; 
			}
		}
	}

	// template <typename graph_type, typename scalar_type>
	// tensor2(graph_type& graph_)
	// :tensor2(graph_, 0.)
	// {}

	tensor2& operator=(tensor2 const& rhs_){
		DEBUG_MSG("tensor2 copy assignment operator is called");
		if(this != &rhs_){
	        std::memcpy(_data, rhs_._data, sizeof(__dat_t)*__d1*__d2);		
		}
		return *this;
	}

    tensor2(tensor2&& rhs_) noexcept
    : _data{new __dat_t[__d1*__d2]}
    {
    	std::swap(_data, rhs_._data);
    	DEBUG_MSG("tensor2 move constructor is called");
    }
    tensor2& operator=(tensor2&& rhs_) noexcept{
    	if(this != &rhs_){
    		std::swap(_data, rhs_._data);
    	}
    	DEBUG_MSG("tensor2 move assignment operator is called");
    	return *this;
    }
	~tensor2(){
		if (_data!=nullptr){
		    delete[] _data;
		    _data=nullptr;
		}
	}
	tensor2(std::string const& other_):_data{new __dat_t[__d1*__d2]}{
	    if (other_ == "identity")
	    {
	        ASSERT_MSG(__d1==__d2, "ERROR:tensor2 has different dimensions, cannot be identity.");
	        for (std::size_t n1 = 0; n1 < __d1; ++n1)
	        {
	            (*this)(n1,n1) = 1;
	        }
	    }
	}

	// template <typename val_type>
	// tensor2( ad_graph<val_type> & graph_, std::string const& other_)
	// :_data{new __dat_t[__d1*__d2]}
	// {
	//     if (other_ == "identity"){
	//         ASSERT_MSG(__d1==__d2, "ERROR:tensor2 has different dimensions, cannot be identity.");
	//         for (std::size_t n1 = 0; n1 < __d1; ++n1){
	//             (*this)(n1,n1) = __dat_t(graph_, 1) ;  ;
	//         }
	//     }
	// }

	inline __dat_t& operator()(std::size_t n1_, std::size_t n2_){
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in lvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	inline __dat_t operator()(std::size_t n1_, std::size_t n2_)const{
		ASSERT_MSG(n1_< __d1 && n2_ < __d2, "tensor2() index out of bounds in rvalue. ");
		return _data[ n1_ * __d2 + n2_];
	}
	
	template <char i, char j>
	inline expr2<__dat_t, __d1, __d2, i, j>& operator()(Ident<i> i_, Ident<j> j_){
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>&>(*this);
	}

	template <char i, char j>
	inline expr2<__dat_t, __d1, __d2, i, j> const& operator()(Ident<i> i_, Ident<j> j_)const{
        return static_cast<expr2<__dat_t, __d1, __d2, i, j>const&>(*this);
	}

	template <char i>
	inline __dat_t operator()(Ident<i> i_, Ident<i/*same*/> j_){
		ASSERT_MSG(__d1 == __d2, "Dimension size should be equal for dummy indices. ");
		__dat_t ret((*this)(0,0).get_graph(), 0.) ;
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			ret = ret + (*this)(n1,n1);
		}
        return ret;
	}

	inline tensor2& operator*=(__dat_t const& scalar_){
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				(*this)(n1,n2) *= scalar_ ;
			}
		}
		return (*this);
	}

	// template <typename val_type>
	// ad_graph<val_type>* get_graph() const{
	// 	return (*this)(0,0).get_graph();
	// }


	friend std::ostream& operator<<(std::ostream & os, tensor2 const& v ){
		os<<std::endl<<"tensor2=[\n" ;
		for (std::size_t n1 = 0; n1 < __d1; ++n1){
			for (std::size_t n2 = 0; n2 < __d2; ++n2){
				os<<v(n1,n2) << "\t" ;
			}
			os<<"\n";
		}
		os<<"]" << std::endl;
		return os;
	}

};


// friend std::ostream & operator<< (std::ostream & os, const Expr2 & v)
// {
// 	int n1;
// 	int n2;
// 	os << std::endl << "[" << std::endl;
// 	for (n1 = 0; n1 < v.get_dim1(); ++n1)
// 	{
// 		for (n2 = 0; n2 < v.get_dim2(); ++n2)
// 		{
// 			os << v(n1,n2) << " ";
// 		}
// 		os << std::endl;
// 	}
// 	os << "]" << std::endl;

// 	return os;
// }