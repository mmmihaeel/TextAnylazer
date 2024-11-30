#ifndef LETTER_COUNTER_H
#define LETTER_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <mutex>
#include <cctype>

class LetterCounter : public Operation {
private:
    int letterCount;
    bool caseInsensitive;
    size_t maxTextLength;
    mutable std::mutex mtx;
    TextAnylazerModel& model;

public:
    LetterCounter(TextAnylazerModel& model, bool caseInsensitive = true, size_t maxTextLength = 10000);

    void calculate(const std::string& text) override;
    bool validate(const std::string& text) const override;
    void update(const std::string& message) override;

    void printResults(std::ostream& out) const override; 

    int getLetterCount() const;

    std::string getResults() const;
    void setCaseInsensitive(bool value);
    void setMaxTextLength(size_t length);
    void reset();
    bool isCaseInsensitive() const;
    size_t getMaxTextLength() const;
};

#endif