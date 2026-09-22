#ifndef SUBJECT_H
#define SUBJECT_H

#include "IncidentObserver.h"
#include <vector>

class Incident;

class Subject {
public:
    virtual ~Subject() {}

    void attach(IncidentObserver* observer);
    void detach(IncidentObserver* observer);

protected:
    void notify(const Incident& incident, IncidentUpdateType updateType);

private:
    // Observers are shared, long-lived collaborators; Subject does not own
    // them. They must detach before their destruction.
    std::vector<IncidentObserver*> observers;
};

#endif
