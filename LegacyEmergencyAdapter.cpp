#include "LegacyEmergencyAdapter.h"
#include "LegacyCityEmergencySystem.h"

#include "Types.h"



//Helper functions:

//Interal helper for zone conversion
 static int cityZoneForArea(int areaId) {
    //Simply converts a single/two-digit code into a postcode
    return 1000 + areaId;
}
//Internal helper for severity
static int priorityForSeverity(IncidentSeverity severity) {
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

static std::string typeToString(IncidentType type){
    switch (type){
        case IncidentType::Fire:
            return "Fire";
            break;
        case IncidentType::Medical:
            return "Medical";
            break;
        case IncidentType::HazardousSpill:
            return "Hazardous Spill";
            break;
        case IncidentType::SecurityThreat:
            return "Security Threat";
            break;
        default:
            return "Unknown";

    }

    return "Unknown";
}


//End of helper functions

void LegacyEmergencyAdapter::notifyAgency(const Incident* incident) {
    std::string details;

    details = "IncidentID: " + std::to_string(incident->getId()) + ", IncidentState: " + incident->getStateName() + ", IncidentType: " + typeToString(incident->getType());

    legacySystem.submitEmergencyReport(cityZoneForArea(incident->getAreaId()),details, priorityForSeverity(incident->getSeverity()));
}
