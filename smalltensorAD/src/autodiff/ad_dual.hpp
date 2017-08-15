#pragma once

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
	ad_dual(ad_graph<val_type>* graph_, val_type value_)
	:_value(value_), _graph(graph_)
	{
		_id = _graph->_id_count++;
		DEBUG_MSG("create new dual: "<<_id<<", value= "<<value_ << "\n");
	}

	ad_dual(ad_graph<val_type>& graph_, val_type value_)
	:_value(value_), _graph(&graph_)
	{
		_id = _graph->_id_count++;
		DEBUG_MSG("create new dual: "<<_id<<", value= "<<value_ << "\n");
	}

	ad_dual(ad_dual & rhs_)
	: _id(rhs_.get_ID())
	, _value(rhs_.get_value())
	, _graph(rhs_.get_graph())
	{
	}

	ad_dual(ad_dual && rhs_)
	: _id(std::move(rhs_.get_ID()))
	, _value(std::move(rhs_.get_value()))
	, _graph(rhs_.get_graph())
	{
	}

	ad_dual& operator=(ad_dual& rhs_){
		_id = rhs_.get_ID();
		_value = rhs_.get_value();
		_graph = rhs_.get_graph();
		return (*this);
	}

	ad_dual operator=(ad_dual&& rhs_){
		_id = rhs_.get_ID();
		_value = rhs_.get_value();
		_graph = rhs_.get_graph();
		return (*this);
	}

	nodeID get_ID() const { return _id; }

	val_type get_value() const { return _value; }
	void set_value(val_type const& val_) { _value=val_; }

	ad_graph<val_type>* get_graph() const{
		if(_graph == nullptr){
			std::cerr<<"AD Usage ERROR!!! The dual-node does not have a graph! \n";
			std::cerr<<"AD Usage ERROR!!! dual-node ID = "<<_id<<", value = "<<_value<<"\n";
		}
		return _graph;
	}
	void reset_graph(ad_graph<val_type>& graph_){
		_graph = &graph_ ;
		_id = _graph->_id_count++;
	}

	ad_dual& operator=(val_type& v){
		std::cerr<<"AD Usage ERROR!!! Cannot directly assign value to dual-node without a pre-defined graph! \n";
		return (*this);
	}


	friend std::ostream& operator<<(std::ostream & os, ad_dual const& v ){
		os << v._value <<" " ;
		// os<<"{dual_value="<< v._value << ", dual_ID="<<v._id <<"}"<<std::endl;
		return os;
	}
};


template <typename val_type>
val_type fabs(ad_dual<val_type>& v) {return std::fabs(v._value);}

template <typename val_type>
val_type abs(ad_dual<val_type>& v)  {return std::abs(v._value);}

