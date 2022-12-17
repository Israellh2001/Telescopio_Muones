#ifndef PhysicsList_hh
#define PhysicsList_hh

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"

class PhysicsList: public G4VModularPhysicsList{
	public:
		PhysicsList();
		~PhysicsList();
};
#endif
