#ifndef WHITESPACE_COUNTER_H
#define WHITESPACE_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <mutex>
#include <ostream>
#include <cctype>

class WhitespaceCounter : public Operation {
private:
    int whitespaceCount;                
    size_t maxTextLength;                
    mutable std::mutex mtx;          
    TextAnylazerModel& model;        

public:
    WhitespaceCounter(TextAnylazerModel& model, size_t maxTextLength = 10000);

    void calculate(const std::string& text) override;
    void printResults(std::ostream& out) const override;
    bool validate(const std::string& text) const override;

    int getWhitespaceCount() const;

    void update(const std::string& message) override;

    std::string getResults() const;
    void setMaxTextLength(size_t length);
    void reset();
    size_t getMaxTextLength() const;
};

#endif