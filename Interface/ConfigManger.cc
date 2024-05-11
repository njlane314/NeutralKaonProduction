#include "ubana/NeutralKaonProduction/Interface/include/ConfigManager.h"
//_________________________________________________________________________________________
ConfigManager& ConfigManager::Initialise(fhicl::ParameterSet const& p) 
{
    static ConfigManager instance(p);

    return instance;
}
//_________________________________________________________________________________________
ConfigManager& ConfigManager::GetInstance() 
{
    static ConfigManager* instancePtr = nullptr;
    if (!instancePtr) {
        throw std::logic_error("Attempted to use GetInstance() before initialising with Initialise.");
    }
    return *instancePtr;
}
//_________________________________________________________________________________________
ConfigManager::ConfigManager(fhicl::ParameterSet const& p) 
    : m_debug(p.get<bool>("debug", false)) //,
{
    static ConfigManager* instancePtr = this; 
}