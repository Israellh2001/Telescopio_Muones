#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : 
G4VSensitiveDetector(name){}
SensitiveDetector::~SensitiveDetector(){}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROHist){
	G4TouchableHistory* touchable =
		(G4TouchableHistory*)(aStep -> GetPreStepPoint() -> GetTouchable());

	if (aStep->GetPreStepPoint()->GetCharge()==0) return true;
	/* if (aStep->GetPreStepPoint()->GetTotalEnergy() < 1000 ) return true; */
	
	G4double energy = aStep->GetPreStepPoint()->GetTotalEnergy();
	G4double carga = aStep->GetPreStepPoint()->GetCharge();

	G4VPhysicalVolume* mother = touchable -> GetVolume(3);
	G4String motherName = mother -> GetName();
	G4ThreeVector posMother = mother -> GetTranslation();

	G4VPhysicalVolume* box = touchable -> GetVolume(2);
	G4String boxName = box -> GetName();
	G4ThreeVector posBox = box -> GetTranslation();

	G4VPhysicalVolume* plane = touchable -> GetVolume(1);
	G4int planeNumber = plane -> GetCopyNo();
	G4String planeName = plane -> GetName();
	G4ThreeVector posPlane = plane -> GetTranslation();

	G4VPhysicalVolume* strip = touchable -> GetVolume();
	G4int stripNumber = strip -> GetCopyNo(); 
	G4String stripName = strip -> GetName();
	G4ThreeVector posStrip = strip -> GetTranslation();
	G4ThreeVector pos = posBox + posPlane + posStrip;

	G4cout << "Un muon toco el plano " << planeName << " No: " << planeNumber << G4endl;
	G4cout << "En el cable " << stripName << " No: " << stripNumber << G4endl;
	G4cout << "Energía: "<< energy << "Carga: " << carga << G4endl;
 
	//G4cout << "Posicion del cable: " << pos << G4endl;

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	G4int evt = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();

	man -> FillNtupleIColumn(0, evt);
	man -> FillNtupleIColumn(1, planeNumber);
	man -> FillNtupleIColumn(2, stripNumber);
	man -> FillNtupleDColumn(3, pos[0]);
	man -> FillNtupleDColumn(4, pos[1]);
	man -> FillNtupleDColumn(5, pos[2]);
	man -> FillNtupleDColumn(6, energy);
	man -> AddNtupleRow(0);

	return true;
}
