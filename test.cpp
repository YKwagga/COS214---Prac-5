#include "ExternalEmergencyService.h"
#include "LegacyCityEmergencySystem.h"
#include "LegacyEmergencyAdapter.h"
#include "Incident.h"
#include "Types.h"
#include<iostream>
int main(){
    //So the two types, cool
    IncidentType incidentType = IncidentType::Fire;
    IncidentSeverity severity = IncidentSeverity::High;
    std::cout<<"AHAHAHA, emergency, fire!!"<<std::endl;
    LegacyCityEmergencySystem* system = new LegacyCityEmergencySystem();

    ExternalEmergencyService* service = new LegacyEmergencyAdapter(*system);

    service->notifyAgency(0,incidentType,severity,18,"wee");


}
