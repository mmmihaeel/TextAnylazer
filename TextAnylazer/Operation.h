#ifndef OPERATION_H
#define OPERATION_H

#include "Observer.h"
#include <iostream>
#include <string>

class Operation : public Observer {
public:
    virtual ~Operation() = default;
    virtual void calculate(const std::string& text) = 0;
    virtual void printResults(std::ostream& out) const = 0;
    virtual bool validate(const std::string& text) const = 0;
};

#endif