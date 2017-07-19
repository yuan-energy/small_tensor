#ifndef ad_dual_log_HPP_
#define ad_dual_log_HPP_




template <typename val_type>
ad_dual<val_type>
log(ad_dual<val_type> const& rhs){
	ad_dual<val_type> out(*(rhs._graph), log(rhs._value)) ;
	out._graph->add_direct_derivative( out, rhs, 1./(rhs._value) );
	return out;
}






#endif