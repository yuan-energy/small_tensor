#ifndef ad_dual_plus_HPP_
#define ad_dual_plus_HPP_


template <typename val_type>
ad_dual<val_type> 
operator+(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(l._graph), l._value + r._value) ;
	out._graph->add_direct_derivative(out, l, 1.);
	out._graph->add_direct_derivative(out, r, 1.);
	return out;
}

template <typename val_type, typename scalar_type>
ad_dual<val_type> 
operator+(scalar_type const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(r._graph), l + r._value) ;
	out._graph->add_direct_derivative(out, r, 1.);
	return out;
}

template <typename val_type, typename scalar_type>
ad_dual<val_type> 
operator+(ad_dual<val_type> const& l, scalar_type const& r){
	ad_dual<val_type> out(*(l._graph), l._value + r) ;
	out._graph->add_direct_derivative(out, l, 1.);
	return out;
}





#endif