#include "ActionInitializer.hh"

ActionInitializer::ActionInitializer(){}
ActionInitializer::~ActionInitializer(){}

void ActionInitializer::Build() const{
	PrimaryGeneratorAction *generator = new PrimaryGeneratorAction();
	SetUserAction(generator);
 }
