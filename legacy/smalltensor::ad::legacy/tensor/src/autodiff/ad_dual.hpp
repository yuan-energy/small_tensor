#pragma once
#include "../../utils/__utils.h"
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
	void set_value(val_type const& val_) { _value=val_; }


};




