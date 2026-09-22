#ifndef EXTERNAL_AGENCY_NOTIFIER_H
#define EXTERNAL_AGENCY_NOTIFIER_H

#include "IncidentObserver.h"

class ExternalEmergencyService;

class ExternalAgencyNotifier : public IncidentObserver {
public:
    explicit ExternalAgencyNotifier(ExternalEmergencyService* service)
        : service(service) {}

    void update(const Incident& incident,
                IncidentUpdateType updateType) override;

private:
    ExternalEmergencyService* service; // non-owning target interface
};

#endif
