#pragma once




template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(l.get_graph(), l._value / r._value) ;
	out._graph->add_direct_derivative(out, l, 1./r._value);
	out._graph->add_direct_derivative(out, r, -l._value/r._value/r._value);
	return out;
}


template <typename val_type>
ad_dual<val_type> 
operator/(val_type const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(r.get_graph(), l / r._value) ;
	out._graph->add_direct_derivative(out, r, -l/r._value/r._value);
	return out;
}


template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, val_type const& r){
	if( l._graph == nullptr){
		ASSERT_MSG(l._graph != nullptr, "ERROR locates in operation "<<l._value<<"/"<<r<< "\n");
		cerr<<"ERROR!!! Graph is not set yet for this dual-node in operation divide /\n";
		cerr<<"ERROR locates in operation "<<l._value<<"/"<<r<< "\n";
	}
	ad_dual<val_type> out(l.get_graph(), l._value / r) ;
	out._graph->add_direct_derivative(out, l, 1./r);
	return out;
}




template <typename val_type>
ad_dual<val_type> 
operator/(int const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(r.get_graph(), l / r._value) ;
	out._graph->add_direct_derivative(out, r, -l/r._value/r._value);
	return out;
}


template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, int const& r){
	if( l._graph == nullptr){
		ASSERT_MSG(l._graph != nullptr, "ERROR locates in operation "<<l._value<<"/"<<r<< "\n");
		cerr<<"ERROR!!! Graph is not set yet for this dual-node in operation divide /\n";
		cerr<<"ERROR locates in operation "<<l._value<<"/"<<r<< "\n";
	}
	ad_dual<val_type> out(l.get_graph(), l._value / r) ;
	out._graph->add_direct_derivative(out, l, 1./r);
	return out;
}

