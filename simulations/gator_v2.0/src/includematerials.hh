  #include "globals.hh"

  #include "G4Material.hh"
  #include <math.h>
  #include <string.h>
  #include <stdio.h>

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4double temperature;
  G4double pressure;
  G4double fractionmass;
  G4int    ncomponents;
  G4String name, symbol;
  
  G4Element* H  = new G4Element(name="Hydrogen", symbol="H", z=1., a=1.00794*g/mole);
  G4Element* C  = new G4Element(name="Carbon",symbol="C" ,z=6., a=12.011*g/mole);
  G4Element* Fe = new G4Element(name="Iron"  ,symbol="Fe",z=26.,a=55.85*g/mole);
  G4Element* Co = new G4Element(name="Cobalt",symbol="Co",z=27.,a=58.9332*g/mole);
  G4Element* N  = new G4Element(name="Nitrogen",symbol="N",z=7.,a=14.01*g/mole);
  G4Element* O  = new G4Element(name="Oxygen" ,symbol="O" , z=8., a=16.0*g/mole);
  G4Element* Al = new G4Element(name="Aluminum",symbol="Al",z=13.,a=26.98*g/mole);
  G4Element* F  = new G4Element(name="Flourine", symbol="F", z=9., a=18.998*g/mole);
  G4Element* Cr  = new G4Element(name="Chromium", symbol="Cr", z=24., a=51.9961*g/mole);
  G4Element* Ni  = new G4Element(name="Nickel", symbol="Ni", z=28., a=58.6934*g/mole);
  G4Element* Mn  = new G4Element(name="Manganese", symbol="Mn", z=25., a=54.93805*g/mole);
  G4Element* Mo  = new G4Element(name="Molybdenum", symbol="Mo", z=42., a=95.94*g/mole);
  G4Element* Ti  = new G4Element(name="Titanium", symbol="Ti", z=22., a=47.867*g/mole);
  G4Element* Si  = new G4Element(name="Silicon", symbol="Si", z=14., a=28.0855*g/mole);
  G4Element* P   = new G4Element(name="Phosphorus", symbol="P", z=15., a=30.973762*g/mole);
  G4Element* S  = new G4Element(name="Sulfur", symbol="S", z=16., a=32.066*g/mole);
  G4Element* Na  = new G4Element(name="Sodium", symbol="Na", z=11., a=22.989769	*g/mole);
  G4Element* Mg  = new G4Element(name="Magnesium", symbol="Mg", z=12., a=24.3050*g/mole);
  G4Element* Ca  = new G4Element(name="Calcium", symbol="Ca", z=20., a=40.078*g/mole);
  G4Element* K  = new G4Element(name="Potassium", symbol="K", z=19., a=39.0983*g/mole);
  G4Element* Zn  = new G4Element(name="Zinc", symbol="Zn", z=30., a=65.38*g/mole);
  G4Element* Th  = new G4Element(name="Thorium", symbol="Th", z=90., a=232.0381*g/mole);
  G4Element* Au  = new G4Element(name="Gold", symbol="Au", z=79., a=196.9666*g/mole);
  G4Element* Pb_el  = new G4Element(name="Lead", symbol="Pb", z=82., a=207.2*g/mole);
  G4Element* Cu_el  = new G4Element(name="Copper", symbol="Cu", z=29., a=63.546*g/mole);
//  G4Element* W  = new G4Element(name="Tungsten", symbol="W", z=74., a=183.84*g/mole);

G4Material* Tetratex_mat = new G4Material("Tetratex_mat",density=0.301*g/cm3,2);
Tetratex_mat->AddElement(C, 0.240183);
Tetratex_mat->AddElement(F, 0.759817);

//Tetratex new mat added below just to investigate uncertanties caused by the density
G4Material* Tetratex_newmat = new G4Material("Tetratex_newmat",density=0.601*g/cm3,2);
Tetratex_newmat->AddElement(C, 0.240183);
Tetratex_newmat->AddElement(F, 0.759817);

//Tetratex new mat added below just to investigate uncertanties caused by the density
G4Material* Tetratex_highdens = new G4Material("Tetratex_highdens",density=3.0*g/cm3,2);
Tetratex_highdens->AddElement(C, 0.240183);
Tetratex_highdens->AddElement(F, 0.759817);

//Tetratex new mat added below just to investigate uncertanties caused by the density
G4Material* Tetratex_newmatlow = new G4Material("Tetratex_newmatlow",density=0.100*g/cm3,2);
Tetratex_newmatlow->AddElement(C, 0.240183);
Tetratex_newmatlow->AddElement(F, 0.759817);

G4Material* Titanium_mat = new G4Material(name="Titanium_mat",z=22.,a=47.867*g/mole,density=4.506*g/cm3);
G4Material* Titanium_electropolished = new G4Material(name="Titanium_electropolished",z=22.,a=47.867*g/mole,density=4.3*g/cm3);

G4Material* Alumina_mat = new G4Material(name="Alumina_mat", density=3.68*g/cm3, ncomponents=2);
Alumina_mat->AddElement(Al, 2);
Alumina_mat->AddElement(O, 3);

G4Material* Pb = new G4Material("Lead", z=82., a=207.19*g/mole,
				  density=11.34*g/cm3);

//  G4Material* Pb2 = new G4Material("Lead3", z=82., a=207.19*g/mole,
//				  density=11.34*g/cm3);

//  G4Material* Pb4 = new G4Material("Lead4", z=82., a=207.19*g/mole,
//				  density=11.34*g/cm3);

  G4Material* PoPb = new G4Material("PoPb", z=82., a=207.19*g/mole,
				  density=11.34*g/cm3);

//  G4Material* CDMSPb = new G4Material("CDMSPb", z=82., a=207.19*g/mole,
//				  density=11.34*g/cm3);
//
  G4Material* Cu = new G4Material("Copper", z=29., a=63.546*g/mole, density=8.920*g/cm3);
//  G4Material* Cu2 = new G4Material("Copper2", z=29., a=63.546*g/mole,
//				  density=8.920*g/cm3);

  G4Material* Silver = new G4Material("Silver", z=13., a=107.868*g/mole, density=10.49*g/cm3);

  G4Material* Aluminum = new G4Material("Aluminum",density=2.7*g/cm3,ncomponents=1);
  	Aluminum->AddElement(Al,fractionmass=1.0);
  
  G4Material* Ge = new G4Material("Germanium", z=32., a=72.64*g/mole,
				  density=5.332*g/cm3);
  
  G4Material* activeGe = new G4Material("activeGe", z=32., a=72.64*g/mole,
				  density=5.332*g/cm3); //This is just a trick to change the name of the same Germanium for the active part
  
  G4Material* Air = new G4Material(name="Air" , density=1.290*mg/cm3, ncomponents=2);
       Air->AddElement(N, fractionmass=0.7);
       Air->AddElement(O, fractionmass=0.3);
  
  G4Material* Vacuum = new G4Material(name="Vacuum", z=1., a=1.*g/mole, 
				      density=1.e-20*g/cm3, kStateGas, 
				      temperature=0.1*kelvin, pressure=1.e-20*bar);
  
  G4Material* Teflon = new G4Material(name="Teflon", density=2.20*g/cm3, ncomponents=2);
       Teflon->AddElement(C,2);
       Teflon->AddElement(F,4);
  
  G4Material* Teflon2 = new G4Material(name="Teflon2", density=2.20*g/cm3, ncomponents=2);
       Teflon2->AddElement(C,2);
       Teflon2->AddElement(F,4);
  
  G4Material* mylar = new G4Material(name="mylar", density=1.3925*g/cm3, ncomponents=3);
       mylar->AddElement(C,10);
       mylar->AddElement(H,8);
       mylar->AddElement(O,8);
  
  G4Material* kapton = new G4Material(name="kapton", density=1.42*g/cm3, ncomponents=4);
       kapton->AddElement(C,22);
       kapton->AddElement(H,10);
       kapton->AddElement(O,5);
       kapton->AddElement(N,2);
  
  G4Material* kapton_F = new G4Material(name="kapton_F", density=1.59*g/cm3, ncomponents=4);
       kapton_F->AddElement(C,22);
       kapton_F->AddElement(H,10);
       kapton_F->AddElement(O,5);
       kapton_F->AddElement(N,2);
  
  G4Material* Steel_304 = new G4Material(name="Steel_304" , density=8.03*g/cm3, ncomponents=8);
       Steel_304->AddElement(Fe, fractionmass=0.6944);
       Steel_304->AddElement(C, fractionmass=0.005);   
       Steel_304->AddElement(Cr, fractionmass=0.185);
       Steel_304->AddElement(Ni, fractionmass=0.10);
       Steel_304->AddElement(Mn, fractionmass=0.01);
       Steel_304->AddElement(Si, fractionmass=0.005);
       Steel_304->AddElement(P, fractionmass=0.0004);
       Steel_304->AddElement(S, fractionmass=0.0002);

 // below commented out (not used and generates warning) 
//  WARNING !! for SS316L sum of fractional masses 0.95941 is not 1     
//  G4Material* SS316L = new G4Material("SS316L", density=8.00*g/cm3, ncomponents=9, kStateSolid);
//  SS316L->AddElement(Fe, fractionmass=0.6075);
//  SS316L->AddElement(C , fractionmass= 0.008);
//  SS316L->AddElement(Cr, fractionmass=0.17);
//  SS316L->AddElement(Ni, fractionmass=0.12);
//  SS316L->AddElement(Mo, fractionmass= 0.025);  
//  SS316L->AddElement(Mn, fractionmass= 0.02);
//  SS316L->AddElement(Si, fractionmass= 0.0075);
//  SS316L->AddElement(P, fractionmass=0.00041);
//  SS316L->AddElement(N, fractionmass=0.001);
  
  G4Material* Cirlex = new G4Material(name="Cirlex", density=1.43*g/cm3,ncomponents=4);
       Cirlex->AddElement(C,22);
       Cirlex->AddElement(H,10);
       Cirlex->AddElement(N,2);
       Cirlex->AddElement(O,5);
  
  G4Material* Cirlex_sim = new G4Material(name="Cirlex_sim", density=0.59*g/cm3,ncomponents=4);
       Cirlex_sim->AddElement(C,22);
       Cirlex_sim->AddElement(H,10);
       Cirlex_sim->AddElement(N,2);
       Cirlex_sim->AddElement(O,5);
  
  G4Material* pmt_material = new G4Material(name="pmt_material" , density=1.19*g/cm3, ncomponents=3);
       pmt_material->AddElement(Fe, fractionmass=0.88);
       pmt_material->AddElement(C, fractionmass=0.04);   
       pmt_material->AddElement(Co, fractionmass=0.08);
  
  G4Material* Polyethylene = new G4Material(name="Polyethylene", density=0.95*g/cm3, ncomponents=2);
       Polyethylene->AddElement(C,2);
       Polyethylene->AddElement(H,4);
  
  G4Material* poly_material = new G4Material(name="poly_material", density=1.75*g/cm3, ncomponents=2);
       poly_material->AddElement(C,2);
       poly_material->AddElement(F,4);
  
  G4Material* Ceramic = new G4Material(name="Ceramic", density = 3.75*g/cm3,ncomponents=2);
       Ceramic->AddElement(Al,2); 
       Ceramic->AddElement(O,3);
  
  G4Material* Polystyrene = new G4Material(name="Polystyrene", density = 1.06*g/cm3, ncomponents = 2);
	Polystyrene->AddElement(C, fractionmass=0.922582);
	Polystyrene->AddElement(H, fractionmass=0.077418);
	
	//Material definition
	//NOTE: This Kovar is Co free, whereas in normal Kovar there is about 16% of Co
	G4Material* PMTkovar_mat = new G4Material("PMTkovar_mat",density=8.36*g/cm3,2);
	PMTkovar_mat -> AddElement(Fe,0.71);
	PMTkovar_mat -> AddElement(Ni,0.29);
