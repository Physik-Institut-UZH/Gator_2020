
// ParticleSourceMessenger program
// --------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
// This particle source is a shortened version of G4GeneralParticleSource by
// C Ferguson, F Lei & P Truscott (University of Southampton / DERA), with
// some minor modifications.
//////////////////////////////////////////////////////////////////////////////

#include "GeParticleSourceMessenger.hh"
#include "GeParticleSource.hh"

#include "G4Geantino.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleTable.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4ios.hh"
#include <fstream>
#include <iomanip>
#include "G4Tokenizer.hh"
#include <strstream>

///////////////////////////////////////////////////////////////////////////////
GeParticleSourceMessenger::GeParticleSourceMessenger(GeParticleSource * fPtclGun):fParticleGun(fPtclGun), fShootIon(false)
{

	particleTable = G4ParticleTable::GetParticleTable();

	// create directory
	gunDirectory = new G4UIdirectory("/Xe/gun/");
	gunDirectory->SetGuidance("Particle Source control commands.");

	// list available particles
	listCmd = new G4UIcmdWithoutParameter("/Xe/gun/List", this);
	listCmd->SetGuidance("List available particles.");
	listCmd->SetGuidance(" Invoke G4ParticleTable.");

	// set particle  
	particleCmd = new G4UIcmdWithAString("/Xe/gun/particle", this);
	particleCmd->SetGuidance("Set particle to be generated.");
	particleCmd->SetGuidance(" (geantino is default)");
	particleCmd->SetGuidance(" (ion can be specified for shooting ions)");
	particleCmd->SetParameterName("particleName", true);
	particleCmd->SetDefaultValue("geantino");
	
	G4String candidateList;
	
	G4int nPtcl = particleTable->entries();

	for(G4int i = 0; i < nPtcl; i++)
	{
		candidateList += particleTable->GetParticleName(i);
		candidateList += " ";
	}
	
	candidateList += "ion ";
	particleCmd->SetCandidates(candidateList);

	// particle direction
	directionCmd = new G4UIcmdWith3Vector("/Xe/gun/direction", this);
	directionCmd->SetGuidance("Set momentum direction.");
	directionCmd->SetGuidance("Direction needs not to be a unit vector.");
	directionCmd->SetParameterName("Px", "Py", "Pz", true, true);
	directionCmd->SetRange("Px != 0 || Py != 0 || Pz != 0");

	// particle energy
	energyCmd = new G4UIcmdWithADoubleAndUnit("/Xe/gun/energy", this);
	energyCmd->SetGuidance("Set kinetic energy.");
	energyCmd->SetParameterName("Energy", true, true);
	energyCmd->SetDefaultUnit("GeV");
	//energyCmd->SetUnitCategory("Energy");
	//energyCmd->SetUnitCandidates("eV keV MeV GeV TeV");

	positionCmd = new G4UIcmdWith3VectorAndUnit("/Xe/gun/position", this);
	positionCmd->SetGuidance("Set starting position of the particle.");
	positionCmd->SetParameterName("X", "Y", "Z", true, true);
	positionCmd->SetDefaultUnit("cm");
	//positionCmd->SetUnitCategory("Length");
	//positionCmd->SetUnitCandidates("microm mm cm m km");

	// ion 
	ionCmd = new G4UIcommand("/Xe/gun/ion", this);
	ionCmd->SetGuidance("Set properties of ion to be generated.");
	ionCmd->SetGuidance("[usage] /gun/ion Z A Q E");
	ionCmd->SetGuidance("        Z:(int) AtomicNumber");
	ionCmd->SetGuidance("        A:(int) AtomicMass");
	ionCmd->SetGuidance("        Q:(int) Charge of Ion (in unit of e)");
	ionCmd->SetGuidance("        E:(double) Excitation energy (in keV)");

	G4UIparameter* param;

	param = new G4UIparameter("Z", 'i', false);
	param->SetDefaultValue("1");
	ionCmd->SetParameter(param);
	param = new G4UIparameter("A", 'i', false);
	param->SetDefaultValue("1");
	ionCmd->SetParameter(param);
	param = new G4UIparameter("Q", 'i', true);
	param->SetDefaultValue("0");
	ionCmd->SetParameter(param);
	param = new G4UIparameter("E", 'd', true);
	param->SetDefaultValue("0.0");
	ionCmd->SetParameter(param);

	// source distribution type
	typeCmd = new G4UIcmdWithAString("/Xe/gun/type", this);
	typeCmd->SetGuidance("Sets source distribution type.");
	typeCmd->SetGuidance("Either Point or Volume");
	typeCmd->SetParameterName("DisType", true, true);
	typeCmd->SetDefaultValue("Point");
	typeCmd->
		SetCandidates
		("Point Volume PointRandomOC PointRandomOC1 PointRandomIC PointRandomPMT PointRandomTeflon PointRandomHVft RandomXe RandomIC RandomCopper PointRandomBases PointRandomPoly PointRandomPMTs PointRandomSS PointRandomCu PointRandomPTFE PointRandomQUPIDs PointRandomRb PointRandomW PointRandomPb PointRandomConc PointRandomSoil PointRandomContainer PointRandomRock PointRandomTiCastle PointRandomARATHANE PointRandomXeBottle PointRandomUnitiTiGr1 PointRandomOFCHCu PointRandomKAPTONstripes PointRandomDetector PointRandomPMTAl2O3 PointRandomPMTsteel PointRandomPMTkovar PointRandomR11410 PointRandomWTostoSS PointRandomNironitSS");

	// source shape
	shapeCmd = new G4UIcmdWithAString("/Xe/gun/shape", this);
	shapeCmd->SetGuidance("Sets source shape type.");
	shapeCmd->SetParameterName("Shape", true, true);
	shapeCmd->SetDefaultValue("NULL");
	shapeCmd->SetCandidates("Sphere Cylinder");

	// centre coordinates
	centreCmd = new G4UIcmdWith3VectorAndUnit("/Xe/gun/centre", this);
	centreCmd->SetGuidance("Set centre coordinates of source.");
	centreCmd->SetParameterName("X", "Y", "Z", true, true);
	centreCmd->SetDefaultUnit("cm");
	centreCmd->SetUnitCandidates("nm mum mm cm m km");

	// centre coordinates in r, phi, z
	centre_rCmd = new G4UIcmdWithADoubleAndUnit("/Xe/gun/centre_r", this);
	centre_rCmd->
		SetGuidance("Set centre coordinates of source in r, phi and z");
	centre_rCmd->SetParameterName("R", true, true);
	centre_rCmd->SetDefaultUnit("cm");
	centre_rCmd->SetUnitCandidates("nm mum mm cm m km");

	centre_phiCmd = new G4UIcmdWithADoubleAndUnit("/Xe/gun/centre_phi", this);
	centre_phiCmd->
		SetGuidance("Set centre coordinates of source in r, phi and z");
	centre_phiCmd->SetParameterName("Phi", true, true);
	centre_phiCmd->SetDefaultUnit("deg");
	centre_phiCmd->SetUnitCandidates("rad deg");

	centre_zCmd = new G4UIcmdWithADoubleAndUnit("/Xe/gun/centre_z", this);
	centre_zCmd->
		SetGuidance("Set centre coordinates of source in r, phi and z");
	centre_zCmd->SetParameterName("Z", true, true);
	centre_zCmd->SetDefaultUnit("cm");
	centre_zCmd->SetUnitCandidates("nm mum mm cm m km");

	// half height of source
	halfzCmd = new G4UIcmdWithADoubleAndUnit("/Xe/gun/halfz", this);
	halfzCmd->SetGuidance("Set z half length of source.");
	halfzCmd->SetParameterName("Halfz", true, true);
	halfzCmd->SetDefaultUnit("cm");
	halfzCmd->SetUnitCandidates("nm mum mm cm m km");

	// radius of source  
	radiusCmd = new G4UIcmdWithADoubleAndUnit("/Xe/gun/radius", this);
	radiusCmd->SetGuidance("Set radius of source.");
	radiusCmd->SetParameterName("Radius", true, true);
	radiusCmd->SetDefaultUnit("cm");
	radiusCmd->SetUnitCandidates("nm mum mm cm m km");

	// confine to volume
	confineCmd = new G4UIcmdWithAString("/Xe/gun/confine", this);
	confineCmd->SetGuidance("Confine source to volume (NULL to unset).");
	confineCmd->SetGuidance("usage: confine VolName");
	confineCmd->SetParameterName("VolName", true, true);
	confineCmd->SetDefaultValue("NULL");

	// angular distribution
	angtypeCmd = new G4UIcmdWithAString("/Xe/gun/angtype", this);
	angtypeCmd->SetGuidance("Sets angular source distribution type");
	angtypeCmd->SetGuidance("Possible variables are: iso direction");
	angtypeCmd->SetParameterName("AngDis", true, true);
	angtypeCmd->SetDefaultValue("iso");
	angtypeCmd->SetCandidates("iso direction");

	// energy distribution
	energytypeCmd = new G4UIcmdWithAString("/Xe/gun/energytype", this);
	energytypeCmd->SetGuidance("Sets energy distribution type");
	energytypeCmd->SetGuidance("Possible variables are: Mono");
	energytypeCmd->SetParameterName("EnergyDis", true, true);
	energytypeCmd->SetDefaultValue("Mono");
	energytypeCmd->
		SetCandidates("Mono AmBe Ac228 Ba133 Bi214 Bi212 Bi210 Co57 Co60 Cs137 K40 Th234 Th230 Th228 Pb214 Pb212 Pb210 Ra224 Ra226 Po212 U234 XeAct");

	// create flag to start conversion/beta e-

	CEflagCmd = new G4UIcmdWithAnInteger("/Xe/generateCE", this);
	CEflagCmd->
		SetGuidance("Flag to switch start of conversion/beta e- on/off");
	CEflagCmd->SetGuidance("Default = false");
	CEflagCmd->SetParameterName("generateCEFlag", false);

	// verbosity
	verbosityCmd = new G4UIcmdWithAnInteger("/Xe/gun/verbose", this);
	verbosityCmd->SetGuidance("Set Verbose level for gun");
	verbosityCmd->SetGuidance(" 0 : Silent");
	verbosityCmd->SetGuidance(" 1 : Limited information");
	verbosityCmd->SetGuidance(" 2 : Detailed information");
	verbosityCmd->SetParameterName("level", false);
	verbosityCmd->SetRange("level>=0 && level <=2");

}

GeParticleSourceMessenger::~GeParticleSourceMessenger()
{

	delete typeCmd;
	delete shapeCmd;
	delete centreCmd;
	delete centre_rCmd;
	delete centre_phiCmd;
	delete centre_zCmd;
	delete halfzCmd;
	delete radiusCmd;
	delete confineCmd;
	delete angtypeCmd;
	delete energytypeCmd;
	delete verbosityCmd;
	delete ionCmd;
	delete particleCmd;
	delete positionCmd;
	delete directionCmd;
	delete energyCmd;
	delete listCmd;
	delete CEflagCmd;

	delete gunDirectory;
}

void
GeParticleSourceMessenger::SetNewValue
	(G4UIcommand * command, G4String newValues)
{

	if(command == typeCmd)
		fParticleGun->SetPosDisType(newValues);

	else if(command == shapeCmd)
		fParticleGun->SetPosDisShape(newValues);

	else if(command == centreCmd)
		fParticleGun->SetCentreCoords(centreCmd->
			GetNew3VectorValue(newValues));

	else if(command == centre_rCmd)
		fParticleGun->SetCentreR(centre_rCmd->GetNewDoubleValue(newValues));

	else if(command == centre_phiCmd)
		fParticleGun->SetCentrePhi(centre_phiCmd->
			GetNewDoubleValue(newValues));

	else if(command == centre_zCmd)
		fParticleGun->SetCentreZ(centre_zCmd->GetNewDoubleValue(newValues));

	else if(command == halfzCmd)
		fParticleGun->SetHalfZ(halfzCmd->GetNewDoubleValue(newValues));

	else if(command == radiusCmd)
		fParticleGun->SetRadius(radiusCmd->GetNewDoubleValue(newValues));

	else if(command == angtypeCmd)
		fParticleGun->SetAngDistType(newValues);

	else if(command == confineCmd)
		fParticleGun->ConfineSourceToVolume(newValues);

	else if(command == energytypeCmd)
		fParticleGun->SetEnergyDisType(newValues);

	else if(command == verbosityCmd)
		fParticleGun->SetVerbosity(verbosityCmd->GetNewIntValue(newValues));

	else if(command == CEflagCmd)
		fParticleGun->SetCEflag(CEflagCmd->GetNewIntValue(newValues));

	else if(command == particleCmd)
	{
		if(newValues == "ion")
		{
			fShootIon = true;
		}
		else
		{
			fShootIon = false;
			G4ParticleDefinition *
				pd = particleTable->FindParticle(newValues);

			if(pd != NULL)
			{
				fParticleGun->SetParticleDefinition(pd);
			}
		}
	}

	else if(command == ionCmd)
	{
		if(fShootIon)
		{
			G4Tokenizer
			next(newValues);

			// check argument
			fAtomicNumber = StoI(next());
			fAtomicMass = StoI(next());
			G4String
				sQ = next();

			if(sQ.isNull())
			{
				fIonCharge = fAtomicNumber;
			}
			else
			{
				fIonCharge = StoI(sQ);
				sQ = next();
				if(sQ.isNull())
				{
					fIonExciteEnergy = 0.0;
				}
				else
				{
					fIonExciteEnergy = StoD(sQ) * keV;
				}
			}

			G4ParticleDefinition *
				ion;

			ion =
				particleTable->GetIon(fAtomicNumber, fAtomicMass,
				fIonExciteEnergy);
			if(ion == 0)
			{
				G4cout << "Ion with Z=" << fAtomicNumber;
				G4cout << " A=" << fAtomicMass << "is not be defined" <<
					G4endl;
			}
			else
			{
				fParticleGun->SetParticleDefinition(ion);
				fParticleGun->SetParticleCharge(fIonCharge * eplus);
			}
		}
		else
		{
			G4cout <<
				"Set /Xe/gun/particle to ion before using /Xe/gun/ion command";
			G4cout << G4endl;
		}
	}

	else if(command == listCmd)
		particleTable->DumpTable();

	else if(command == directionCmd)
	{
		fParticleGun->SetAngDistType("direction");
		fParticleGun->SetParticleMomentumDirection
			(directionCmd->GetNew3VectorValue(newValues));
	}

	else if(command == energyCmd)
	{
		fParticleGun->SetEnergyDisType("Mono");
		fParticleGun->SetMonoEnergy(energyCmd->GetNewDoubleValue(newValues));
	}

	else if(command == positionCmd)
	{
		fParticleGun->SetPosDisType("Point");
		fParticleGun->SetCentreCoords(positionCmd->
			GetNew3VectorValue(newValues));
	}
	else
		G4cout << "Error entering command" << G4endl;
}
