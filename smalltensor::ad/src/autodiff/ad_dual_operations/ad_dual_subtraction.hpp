#pragma once




template <typename val_type>
ad_dual<val_type> 
operator-(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(l.get_graph(), l._value - r._value) ;
	out._graph->add_direct_derivative(out, l,  1.);
	out._graph->add_direct_derivative(out, r, -1.);
	return out;
}



template <typename val_type>
ad_dual<val_type> 
operator-(ad_dual<val_type> const& l, val_type const& r){
	ad_dual<val_type> out(l.get_graph(), l._value - r) ;
	out._graph->add_direct_derivative(out, l,  1.);
	return out;
}



template <typename val_type>
ad_dual<val_type> 
operator-(val_type const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(r.get_graph(), l - r._value) ;
	out._graph->add_direct_derivative(out, r, -1.);
	return out;
}




template <typename val_type>
ad_dual<val_type> 
operator-(ad_dual<val_type> const& l, int const& r){
	ad_dual<val_type> out(l.get_graph(), l._value - r) ;
	out._graph->add_direct_derivative(out, l,  1.);
	return out;
}



template <typename val_type>
ad_dual<val_type> 
operator-(int const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(r.get_graph(), l - r._value) ;
	out._graph->add_direct_derivative(out, r, -1.);
	return out;
}


