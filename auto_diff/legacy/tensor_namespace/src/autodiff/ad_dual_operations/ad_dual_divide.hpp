#pragma once




template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(l._graph), l._value / r._value) ;
	out._graph->add_direct_derivative(out, l, 1./r._value);
	out._graph->add_direct_derivative(out, r, -l._value/r._value/r._value);
	return out;
}


template <typename val_type, typename scalar_type>
ad_dual<val_type> 
operator/(scalar_type const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(r._graph), l / r._value) ;
	out._graph->add_direct_derivative(out, r, -l/r._value/r._value);
	return out;
}


template <typename val_type, typename scalar_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, scalar_type const& r){
	ad_dual<val_type> out(*(l._graph), l._value / r) ;
	out._graph->add_direct_derivative(out, l, 1./r);
	return out;
}

