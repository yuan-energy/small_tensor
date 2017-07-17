#include "ad_graph.hpp"
// #include "dual.hpp"

dual::dual(double value_)
:_value(value_)
{
	_id = _graph._id_count++;
	DEBUG_MSG("create new dual: "<<_id<<", value= "<<value_ << "\n");
}
// dual::~dual(){}













dual 
operator+(dual const& l, dual const& r){
	dual out(l._graph, l._value + r._value) ;
	out._graph.add_direct_derivative(out, l, 1.);
	out._graph.add_direct_derivative(out, r, 1.);
	return out;
}


dual 
operator-(dual const& l, dual const& r){
	dual out(l._graph, l._value - r._value) ;
	out._graph.add_direct_derivative(out, l,  1.);
	out._graph.add_direct_derivative(out, r, -1.);
	return out;
}


dual 
operator*(dual const& l, dual const& r){
	dual out(l._graph, l._value * r._value) ;
	out._graph.add_direct_derivative(out, l, r._value);
	out._graph.add_direct_derivative(out, r, l._value);
	return out;
}

dual 
operator*(double l, dual const& r){
	dual out(r._graph, l * r._value) ;
	out._graph.add_direct_derivative(out, r, l);
	return out;
}

dual 
operator*(dual const& l, double r){
	dual out(l._graph, l._value * r) ;
	out._graph.add_direct_derivative(out, l, r);
	return out;
}

dual 
operator/(dual const& l, dual const& r){
	dual out(l._graph, l._value / r._value) ;
	out._graph.add_direct_derivative(out, l, 1./r._value);
	out._graph.add_direct_derivative(out, r, -l._value/r._value/r._value);
	return out;
}


dual
exp(dual const& rhs){
	dual out(rhs._graph, exp(rhs._value)) ;
	out._graph.add_direct_derivative( out, rhs, exp(rhs._value) );
	return out;
}

dual
log(dual const& rhs){
	dual out(rhs._graph, log(rhs._value)) ;
	out._graph.add_direct_derivative( out, rhs, 1./(rhs._value) );
	return out;
}

