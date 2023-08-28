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
	//Plomo
	G4Material *lead = nist-> FindOrBuildMaterial("G4_Pb");
	
	//Variables de dimensiones
	//Recordar que las dimensiones finales en realidad son el doble de que se indica aquí
	double worldHeight = 4.06;
	double worldWidth = 1;
	double sampleGap = 1;
	double boxesHeight = (worldHeight - sampleGap)/2;
	double boxesWidth = worldWidth;
	double chamberWidth = (worldWidth+0.3)/2;
	double chamberHeight = 0.005;
	double extra = 0;


	//Caja madre
	G4Box *solidWorld = new G4Box("solidWorld", worldWidth*m, worldWidth*m, worldHeight*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, 
		"physWorld", 0, false, 0, true);
	
	//Primer caja que detecta los muones
	G4Box *firstBox = new G4Box("firstBox",boxesWidth*m, boxesWidth*m, boxesHeight*m);
	G4LogicalVolume *firstLogical = new G4LogicalVolume(firstBox, worldMat, "firstLogical"); 
        new G4PVPlacement(0,G4ThreeVector(0,0,
		(worldHeight-boxesHeight)*m),firstLogical, "firstPhysical", logicWorld, false, 0, true);
	
	//Segunda caja que detecta los muones
	G4Box *secondBox = new G4Box("secondBox", boxesWidth*m, boxesWidth*m, boxesHeight*m);
	G4LogicalVolume *secondLogical = new G4LogicalVolume(secondBox, worldMat, "secondLogical");
	new G4PVPlacement(0,
		G4ThreeVector(0,0,-1*(worldHeight - boxesHeight)*m), secondLogical,"secondPhysical",
		logicWorld, false, 0, true);

	// Dentro de la primer caja vamos a declarar las driftchambers	
	G4Box *chamberX1Box = new G4Box("chamberX1", chamberWidth*m, chamberWidth*m, chamberHeight*m);
	G4LogicalVolume *chamberX1Logical = new G4LogicalVolume(chamberX1Box, chamberMat, "chamberX1Logical");

	G4Box *chamberY1Box = new G4Box("chamberY1", chamberWidth*m, chamberWidth*m, chamberHeight*m);
	G4LogicalVolume *chamberY1Logical = new G4LogicalVolume(chamberY1Box, chamberMat, "chamberY1Logical");
	
	//For para colocar las tres chambers que iran antes de la muestra
	for(int i = 1; i<=3; i++){ 
		new G4PVPlacement(0,
			G4ThreeVector(0,0,(boxesHeight - i*(1 + chamberHeight))*m), chamberX1Logical, "chamberX1Physical",
			firstLogical, false, 10+i, true);

		new G4PVPlacement(0,
			G4ThreeVector(0,0,(boxesHeight - i*(1 + 3*chamberHeight))*m), chamberY1Logical, "chamberY1Physical",
			firstLogical, false, 10+i, true);
	}

	// Dentro de la segunda caja vamos a declarar las driftchambers
	G4Box *chamberX2Box = new G4Box("chamberX2",(chamberWidth+extra)*m, (chamberWidth+extra)*m, chamberHeight*m);
	G4LogicalVolume *chamberX2Logical = new G4LogicalVolume(chamberX2Box, chamberMat, "chamberX2Logical");

	G4Box *chamberY2Box = new G4Box("chamberY2", (chamberWidth+extra)*m, (chamberWidth+extra)*m, chamberHeight*m);
	G4LogicalVolume *chamberY2Logical = new G4LogicalVolume(chamberY2Box, chamberMat, "chamberY2Logical");

	//For para colocar las tres chambers que iran despues de la muestra
	for(int i = 0; i<3; i++){ 
		new G4PVPlacement(0,
			G4ThreeVector(0,0,(boxesHeight - (i + (i+0.5)*chamberHeight))*m), chamberX2Logical, "chamberX2Physical",
			secondLogical, false,20+i, true);

		new G4PVPlacement(0,
			G4ThreeVector(0,0,(boxesHeight - (i + 3*(i+0.5)*chamberHeight))*m), chamberY2Logical, "chamberY2Physical",
			secondLogical, false, 20+i, true);
	}
	
	//For para colocar las strip en cada primer grupo de chambers
	double stripWidth = 0.005;
	double stripHeight = chamberHeight/100;
	double pitch = 0.0;
	int N = int( chamberWidth/(stripWidth+pitch)); 

	G4Box *stripY1Box = new G4Box("stripY1Box", stripWidth*m, chamberWidth*m, stripHeight*m);
	stripY1Logical = new G4LogicalVolume(stripY1Box, chamberMat, "stripY1Logical");

	G4Box *stripX1Box = new G4Box("stripX1Box", chamberWidth*m, stripWidth*m, stripHeight*m);
	stripX1Logical = new G4LogicalVolume(stripX1Box, chamberMat, "stripX1Logical");

	for(int i = 0; i<N; i++){
		new G4PVPlacement(0,
			G4ThreeVector(((pitch + stripWidth)*(2*i+1) - (chamberWidth+extra))*m,0,0), stripY1Logical, "stripY1Physical",
			chamberY1Logical, false, 20000+i, true);

		new G4PVPlacement(0,
                          G4ThreeVector(0,((pitch + stripWidth)*(2*i+1) - chamberWidth)*m,0), stripX1Logical, "stripX1Physical",
                          chamberX1Logical, false, 10000+i, true);
	}

	//For para colocar las strip en cada segundo grupo de chambers
	N = int( (chamberWidth+extra)/(stripWidth+pitch)); 

	G4Box *stripY2Box = new G4Box("stripY2Box", stripWidth*m, (chamberWidth)*m, (stripHeight)*m);
	stripY2Logical = new G4LogicalVolume(stripY2Box, chamberMat, "stripY2Logical");

        G4Box *stripX2Box = new G4Box("stripX2Box", (chamberWidth)*m, stripWidth*m, (stripHeight)*m);
        stripX2Logical = new G4LogicalVolume(stripX2Box, chamberMat, "stripX2Logical");
 
        for(int i = 0; i<N; i++){
		new G4PVPlacement(0,
			G4ThreeVector(((pitch + stripWidth)*(2*i+1) - (chamberWidth+extra))*m,0,0), stripY2Logical, "stripY2Physical",
			chamberY2Logical, false, 40000+i, true);
    
                new G4PVPlacement(0,
			G4ThreeVector(0,((pitch + stripWidth)*(2*i+1) - (chamberWidth+extra))*m,0), stripX2Logical, "stripX2Physical",
			chamberX2Logical, false, 30000+i, true);
        }

	//Colocar prueba de Plomo
	G4Box *leadBox = new G4Box("leadBox", 0.5*m, 0.5*m, 0.5*m);
	G4LogicalVolume *leadLogical = new G4LogicalVolume(leadBox, lead, "leadLogical");
	new G4PVPlacement(0,
		G4ThreeVector(0,0,0), leadLogical, "leadPhysical", logicWorld, false, 0, true);

	return physWorld;	
}

void DetectorConstruction::ConstructSDandField(){
	SensitiveDetector* SD1 = new SensitiveDetector("SD1");
	SensitiveDetector* SD2 = new SensitiveDetector("SD2");
	SensitiveDetector* SD3 = new SensitiveDetector("SD3");
	SensitiveDetector* SD4 = new SensitiveDetector("SD4");
	
	stripX1Logical -> SetSensitiveDetector(SD1);
	stripY1Logical -> SetSensitiveDetector(SD2);
	stripX2Logical -> SetSensitiveDetector(SD3);
	stripY2Logical -> SetSensitiveDetector(SD4);
}
