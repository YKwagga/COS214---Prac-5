#include "Subject.h"
#include "Incident.h"

#include <algorithm>

void Subject::attach(IncidentObserver* observer) {
    if (observer == nullptr) {
        return;
    }

    if (std::find(observers.begin(), observers.end(), observer)
            == observers.end()) {
        observers.push_back(observer);
    }
}

void Subject::detach(IncidentObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer),
                    observers.end());
}

void Subject::notify(const Incident& incident, IncidentUpdateType updateType) {
    // Copying makes an observer safe to detach itself while being updated.
    const std::vector<IncidentObserver*> snapshot = observers;
    for (std::vector<IncidentObserver*>::const_iterator it = snapshot.begin();
         it != snapshot.end(); ++it) {
        if (*it != nullptr) {
            (*it)->update(incident, updateType);
        }
    }
}
