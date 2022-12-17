#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume *DetectorConstruction::Construct(){
	G4NistManager *nist = G4NistManager::Instance();

	//Material de la caja madre
	G4Material *worldMat = nist -> FindOrBuildMaterial("G4_AIR");
	//Meterial de las chambers
	G4Material *chamberMat = nist -> FindOrBuildMaterial("G4_Ar");
	
	//Caja Madre
	G4Box *solidWorld = new G4Box("solidWorld", 1.*m,2.*m,1.*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true);

	return physWorld;	
}
