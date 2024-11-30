#ifndef DIGIT_COUNTER_H
#define DIGIT_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <mutex>
#include <cctype>
#include <ostream>
#include <iostream>

class DigitCounter : public Operation {
private:
    int digitCount;                 
    size_t maxTextLength;              
    mutable std::mutex mtx;             
    TextAnylazerModel& model;           

public:
    DigitCounter(TextAnylazerModel& model, size_t maxTextLength = 10000);

    void calculate(const std::string& text) override;
    void printResults(std::ostream& out) const override;
    bool validate(const std::string& text) const override;
    void update(const std::string& message) override;

    int getDigitCount() const;

    std::string getResults() const;
    void setMaxTextLength(size_t length);
    void reset();
    size_t getMaxTextLength() const;
};

#endif