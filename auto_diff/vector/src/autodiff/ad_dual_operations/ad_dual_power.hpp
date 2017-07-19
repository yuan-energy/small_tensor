#ifndef ad_dual_power_HPP_
#define ad_dual_power_HPP_



template <typename val_type, typename scalar_type>
ad_dual<val_type>
pow(ad_dual<val_type> const& base_, scalar_type const& expon_ ){
	ad_dual<val_type> out(*(base_._graph), pow(base_._value, expon_)) ;
	out._graph->add_direct_derivative( out, base_, expon_ * pow(base_._value, expon_-1) );
	return out;
}



#endif