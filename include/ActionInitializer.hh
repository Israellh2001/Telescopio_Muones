#ifndef ActionInitializer_HH
#define ActionInitializer_hh

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

class ActionInitializer : public G4VUserActionInitialization{
	
	public:
		ActionInitializer();
		~ActionInitializer();

		virtual	void Build() const;
};
#endif
