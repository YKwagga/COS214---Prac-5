#ifndef EXTERNAL_EMERGENCY_SERVICE_H
#define EXTERNAL_EMERGENCY_SERVICE_H

#include "Types.h"

class ExternalEmergencyService {
public:
    virtual ~ExternalEmergencyService() {}

    virtual void notifyAgency(int incidentId,
                              IncidentType type,
                              IncidentSeverity severity,
                              int areaId,
                              const char* stateName) = 0;
};

#endif
