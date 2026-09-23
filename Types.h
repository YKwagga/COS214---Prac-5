#ifndef TYPES_H
#define TYPES_H

#include <string>

enum class ComponentEventType {
    AreaSecured,
    NeedBackup,
    UnitArrived,
    TaskComplete
};

enum class ResponseUnitType{
    Security,
    Medical,
    Access,
    Alert
};

enum class ResponseStatus {
    Available,
    Dispatched,
    OnScene,
    Busy,
    Offline
};

// Incident lifecycle values are separate from the operational state of an
// individual response component.
enum class IncidentType {
    Fire,
    Medical,
    SecurityThreat,
    HazardousSpill
};

enum class IncidentSeverity {
    Low,
    Medium,
    High,
    Critical
};

enum class IncidentAction {
    Dispatch,
    BeginResponse,
    Resolve,
    Cancel
};

enum class IncidentUpdateType {
    Created,
    StateChanged,
    Resolved,
    Cancelled
};

inline const char* toString(IncidentType type) {
    switch (type) {
        case IncidentType::Fire: return "Fire";
        case IncidentType::Medical: return "Medical";
        case IncidentType::SecurityThreat: return "Security threat";
        case IncidentType::HazardousSpill: return "Hazardous spill";
    }
    return "Unknown";
}

inline const char* toString(IncidentSeverity severity) {
    switch (severity) {
        case IncidentSeverity::Low: return "Low";
        case IncidentSeverity::Medium: return "Medium";
        case IncidentSeverity::High: return "High";
        case IncidentSeverity::Critical: return "Critical";
    }
    return "Unknown";
}

inline const char* toString(IncidentAction action) {
    switch (action) {
        case IncidentAction::Dispatch: return "dispatch";
        case IncidentAction::BeginResponse: return "begin response";
        case IncidentAction::Resolve: return "resolve";
        case IncidentAction::Cancel: return "cancel";
    }
    return "perform action";
}

inline const char* toString(ResponseUnitType t) {
    switch (t) {
        case ResponseUnitType::Security: return "Security";
        case ResponseUnitType::Medical:  return "Medical";
        case ResponseUnitType::Alert:    return "Alert";
        case ResponseUnitType::Access:   return "Access";
    }
    return "Unknown";
}

struct ComponentEvent {
    ComponentEventType type;
    std::string message;
    int incidentId;

    ComponentEvent(ComponentEventType t,
                   const std::string& msg,
                   int iid)
        : type(t), message(msg), incidentId(iid) {}
};

#endif
