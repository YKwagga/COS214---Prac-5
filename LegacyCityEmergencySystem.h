#ifndef LEGACY_CITY_EMERGENCY_SYSTEM_H
#define LEGACY_CITY_EMERGENCY_SYSTEM_H

#include <iostream>

// Represents an incompatible external API. CampusGuard should not expose this
// C-style signature to its internal services.
class LegacyCityEmergencySystem {
public:
    void submitEmergencyReport(int cityZoneCode,
                               const char* rawPayload,
                               int priorityCode) {
        std::cout << "[Legacy City System] zone=" << cityZoneCode
                  << ", priority=" << priorityCode
                  << ", payload=" << rawPayload << "\n";
    }
};

#endif
