#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <vector>
#include <fhiclcpp/types/Atom.h>
#include <fhiclcpp/types/Sequence.h>
#include <fhiclcpp/ParameterSet.h>

namespace ub_neutral_kaons {

class ConfigManager {
public:
    static ConfigManager& Initialise(fhicl::ParameterSet const& p);
    static ConfigManager& GetInstance();

    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    bool isDebugEnabled() const { return m_debug; }

private:
    ConfigManager(fhicl::ParameterSet const& p);

    static ConfigManager* instancePtr;

    bool m_debug;
};

}

#endif // CONFIGMANAGER_H