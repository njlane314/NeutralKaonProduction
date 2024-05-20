#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/SubRun.h"

namespace ub_neutral_kaons {

class DataHandler {
public:
    static DataHandler* Instance();
    ~DataHandler();

    DataHandler(const DataHandler&) = delete;
    DataHandler& operator=(const DataHandler&) = delete;

    void Reset(); 

private:
    DataHandler(const char* filename = "output.root");

    static DataHandler* m_instance;

    TFile* m_RootFile;
    TTree* m_SimTree;

    std::vector<SimParticle> m_SimPrimaryLeptons, m_SimPrimaryHadrons, m_SimPrimaryNeutrals, m_SimNeutralDecays;
};

} 

#endif // DATAHANDLER_H
