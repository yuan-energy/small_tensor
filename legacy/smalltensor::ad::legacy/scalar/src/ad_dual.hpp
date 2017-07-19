#ifndef AD_DUAL_HPP_
#define AD_DUAL_HPP_
#include "__types.h"
#include "ad_graph.hpp"

class ad_graph;

class ad_dual
{
public:
	nodeID _id;
	double _value;
	ad_graph* _graph;
public:
	ad_dual();
	ad_dual(ad_graph& graph_ , double value);
	// ~ad_dual();

	double get_value() const { return _value; }


};



ad_dual operator+(ad_dual const& l, ad_dual const& r);
ad_dual operator-(ad_dual const& l, ad_dual const& r);
ad_dual operator*(ad_dual const& l, ad_dual const& r);
ad_dual operator*(double l, ad_dual const& r);
ad_dual operator*(ad_dual const& l, double r);
ad_dual operator/(ad_dual const& l, ad_dual const& r);
ad_dual exp(ad_dual const& rhs);
ad_dual log(ad_dual const& rhs);

#endif