// #include "../ltensor/LTensor.h"
#include "../../../smalltensor::ad/app/smalltensor.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;


typedef std::vector<double> DVEC;

#define RETURN2SMOOTH_TOLERANCE 1E-12
#define RETURN2SMOOTH_MAXITER 20
#define RETURN2APEX_TOLERANCE 1E-12
#define RETURN2APEX_MAXITER 20
#define ZBRENT_TOLERANCE 1E-12
#define ZBRENT_MAXITER 20
class dp
{
public:
	dp(DVEC constants_prop, double initial_confine);

	int setStrainIncr(stresstensor const& strain_incr);

	double yield_surface(stresstensor const& dev_stress, double pressure) ;
	double yield_surface(stresstensor const& stress);
	stresstensor const& getCommitStress()  const ; 
	stresstensor const& getCommitStrain()  const ; 
	stresstensor const& getCommitStrainPlastic()  const ; 
	stifftensor const& getTangentTensor()  const ; 

	void CommitState();
	// ~dp();
private:
	int return2smooth(stresstensor const& strain_trial, bool& valid);
	int return2apex(stresstensor const& strain_trial, double p_trial);
	stresstensor getDev(stresstensor const& strain);
	double getJ2(stresstensor const& dev_stress);
	int compute_stiffness_return2smooth(double dlambda, stresstensor const& strain_trial);
	int compute_stiffness_return2apex();
	double backward_zbrentstress(const stresstensor& start_stress,
	                        const stresstensor& end_stress,
	                        double x1, double x2, double tol) ; 
private:
	double _shear_modulus;
	double _vol_K;
	double _eta;
	double _eta_bar;
	double _cohesion;
	double _initial_confine;
	double _intersection_factor;

	stresstensor _stress_dev_iter;
	double _p_iter ; 
	stresstensor _commit_stress ; 

	stresstensor _strain_iter;
	stresstensor _commit_strain ; 
	
	stresstensor _strain_plastic_iter;
	stresstensor _commit_strain_plastic; 

	Index<'i'> _i;
	Index<'j'> _j;
	Index<'k'> _k;
	Index<'l'> _l;
	stifftensor _Stiffness;
	stifftensor _Eelastic;

	stresstensor _test_strain_incr;
	stresstensor _test_stress_trial;

	static stresstensor kronecker_delta;
	
};