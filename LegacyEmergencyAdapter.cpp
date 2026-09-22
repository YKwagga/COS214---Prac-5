#include "LegacyEmergencyAdapter.h"
#include "LegacyCityEmergencySystem.h"

#include <sstream>

namespace {
int cityZoneForArea(int areaId) {
    return 1000 + areaId;
}

int priorityForSeverity(IncidentSeverity severity) {
    switch (severity) {
        case IncidentSeverity::Critical: return 1;
        case IncidentSeverity::High: return 2;
        case IncidentSeverity::Medium: return 3;
        case IncidentSeverity::Low: return 4;
    }
    return 4;
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
