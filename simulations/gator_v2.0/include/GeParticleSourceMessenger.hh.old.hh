
// ParticleSourceMessenger header
// --------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
// This particle source is a shortened version of G4GeneralParticleSource by
// C Ferguson, F Lei & P Truscott (University of Southampton / DERA), with
// some minor modifications.
//////////////////////////////////////////////////////////////////////////////

#ifndef GeParticleSourceMessenger_h
#    define GeParticleSourceMessenger_h 1

#    include "G4UImessenger.hh"
#    include "globals.hh"

class GeParticleSource;

class G4ParticleTable;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class GeParticleSourceMessenger:public G4UImessenger
{

  public:
	GeParticleSourceMessenger(GeParticleSource * fPtclGun);
	~GeParticleSourceMessenger();

	void SetNewValue(G4UIcommand * command, G4String newValues);

  private:
	 GeParticleSource * fParticleGun;
	G4ParticleTable *particleTable;

  private:
	 G4UIdirectory * gunDirectory;

	G4UIcmdWithAString *typeCmd;
	G4UIcmdWithAString *shapeCmd;
	G4UIcmdWith3VectorAndUnit *centreCmd;
	G4UIcmdWithADoubleAndUnit *centre_rCmd;
	G4UIcmdWithADoubleAndUnit *centre_phiCmd;
	G4UIcmdWithADoubleAndUnit *centre_zCmd;
	G4UIcmdWithADoubleAndUnit *halfzCmd;
	G4UIcmdWithADoubleAndUnit *radiusCmd;
	G4UIcmdWithAString *confineCmd;
	G4UIcmdWithAString *angtypeCmd;
	G4UIcmdWithAString *energytypeCmd;
	G4UIcmdWithAnInteger *verbosityCmd;
	G4UIcmdWithAnInteger *CEflagCmd;
	G4UIcommand *ionCmd;
	G4UIcmdWithAString *particleCmd;
	G4UIcmdWith3VectorAndUnit *positionCmd;
	G4UIcmdWith3Vector *directionCmd;
	G4UIcmdWithADoubleAndUnit *energyCmd;
	G4UIcmdWithoutParameter *listCmd;

  private:
	 G4bool fShootIon;
	G4int fAtomicNumber;
	G4int fAtomicMass;
	G4int fIonCharge;
	G4double fIonExciteEnergy;

};

#endif
