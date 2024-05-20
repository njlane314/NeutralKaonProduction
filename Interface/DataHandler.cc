#include "ubana/NeutralKaonProduction/Interface/include/DataHandler.h"
//_________________________________________________________________________________________
namespace ub_neutral_kaons {
//_________________________________________________________________________________________
DataHandler* DataHandler::m_instance = nullptr;
//_________________________________________________________________________________________
DataHandler* DataHandler::Instance() 
{
    if (m_instance == nullptr){
        m_instance = new DataHandler();
    }

    return m_instance;
}
//_________________________________________________________________________________________
DataHandler::~DataHandler() 
{
    if (m_RootFile){
        m_RootFile->Close();
        delete m_RootFile;
    }
}
//_________________________________________________________________________________________
DataHandler::DataHandler(const char* filename)
{
    m_RootFile = new TFile(filename, "RECREATE");

    m_SimTree = new TTree("SimTree", "Simulation");
    m_SimTree->Branch("LeptonicPrimaryParticles", &m_LeptonicPrimaryParticles);
    m_SimTree->Branch("HadronicPrimaryParticles", &m_HadroncPrimaryParticles);
    m_SimTree->Branch("NeutralPrimaryParticles", &m_NeutralPrimaryParticles);
    m_SimTree->Branch("NeutralDecayParticles", &m_NeutralDecayParticles);
}
void DataHandler::FillEvent()
{
    ResetVariables();
    AssignVariables();

    m_SimTree->Fill();
}
//_________________________________________________________________________________________
void DataHandler::ResetVariables()
{
    m_LeptonicPrimaryParticles.clear();
    m_HadroncPrimaryParticles.clear();
    m_NeutralPrimaryParticles.clear();
    m_NeutralDecayParticles.clear();
}
//_________________________________________________________________________________________
void DataHandler::AssignVariables()
{   
    SimulationAnalyser* SimAna = SimulationAnalyser();
    m_LeptonicPrimaryParticles = SimAna.SimInfo.LeptonicPrimaryParticles;
    m_HadroncPrimaryParticles = SimAna.SimInfo.HadronicPrimaryParticles;
    m_NeutralPrimaryParticles = SimAna.SimInfo.NeutralPrimaryParticles;
    m_NeutralDecayParticles = SimAna.SimInfo.NeutralDecayParticles;
}
//_________________________________________________________________________________________
} 