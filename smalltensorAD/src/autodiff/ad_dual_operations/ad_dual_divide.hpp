#pragma once




template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(l.get_graph(), l._value / r._value) ;
	out._graph->add_direct_derivative(out, l, 1./r._value);
	out._graph->add_direct_derivative(out, r, -l._value/r._value/r._value);
	if( std::fabs(r._value) < std::numeric_limits<double>::epsilon() ){
		std::cerr<<"ERROR!!! Divide by zero! " ;
		std::cerr<<"in AD operation "<<l._value<< "/" << r._value <<"\n" ;
	}
	return out;
}


template <typename val_type>
ad_dual<val_type> 
operator/(val_type const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(r.get_graph(), l / r._value) ;
	out._graph->add_direct_derivative(out, r, -l/r._value/r._value);
	if( std::fabs(r._value) < std::numeric_limits<double>::epsilon() ){
		std::cerr<<"ERROR!!! Divide by zero! " ;
		std::cerr<<"in AD operation "<<l<< "/" << r._value <<"\n" ;
	}
	return out;
}


template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, val_type const& r){
	ad_dual<val_type> out(l.get_graph(), l._value / r) ;
	out._graph->add_direct_derivative(out, l, 1./r);
	if( std::fabs(r) < std::numeric_limits<double>::epsilon() ){
		std::cerr<<"ERROR!!! Divide by zero! " ;
		std::cerr<<"in AD operation "<< l._value << "/" << r <<"\n" ;
	}
	return out;
}




template <typename val_type>
ad_dual<val_type> 
operator/(int const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(r.get_graph(), l / r._value) ;
	out._graph->add_direct_derivative(out, r, -l/r._value/r._value);
	if( std::fabs(r._value) < std::numeric_limits<double>::epsilon() ){
		std::cerr<<"ERROR!!! Divide by zero! " ;
		std::cerr<<"in AD operation "<< l << "/" << r._value <<"\n" ;
	}
	return out;
}


template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, int const& r){
	ad_dual<val_type> out(l.get_graph(), l._value / r) ;
	out._graph->add_direct_derivative(out, l, 1./r);
	if( std::abs(r) < std::numeric_limits<double>::epsilon() ){
		std::cerr<<"ERROR!!! Divide by zero! " ;
		std::cerr<<"in AD operation "<< l._value << "/" << r <<"\n" ;
	}
	return out;
}

