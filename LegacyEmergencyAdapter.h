#ifndef LEGACY_EMERGENCY_ADAPTER_H
#define LEGACY_EMERGENCY_ADAPTER_H

#include "ExternalEmergencyService.h"
#include "Incident.h"

class LegacyCityEmergencySystem;

//Inherits from target/ internal interface
class LegacyEmergencyAdapter : public ExternalEmergencyService {
    private:
        //LegacySystem object
        LegacyCityEmergencySystem& legacySystem;

    public:
        //explicit declaration, won't automaticallly create legacy system
        explicit LegacyEmergencyAdapter(LegacyCityEmergencySystem& legacySystem): legacySystem(legacySystem) {}

        void notifyAgency(const Incident* incident) override;


};

#endif //EXTERNALEMERGENCYADAPTER_H
