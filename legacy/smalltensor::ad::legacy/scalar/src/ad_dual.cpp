#include "ad_graph.hpp"
#include "ad_dual.hpp"

ad_dual::ad_dual(){}

ad_dual::ad_dual(ad_graph& graph_, double value_)
:_value(value_), _graph(&graph_)
{
	_id = _graph->_id_count++;
	DEBUG_MSG("create new dual: "<<_id<<", value= "<<value_ << "\n");
}
// ad_dual::~ad_dual(){}













ad_dual 
operator+(ad_dual const& l, ad_dual const& r){
	ad_dual out(*(l._graph), l._value + r._value) ;
	out._graph->add_direct_derivative(out, l, 1.);
	out._graph->add_direct_derivative(out, r, 1.);
	return out;
}


ad_dual 
operator-(ad_dual const& l, ad_dual const& r){
	ad_dual out(*(l._graph), l._value - r._value) ;
	out._graph->add_direct_derivative(out, l,  1.);
	out._graph->add_direct_derivative(out, r, -1.);
	return out;
}


ad_dual 
operator*(ad_dual const& l, ad_dual const& r){
	ad_dual out(*(l._graph), l._value * r._value) ;
	out._graph->add_direct_derivative(out, l, r._value);
	out._graph->add_direct_derivative(out, r, l._value);
	return out;
}

ad_dual 
operator*(double l, ad_dual const& r){
	ad_dual out(*(r._graph), l * r._value) ;
	out._graph->add_direct_derivative(out, r, l);
	return out;
}

ad_dual 
operator*(ad_dual const& l, double r){
	ad_dual out(*(l._graph), l._value * r) ;
	out._graph->add_direct_derivative(out, l, r);
	return out;
}

ad_dual 
operator/(ad_dual const& l, ad_dual const& r){
	ad_dual out(*(l._graph), l._value / r._value) ;
	out._graph->add_direct_derivative(out, l, 1./r._value);
	out._graph->add_direct_derivative(out, r, -l._value/r._value/r._value);
	return out;
}


ad_dual
exp(ad_dual const& rhs){
	ad_dual out(*(rhs._graph), exp(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, exp(rhs._value) );
	return out;
}

ad_dual
log(ad_dual const& rhs){
	ad_dual out(*(rhs._graph), log(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, 1./(rhs._value) );
	return out;
}

