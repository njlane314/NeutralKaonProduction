#ifndef SIMULATIONANALYSER_H
#define SIMULATIONANALYSER_H

#include <string>
#include <vector>

#include "TVector3.h"

#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "canvas/Persistency/Common/FindMany.h"				
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCNeutrino.h"
#include "cetlib_except/exception.h"

namespace ub_neutral_kaons {

struct SimulationInformation 
{
   double Weight = 1.0;

   std::vector<SimParticle> LeptonicPrimaryParticles;
   std::vector<SimParticle> HadronicPrimaryParticles;

   std::vector<SimParticle> NeutralPrimaryParticles;
   std::vector<SimParticle> NeutralDecayParticles;
};

class SimulationAnalyser {
public:
   SimulationAnalyser::SimulationAnalyser(art::Event const& event)

   SimulationInformation GetSimInfo() { return SimInfo };

private:
   void AnalyseEvent();
   void CategorisePrimaryParticles();
   
   void HandlePrimaryMuons();
   void HanldePrimaryKaonShorts();

   art::Handle<std::vector<simb::MCParticle>> m_SimHandle;
   std::vector<art::Ptr<simb::MCParticle>> m_SimParticles;

   std::map<int, art::Ptr<simb::MCParticle>> m_SimParticleMap;

   std::vector<int> m_PrimaryParticles;
   std::vector<int> m_PrimaryPions;
   std::vector<int> m_PrimaryMuons;
   std::vector<int> m_PrimaryKaonShorts;

   SimulationInformation SimInfo;
};

}

#endif