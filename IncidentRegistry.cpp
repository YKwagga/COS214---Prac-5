#include "IncidentRegistry.h"

#include <iostream>

Incident& IncidentRegistry::createIncident(IncidentType type,
                                            IncidentSeverity severity,
                                            int areaId) {
    std::unique_ptr<Incident> incident(
        new Incident(nextIncidentId++, type, severity, areaId));
    Incident& created = *incident;
    incidents.push_back(std::move(incident));

    std::cout << "[Registry] Created incident " << created.getId()
              << " (" << toString(type) << ", " << toString(severity)
              << ", area " << areaId << ")\n";
    return created;
}

Incident* IncidentRegistry::findIncident(int incidentId) {
    for (std::vector<std::unique_ptr<Incident> >::iterator it = incidents.begin();
         it != incidents.end(); ++it) {
        if ((*it)->getId() == incidentId) {
            return it->get();
        }
    }
    return nullptr;
}

const Incident* IncidentRegistry::findIncident(int incidentId) const {
    for (std::vector<std::unique_ptr<Incident> >::const_iterator it = incidents.begin();
         it != incidents.end(); ++it) {
        if ((*it)->getId() == incidentId) {
            return it->get();
        }
    }
    return nullptr;
}
