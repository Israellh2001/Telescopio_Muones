#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

class PhysicsList: public G4VModularPhysicsList{
	public:
		PhysicsList();
		~PhysicsList();
};
#endif
