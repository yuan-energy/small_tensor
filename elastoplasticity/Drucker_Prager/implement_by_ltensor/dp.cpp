#include "dp.h"

DTensor2 dp::kronecker_delta(3, 3, "identity");

dp::dp(DVEC constants_prop, double initial_confine)
{
	_shear_modulus   = constants_prop[0] ;
	_vol_K           = constants_prop[1] ;
	_eta             = constants_prop[2] ;
	_eta_bar         = constants_prop[3] ;
	_cohesion        = constants_prop[4] ;
	_initial_confine = initial_confine ;
	_intersection_factor = 0.; 
	_stress_dev_iter = DTensor2(3,3,0.) ; 
	_commit_stress = DTensor2(3,3,0.) ; 
	_strain_iter  = DTensor2(3,3,0.) ; 
	_commit_strain = DTensor2(3,3,0.) ; 
	_strain_plastic_iter = DTensor2(3,3,0.) ; 
	_commit_strain_plastic = DTensor2(3,3,0.) ; 
	_Stiffness = DTensor4(3,3,3,3,0.) ; 
	_Eelastic  = DTensor4(3,3,3,3,0.) ; 

	_test_strain_incr = DTensor2(3,3,0.) ; 
	_test_stress_trial = DTensor2(3,3,0.) ; 

	_p_iter = - _initial_confine ; 
	_commit_stress(_i,_j) = _p_iter * kronecker_delta(_i,_j) ;
	double strain_trial_vol =  _p_iter /_vol_K ; 
	_strain_iter(_i,_j) = strain_trial_vol * kronecker_delta(_i,_j);
	_commit_strain = _strain_iter ; 



	double yield_surface_val = yield_surface(_stress_dev_iter , _p_iter) ;
	_Stiffness(_i,_j,_k,_l) = 
			_vol_K * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) + _shear_modulus * 
			(
				kronecker_delta(_i,_k)*kronecker_delta(_j,_l) + kronecker_delta(_i,_l) * kronecker_delta(_j,_k) 
				+ (-1.) * 
				2./3. * kronecker_delta(_i,_j) * kronecker_delta(_k,_l)
			);
	_Eelastic = _Stiffness ;
	
} 


int dp::setStrainIncr(DTensor2 const& strain_incr){
	DTensor2 strain_trial(3,3,0.) ; 
	strain_trial(_i,_j) = _commit_strain(_i,_j) + strain_incr(_i,_j);
	_strain_iter = strain_trial ; 
	DTensor2 strain_incr_dev(3,3,0.) ; 
	strain_incr_dev = getDev(strain_incr);
	double strain_plastic_incr_vol = strain_incr(_i,_i);
	DTensor2 stress_trial_dev(3,3,0.);
	_stress_dev_iter = getDev(_commit_stress);
	_p_iter = 1./3. * _commit_stress(_i,_i);
	stress_trial_dev(_i,_j) = _stress_dev_iter(_i,_j) 
							+ 2 * _shear_modulus * strain_incr_dev(_i,_j) ; 
	double p_trial = _p_iter + _vol_K * strain_plastic_incr_vol ; 
	double yield_surface_val = yield_surface(stress_trial_dev , p_trial) ;
	// cout<< "yield_surface_val = " << yield_surface_val  << endl;
	_stress_dev_iter = stress_trial_dev ; 
	_p_iter = p_trial ; 
	DTensor2 stress_trial(3,3,0.);
	stress_trial(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j) ; 
	_intersection_factor = backward_zbrentstress(_commit_stress,
	                        stress_trial,
	                        0.0, 1.0, ZBRENT_TOLERANCE) ;


	if (yield_surface_val <= 0.0)
	{
		cout<<"elastic!\n" <<endl;
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



	// test
	DTensor2 stress_multiply(3,3,0.);
	DTensor2 stress_multiply_dev(3,3,0.);
	double stress_multiply_p ;
	stress_multiply(_i,_j) = _commit_stress(_i,_j) + _Stiffness(_i,_j,_k,_l)*strain_incr(_k,_l);
	stress_multiply_dev = getDev(stress_multiply);
	stress_multiply_p = 1./3. * stress_multiply(_i,_i);
	yield_surface_val = yield_surface(stress_multiply_dev, stress_multiply_p);


	// _commit_stress(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j);
	cout<<"Inside Check stress_multiply yf_val = " << yield_surface_val << endl;
	// cout<<"Inside Check stress_integrate yf_val = " << yield_surface(_commit_stress) << endl;
	cout<<"stress_multiply = " << stress_multiply << endl;
	// cout<<"stress_integrate = " << _commit_stress << endl;
	// check if softening:
	// for (int ii = 0; ii < 3; ++ii){
	// 	for (int jj = 0; jj < 3; ++jj){
	// 		if(strain_incr(ii,jj)*stress_multiply(ii,jj)<-1){
	// 			cout<<"!!! SOFTENING detected. \n";
	// 		}
	// 	}
	// }
	_test_strain_incr = strain_incr;
	_test_stress_trial = stress_trial;

}



double dp::yield_surface(DTensor2 const& dev_stress, double pressure) {
	return sqrt(getJ2(dev_stress)) + _eta * pressure - _cohesion ;
}

double dp::yield_surface(DTensor2 const& stress){
	double pressure = stress(_i,_i) / 3. ;
	static DTensor2 stress_dev(3,3,0.);
	stress_dev = getDev(stress);
	return yield_surface(stress_dev, pressure) ;
}

int dp::return2smooth(DTensor2 const& strain_trial, bool& valid){
	DTensor2 stress_trial_dev = _stress_dev_iter ; 
	double p_trial = _p_iter ; 
	double dlambda{0.}; 
	double residual = yield_surface(stress_trial_dev, p_trial); 
	double sqrt_J2_stress_trial_dev = sqrt(getJ2(stress_trial_dev)) ; 
	int iter{0};
	while(fabs(residual) > RETURN2SMOOTH_TOLERANCE 
		&& 
		iter < RETURN2SMOOTH_MAXITER )
	{
		iter++;

		double grad = - _shear_modulus - _vol_K * _eta * _eta_bar ; 
		dlambda = dlambda - residual / grad ; 
		residual = sqrt_J2_stress_trial_dev - _shear_modulus * dlambda
					+ _eta * (p_trial - _vol_K * _eta_bar * dlambda) - _cohesion;
	}

	if( iter > RETURN2SMOOTH_MAXITER )
	{
		cerr<< "ERROR: dp::return2smooth iter > RETURN2SMOOTH_MAXITER" <<endl;
		return -1;
	}

	double ratio = _shear_modulus * dlambda / sqrt_J2_stress_trial_dev ; 
	_stress_dev_iter(_i,_j) = (1. - ratio) * stress_trial_dev(_i,_j) ; 
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

	// // After Return Check:
	// cout<< "=========================================================\n";
	// double yield_surface_val = yield_surface(stress_trial_dev , p_trial) ;
	// cout<< "BeforeReturn Check    yf_v = " << yield_surface_val  << endl;
	// cout<< "BeforeReturn Check _p_iter = " << p_trial            << endl;
	// cout<< "BeforeReturn Check      J2 = " << getJ2(stress_trial_dev)  << endl;
	// cout<< "---------------------------------------------------------\n";
	// yield_surface_val = yield_surface(_stress_dev_iter , _p_iter) ;
	// cout<< "After Return Check    yf_v = " << yield_surface_val  << endl;
	// cout<< "After Return Check _p_iter = " << _p_iter            << endl;
	// cout<< "After Return Check      J2 = " << getJ2(_stress_dev_iter)  << endl;
	// cout<< "---------------------------------------------------------\n";

	compute_stiffness_return2smooth(dlambda, strain_trial);

	return 0;
}




int dp::return2apex(DTensor2 const& strain_trial, double p_trial){
	double strain_plastic_incr_vol{0.} ; 
	double residual = _cohesion / _eta_bar - p_trial ; 
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

	_stress_dev_iter *= 0. ;

	// cout<< "---------------------------------------------------------\n";
	// double yield_surface_val = yield_surface(_stress_dev_iter , _p_iter) ;
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
	_commit_stress(_i,_j) = _stress_dev_iter(_i,_j) + _p_iter * kronecker_delta(_i,_j);
	_commit_strain = _strain_iter ; 
	_commit_strain_plastic = _strain_plastic_iter ; 
}

DTensor2 const& dp::getCommitStress() const {return _commit_stress;  }
DTensor2 const& dp::getCommitStrain() const {return _commit_strain;  }
DTensor2 const& dp::getCommitStrainPlastic() const {return _commit_strain_plastic;  }
DTensor4 const& dp::getTangentTensor() const {return _Stiffness; }


// Helper
DTensor2 dp::getDev(DTensor2 const& strain){
	double vol = strain(_i,_i);
	DTensor2 dev_strain(3,3,0.);
	dev_strain(_i,_j) = strain(_i,_j) - vol/3. * kronecker_delta(_i,_j);
	return dev_strain;
}
double dp::getJ2(DTensor2 const& dev_stress){
	return 0.5 * dev_stress(_i,_j) * dev_stress(_i,_j) ;
}

int dp::compute_stiffness_return2smooth(double dlambda, DTensor2 const& strain_trial){
	DTensor2 strain_trial_dev = getDev(strain_trial) ; 
	double norm_dev = sqrt( strain_trial_dev(_k,_l) * strain_trial_dev(_k,_l) ) ;
	cout<<">>> dlambda = " << dlambda<< endl;
	cout<<">>> strain_trial = " << strain_trial<< endl;






	if(norm_dev<1E-10){
		cout<<"!!!!norm_dev="<<norm_dev<<endl;
		return 0;
	}
	double strain_trial_vol = strain_trial(_i,_i) ; 
	double con_A = 1. / (_shear_modulus + _vol_K * _eta * _eta_bar) ; 
	DTensor2 con_D(3,3,0.) ;
	con_D(_i,_j) = copysign(1.0, _test_stress_trial(_k,_l)*strain_trial(_k,_l)) * strain_trial_dev(_i,_j) / norm_dev ; 
	cout<<">>> con_D = " << con_D<< endl;



	_Stiffness(_i,_j,_k,_l) = 
				  2. * _shear_modulus * ( 1. - dlambda / sqrt(2.) / norm_dev ) 
					 * (kronecker_delta(_i,_k) * kronecker_delta(_j,_l) + (-1./3.)  * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) )
				+ 2. * _shear_modulus * ( dlambda / sqrt(2.) / norm_dev - _shear_modulus * con_A )
					 * con_D(_i,_j) * con_D(_k,_l) 
				+ (-1.) * sqrt(2.) * _shear_modulus * con_A * _vol_K * (_eta * con_D(_i,_j) * kronecker_delta(_k,_l) + _eta_bar * kronecker_delta(_i,_j) * con_D(_k,_l) )
				+ _vol_K * (1. - _vol_K * _eta * _eta_bar * con_A ) * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) ; 



	DTensor2 unit_strain(3,3,0.);
	std::vector<DTensor2>  d_strains( 9, unit_strain ) ;
	std::vector<DTensor2>  d_stress( 9, unit_strain ) ;

	for (int i = 0; i < 3; ++i)	{
		for (int j = 0; j < 3; ++j) {
			(d_strains[i*3+j])(i,j) = 1. ; 
		}
	}


	// DTensor2 stress_trial_dev(3,3,0.);
	// stress_trial_dev = getDev(_test_stress_trial);
	// double sqrt_J2_stress_trial_dev = sqrt(getJ2(stress_trial_dev)) ; 
	// double ratio = _shear_modulus * dlambda / sqrt_J2_stress_trial_dev ; 
	// _stress_dev_iter(_i,_j) = (1. - ratio) * stress_trial_dev(_i,_j) ; 
	// _p_iter = p_trial - _vol_K * _eta_bar * dlambda ; 




	for (int i = 0; i < 9; ++i){
		DTensor2 pre_stress_dev(3,3,0.);
		DTensor2 stress_trial_dev(3,3,0.);
		DTensor2 stres_s(3,3,0.);
		pre_stress_dev = getDev(_commit_stress);
		stress_trial_dev(_i,_j) = pre_stress_dev(_i,_j) 
								+ 2 * _shear_modulus * (d_strains[i])(_i,_j) ; 
		double sqrt_J2_stress_trial_dev = sqrt(getJ2(stress_trial_dev)) ; 
		if(sqrt_J2_stress_trial_dev==0){
			cerr<< "sqrt_J2_stress_trial_dev==0 ! " <<endl;
			return -1;
		}
		double ratio = _shear_modulus * dlambda / sqrt_J2_stress_trial_dev ; 
		stres_s(_i,_j) = (1. - ratio) * stress_trial_dev(_i,_j) ; 
		double p_trial = 1./3. * _commit_stress(_i,_i);
		double strain_plastic_incr_vol = (d_strains[i])(_i,_i);
		p_trial = p_trial + _vol_K * strain_plastic_incr_vol ; 
		double p_ite_r = p_trial - _vol_K * _eta_bar * dlambda ;

		(d_stress[i])(_i,_j) = stres_s(_i,_j) + p_ite_r * kronecker_delta(_i,_j) ;
		(d_stress[i])(_i,_j) = (d_stress[i])(_i,_j) - _commit_stress(_i,_j);
	}
	
	// cout<<"(d_stress[i])= " << (d_stress[0]) <<endl;

	// DTensor4 new_Stiffness(3,3,3,3,0.) ; 
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			_Stiffness(_i,_j,i,j) = (d_stress[i*3+j])(_i,_j) ;
		}
	}

	// _Stiffness(_i,_j,_k,_l) = 
	// 		_vol_K * kronecker_delta(_i,_j) * kronecker_delta(_k,_l) + _shear_modulus * 
	// 		(
	// 			kronecker_delta(_i,_k)*kronecker_delta(_j,_l) + kronecker_delta(_i,_l) * kronecker_delta(_j,_k) 
	// 			+ (-1.) * 
	// 			2./3. * kronecker_delta(_i,_j) * kronecker_delta(_k,_l)
	// 		);
	// static bool first_time = true;
	if(_intersection_factor > 0 ){
		_Stiffness(_i,_j,_k,_l) = _intersection_factor * _Eelastic(_i,_j,_k,_l) + (1.-_intersection_factor) * _Stiffness(_i,_j,_k,_l);
		// first_time = false;
	}

	return 0;
}

int dp::compute_stiffness_return2apex(){
	cout<<"dp::compute_stiffness_return2apex " <<endl;
	_Stiffness = DTensor4(3,3,3,3,0.);
	if(_intersection_factor > 0 ){
		_Stiffness(_i,_j,_k,_l) = _intersection_factor * _Eelastic(_i,_j,_k,_l) + (1.-_intersection_factor) * _Stiffness(_i,_j,_k,_l);
		// first_time = false;
	}
	return 0;
}


double dp::backward_zbrentstress(const DTensor2& start_stress,
                        const DTensor2& end_stress,
                        double x1, double x2, double tol)
    {

        double EPS = numeric_limits<double>::epsilon();

        int iter;
        double a = x1;
        double b = x2;
        double c = 0.0;
        double d = 0.0;
        double e = 0.0;
        double min1 = 0.0;
        double min2 = 0.0;
        double fc = 0.0;
        double p = 0.0;
        double q = 0.0;
        double r = 0.0;
        double s = 0.0;
        double tol1 = 0.0;
        double xm = 0.0;

        // double fa = func(start_stress, end_stress, *ptr_material_parameter, a);
        // double fb = func(start_stress, end_stress, *ptr_material_parameter, b);

        static DTensor2 sigma_a(3, 3, 0.0);
        static DTensor2 sigma_b(3, 3, 0.0);

        sigma_a(_i, _j) = start_stress(_i, _j) * (1 - a)  + end_stress(_i, _j) * a;
        sigma_b(_i, _j) = start_stress(_i, _j) * (1 - b)  + end_stress(_i, _j) * b;

        double fa = yield_surface(sigma_a);
        double fb = yield_surface(sigma_b);

        // cout << "   brent fa = " << fa << " fb = " << fb << endl;


        if ( (fb * fa) > 0.0)
        {
        	return -1E-12;
            // std::cout << "\a\n Root must be bracketed in ZBRENTstress " << std::endl;
            // exit(1);
        }

        fc = fb;

        for ( iter = 1; iter <= ZBRENT_MAXITER; iter++ )
        {
            if ( (fb * fc) > 0.0)
            {
                c = a;
                fc = fa;
                e = d = b - a;
            }

            if ( fabs(fc) < fabs(fb) )
            {
                a = b;
                b = c;
                c = a;
                fa = fb;
                fb = fc;
                fc = fa;
            }

            tol1 = 2.0 * EPS * fabs(b) + 0.5 * tol;
            xm = 0.5 * (c - b);

            if ( fabs(xm) <= tol1 || fb == 0.0 )
            {
                return b;
            }

            if ( fabs(e) >= tol1 && fabs(fa) > fabs(fb) )
            {
                s = fb / fa;

                if (a == c)
                {
                    p = 2.0 * xm * s;
                    q = 1.0 - s;
                }
                else
                {
                    q = fa / fc;
                    r = fb / fc;
                    p = s * ( 2.0 * xm * q * (q - r) - (b - a) * (r - 1.0) );
                    q = (q - 1.0) * (r - 1.0) * (s - 1.0);
                }

                if (p > 0.0)
                {
                    q = -q;
                }

                p = fabs(p);
                min1 = 3.0 * xm * q - fabs(tol1 * q);
                min2 = fabs(e * q);

                if (2.0 * p < (min1 < min2 ? min1 : min2))
                {
                    e = d;
                    d = p / q;
                }
                else
                {
                    d = xm;
                    e = d;
                }
            }
            else
            {
                d = xm;
                e = d;
            }

            a = b;
            fa = fb;

            if (fabs(d) > tol1)
            {
                b += d;
            }
            else
            {
                b += (xm > 0.0 ? fabs(tol1) : -fabs(tol1));
            }

            // fb = func(start_stress, end_stress, *ptr_material_parameter, b);
            sigma_b(_i, _j) = start_stress(_i, _j) * (1 - b)  + end_stress(_i, _j) * b;
            fb = yield_surface(sigma_b);
        }

        return 0.0;
    }