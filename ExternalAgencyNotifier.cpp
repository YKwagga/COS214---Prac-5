#include "ExternalAgencyNotifier.h"
#include "ExternalEmergencyService.h"
#include "Incident.h"

#include <iostream>

void ExternalAgencyNotifier::update(const Incident& incident,
                                    IncidentUpdateType updateType) {
    if (service == nullptr) {
        return;
    }

    const bool shouldEscalate =
        incident.getSeverity() == IncidentSeverity::Critical &&
        (updateType == IncidentUpdateType::StateChanged ||
         updateType == IncidentUpdateType::Resolved);

    if (!shouldEscalate) {
        return;
    }

    std::cout << "[External notifier] Escalating incident "
              << incident.getId() << " to the city agency\n";
    service->notifyAgency(&incident);
}
