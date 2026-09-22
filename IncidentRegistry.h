#ifndef INCIDENT_REGISTRY_H
#define INCIDENT_REGISTRY_H

#include "Incident.h"

#include <memory>
#include <vector>

class IncidentRegistry {
public:
    IncidentRegistry() : nextIncidentId(100) {}

    Incident& createIncident(IncidentType type,
                             IncidentSeverity severity,
                             int areaId);
    Incident* findIncident(int incidentId);
    const Incident* findIncident(int incidentId) const;

    const std::vector<std::unique_ptr<Incident> >& allIncidents() const {
        return incidents;
    }

private:
    int nextIncidentId;
    std::vector<std::unique_ptr<Incident> > incidents;
};

#endif
