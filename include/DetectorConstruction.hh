#ifndef Construction_hh
#define Construction_hh

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"

#include "SensitiveDetector.hh"

class DetectorConstruction : public G4VUserDetectorConstruction{
	
	public:
		//funcion para crear el objeto
		DetectorConstruction();
		//funcion para destruir el objeto
		~DetectorConstruction();

		//Funcion donde ira toda la descripción de la geometria
		virtual G4VPhysicalVolume *Construct();

		void ConstructSDandField();
	private:
		G4LogicalVolume *stripX1Logical;
		G4LogicalVolume *stripY1Logical;
		G4LogicalVolume *stripX2Logical;
		G4LogicalVolume *stripY2Logical;


};
#endif
