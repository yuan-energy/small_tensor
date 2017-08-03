#pragma once


template <typename val_type>
ad_dual<val_type> 
operator-( ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(r._graph),  - r._value) ;
	out._graph->add_direct_derivative(out, r, -1.);
	return out;
}

