#ifndef WORD_COUNTER_H
#define WORD_COUNTER_H

#include "Operation.h"
#include "ValidationException.h"
#include "TextAnylazerModel.h"
#include <string>
#include <set>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <ostream>
#include <algorithm>
#include <mutex>

class WordCounter : public Operation {
private:
    int wordCount;                      
    std::set<std::string> stopwords;   
    mutable std::mutex mtx;                
    TextAnylazerModel& model;        

    std::string normalizeWord(const std::string& word) const;

public:
    WordCounter(TextAnylazerModel& model, const std::set<std::string>& stopwordsList = {});

    void calculate(const std::string& text) override;
    void printResults(std::ostream& out) const override;
    bool validate(const std::string& text) const override;

    void update(const std::string& message) override;

    int getWordCount() const;
    void addStopword(const std::string& stopword);
    void reset();
};

#endif 