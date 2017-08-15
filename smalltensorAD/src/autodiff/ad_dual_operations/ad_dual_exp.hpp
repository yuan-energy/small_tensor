#pragma once

template <typename val_type>
ad_dual<val_type>
exp(ad_dual<val_type> const& rhs){
	ad_dual<val_type> out(rhs.get_graph(), std::exp(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, std::exp(rhs._value) );
	return out;
}

