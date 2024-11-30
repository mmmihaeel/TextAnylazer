#ifndef PUNCTUATION_COUNTER_H
#define PUNCTUATION_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <mutex>

class PunctuationCounter : public Operation {
private:
    int punctuationCount;
    size_t maxTextLength;
    mutable std::mutex mtx;
    TextAnylazerModel& model;

public:
    PunctuationCounter(TextAnylazerModel& model, size_t maxTextLength = 10000);

    void calculate(const std::string& text) override;
    bool validate(const std::string& text) const override;
    void update(const std::string& message) override;

    std::string getResults() const;
    void printResults(std::ostream& out) const override;

    int getPunctuationCount() const;

    void reset();
    void setMaxTextLength(size_t length);
    size_t getMaxTextLength() const;
};

#endif