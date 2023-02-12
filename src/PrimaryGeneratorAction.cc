#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(){
	particlegun = new G4ParticleGun(1);
}
PrimaryGeneratorAction::~PrimaryGeneratorAction(){
	delete particlegun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event){
	
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	G4ParticleDefinition* pMuon = particleTable->FindParticle("mu+");
	G4ParticleDefinition* nMuon = particleTable->FindParticle("mu-");

	int modo = 1;
	switch(modo){
		// Generar un punto aleatorio en el plano de las chambers esto es en 
		// -2.03<x<2.03 y -2.03<y<-2.03
		// Con 4GeV de energía
		case 1:
			G4double y = 2.03*(G4UniformRand()-0.5)/2*m;	
			G4double x = 2.03*(G4UniformRand()-0.5)/2*m;	
			G4ThreeVector pos(x,y,4.06*m);	
			G4ThreeVector mom(0,0,-1);
			
			particlegun -> SetParticlePosition(pos);
			particlegun -> SetParticleMomentumDirection(mom);
			particlegun -> SetParticleMomentum(4*GeV);
			
			if(G4UniformRand()<0.5){particlegun -> SetParticleDefinition(nMuon);}
			else{particlegun -> SetParticleDefinition(pMuon);}

			particlegun -> GeneratePrimaryVertex(event);
			break;

		}

}
