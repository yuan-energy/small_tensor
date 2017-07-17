#ifndef dual_HPP_
#define dual_HPP_
#include "../graph/ad_graph.hpp"

class ad_graph::dual
{
public:
	nodeID _id;
	double _value;

public:
	dual(double value);

	double get_value() const { return _value; }


};



dual operator+(dual const& l, dual const& r);
dual operator-(dual const& l, dual const& r);
dual operator*(dual const& l, dual const& r);
dual operator*(double l, dual const& r);
dual operator*(dual const& l, double r);
dual operator/(dual const& l, dual const& r);
dual exp(dual const& rhs);
dual log(dual const& rhs);

#endif