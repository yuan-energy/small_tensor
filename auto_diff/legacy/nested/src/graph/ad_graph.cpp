#include "ad_graph.hpp"
ad_graph::ad_graph()
: _id_count{0}
{
}

// ad_graph::~ad_graph(){}

void
ad_graph::
add_direct_derivative(
		dual const& of, 
		dual const& wrt, 
		double value){
	_derivatives[of._id][wrt._id] += value ; 

	DEBUG_MSG("add_direct_derivative : "
			  "ID"<<of._id<<"/dID"<<wrt._id<<"+="<<value << "\n");
}

double 
ad_graph::
get_derivative(dual const& of, dual const& wrt){
	return get_derivative(of._id, wrt._id);
}

double 
ad_graph::
get_derivative(nodeID of, nodeID wrt){
	if(wrt==of){
		return 1.;
	}else{
		derivativeTable::const_iterator it= _derivatives.find(of);
		if( _derivatives.find(of)==_derivatives.end() ){
			return 0.;
		}else{
			double ret = 0. ; 
			for(map<nodeID, double>::value_type const& 
				direct_derivative : it->second)
			{
				if(direct_derivative.first == wrt){
					ret += direct_derivative.second;
				}else{
					ret += direct_derivative.second 
					       * get_derivative(direct_derivative.first, wrt);
				}
			}
			return ret;
		}
	}
}

