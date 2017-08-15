#include <LTensor.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

typedef vector<double> DVEC;

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

	int setStrainIncr(DTensor2 const& strain_incr);

	double yield_surface(DTensor2 const& dev_stress, double pressure) ;
	double yield_surface(DTensor2 const& stress);
	DTensor2 const& getCommitStress()  const ; 
	DTensor2 const& getCommitStrain()  const ; 
	DTensor2 const& getCommitStrainPlastic()  const ; 
	DTensor4 const& getTangentTensor()  const ; 

	void CommitState();
	// ~dp();
private:
	int return2smooth(DTensor2 const& strain_trial, bool& valid);
	int return2apex(DTensor2 const& strain_trial, double p_trial);
	DTensor2 getDev(DTensor2 const& strain);
	double getJ2(DTensor2 const& dev_stress);
	int compute_stiffness_return2smooth(double dlambda, DTensor2 const& strain_trial);
	int compute_stiffness_return2apex();
	double backward_zbrentstress(const DTensor2& start_stress,
	                        const DTensor2& end_stress,
	                        double x1, double x2, double tol) ; 
private:
	double _shear_modulus;
	double _vol_K;
	double _eta;
	double _eta_bar;
	double _cohesion;
	double _initial_confine;
	double _intersection_factor;

	DTensor2 _stress_dev_iter;
	double _p_iter ; 
	DTensor2 _commit_stress ; 

	DTensor2 _strain_iter;
	DTensor2 _commit_strain ; 
	
	DTensor2 _strain_plastic_iter;
	DTensor2 _commit_strain_plastic; 

	Index<'i'> _i;
	Index<'j'> _j;
	Index<'k'> _k;
	Index<'l'> _l;
	DTensor4 _Stiffness;
	DTensor4 _Eelastic;

	DTensor2 _test_strain_incr;
	DTensor2 _test_stress_trial;

	static DTensor2 kronecker_delta;
	
};