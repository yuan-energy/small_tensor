#ifndef AD_DUAL_HPP_
#define AD_DUAL_HPP_
#include "__types.h"
#include "ad_graph.hpp"

template <typename val_type>
class ad_graph ;

template <typename val_type>
class ad_dual
{
public:
	nodeID _id;
	val_type _value;
	ad_graph<val_type>* _graph;
public:
	ad_dual(){};
	ad_dual(ad_graph<val_type> & graph_, val_type value_)
	:_value(value_), _graph(&graph_)
	{
		_id = _graph->_id_count++;
		DEBUG_MSG("create new dual: "<<_id<<", value= "<<value_ << "\n");
	}


	val_type get_value() const { return _value; }


};


template <typename val_type>
ad_dual<val_type> 
operator+(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(l._graph), l._value + r._value) ;
	out._graph->add_direct_derivative(out, l, 1.);
	out._graph->add_direct_derivative(out, r, 1.);
	return out;
}

template <typename val_type>
ad_dual<val_type> 
operator-(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(l._graph), l._value - r._value) ;
	out._graph->add_direct_derivative(out, l,  1.);
	out._graph->add_direct_derivative(out, r, -1.);
	return out;
}

template <typename val_type>
ad_dual<val_type> 
operator*(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(l._graph), l._value * r._value) ;
	out._graph->add_direct_derivative(out, l, r._value);
	out._graph->add_direct_derivative(out, r, l._value);
	return out;
}

template <typename val_type>
ad_dual<val_type> 
operator*(val_type l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(r._graph), l * r._value) ;
	out._graph->add_direct_derivative(out, r, l);
	return out;
}

template <typename val_type>
ad_dual<val_type> 
operator*(ad_dual<val_type> const& l, val_type r){
	ad_dual<val_type> out(*(l._graph), l._value * r) ;
	out._graph->add_direct_derivative(out, l, r);
	return out;
}

template <typename val_type>
ad_dual<val_type> 
operator/(ad_dual<val_type> const& l, ad_dual<val_type> const& r){
	ad_dual<val_type> out(*(l._graph), l._value / r._value) ;
	out._graph->add_direct_derivative(out, l, 1./r._value);
	out._graph->add_direct_derivative(out, r, -l._value/r._value/r._value);
	return out;
}


template <typename val_type>
ad_dual<val_type>
exp(ad_dual<val_type> const& rhs){
	ad_dual<val_type> out(*(rhs._graph), exp(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, exp(rhs._value) );
	return out;
}

template <typename val_type>
ad_dual<val_type>
log(ad_dual<val_type> const& rhs){
	ad_dual<val_type> out(*(rhs._graph), log(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, 1./(rhs._value) );
	return out;
}



#endif