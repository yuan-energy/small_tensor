#pragma once



template <typename val_type>
ad_dual<val_type>
pow(ad_dual<val_type> const& base_, val_type const& expon_ ){
	ad_dual<val_type> out(base_.get_graph(), std::pow(base_._value, expon_)) ;
	out._graph->add_direct_derivative( out, base_, expon_ * std::pow(base_._value, expon_-1) );
	return out;
}

template <typename val_type>
ad_dual<val_type>
pow(ad_dual<val_type> const& base_, int const& expon_ ){
	ad_dual<val_type> out(base_.get_graph(), std::pow(base_._value, expon_)) ;
	out._graph->add_direct_derivative( out, base_, expon_ * std::pow(base_._value, expon_-1) );
	return out;
}



template <typename val_type>
ad_dual<val_type>
sqrt(ad_dual<val_type> const& base_){
	ad_dual<val_type> out(base_.get_graph(), std::sqrt(base_._value)) ;
	out._graph->add_direct_derivative( out, base_, 0.5 / std::sqrt(base_._value) );
	return out;
}


