#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4UIXm.hh"


#include "DetectorConstr.hh"
#include "GeConstruction.hh"
#include "GePhysicsList.hh"
#include "GePrimaryGeneratorAction.hh"
#include "GeTrackingAction.hh"
#include "GeEventAction.hh"
#include "GeRunAction.hh"
#include "GeSteppingAction.hh"

#include "GeMyTree.hh"
//ROOT Includes
#include "TH1.h"
#include "TPostScript.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TBranch.h"
#include "Rtypes.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef G4VIS_USE 
#include "GeVisManager.hh"
#endif


int main(int argc, char** argv)
{

 std::cout<<"\n Running the binary to produce the .wrl file and run overlap checks\n "<<std::endl;

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;




  // set mandatory initialization classes
  runManager->SetUserInitialization(new GeConstruction);
  //runManager->SetUserInitialization(new DetectorConstr);
  runManager->SetUserInitialization(new GePhysicsList);

 G4UIsession* session=0;

  if (argc==1)  
 // Define UI session for interactive mode.

{     
// G4UIterminal is a (dumb) terminal.

#ifdef G4UI_USE_XM
      session = new G4UIXm(argc,argv);

#else           
      session = new G4UIterminal(new G4UItcsh);      
#endif
    }
 

#ifdef G4VIS_USE 
 //visualization manager 
 G4VisManager* visManager = new GeVisManager;
 visManager->Initialize();
#endif

  // set mandatory user action class
  GePrimaryGeneratorAction* GeGenerator = new GePrimaryGeneratorAction;
  runManager->SetUserAction(GeGenerator);
  runManager->SetUserAction(new GeTrackingAction);
  //runManager->SetUserAction(new GeSteppingAction);
  GeRunAction* GeRun = new GeRunAction;
  runManager->SetUserAction(GeRun);


  G4String outfile;
  //  char tmp1[10],tmp2[10];

  MyTree ev;
  TTree* t1 = new TTree("t1","Hits");
  
  t1->Branch("eventid",&ev.eventid,"eventid/I");
  t1->Branch("NoHits",&ev.NoHits,"NoHits/I");  
  t1->Branch("xp",&ev.xp,"xp/F");
  t1->Branch("yp",&ev.yp,"yp/F");
  t1->Branch("zp",&ev.zp,"zp/F");
  t1->Branch("te",&ev.te,"te/F");  
  t1->Branch("GeEtot",&ev.GeEtot,"GeEtot/F"); 
  t1->Branch("GeEhit",&ev.GeEhit,"GeEhit/F"); 
  


//  t1->Branch("time",&ev.time,"time/F");
//  t1->Branch("extint",&ev.extint,"extint/I");

  G4int evt_num;
  GeEventAction *ev_act = new GeEventAction(&evt_num,t1,&ev,GeRun,GeGenerator) ;
  runManager->SetUserAction(ev_act);


  // Initialize G4 kernel
  runManager->Initialize();
   //std::cout<<" ############ "<<evt_num<<"\n\n";

 std::cout<<"\n *** When running to creat the geometry, check all overlaps are ok in the window ***\n Then, ctrl+c to close the G4UIXm window and continue (do not ctrl+c before the binary finished running) \n\n";

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
//   UI->ApplyCommand("/run/verbose 0");
//   UI->ApplyCommand("/event/verbose 0");
//   UI->ApplyCommand("/tracking/verbose 0");
  if (session)   // Define UI session for interactive mode.
    {
      // G4UIterminal is a (dumb) terminal.
      UI->ApplyCommand("/control/execute vis.mac");    
//#ifdef G4UI_USE_XM
      // Customize the G4UIXm menubar with a macro file :
//      UI->ApplyCommand("/control/execute visTutor/gui.mac");
//#endif
      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    { 
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }



	//  char tmp1[10],tmp2[10];
	if(argv[2]) outfile=argv[2]; else outfile = "ge_hits.root";
	TFile* file = new TFile(outfile,"RECREATE");
  
 	t1->Write();
 	file->Close();  
	
	delete t1;
	delete file;

//   // start a run
//   int numberOfEvent = 10;
//   runManager->BeamOn(numberOfEvent);


// job termination
#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;
  return 0;
}

