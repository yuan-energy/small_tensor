#include <LTensor.h>
#include "../../../../app/smalltensor.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
using namespace smalltensor::ad;


#define RETURN2SMOOTH_TOLERANCE 1E-10
#define RETURN2SMOOTH_MAXITER 20
#define RETURN2APEX_TOLERANCE 1E-10
#define RETURN2APEX_MAXITER 20
#define ZBRENT_TOLERANCE 1E-10
#define ZBRENT_MAXITER 20
class DruckerPragerPerfectlyPlastic
{
public:
	DruckerPragerPerfectlyPlastic(std::vector<double> const& constants_prop, double initial_confine);

	int setTrialStrainIncr(DTensor2 const& strain_incr);

	ad_dual<double> yield_surface(stresstensor const& dev_stress, ad_dual<double> pressure) ;
	ad_dual<double> yield_surface(stresstensor const& stress);
	DTensor2 const& getStressTensor()  const ; 
	DTensor2 const& getStrainTensor()  const ; 
	DTensor2 const& getStrainPlasticTensor()  const ; 
	DTensor4 const& getTangentTensor()  const ; 
	const char *getClassType( void ) const{return "DruckerPragerPerfectlyPlastic";};
	const char *getType( void ) const{return "DruckerPragerPerfectlyPlastic";};
	int getObjectSize(){return sizeof(*this);};

	void Print( ostream &s, int flag = 0 );
	DruckerPragerPerfectlyPlastic *getCopy( void );

	void commitState();
	void revertToLastCommit();
	void revertToStart();

	// virtual ~DruckerPragerPerfectlyPlastic();
private:
	void reset_computational_graph();
	int return2smooth(stresstensor const& strain_trial, bool& valid);
	int return2apex(stresstensor const& strain_trial, ad_dual<double> p_trial);
	stresstensor getDev(stresstensor const& strain);
	ad_dual<double> getJ2(stresstensor const& dev_stress);

	double get_shear_modulus() const;
	double get_vol_K() const;
	double get_eta() const;
	double get_eta_bar() const;
	double get_cohesion() const;
	double get_initial_confine() const;

	// int compute_stiffness_return2smooth(ad_dual<double> dlambda, stresstensor const& strain_trial);
	// int compute_stiffness_return2apex();
	// ad_dual<double> backward_zbrentstress(const stresstensor& start_stress,
	//                         const stresstensor& end_stress,
	//                         ad_dual<double> x1, ad_dual<double> x2, ad_dual<double> tol) ; 
private:
	ad_graph<double> _GRAPH;
	double _shear_modulus;
	double _vol_K;
	double _eta;
	double _eta_bar;
	double _cohesion;
	double _initial_confine;
	// ad_dual<double> _intersection_factor;

	stresstensor _stress_dev_iter;
	ad_dual<double> _p_iter ; 
	stresstensor _stress_iter;
	stresstensor _commit_stress ; 

	stresstensor _strain_iter;
	stresstensor _commit_strain ; 
	
	stresstensor _strain_plastic_iter;
	stresstensor _commit_strain_plastic; 

	stifftensor _Stiffness;
	stifftensor _Eelastic;

	stresstensor kronecker_delta;
	stresstensor _d_strain;
	stresstensor _d_stress;

	smalltensor::ad::Ident<'i'> _i;
	smalltensor::ad::Ident<'j'> _j;
	smalltensor::ad::Ident<'k'> _k;
	smalltensor::ad::Ident<'l'> _l;	
};
// _intersection_factor = 0.; 
// _stress_dev_iter = DTensor2(3,3,0.) ; 
// _commit_stress = DTensor2(3,3,0.) ; 
// _strain_iter  = DTensor2(3,3,0.) ; 
// _commit_strain = DTensor2(3,3,0.) ; 
// _strain_plastic_iter = DTensor2(3,3,0.) ; 
// _commit_strain_plastic = DTensor2(3,3,0.) ; 
// _Stiffness = DTensor4(3,3,3,3,0.) ; 
// _Eelastic  = DTensor4(3,3,3,3,0.) ; 
// _test_strain_incr = DTensor2(3,3,0.) ; 
// _test_stress_trial = DTensor2(3,3,0.) ; 
// _p_iter = - _initial_confine ; 