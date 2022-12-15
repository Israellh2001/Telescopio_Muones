#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

int main(int argc, char** argv){
	
	# Creamos los objetos principales que usara geant
	G4RunManager *runManager = new G4RunManager();
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	G4VisManager *visManager = new G4VisExecutive();
	G4UImanager *UImanager = G4UImanager::GetUIpointer();

	# Inicializamos los objetos
	visManager -> Initialize();
	ui -> SessionStart();
	runManager -> Initialize();

	return 0;
}
