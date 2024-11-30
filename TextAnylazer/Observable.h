#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include <algorithm>
#include "Observer.h"

class Observable {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers(const std::string& message) const;
};

#endif 