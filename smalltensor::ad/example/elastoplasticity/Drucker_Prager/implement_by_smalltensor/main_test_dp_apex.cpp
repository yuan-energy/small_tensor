#include <LTensor.h>
#include "DruckerPragerPerfectlyPlastic.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int main(int argc, char const *argv[])
{
	Index<'i'> i;
	Index<'j'> j;

	double _shear_modulus   = 2E7 ;
	double poisson          = 0.1;
	double _vol_K           = _shear_modulus / 3. / (1. - 2. * poisson) ;
	double _eta             = 0.2  ;
	double _eta_bar         = 0.2  ;
	double _cohesion        = 100  ;
	double _initial_confine = 1000 ;
	std::vector<double> material_constants{_shear_modulus, 
							_vol_K, 
							_eta, 
							_eta_bar, 
							_cohesion
							}; 

	auto theMaterial = new DruckerPragerPerfectlyPlastic(material_constants, _initial_confine) ; 


	DTensor2 input_strain(3,3,0.);
	input_strain *= 0. ;
	double max_strain = 0.005;
	int Nstep = 100;
	input_strain(0,1) = max_strain / Nstep ;
	input_strain(1,0) = input_strain(0,1);

	ofstream fout("strain_stress.txt");
	DTensor2 stress_ret(3,3,0.);
	DTensor2 strain_ret(3,3,0.);


	// **************************************************************
	// Write the initial state
	// **************************************************************
	stress_ret = theMaterial->getStressTensor();
	strain_ret = theMaterial->getStrainTensor();
	cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
	fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;

	// **************************************************************
	// Loading
	// **************************************************************
	for (int step = 0; step < Nstep; ++step)
	{
		theMaterial->setTrialStrainIncr(input_strain); 
		theMaterial->commitState();
		stress_ret = theMaterial->getStressTensor();
		strain_ret = theMaterial->getStrainTensor();
		cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
		fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
	}

	// **************************************************************
	// Volumetric loading
	// **************************************************************
	cout<<"************* Volumetric loading ************" <<endl;
	max_strain = 0.01 ; 
	Nstep = 100 ; 
	input_strain(0,0) = max_strain/Nstep; 
	input_strain(1,1) = max_strain/Nstep; 
	input_strain(2,2) = max_strain/Nstep; 
	for (int step = 0; step < Nstep; ++step)
	{
		theMaterial->setTrialStrainIncr(input_strain); 
		theMaterial->commitState();
		stress_ret = theMaterial->getStressTensor();
		strain_ret = theMaterial->getStrainTensor();
		cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
		fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
	}

	// **************************************************************
	// Volumetric loading
	// **************************************************************
	cout<<"************* Volumetric unloading ************" <<endl;
	// input_strain(i,j) = -1. * input_strain(i,j);
	input_strain(0,0) = 0. * max_strain/Nstep; 
	input_strain(1,1) = 0. * max_strain/Nstep; 
	input_strain(2,2) = 0. * max_strain/Nstep; 

	for (int step = 0; step < Nstep; ++step)
	{
		theMaterial->setTrialStrainIncr(input_strain); 
		theMaterial->commitState();
		stress_ret = theMaterial->getStressTensor();
		strain_ret = theMaterial->getStrainTensor();
		cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
		fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
	}

	int Nloop = 2 ; 
	for (int loop = 0; loop < Nloop; ++loop)
	{
		// **************************************************************
		// Un-Loading
		// **************************************************************
		input_strain(i,j) = -1. * input_strain(i,j);
		for (int step = 0; step < 2 * Nstep; ++step)
		{
			theMaterial->setTrialStrainIncr(input_strain); 
			theMaterial->commitState();
			stress_ret = theMaterial->getStressTensor();
			strain_ret = theMaterial->getStrainTensor();
			cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
			fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
		}

		// **************************************************************
		// Re-Loading
		// **************************************************************
		input_strain(i,j) = -1. * input_strain(i,j);
		for (int step = 0; step < 2 * Nstep; ++step)
		{
			theMaterial->setTrialStrainIncr(input_strain); 
			theMaterial->commitState();
			stress_ret = theMaterial->getStressTensor();
			strain_ret = theMaterial->getStrainTensor();
			cout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
			fout<< strain_ret(0,1) <<"\t" << stress_ret(0,1) <<endl;
		}
	}


	delete theMaterial;
	return 0;
}