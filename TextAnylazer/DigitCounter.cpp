#include "DigitCounter.h"

DigitCounter::DigitCounter(TextAnylazerModel& model, size_t maxTextLength)
    : digitCount(0), maxTextLength(maxTextLength), model(model) {}

void DigitCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    digitCount = 0;
    for (char ch : text) {
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            ++digitCount;
        }
    }

    model.addResult("Digits: " + std::to_string(digitCount));
}

void DigitCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Digits: " << digitCount << std::endl;
}

bool DigitCounter::validate(const std::string& text) const {
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

void DigitCounter::update(const std::string& message) {
    std::cout << "DigitCounter received update: " << message << std::endl;
}

std::string DigitCounter::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    return "Digits: " + std::to_string(digitCount);
}

void DigitCounter::setMaxTextLength(size_t length) {
    std::lock_guard<std::mutex> lock(mtx);
    maxTextLength = length;
}

void DigitCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    digitCount = 0;
}

size_t DigitCounter::getMaxTextLength() const {
    std::lock_guard<std::mutex> lock(mtx);
    return maxTextLength;
}

int DigitCounter::getDigitCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return digitCount;
}