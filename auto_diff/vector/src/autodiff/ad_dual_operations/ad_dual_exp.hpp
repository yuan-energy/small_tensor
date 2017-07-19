#ifndef ad_dual_exp_HPP_
#define ad_dual_exp_HPP_

template <typename val_type>
ad_dual<val_type>
exp(ad_dual<val_type> const& rhs){
	ad_dual<val_type> out(*(rhs._graph), exp(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, exp(rhs._value) );
	return out;
}

#endif