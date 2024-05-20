#include "ubana/NeutralKaonProduction/Analyser/Include/SimulationAnalyser.h"
//_________________________________________________________________________________________
namespace ub_neutral_kaons {
//_________________________________________________________________________________________
SimulationAnalyser::SimulationAnalyser(art::Event const& event) :
{
   m_ConfigManager = ConfigManager::GetInstance();

   if(!event.getByLabel(m_ConfigManager.getSimulationLabel(), m_SimHandle));

   art::fill_ptr_vector(m_SimParticles, m_SimHandle);

   for(const art::Ptr<simb::MCParticle> &a_SimParticle : m_SimParticles){
      m_SimParticleMap.insert(std::make_pair(a_SimParticle->TrackId(), a_SimParticle));
   }

   SimulationInformation m_SimInfo; 

   AnalyseEvent();
}
//_________________________________________________________________________________________
void SimulationAnalyser::AnalyseEvent()
{
   CategorisePrimaryParticles();

   HandlePrimaryMuons();
   HandlePrimaryKaonShorts();
}
//_________________________________________________________________________________________
void SimulationAnalyser::CategorisePrimaryParticles()
{
   m_PrimaryParticles.clear();
   m_PimaryPions.clear();
   m_PrimaryMuons.clear();
   m_PrimaryKaonShorts.clear();

   for(const art::Ptr<simb::MCParticle> &a_SimParticle : m_SimParticles){
      if(a_SimParticle->Mother() != 0 || a_SimParticle->PdgCode() > 1000) continue;

      m_PrimaryParticles.push_back(a_SimParticle->TrackId());

      if(isNeutralKaon(a_SimParticle->PdgCode())){
         std::vector<int> temp_Daughters = SimHelper::GetDaughters(a_SimParticle);
         
         if(isKaonShort(m_SimParticleMap[temp_Daughters.at(0)].PdgCode())){
            m_PrimaryKaonShorts.push_back(a_SimParticle->TrackId());
         }
      }
      else if(isMuon(a_SimParticle->PdgCode())){
         m_PrimaryMuons.push_back(a_SimParticle->TrackId());
      }
      else if(isPion(a_SimParticle->PdgCode())){
         m_PrimaryPions.push_back(a_SimParticle->TrackId()); 
      }
   }
}
//_________________________________________________________________________________________
void SimulationAnalyser::HandlePrimaryMuons()
{
   for(int p_id : m_PrimaryMuons){
      if(m_SimParticleMap.find(p_id) == m_SimParticleMap.end()) continue; 

      art::Ptr<simb::MCParticle> a_PrimaryMuon = m_SimParticleMap[p_id];
      SimParticle temp_PrimaryMuon = ConstructSimParticle(a_PrimaryMuon);

      m_SimInfo.LeptonicPrimaryParticles.push_back(temp_PrimaryMuon);
   } 
}
//_________________________________________________________________________________________
void SimulationAnalyser::HandlePrimaryPions()
{
   for(int p_id : m_PrimaryPions){
      if(m_SimParticleMap.find(p_id) == m_SimParticleMap.end()) continue; 

      art::Ptr<simb::MCParticle> a_PrimaryPion = m_SimParticleMap[p_id];
      SimParticle temp_PrimaryPion = ConstructSimParticle(a_PrimaryPion);

      m_SimInfo.HadronicPrimaryParticles.push_back(temp_PrimaryPion);
   } 
}
//_________________________________________________________________________________________
void SimulationAnalyser::HandlePrimaryKaonShorts(){
   for(int ks_id : m_PrimaryKaonShorts){
      if(m_SimParticleMap.find(ks_id) == m_SimParticleMap.end()) continue; 

      art::Ptr<simb::MCParticle> a_KaonShort = m_SimParticleMap[ks_id];
      SimParticle temp_KaonShort = ConstructSimParticle(a_KaonShort);

      std::vector<int> id_Daughters = SimHelper::GetDaughters(a_KaonShort);
      if(id_Daughters.size() == 2) continue;

      int n_ChargedPions = 0;
      int n_NeutralPions = 0;
      std::vector<SimParticle> temp_DaughterVector;
      for(int d_id : id_Daughters){
         if(m_SimParticleMap.find(d_id) == m_SimParticleMap.end()) continue; 

         art::Ptr<simb::MCParticle> a_Daughter = m_SimParticleMap[d_id];
         SimParticle temp_Daughter = ConstructSimParticle(a_Daughter);

         if(isChargedPion(a_Daughter->PdgCode())){
            n_ChargedPions++;
            temp_DaughterVector.push_back(temp_Daughter);
         }
         else if(isNeutralPion(a_Daughter->PdgCode())){
            n_NeutralPions++;
            temp_DaughterVector.push_back(temp_Daughter);
         }

         if(n_ChargedPions != 2 || n_NeutralPions != 2) continue; 

         m_SimInfo.NeutralDecayParticles.insert(m_SimInfo.NeutralDecayParticles.end(), temp_DaughterVector.begin(), temp_DaughterVector.end());
      }

      m_SimInfo.NeutralPrimaryParticles.push_back(temp_KaonShort); 
   }
}
//_________________________________________________________________________________________
}