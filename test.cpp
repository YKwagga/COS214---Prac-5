#include "ExternalEmergencyService.h"
#include "LegacyCityEmergencySystem.h"
#include "LegacyEmergencyAdapter.h"
#include "Types.h"
#include<iostream>

//Managing incidents
#include "Incident.h"
#include "IncidentObserver.h"
#include "EmergencyResponseMediator.h"
#include "IncidentAuditLog.h"
#include "ExternalAgencyNotifier.h"

int main(){
    //So the two types, cool
    IncidentType incidentType = IncidentType::Fire;
    IncidentSeverity severity = IncidentSeverity::High;
    std::cout<<"AHAHAHA, emergency, fire!!"<<std::endl;
    LegacyCityEmergencySystem* system = new LegacyCityEmergencySystem();

    ExternalEmergencyService* service = new LegacyEmergencyAdapter(*system);


    //Incident created
    Incident* incident = new Incident(0,incidentType,severity,18);

    service->notifyAgency(incident);

    //Observer
    IncidentObserver* observer = new EmergencyResponseMediator();
    IncidentObserver* audit = new IncidentAuditLog();

    //Finally for the external agency
    IncidentObserver* external = new ExternalAgencyNotifier(service);

    incident->attach(observer);
    incident->attach(audit);
    incident->attach(external);


    incident->request(IncidentAction::Dispatch);
    incident->detach(audit);
    incident->request(IncidentAction::BeginResponse);


    //deletes pointers
    delete system;
    delete service;
    delete incident;
    delete observer;
    delete audit;
    delete external;






}
