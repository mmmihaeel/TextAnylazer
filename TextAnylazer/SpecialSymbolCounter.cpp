#include "SpecialSymbolCounter.h"
#include <unordered_set>
#include <cctype>

SpecialSymbolCounter::SpecialSymbolCounter(TextAnylazerModel& model, size_t maxTextLength)
    : specialSymbolCount(0), maxTextLength(maxTextLength), model(model) {}

void SpecialSymbolCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    specialSymbolCount = 0;

    const std::unordered_set<char> specialSymbols = { '@', '#', '$', '%', '^', '&', '*', '~', '<', '>', '|', '\\' };

    for (char ch : text) {
        if (specialSymbols.count(ch)) {
            ++specialSymbolCount;
        }
    }

    model.addResult("Special Symbols: " + std::to_string(specialSymbolCount));
}

void SpecialSymbolCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Special Symbols: " << specialSymbolCount << std::endl;
}

bool SpecialSymbolCounter::validate(const std::string& text) const {
    if (text.empty()) {
        throw ValidationException("Validation failed: Input text is empty.");
    }
    if (text.size() > maxTextLength) {
        throw ValidationException("Validation failed: Input text length exceeds the maximum allowed length (" +
            std::to_string(maxTextLength) + ").");
    }
    if (text.find('\0') != std::string::npos) {
        throw ValidationException("Validation failed: Input text contains null characters.");
    }
    return true;
}

void SpecialSymbolCounter::update(const std::string& message) {
    std::cout << "SpecialSymbolCounter received update: " << message << std::endl;
}

std::string SpecialSymbolCounter::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    return "Special Symbols: " + std::to_string(specialSymbolCount);
}

void SpecialSymbolCounter::setMaxTextLength(size_t length) {
    std::lock_guard<std::mutex> lock(mtx);
    maxTextLength = length;
}

void SpecialSymbolCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    specialSymbolCount = 0;
}

size_t SpecialSymbolCounter::getMaxTextLength() const {
    std::lock_guard<std::mutex> lock(mtx);
    return maxTextLength;
}

int SpecialSymbolCounter::getSpecialSymbolCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return specialSymbolCount;
}