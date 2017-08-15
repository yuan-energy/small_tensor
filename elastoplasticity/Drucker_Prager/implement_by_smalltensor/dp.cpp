#include "dp.h"

using namespace smalltensor::ad;
// stresstensor dp::kronecker_delta("identity");

dp::dp(DVEC constants_prop, double initial_confine)
{
	_shear_modulus   = constants_prop[0] ;
	_vol_K           = constants_prop[1] ;
	_eta             = constants_prop[2] ;
	_eta_bar         = constants_prop[3] ;
	_cohesion        = constants_prop[4] ;
	_initial_confine = initial_confine ;
	_GRAPH.clear() ;
	// _intersection_factor = 0.; 
	kronecker_delta = stresstensor(_GRAPH, 0.) ;
	for (int ii = 0; ii < 3; ++ii){
		kronecker_delta(ii,ii).set_value(1) ;
	}

	_p_iter = ad_dual<double>(_GRAPH,  -_initial_confine) ; 
	_commit_stress(_i,_j) = _p_iter * kronecker_delta(_i,_j) ;
	ad_dual<double> strain_trial_vol =  _p_iter /_vol_K ; 
	_strain_iter(_i,_j) = strain_trial_vol * kronecker_delta(_i,_j);
	_commit_strain = _strain_iter ; 
	_stress_dev_iter = stresstensor(_GRAPH,0.);

	// ad_dual<double> yield_surface_val = yield_surface(_stress_dev_iter , _p_iter) ;
	_Stiffness(_i,_j,_k,_l) = 
			_vol_K * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) + _shear_modulus * 
			(
				kronecker_delta(_i,_k)*kronecker_delta(_j,_l) + kronecker_delta(_i,_l) * kronecker_delta(_j,_k) 
				+ (-1.) * 
				2./3. * kronecker_delta(_i,_j) * kronecker_delta(_k,_l)
			);
	_Eelastic = _Stiffness ;
} 

void dp::reset_computational_graph(){
	_GRAPH.clear() ;
	// _commit_strain.reset_graph(_GRAPH);

	_d_strain.reset_graph(_GRAPH);
	_d_stress.reset_graph(_GRAPH);

	_p_iter.reset_graph(_GRAPH);
	_stress_dev_iter.reset_graph(_GRAPH);
	_commit_stress.reset_graph(_GRAPH);
	_strain_iter.reset_graph(_GRAPH);
	_commit_strain.reset_graph(_GRAPH);
	_strain_plastic_iter.reset_graph(_GRAPH);
	_commit_strain_plastic.reset_graph(_GRAPH);
	_test_strain_incr.reset_graph(_GRAPH);
	_test_stress_trial.reset_graph(_GRAPH);
	kronecker_delta.reset_graph(_GRAPH);

	_Stiffness.reset_graph(_GRAPH);
	_Eelastic.reset_graph(_GRAPH);
}

int dp::setStrainIncr(DTensor2 const& strain_incr_){
	reset_computational_graph();
	
	
	for (int ii = 0; ii < 3; ++ii)	{
		for (int jj = 0; jj < 3; ++jj)		{
			_d_strain(ii,jj).set_value(strain_incr_(ii,jj));
		}
	}
	stresstensor strain_trial(_GRAPH, 0.) ;
	strain_trial(_i,_j) = _commit_strain(_i,_j) + _d_strain(_i,_j);
	_strain_iter = strain_trial ; 
	stresstensor strain_incr_dev;
	strain_incr_dev = getDev(_d_strain);
	ad_dual<double> strain_plastic_incr_vol = _d_strain(_i,_i);
	stresstensor stress_trial_dev;


	_stress_dev_iter = getDev(_commit_stress);



	_p_iter = 1./3. * _commit_stress(_i,_i);
	stress_trial_dev(_i,_j) = _stress_dev_iter(_i,_j) 
							+ 2 * _shear_modulus * strain_incr_dev(_i,_j) ; 
	ad_dual<double> p_trial = _p_iter + _vol_K * strain_plastic_incr_vol ; 
	ad_dual<double> yield_surface_val = yield_surface(stress_trial_dev , p_trial) ;
	// cout<< "---> yield_surface_val = " << yield_surface_val  << endl;
	_stress_dev_iter = stress_trial_dev ; 
	_p_iter = p_trial ; 
	stresstensor stress_trial;
	stress_trial(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j) ; 
	// _intersection_factor = backward_zbrentstress(_commit_stress,
	//                         stress_trial,
	//                         0.0, 1.0, ZBRENT_TOLERANCE) ;


	if (yield_surface_val <= 0.0)
	{
		cout<<"elastic!!\n" <<endl;
		_d_stress(_i,_j) = stress_trial(_i,_j) - _commit_stress(_i,_j) ;
		_Stiffness(_i,_j,_k,_l) = _d_stress(_i,_j) / _d_strain(_k,_l) ; 
		return 0 ;
	}
	else
	{
		cout<<"plastic!\n" <<endl;
		bool validity{false} ; 
		if(return2smooth(strain_trial, validity) != 0 ){
			cerr<<"failed to return2smooth!" <<endl;
			return -1;
		}
		if (!validity)
		{
			if(return2apex(strain_trial, p_trial) != 0 ){
				cerr<<"failed to return2apex!"<<endl;
				return -1;
			}
		}
	}

	// cerr<<"--->>> debug step 6 \n " ;
	_d_stress(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j) - _commit_stress(_i,_j) ;
	// cerr<<"--->>> debug step 7 \n " ;
	_Stiffness(_i,_j,_k,_l) = _d_stress(_i,_j) / _d_strain(_k,_l) ; 
	// cerr<<"--->>> debug step 8 \n " ;

	// test
	// stresstensor stress_multiply;
	// stresstensor stress_multiply_dev;
	// ad_dual<double> stress_multiply_p(_GRAPH,0.) ;
	// stress_multiply(_i,_j) = _commit_stress(_i,_j) + _Stiffness(_i,_j,_k,_l) * _d_strain(_k,_l);
	// stress_multiply_dev = getDev(stress_multiply);
	// stress_multiply_p = 1./3. * stress_multiply(_i,_i);
	// yield_surface_val = yield_surface(stress_multiply_dev, stress_multiply_p);


	// // _commit_stress(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j);
	// cout<<"Inside Check stress_multiply yf_val = " << yield_surface_val << endl;
	// // cout<<"Inside Check stress_integrate yf_val = " << yield_surface(_commit_stress) << endl;
	// cout<<"stress_multiply = " << stress_multiply << endl;
	// // cout<<"stress_integrate = " << _commit_stress << endl;
	// // check if softening:
	// // for (int ii = 0; ii < 3; ++ii){
	// // 	for (int jj = 0; jj < 3; ++jj){
	// // 		if(strain_incr(ii,jj)*stress_multiply(ii,jj)<-1){
	// // 			cout<<"!!! SOFTENING detected. \n";
	// // 		}
	// // 	}
	// // }
	// _test_strain_incr = _d_strain;
	// _test_stress_trial = stress_trial;
	return 0;
}



ad_dual<double> dp::yield_surface(stresstensor const& dev_stress, ad_dual<double> pressure) {
	return sqrt(getJ2(dev_stress)) + _eta * pressure - _cohesion ;
}

ad_dual<double> dp::yield_surface(stresstensor const& stress){
	ad_dual<double> pressure = stress(0,0) / 3. + stress(1,1) / 3.  + stress(2,2)/3. ;
	stresstensor stress_dev = getDev(stress);
	return yield_surface(stress_dev, pressure) ;
}

int dp::return2smooth(stresstensor const& strain_trial, bool& valid){
	stresstensor stress_trial_dev = _stress_dev_iter ; 
	ad_dual<double> p_trial = _p_iter ; 
	ad_dual<double> dlambda = ad_dual<double>(_GRAPH, 0.);
	ad_dual<double> residual = yield_surface(stress_trial_dev, p_trial); 
	ad_dual<double> sqrt_J2_stress_trial_dev = sqrt(getJ2(stress_trial_dev)) ; 
	int iter{0};
	while(fabs(residual) > RETURN2SMOOTH_TOLERANCE 
		&& 
		iter < RETURN2SMOOTH_MAXITER )
	{
		iter++;

		double grad = - _shear_modulus - _vol_K * _eta * _eta_bar ; 
		dlambda = dlambda - residual / grad ; 
		// cout<<"---->>> debug step 1 \n " ;
		residual = sqrt_J2_stress_trial_dev - _shear_modulus * dlambda
					+ _eta * (p_trial - _vol_K * _eta_bar * dlambda) - _cohesion;
	}
	// cout<<"---->>>> iter = " << iter <<endl;
	if( iter >= RETURN2SMOOTH_MAXITER )
	{
		cerr<< "ERROR: dp::return2smooth iter >= RETURN2SMOOTH_MAXITER" <<endl;
		cerr<< "residual = " << residual <<endl;
		return -1;
	}

	// cout<<"---->>> debug step 2 \n " ;
	ad_dual<double> ratio = _shear_modulus * dlambda / sqrt_J2_stress_trial_dev ; 
	// cout<<"---->>> debug step 3 \n " ;
	_stress_dev_iter(_i,_j) = (1. - ratio) * stress_trial_dev(_i,_j) ; 
	// cout<<"---->>> debug step 4 \n " ;
	_p_iter = p_trial - _vol_K * _eta_bar * dlambda ; 

	valid = false;
	if (ratio < 1.0)
	{
		valid = true;
		_strain_plastic_iter(_i,_j) = strain_trial(_i,_j) - 
								(
									_stress_dev_iter(_i,_j) / 2. / _shear_modulus
									+
									_p_iter / 3. / _vol_K * kronecker_delta(_i,_j)
								) ; 
	}
	// cout<<"---->>> debug step 5 \n " ;

	// // After Return Check:
	// cout<< "=========================================================\n";
	// ad_dual<double> yield_surface_val = yield_surface(stress_trial_dev , p_trial) ;
	// cout<< "BeforeReturn Check    yf_v = " << yield_surface_val  << endl;
	// cout<< "BeforeReturn Check _p_iter = " << p_trial            << endl;
	// cout<< "BeforeReturn Check      J2 = " << getJ2(stress_trial_dev)  << endl;
	// cout<< "---------------------------------------------------------\n";
	// yield_surface_val = yield_surface(_stress_dev_iter , _p_iter) ;
	// cout<< "After Return Check    yf_v = " << yield_surface_val  << endl;
	// cout<< "After Return Check _p_iter = " << _p_iter            << endl;
	// cout<< "After Return Check      J2 = " << getJ2(_stress_dev_iter)  << endl;
	// cout<< "---------------------------------------------------------\n";

	// compute_stiffness_return2smooth(dlambda, strain_trial);

	return 0;
}




int dp::return2apex(stresstensor const& strain_trial, ad_dual<double> p_trial){
	ad_dual<double> strain_plastic_incr_vol=ad_dual<double>(*(p_trial._graph), 0.); 
	ad_dual<double> residual =  _cohesion / _eta_bar - p_trial  ; 
	int iter{0};
	while(fabs(residual) > RETURN2APEX_TOLERANCE 
		&& 
		iter < RETURN2APEX_MAXITER )
	{
		iter++;

		double grad = _vol_K ; 
		strain_plastic_incr_vol = strain_plastic_incr_vol - residual / grad ; 
		_p_iter = p_trial - _vol_K * strain_plastic_incr_vol ; 
		residual =  _cohesion / _eta_bar - _p_iter ; 
	}
	if( iter > RETURN2APEX_MAXITER )
	{
		cerr<< "ERROR: dp::return2apex iter > RETURN2APEX_MAXITER" <<endl;
		return -1;
	}

	_stress_dev_iter(_i,_j) = _stress_dev_iter(_i,_j) * 0. ;

	// cout<< "---------------------------------------------------------\n";
	// ad_dual<double> yield_surface_val = yield_surface(_stress_dev_iter , _p_iter) ;
	// cout<< "After Return 2Apex    yf_v = " << yield_surface_val  << endl;
	// cout<< "After Return 2Apex _p_iter = " << _p_iter            << endl;
	// cout<< "After Return 2Apex      J2 = " << getJ2(_stress_dev_iter)  << endl;
	// cout<< "=========================================================\n";

	_strain_plastic_iter(_i,_j) = strain_trial(_i,_j) - 
							(
								_stress_dev_iter(_i,_j) / 2. / _shear_modulus
								+
								_p_iter / 3. / _vol_K * kronecker_delta(_i,_j)
							) ; 
	compute_stiffness_return2apex();
	return 0; 
}

void dp::CommitState(){
	// stresstensor d_stress(_GRAPH,0.);
	// stresstensor d_strain(_GRAPH,0.);
	// d_stress(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j) - _commit_stress(_i,_j) ;
	// d_strain(_i,_j) = _strain_iter(_i,_j) - _commit_strain(_i,_j);
	// _Stiffness(_i,_j,_k,_l) = d_stress(_i,_j) / d_strain(_k,_l) ; 

	_commit_stress(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j);
	_commit_strain = _strain_iter ; 
	_commit_strain_plastic = _strain_plastic_iter ; 
}

DTensor2 dp::getCommitStress() const {
	// cout<<"_commit_stress="<<_commit_stress<<endl;
	static DTensor2 commit_stress(3,3);
	for (int ii = 0; ii < 3; ++ii)	{
		for (int jj = 0; jj < 3; ++jj)		{
			commit_stress(ii,jj) = _commit_stress(ii,jj).get_value() ;
		}
	}
	return commit_stress;  
}
DTensor2 dp::getCommitStrain() const {
	static DTensor2 commit_strain(3,3);
	for (int ii = 0; ii < 3; ++ii)	{
		for (int jj = 0; jj < 3; ++jj)		{
			commit_strain(ii,jj) = _commit_strain(ii,jj).get_value() ;
		}
	}
	return commit_strain;  
}
DTensor2 dp::getCommitStrainPlastic() const {
	static DTensor2 commit_strain_plastic(3,3);
	for (int ii = 0; ii < 3; ++ii)	{
		for (int jj = 0; jj < 3; ++jj)		{
			commit_strain_plastic(ii,jj) = _commit_strain_plastic(ii,jj).get_value() ;
		}
	}
	return commit_strain_plastic;  
}
DTensor4 dp::getTangentTensor() const {
	static DTensor4 Stiffness(3,3,3,3);
	for (int ii = 0; ii < 3; ++ii)	{
		for (int jj = 0; jj < 3; ++jj) {
			for (int kk = 0; kk < 3; ++kk) {
				for (int ll = 0; ll < 3; ++ll) {
					Stiffness(ii,jj,kk,ll) = _Stiffness(ii,jj,kk,ll).get_value() ;
				}
			}
		}
	}
	return Stiffness; 
}


// Helper
stresstensor dp::getDev(stresstensor const& strain){
	ad_dual<double> vol = strain(0,0)+strain(1,1)+strain(2,2) ;
	// ad_dual<double> vol = strain(_i,_i) ;
	stresstensor dev_strain;
	dev_strain(_i,_j) = strain(_i,_j) - vol/3. * kronecker_delta(_i,_j);
	return dev_strain;
}
ad_dual<double> dp::getJ2(stresstensor const& dev_stress){
	return 0.5 * dev_stress(_i,_j) * dev_stress(_i,_j) ;
}

int dp::compute_stiffness_return2smooth(ad_dual<double> dlambda, stresstensor const& strain_trial){
	stresstensor strain_trial_dev = getDev(strain_trial) ; 
	ad_dual<double> norm_dev = sqrt( strain_trial_dev(_k,_l) * strain_trial_dev(_k,_l) ) ;
	cout<<">>> dlambda = " << dlambda<< endl;
	cout<<">>> strain_trial = " << strain_trial<< endl;






	if(norm_dev<1E-10){
		cout<<"!!!!norm_dev="<<norm_dev<<endl;
		return 0;
	}
	// ad_dual<double> strain_trial_vol = (strain_trial(0,0)+strain_trial(1,1)+strain_trial(2,2))/3. ; 
	double con_A = 1. / (_shear_modulus + _vol_K * _eta * _eta_bar) ; 
	stresstensor con_D;
	// con_D(_i,_j) = copysign(1.0, _test_stress_trial(_k,_l)*strain_trial(_k,_l)) * strain_trial_dev(_i,_j) / norm_dev ; 
	con_D(_i,_j) = strain_trial_dev(_i,_j) / norm_dev ; 
	// cout<<">>> con_D = " << con_D<< endl;



	// _Stiffness(_i,_j,_k,_l) = 
	// 			  2. * _shear_modulus * ( 1. - dlambda / sqrt(2.) / norm_dev ) 
	// 				 * (kronecker_delta(_i,_k) * kronecker_delta(_j,_l) + (-1./3.)  * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) )
	// 			+ 2. * _shear_modulus * ( dlambda / sqrt(2.) / norm_dev - _shear_modulus * con_A )
	// 				 * con_D(_i,_j) * con_D(_k,_l) 
	// 			+ (-1.) * sqrt(2.) * _shear_modulus * con_A * _vol_K * (_eta * con_D(_i,_j) * kronecker_delta(_k,_l) + _eta_bar * kronecker_delta(_i,_j) * con_D(_k,_l) )
	// 			+ _vol_K * (1. - _vol_K * _eta * _eta_bar * con_A ) * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) ; 


	
	// stresstensor unit_strain;
	// std::vector<stresstensor>  d_strains( 9, unit_strain ) ;
	// std::vector<stresstensor>  d_stress( 9, unit_strain ) ;

	// for (int i = 0; i < 3; ++i)	{
	// 	for (int j = 0; j < 3; ++j) {
	// 		(d_strains[i*3+j])(i,j) = 1. ; 
	// 	}
	// }


	// // stresstensor stress_trial_dev(3,3,0.);
	// // stress_trial_dev = getDev(_test_stress_trial);
	// // ad_dual<double> sqrt_J2_stress_trial_dev = sqrt(getJ2(stress_trial_dev)) ; 
	// // ad_dual<double> ratio = _shear_modulus * dlambda / sqrt_J2_stress_trial_dev ; 
	// // _stress_dev_iter(_i,_j) = (1. - ratio) * stress_trial_dev(_i,_j) ; 
	// // _p_iter = p_trial - _vol_K * _eta_bar * dlambda ; 




	// for (int i = 0; i < 9; ++i){
	// 	stresstensor pre_stress_dev(3,3,0.);
	// 	stresstensor stress_trial_dev(3,3,0.);
	// 	stresstensor stres_s(3,3,0.);
	// 	pre_stress_dev = getDev(_commit_stress);
	// 	stress_trial_dev(_i,_j) = pre_stress_dev(_i,_j) 
	// 							+ 2 * _shear_modulus * (d_strains[i])(_i,_j) ; 
	// 	ad_dual<double> sqrt_J2_stress_trial_dev = sqrt(getJ2(stress_trial_dev)) ; 
	// 	if(sqrt_J2_stress_trial_dev==0){
	// 		cerr<< "sqrt_J2_stress_trial_dev==0 ! " <<endl;
	// 		return -1;
	// 	}
	// 	ad_dual<double> ratio = _shear_modulus * dlambda / sqrt_J2_stress_trial_dev ; 
	// 	stres_s(_i,_j) = (1. - ratio) * stress_trial_dev(_i,_j) ; 
	// 	ad_dual<double> p_trial = 1./3. * _commit_stress(_i,_i);
	// 	ad_dual<double> strain_plastic_incr_vol = (d_strains[i])(_i,_i);
	// 	p_trial = p_trial + _vol_K * strain_plastic_incr_vol ; 
	// 	ad_dual<double> p_ite_r = p_trial - _vol_K * _eta_bar * dlambda ;

	// 	(d_stress[i])(_i,_j) = stres_s(_i,_j) + p_ite_r * kronecker_delta(_i,_j) ;
	// 	(d_stress[i])(_i,_j) = (d_stress[i])(_i,_j) - _commit_stress(_i,_j);
	// }
	
	// // cout<<"(d_stress[i])= " << (d_stress[0]) <<endl;

	// // stifftensor new_Stiffness(3,3,3,3,0.) ; 
	// for (int i = 0; i < 3; ++i){
	// 	for (int j = 0; j < 3; ++j){
	// 		_Stiffness(_i,_j,i,j) = (d_stress[i*3+j])(_i,_j) ;
	// 	}
	// }

	// // _Stiffness(_i,_j,_k,_l) = 
	// // 		_vol_K * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) + _shear_modulus * 
	// // 		(
	// // 			kronecker_delta(_i,_k)*kronecker_delta(_j,_l) + kronecker_delta(_i,_l) * kronecker_delta(_j,_k) 
	// // 			+ (-1.) * 
	// // 			2./3. * kronecker_delta(_i,_j) * kronecker_delta(_k,_l)
	// // 		);
	// // static bool first_time = true;
	// if(_intersection_factor > 0 ){
	// 	_Stiffness(_i,_j,_k,_l) = _intersection_factor * _Eelastic(_i,_j,_k,_l) + (1.-_intersection_factor) * _Stiffness(_i,_j,_k,_l);
	// 	// first_time = false;
	// }

	return 0;
}

int dp::compute_stiffness_return2apex(){
	cout<<"dp::compute_stiffness_return2apex " <<endl;
	// _Stiffness = stifftensor(3,3,3,3,0.);
	// if(_intersection_factor > 0 ){
	// 	_Stiffness(_i,_j,_k,_l) = _intersection_factor * _Eelastic(_i,_j,_k,_l) + (1.-_intersection_factor) * _Stiffness(_i,_j,_k,_l);
	// 	// first_time = false;
	// }
	return 0;
}


// double dp::backward_zbrentstress(const stresstensor& start_stress,
//                         const stresstensor& end_stress,
//                         double x1, double x2, double tol)
//     {

//         double EPS = numeric_limits<double>::epsilon();

//         int iter;
//         double a = x1;
//         double b = x2;
//         double c = 0.0;
//         double d = 0.0;
//         double e = 0.0;
//         double min1 = 0.0;
//         double min2 = 0.0;
//         double fc = 0.0;
//         double p = 0.0;
//         double q = 0.0;
//         double r = 0.0;
//         double s = 0.0;
//         double tol1 = 0.0;
//         double xm = 0.0;

//         // ad_dual<double> fa = func(start_stress, end_stress, *ptr_material_parameter, a);
//         // ad_dual<double> fb = func(start_stress, end_stress, *ptr_material_parameter, b);

//         static stresstensor sigma_a;
//         static stresstensor sigma_b;

//         sigma_a(_i, _j) = start_stress(_i, _j) * (1 - a)  + end_stress(_i, _j) * a;
//         sigma_b(_i, _j) = start_stress(_i, _j) * (1 - b)  + end_stress(_i, _j) * b;

//         double fa = yield_surface(sigma_a);
//         double fb = yield_surface(sigma_b);

//         // cout << "   brent fa = " << fa << " fb = " << fb << endl;


//         if ( (fb * fa) > 0.0)
//         {
//         	return -1E-12;
//             // std::cout << "\a\n Root must be bracketed in ZBRENTstress " << std::endl;
//             // exit(1);
//         }

//         fc = fb;

//         for ( iter = 1; iter <= ZBRENT_MAXITER; iter++ )
//         {
//             if ( (fb * fc) > 0.0)
//             {
//                 c = a;
//                 fc = fa;
//                 e = d = b - a;
//             }

//             if ( fabs(fc) < fabs(fb) )
//             {
//                 a = b;
//                 b = c;
//                 c = a;
//                 fa = fb;
//                 fb = fc;
//                 fc = fa;
//             }

//             tol1 = 2.0 * EPS * fabs(b) + 0.5 * tol;
//             xm = 0.5 * (c - b);

//             if ( fabs(xm) <= tol1 || fb == 0.0 )
//             {
//                 return b;
//             }

//             if ( fabs(e) >= tol1 && fabs(fa) > fabs(fb) )
//             {
//                 s = fb / fa;

//                 if (a == c)
//                 {
//                     p = 2.0 * xm * s;
//                     q = 1.0 - s;
//                 }
//                 else
//                 {
//                     q = fa / fc;
//                     r = fb / fc;
//                     p = s * ( 2.0 * xm * q * (q - r) - (b - a) * (r - 1.0) );
//                     q = (q - 1.0) * (r - 1.0) * (s - 1.0);
//                 }

//                 if (p > 0.0)
//                 {
//                     q = -q;
//                 }

//                 p = fabs(p);
//                 min1 = 3.0 * xm * q - fabs(tol1 * q);
//                 min2 = fabs(e * q);

//                 if (2.0 * p < (min1 < min2 ? min1 : min2))
//                 {
//                     e = d;
//                     d = p / q;
//                 }
//                 else
//                 {
//                     d = xm;
//                     e = d;
//                 }
//             }
//             else
//             {
//                 d = xm;
//                 e = d;
//             }

//             a = b;
//             fa = fb;

//             if (fabs(d) > tol1)
//             {
//                 b += d;
//             }
//             else
//             {
//                 b += (xm > 0.0 ? fabs(tol1) : -fabs(tol1));
//             }

//             // fb = func(start_stress, end_stress, *ptr_material_parameter, b);
//             sigma_b(_i, _j) = start_stress(_i, _j) * (1 - b)  + end_stress(_i, _j) * b;
//             fb = yield_surface(sigma_b);
//         }

//         return 0.0;
//     }