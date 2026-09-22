#ifndef LEGACY_EMERGENCY_ADAPTER_H
#define LEGACY_EMERGENCY_ADAPTER_H

#include "ExternalEmergencyService.h"

class LegacyCityEmergencySystem;

class LegacyEmergencyAdapter : public ExternalEmergencyService {
public:
    explicit LegacyEmergencyAdapter(LegacyCityEmergencySystem& legacySystem)
        : legacySystem(legacySystem) {}

    void notifyAgency(int incidentId,
                      IncidentType type,
                      IncidentSeverity severity,
                      int areaId,
                      const char* stateName) override;

private:
    LegacyCityEmergencySystem& legacySystem; // non-owning adaptee
};

#endif
