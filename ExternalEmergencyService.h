#ifndef EXTERNAL_EMERGENCY_SERVICE_H
#define EXTERNAL_EMERGENCY_SERVICE_H

#include "Types.h"
#include "Incident.h"

class ExternalEmergencyService {
public:
    virtual ~ExternalEmergencyService() {}

    virtual void notifyAgency(const Incident* incident) = 0;
};

#endif //EXTERNAL_EMERGENCY_SERVICE_H
