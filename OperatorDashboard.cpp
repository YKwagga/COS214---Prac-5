#include "OperatorDashboard.h"
#include "Incident.h"

#include <iostream>

void OperatorDashboard::update(const Incident& incident,
                               IncidentUpdateType) {
    std::cout << "[Dashboard] Incident " << incident.getId()
              << " | " << toString(incident.getType())
              << " | area " << incident.getAreaId()
              << " | " << toString(incident.getSeverity())
              << " | state: " << incident.getStateName() << "\n";
}
