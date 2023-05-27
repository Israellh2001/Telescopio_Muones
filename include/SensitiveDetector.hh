#ifndef SensitiveDetector_HH
#define SensitiveDetector_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class SensitiveDetector : public G4VSensitiveDetector{
	public:
		SensitiveDetector(G4String);
		~SensitiveDetector();
		virtual G4bool ProcessHits(G4Step* astep, G4TouchableHistory* ROHist);
};
#endif
