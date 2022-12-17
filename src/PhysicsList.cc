#include "PhysicsList.hh"

PhysicsList::PhysicsList(){
	//Registrar las PhysicsList que se utilizaran
	RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4DecayPhysics());
}

PhysicsList::~PhysicsList(){}
