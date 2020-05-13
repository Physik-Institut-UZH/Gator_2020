#ifndef GeParticleSource_h
#define GeParticleSource_h 1

#include "G4VPrimaryGenerator.hh"
#include "G4PrimaryVertex.hh"
#include "G4Navigator.hh"
#include "G4Material.hh"
#include "G4VTouchable.hh"
#include "G4ParticleMomentum.hh"
#include "G4ParticleDefinition.hh"
#include "G4String.hh"

#include "GeParticleSourceMessenger.hh"


//Root histogram
#include "TH1.h"





class GeParticleSource:public G4VPrimaryGenerator
{

  public:
	GeParticleSource();
	~GeParticleSource();
	void GeneratePrimaryVertex(G4Event * evt);

  public:

	// position distribution  
	void SetPosDisType(G4String);
	void SetPosDisShape(G4String);
	void SetCentreCoords(G4ThreeVector);
	void SetCentreR(G4double);
	void SetCentrePhi(G4double);
	void SetCentreZ(G4double);
	void SetHalfZ(G4double);
	void SetRadius(G4double);
	void SetCEflag(G4int);
	void GeneratePointSource();
	void GeneratePointsInVolume();
	void SetRandomPosInMaterial_OC();
	void SetRandomPosInMaterial_IC();
	void SetRandomPosInMaterial_OC1();
	void SetRandomPosInMaterial_PMT();
	void SetRandomPosInMaterial_Teflon();
	void SetRandomPosInMaterial_HVft();
	void SetRandomPosInMaterial_Copper();
	void SetRandomPosInMaterial_Container();
	void SetRandomPosInMaterial_TiCastle();
	void SetRandomPosInMaterial_ARATHANE();
	void SetRandomPosInMaterial_XeBottle();
	void SetRandomPosInMaterial_UnitiTiGr1();
	void SetRandomPosInMaterial_OFCH_Cu();
	void SetRandomPosInMaterial_KAPTONstripes();
	void SetRandomPosInMaterial_Detector();
	void SetRandomPosInMaterial_Al2O3();
	void SetRandomPosInMaterial_PMTsteel();
	void SetRandomPosInMaterial_PMTkovar();
	void SetRandomPosInMaterial_R11410();
	void SetRandomPosInMaterial_WtostoSS();
	void SetRandomPosInMaterial_NironitSS();
	

	void SetRandomXePos();
	void SetRandomICPos();
	
	
//----------------- Put your sample Random position function HERE -------------------------------//
        void SetRandomPosInMaterial_Poly();
        void SetRandomPosInMaterial_Bases();
	void SetRandomPosInMaterial_PMTs();
	void SetRandomPosInMaterial_SS();
	void SetRandomPosInMaterial_Cu();
	void SetRandomPosInMaterial_PTFE();
	void SetRandomPosInMaterial_QUPIDs();
	void SetRandomPosInMaterial_Rb();
	void SetRandomPosInMaterial_W();
	void SetRandomPosInMaterial_Pb();
	void SetRandomPosInMaterial_Conc();
	void SetRandomPosInMaterial_Soil();
	void SetRandomPosInMaterial_Rock();

//-------------------- Everything else is here ------------------------//
	void CreatePrimaryParticle(G4PrimaryVertex * vt);
	G4bool IsSourceConfined();
	void ConfineSourceToVolume(G4String);

	// angular distribution
	void SetAngDistType(G4String);
	void SetParticleMomentumDirection(G4ParticleMomentum);
	void GenerateIsotropicFlux();

	// energy distribution 
	void SetEnergyDisType(G4String);
	void ReadEnergyProbaFile(G4String);
	void ReadIntProbaFile(G4String, G4int);
	double BetaEnergyFromSpectrum(G4int, G4int);
	void GenerateAc228Decay(G4PrimaryVertex * vert);
	int GenerateBa133Decay(G4PrimaryVertex * vert);
	void GenerateBi210Decay(G4PrimaryVertex * vert);
	void GenerateBi212Decay(G4PrimaryVertex * vert);
	void GenerateBi214Decay(G4PrimaryVertex * vert);
	void GenerateCo57Decay(G4PrimaryVertex * vert);
	void GenerateCo60Decay(G4PrimaryVertex * vert);
	void GenerateCs137Decay(G4PrimaryVertex * vert);
	void GenerateK40Decay(G4PrimaryVertex * vert);
	void GeneratePb212Decay(G4PrimaryVertex * vert);
	void GeneratePb210Decay(G4PrimaryVertex * vert);
	void GeneratePb214Decay(G4PrimaryVertex * vert);
	void GeneratePo212Decay(G4PrimaryVertex * vert);
	void GenerateRa224Decay(G4PrimaryVertex * vert);
	void GenerateRa226Decay(G4PrimaryVertex * vert);
	void GenerateTh228Decay(G4PrimaryVertex * vert);
	void GenerateTh230Decay(G4PrimaryVertex * vert);
	void GenerateTh234Decay(G4PrimaryVertex * vert);
	void GenerateU234Decay(G4PrimaryVertex * vert);
	void GenerateAmBe(G4PrimaryVertex * vert);

	void SetMonoEnergy(G4double);
	void GenerateMonoEnergetic();
	inline G4double GetParticleEnergy()
	{
		return particle_energy;
	}
    G4ThreeVector GetParticlePosition()
    {
        return particle_position;
    }

	// verbosity
	void SetVerbosity(G4int);

	// particle properties
	void SetParticleDefinition(G4ParticleDefinition * aParticleDefinition);
	inline void SetParticleCharge(G4double aCharge)
	{
		particle_charge = aCharge;
	}

  private:

	// position distribution
	G4String SourcePosType;
	G4String Shape;
	G4double centre_z;
	G4double centre_r;
	G4double centre_phi;
	G4double halfz;
	G4double Radius;
	G4ThreeVector CentreCoords;
	G4bool Confine;
	G4String VolName;
	G4String AngDistType;
	G4double MinTheta, MaxTheta, MinPhi, MaxPhi;
	G4double Theta, Phi;
	G4String EnergyDisType;
	G4int ceFlag;
	G4double MonoEnergy;

	// particle properties 
	G4int NumberOfParticlesToBeGenerated;
	G4ParticleDefinition *particle_definition;
	G4ParticleMomentum particle_momentum_direction;
	G4double particle_energy;
	G4double particle_charge;
	G4ThreeVector particle_position;
	G4double particle_time;
	G4ThreeVector particle_polarization;

	// Verbose
	G4int verbosityLevel;

  private:

	GeParticleSourceMessenger * theMessenger;
	G4Navigator *gNavigator;
	G4String myMaterial;
	G4int bot, zyl, top, ass;
	G4double emit_energy;
	G4int NofPrimaries;
	G4double primEnergies[5];

	G4int count;
	G4int nlfile[10];
	G4double beta_eng[2000];
	G4double beta_prob[2000];

	G4ParticleDefinition *particle;
	G4ParticleTable *particleTable;
	
	 TH1D* AmBe_n;
	 TH1D* LiqGas;
};

#endif
