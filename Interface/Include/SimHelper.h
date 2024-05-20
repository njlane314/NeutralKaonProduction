#ifndef SIMHELPER_H
#define SIMHELPER_H

#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/SubRun.h"

namespace ub_neutral_kaons {

class SimHelper {
public:
    std::vector<int> getDaughters(art::MCParticle const& aParticle);


};

} 

#endif // SIMHELPER_H
