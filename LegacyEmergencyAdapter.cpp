#include "LegacyEmergencyAdapter.h"
#include "LegacyCityEmergencySystem.h"

#include <sstream>

namespace {
int cityZoneForArea(int areaId) {
    return 1000 + areaId;
}

int priorityForSeverity(IncidentSeverity severity) {
    switch (severity) {
        case IncidentSeverity::Critical:
            return 1;
            break;
        case IncidentSeverity::High:
            return 2;
            break;
        case IncidentSeverity::Medium:
            return 3;
            break;
        case IncidentSeverity::Low:
            return 4;
            break;
        default:
            return 4;
            break;
    }
    //If it reaches the return something broke
    return -1;
}
}

void LegacyEmergencyAdapter::notifyAgency(int incidentId,
                                          IncidentType type,
                                          IncidentSeverity severity,
                                          int areaId,
                                          const char* stateName) {
    std::ostringstream payload;
    payload << "INC=" << incidentId
            << ";TYPE=" << toString(type)
            << ";STATE=" << stateName;

    legacySystem.submitEmergencyReport(cityZoneForArea(areaId),
                                       payload.str().c_str(),
                                       priorityForSeverity(severity));
}
