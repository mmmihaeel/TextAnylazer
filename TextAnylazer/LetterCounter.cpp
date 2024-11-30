#include "LetterCounter.h"

LetterCounter::LetterCounter(TextAnylazerModel& model, bool caseInsensitive, size_t maxTextLength)
    : letterCount(0), caseInsensitive(caseInsensitive), maxTextLength(maxTextLength), model(model) {}

void LetterCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    letterCount = 0;
    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            if (caseInsensitive) {
                ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            }
            ++letterCount;
        }
    }

    model.addResult("Letters: " + std::to_string(letterCount));
}

bool LetterCounter::validate(const std::string& text) const {
    if (text.empty()) {
        throw ValidationException("Validation failed: Input text is empty.");
    }
    if (text.size() > maxTextLength) {
        throw ValidationException("Validation failed: Input text length (" +
            std::to_string(text.size()) +
            ") exceeds the maximum allowed length (" +
            std::to_string(maxTextLength) + ").");
    }
    if (text.find('\0') != std::string::npos) {
        throw ValidationException("Validation failed: Input text contains null characters.");
    }
    return true;
}

void LetterCounter::update(const std::string& message) {
    std::cout << "LetterCounter received update: " << message << std::endl;
}

void LetterCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Letters: " << letterCount << std::endl;
}

std::string LetterCounter::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    return "Letters: " + std::to_string(letterCount);
}

void LetterCounter::setCaseInsensitive(bool value) {
    std::lock_guard<std::mutex> lock(mtx);
    caseInsensitive = value;
}

void LetterCounter::setMaxTextLength(size_t length) {
    std::lock_guard<std::mutex> lock(mtx);
    maxTextLength = length;
}

void LetterCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    letterCount = 0;
}

bool LetterCounter::isCaseInsensitive() const {
    std::lock_guard<std::mutex> lock(mtx);
    return caseInsensitive;
}

size_t LetterCounter::getMaxTextLength() const {
    std::lock_guard<std::mutex> lock(mtx);
    return maxTextLength;
}

int LetterCounter::getLetterCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return letterCount;
}