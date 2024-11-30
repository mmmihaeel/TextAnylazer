#ifndef SPECIAL_SYMBOL_COUNTER_H
#define SPECIAL_SYMBOL_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <mutex>
#include <ostream>
#include <cctype>

class SpecialSymbolCounter : public Operation {
private:
    int specialSymbolCount;          
    size_t maxTextLength;               
    mutable std::mutex mtx;          
    TextAnylazerModel& model;     

public:
    SpecialSymbolCounter(TextAnylazerModel& model, size_t maxTextLength = 10000);

    void calculate(const std::string& text) override;
    void printResults(std::ostream& out) const override;
    bool validate(const std::string& text) const override;

    void update(const std::string& message) override;
        
    int getSpecialSymbolCount() const;

    std::string getResults() const;
    void setMaxTextLength(size_t length);
    void reset();
    size_t getMaxTextLength() const;
};

#endif 