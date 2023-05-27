#include "PhysicsList.hh"

PhysicsList::PhysicsList(){
	//Registrar las PhysicsList que se utilizaran
	RegisterPhysics(new G4EmStandardPhysics());
	RegisterPhysics(new G4DecayPhysics());

	RegisterPhysics(new G4HadronElasticPhysicsHP());
	RegisterPhysics(new G4EmLivermorePhysics());
	RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());
	RegisterPhysics(new G4IonBinaryCascadePhysics());
	RegisterPhysics(new G4RadioactiveDecayPhysics());
}

PhysicsList::~PhysicsList(){}
