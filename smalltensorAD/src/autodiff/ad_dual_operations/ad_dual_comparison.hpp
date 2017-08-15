#pragma once

template <typename val_type>
bool
operator==(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value == r._value;
}

template <typename val_type>
bool
operator==(ad_dual<val_type> const& l, val_type const& r){
	return l._value == r;
}

template <typename val_type>
bool
operator==(val_type const& l, ad_dual<val_type> const& r){
	return l == r._value;
}

template <typename val_type>
bool
operator==(ad_dual<val_type> const& l, int const& r){
	return l._value == r;
}

template <typename val_type>
bool
operator==(int const& l, ad_dual<val_type> const& r){
	return l == r._value;
}





template <typename val_type>
bool
operator>(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value > r._value;
}

template <typename val_type>
bool
operator>(ad_dual<val_type> const& l, val_type const& r){
	return l._value > r;
}

template <typename val_type>
bool
operator>(val_type const& l, ad_dual<val_type> const& r){
	return l > r._value;
}






template <typename val_type>
bool
operator<(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value < r._value;
}

template <typename val_type>
bool
operator<(ad_dual<val_type> const& l, val_type const& r){
	return l._value < r;
}

template <typename val_type>
bool
operator<(val_type const& l, ad_dual<val_type> const& r){
	return l < r._value;
}










template <typename val_type>
bool
operator>=(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value >= r._value;
}

template <typename val_type>
bool
operator>=(ad_dual<val_type> const& l, val_type const& r){
	return l._value >= r;
}

template <typename val_type>
bool
operator>=(val_type const& l, ad_dual<val_type> const& r){
	return l >= r._value;
}






template <typename val_type>
bool
operator<=(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	return l._value <= r._value;
}

template <typename val_type>
bool
operator<=(ad_dual<val_type> const& l, val_type const& r){
	return l._value <= r;
}

template <typename val_type>
bool
operator<=(val_type const& l, ad_dual<val_type> const& r){
	return l <= r._value;
}



