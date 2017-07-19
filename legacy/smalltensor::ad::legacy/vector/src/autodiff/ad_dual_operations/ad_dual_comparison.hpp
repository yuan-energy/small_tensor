#ifndef ad_dual_comparison_HPP_
#define ad_dual_comparison_HPP_

template <typename val_type>
bool
operator==(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value == r._value;
}

template <typename val_type, typename scalar_type>
bool
operator==(ad_dual<val_type> const& l, scalar_type const& r){
	return l._value == r;
}

template <typename val_type, typename scalar_type>
bool
operator==(scalar_type const& l, ad_dual<val_type> const& r){
	return l == r._value;
}






template <typename val_type>
bool
operator>(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value > r._value;
}

template <typename val_type, typename scalar_type>
bool
operator>(ad_dual<val_type> const& l, scalar_type const& r){
	return l._value > r;
}

template <typename val_type, typename scalar_type>
bool
operator>(scalar_type const& l, ad_dual<val_type> const& r){
	return l > r._value;
}






template <typename val_type>
bool
operator<(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value < r._value;
}

template <typename val_type, typename scalar_type>
bool
operator<(ad_dual<val_type> const& l, scalar_type const& r){
	return l._value < r;
}

template <typename val_type, typename scalar_type>
bool
operator<(scalar_type const& l, ad_dual<val_type> const& r){
	return l < r._value;
}

#endif