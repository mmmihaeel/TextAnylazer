#include "PunctuationCounter.h"
#include <cctype>
#include <string>
#include <unordered_set>

PunctuationCounter::PunctuationCounter(TextAnylazerModel& model, size_t maxTextLength)
    : punctuationCount(0), maxTextLength(maxTextLength), model(model) {}

void PunctuationCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    punctuationCount = 0;

    const std::unordered_set<char> validPunctuation = { '.', ',', ';', ':', '!', '?', '\'', '\"', '-' };

    for (char ch : text) {
        if (validPunctuation.count(ch)) {
            ++punctuationCount;
        }
    }

    model.addResult("Punctuation Marks: " + std::to_string(punctuationCount));
}

bool PunctuationCounter::validate(const std::string& text) const {
    if (text.empty()) {
        throw ValidationException("Input text is empty.");
    }

    if (text.size() > maxTextLength) {
        throw ValidationException("Input text exceeds maximum allowed length.");
    }

    if (text.find('\0') != std::string::npos) {
        throw ValidationException("Input text contains null characters.");
    }

    return true;
}

void PunctuationCounter::update(const std::string& message) {
    std::cout << "PunctuationCounter received update: " << message << std::endl;
}

void PunctuationCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Punctuation Marks: " << punctuationCount << std::endl;
}

std::string PunctuationCounter::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    return "Punctuation Marks: " + std::to_string(punctuationCount);
}

void PunctuationCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    punctuationCount = 0;
}

void PunctuationCounter::setMaxTextLength(size_t length) {
    std::lock_guard<std::mutex> lock(mtx);
    maxTextLength = length;
}

size_t PunctuationCounter::getMaxTextLength() const {
    std::lock_guard<std::mutex> lock(mtx);
    return maxTextLength;
}

int PunctuationCounter::getPunctuationCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return punctuationCount;
}