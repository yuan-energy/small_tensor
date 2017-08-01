#ifndef ad_graph_HPP_
#define ad_graph_HPP_

#include "__types.h"
#include "ad_dual.hpp"

using namespace std;

class ad_dual;
class ad_graph
{
private:
	nodeID _id_count;
	derivativeTable _derivatives;
	set<nodeID> _independent_variables;
	double get_derivative(nodeID of, nodeID wrt);
	friend class ad_dual;

public:
	ad_graph();
	// ~ad_graph();

	double get_derivative(ad_dual const& of, ad_dual const& wrt);
	void add_direct_derivative(
		ad_dual const& of, 
		ad_dual const& wrt, 
		double value);

};

#endif 