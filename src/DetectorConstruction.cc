#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume *DetectorConstruction::Construct(){
	// Nota: La estructura esta basada en el ejemplo de geant GammaRayTelescope y B5

	G4NistManager *nist = G4NistManager::Instance();

	//Material de la caja madre
	G4Material *worldMat = nist -> FindOrBuildMaterial("G4_AIR");
	//Meterial de las chambers
	G4Material *chamberMat = nist -> FindOrBuildMaterial("G4_Ar");
	
	//Variables de dimensiones
	int worldHeight = 2;
	double boxesHeight = 0.5;
	double chamberHeight = boxesHeight*2/3;
	
	//Caja madre
	G4Box *solidWorld = new G4Box("solidWorld", 1.*m,1.*m, worldHeight*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, 
		"physWorld", 0, false, 0, true);
	
	//Primer caja que detecta los muones
	G4Box *firstBox = new G4Box("firstBox",1*m,1*m,boxesHeight*m);
	G4LogicalVolume *firstLogical = new G4LogicalVolume(firstBox, worldMat, "firstLogical"); 
	G4VPhysicalVolume *firstPhysical = new G4PVPlacement(0,G4ThreeVector(0,0,
		(worldHeight-boxesHeight)*m),firstLogical, "firstPhysical", logicWorld, false, 0, true);
	
	//Segunda caja que detecta los muones
	G4Box *secondBox = new G4Box("secondBox", 1*m,1*m,boxesHeight*m);
	G4LogicalVolume *secondLogical = new G4LogicalVolume(secondBox, worldMat, "secondLogical");
	G4VPhysicalVolume *secondSolidPhysical = new G4PVPlacement(0,
		G4ThreeVector(0,0,-1*(worldHeight - boxesHeight)*m), secondLogical,"secondPhysical",
		logicWorld, false, 0, true);

	// Dentro de la primer caja vamos a declarar las driftchambers	
	G4Box *chamberX1Box = new G4Box("chamberX1", 0.5*m, 30*cm, chamberHeight/2*m);
	G4LogicalVolume *chamberX1Logical = new G4LogicalVolume(chamberX1Box, chamberMat, "chamberX1Logical");

	G4Box *chamberY1Box = new G4Box("chamberY1", 0.5*m, 30*cm, chamberHeight/2*m);
	G4LogicalVolume *chamberY1Logical = new G4LogicalVolume(chamberY1Box, chamberMat, "chamberY1Logical");

	G4VPhysicalVolume *chamberX1Physical = new G4PVPlacement(0,
		G4ThreeVector(0,0,(boxesHeight-chamberHeight/2)*m), chamberX1Logical, "chamberX1Physical",
		firstLogical, false, 0, true);

	G4VPhysicalVolume *chamberY1Physical = new G4PVPlacement(0,
		G4ThreeVector(0,0,-1*(boxesHeight-chamberHeight/2)*m), chamberY1Logical, "chamberY1Physical",
		firstLogical, false, 0, true);

	// Dentro de la segunda caja vamos a declarar las driftchambers
	G4Box *chamberX2Box = new G4Box("chamberX1", 0.5*m, 30*cm, chamberHeight/2*m);
	G4LogicalVolume *chamberX2Logical = new G4LogicalVolume(chamberX2Box, chamberMat, "chamberX1Logical");

	G4Box *chamberY2Box = new G4Box("chamberY1", 0.5*m, 30*cm, chamberHeight/2*m);
	G4LogicalVolume *chamberY2Logical = new G4LogicalVolume(chamberY2Box, chamberMat, "chamberY1Logical");

	G4VPhysicalVolume *chamberX2Physical = new G4PVPlacement(0,
		G4ThreeVector(0,0,(boxesHeight-chamberHeight/2)*m), chamberX2Logical, "chamberX1Physical",
		secondLogical, false, 0, true);

	G4VPhysicalVolume *chamberY2Physical = new G4PVPlacement(0,
		G4ThreeVector(0,0,-1*(boxesHeight-chamberHeight/2)*m), chamberY1Logical, "chamberY1Physical",
		secondLogical, false, 0, true);
	return physWorld;	
}
