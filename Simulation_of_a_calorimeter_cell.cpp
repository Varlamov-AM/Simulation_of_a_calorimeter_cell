#include "Geometry.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "ROOTWriter.hh"
#include "G4RunManager.hh"
#include "G4OpticalPhysics.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "FTFP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeneralParticleSource.hh"

int main(int argc, char** argv){

    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::MTwistEngine);

    // G4UIExecutive* ui = nullptr;
    // if (argc == 2) {
    //     G4cout << argv[1] << "\n";
    //     ui = new G4UIExecutive(argc, argv);
    // }


    // return 0;
    // Construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    // Detector construction
    runManager->SetUserInitialization(new Geometry());

    // Physics list
    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    physicsList->SetVerboseLevel(1);
    physicsList->RegisterPhysics(new G4OpticalPhysics);
    runManager->SetUserInitialization(physicsList);

    G4int     particle_PDG;
    G4double  particle_Energy;

    // Initialize ROOT
    ROOTWriter::GetPointer()->Initialize();

    runManager->Initialize();

    G4int n_entries = ROOTWriter::GetPointer()->Get_tree_entries();
    G4int n_event_to_simulate = 1;
    G4cout << n_entries << "\n";

    for (int i = 0; i < n_entries; ++i){
        ROOTWriter::GetPointer()->Get_tree_entry(i);
        n_event_to_simulate += ROOTWriter::GetPointer()->Get_event_size();
    }

    ROOTWriter::GetPointer()->Set_event_counter(0);

    G4cout << n_event_to_simulate << "\n";

    if (argc == 3){
        particle_PDG    = atoi(argv[2]);
        G4cout << "Particle_PDG = " << particle_PDG << G4endl;
        // runManager->SetUserAction(new PrimaryGeneratorAction(particle_PDG));
    } else if (argc == 4){
        particle_PDG    = atoi(argv[2]);
        G4cout << "Particle_PDG = " << particle_PDG << G4endl;
        particle_Energy = atof(argv[3]) * GeV;
        G4cout <<
            "Particle Energy = " << particle_Energy << " MeV\n" << G4endl;
        // runManager->SetUserAction(new PrimaryGeneratorAction(particle_PDG,
        //                                                     particle_Energy));
    } else if (argc == 2){
        particle_PDG = 11;
        particle_Energy = 500 * MeV;
        // runManager->SetUserAction(new PrimaryGeneratorAction(particle_PDG,
        //                                                         particle_Energy));
    } else {
        runManager->SetUserAction(new PrimaryGeneratorAction());
    }

    // User action initialization
    runManager->SetUserAction(new EventAction());
    runManager->SetUserAction(new SteppingAction());

    // Initialize G4 kernel
    //

    #ifdef G4VIS_USE
        // Initialize visualization
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
    #endif

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc!=1) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
        // interactive mode : define UI session
    #ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    #ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute init_vis.mac"); 
    #else
        UImanager->ApplyCommand("/control/execute init.mac"); 
    #endif
        ui->SessionStart();
        delete ui;
    #endif
    }

    #ifdef G4VIS_USE
        // Initialize visualization
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
    #endif

    // Get the pointer to the User Interface manager
    // G4UImanager* UImanager = G4UImanager::GetUIp ointer();

    if (argc != 1) {
        // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    } else {
        G4String command = "/run/beamOn ";
        // UImanager->ApplyCommand("/random/setSeeds 12365 1");
        // UImanager->ApplyCommand("/event/verbose 2");
        // UImanager->ApplyCommand("/tracking/verbose 1");
        UImanager->ApplyCommand(command+G4String(Form("%d", n_event_to_simulate)));
    }
  
    ROOTWriter::GetPointer()->Finalize();

    G4cout << "END OF PROGRAM!" << G4endl;

    #ifdef G4VIS_USE
        delete visManager;
    #endif
        delete runManager;  

    return 0;
}
