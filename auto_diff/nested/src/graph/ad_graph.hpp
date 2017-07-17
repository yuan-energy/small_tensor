#ifndef ad_graph_HPP_
#define ad_graph_HPP_

#include "../../utils/__types.h"
// #include "dual.hpp"

using namespace std;

// class dual;
class ad_graph
{
private:
	nodeID _id_count;
	derivativeTable _derivatives;
	// set<nodeID> _independent_variables;
	double get_derivative(nodeID of, nodeID wrt);
	// friend class dual;
	class dual;

public:
	ad_graph();
	// ~ad_graph();

	double get_derivative(dual const& of, dual const& wrt);
	void add_direct_derivative(
		dual const& of, 
		dual const& wrt, 
		double value);

};

#endif 