#ifndef LEGACY_CITY_EMERGENCY_SYSTEM_H
#define LEGACY_CITY_EMERGENCY_SYSTEM_H

#include <iostream>

class LegacyCityEmergencySystem {
public:
    void submitEmergencyReport(int cityZoneCode, const std::string details, int priorityCode) {
        std::cout << "[Legacy City System]:" << "\n" <<" Zone = " << cityZoneCode << "\n" << "Priority = " << priorityCode << "\n" << "Details = " << details << std::endl;
        /*Example output:
         * [Legacy City System]
         * Zone =
         * Priority =
         * Details =
         */

    }
};

#endif //LEGACY_CITY_EMERGENCY_SYSTEM_H
