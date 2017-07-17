#ifndef ad_graph_HPP_
#define ad_graph_HPP_

#include "__types.h"
#include "ad_dual.hpp"

using namespace std;

template <typename val_type>
class ad_dual ;

template <typename val_type>
class ad_graph
{
private:
	typedef std::map<nodeID, std::map<nodeID, val_type>> derivativeTable;
	nodeID _id_count;
	derivativeTable _derivatives;
	set<nodeID> _independent_variables;
	friend class ad_dual<val_type> ;

public:
	ad_graph():_id_count{0}{}


	val_type 
	get_derivative(ad_dual<val_type> const& of, ad_dual<val_type> const& wrt){
		return get_derivative(of._id, wrt._id);
	}

	void
	add_direct_derivative(
			ad_dual<val_type> const& of, 
			ad_dual<val_type> const& wrt, 
			val_type value){
		_derivatives[of._id][wrt._id] += value ; 

		DEBUG_MSG("add_direct_derivative : "
				  "ID"<<of._id<<"/dID"<<wrt._id<<"+="<<value << "\n");
	}



	val_type 
	get_derivative(nodeID of, nodeID wrt){
		if(wrt==of){
			return 1.;
		}else{
			auto it= _derivatives.find(of);
			if( _derivatives.find(of)==_derivatives.end() ){
				return 0.;
			}else{
				val_type ret = 0. ; 
				for(auto const& 
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

};









#endif 