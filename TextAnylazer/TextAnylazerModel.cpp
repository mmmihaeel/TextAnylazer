#include "TextAnylazerModel.h"

void TextAnylazerModel::addResult(const std::string& result) {
    std::lock_guard<std::mutex> lock(mtx);
    results.push_back(result);
    notifyObservers("New result added: " + result);
}

const std::vector<std::string>& TextAnylazerModel::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    return results;
}