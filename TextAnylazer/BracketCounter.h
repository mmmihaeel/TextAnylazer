#ifndef BRACKET_COUNTER_H
#define BRACKET_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <mutex>

class BracketCounter : public Operation {
private:
    int roundBracketCount, squareBracketCount, curlyBracketCount;
    size_t maxTextLength;
    mutable std::mutex mtx;
    TextAnylazerModel& model;

public:
    BracketCounter(TextAnylazerModel& model, size_t maxTextLength = 10000);

    void calculate(const std::string& text) override;
    bool validate(const std::string& text) const override;
    void update(const std::string& message) override;

    void printResults(std::ostream& out) const override;

    int getRoundBracketCount() const;

    int getSquareBracketCount() const;

    int getCurlyBracketCount() const;

    void reset();
    void setMaxTextLength(size_t length);
    size_t getMaxTextLength() const;
};

#endif