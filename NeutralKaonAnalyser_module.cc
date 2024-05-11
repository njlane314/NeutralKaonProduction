#include "NeutralKaonAnalyser.h"
//_________________________________________________________________________________________
ub_neutral_kaons::NeutralKaonAnalyser::NeutralKaonAnalyser(fhicl::ParameterSet const& p)
   : EDAnalyzer{p},
   m_config(ConfigManager::Initialize(p)) //,
   //m_dataHandler(std::make_unique<DataHandler>())
{}
//_________________________________________________________________________________________
void ub_neutral_kaons::NeutralKaonAnalyser::analyze(art::Event const& e)
{
   if(m_config->isDebugEnabled()) std::cout << "Assigning event..." << std::endl;

   //m_dataHandler->assignEvent();
}
//_________________________________________________________________________________________
void ub_neutral_kaons::NeutralKaonAnalyser::beginJob()
{
   if(m_config->isDebugEnabled()) std::cout << "Beginning job..." << std::endl;

   //m_dataHandler->setupTrees();

   if(m_config->isDebugEnabled()) std::cout << "Finished begin job!" << std::endl;
}
//_________________________________________________________________________________________
void ub_neutral_kaons::NeutralKaonAnalyser::endJob()
{
   //m_dataHandler->fillMetaData();
}
//_________________________________________________________________________________________
void ub_neutral_kaons::NeutralKaonAnalyser::FinishEvent()
{
   if(m_config->isDebugEnabled()) std::cout << "Finishing event..." << std::endl;

   //m_dataHandler->fillEvent();

   if(m_config->isDebugEnabled()) std::cout << "Finished event!" << std::endl;
}	
//_________________________________________________________________________________________
void ub_neutral_kaons::NeutralKaonAnalyser::beginSubRun(const art::SubRun& sr)
{
   if(m_config->isDebugEnabled()) std::cout << "Getting subrun POT information..." << std::endl;

   //m_dataHandler->accumulatePOT();
}
//_________________________________________________________________________________________
void ub_neutral_kaons::NeutralKaonAnalyser::endSubRun(const art::SubRun& sr)
{}
//_________________________________________________________________________________________
DEFINE_ART_MODULE(ub_neutral_kaons::NeutralKaonAnalyser)