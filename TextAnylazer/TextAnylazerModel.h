#ifndef TEXT_ANALYZER_MODEL_H
#define TEXT_ANALYZER_MODEL_H

#include "Observable.h"
#include <string>
#include <vector>
#include <mutex>

class TextAnylazerModel : public Observable {
private:
    mutable std::mutex mtx;
    std::vector<std::string> results;

public:
    void addResult(const std::string& result);
    const std::vector<std::string>& getResults() const;
};

#endif