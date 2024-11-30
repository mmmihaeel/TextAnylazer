#include "WhitespaceCounter.h"

WhitespaceCounter::WhitespaceCounter(TextAnylazerModel& model, size_t maxTextLength)
    : whitespaceCount(0), maxTextLength(maxTextLength), model(model) {}

void WhitespaceCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    whitespaceCount = 0;
    for (char ch : text) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            ++whitespaceCount;
        }
    }

    model.addResult("Whitespace Characters: " + std::to_string(whitespaceCount));
}

void WhitespaceCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Whitespace Characters: " << whitespaceCount << std::endl;
}

bool WhitespaceCounter::validate(const std::string& text) const {
    if (text.empty()) {
        throw ValidationException("Validation failed: Input text is empty.");
    }
    if (text.size() > maxTextLength) {
        throw ValidationException("Validation failed: Input text length exceeds the maximum allowed length (" +
            std::to_string(maxTextLength) + ").");
    }
    return true;
}

void WhitespaceCounter::update(const std::string& message) {
    std::cout << "WhitespaceCounter received update: " << message << std::endl;
}

std::string WhitespaceCounter::getResults() const {
    std::lock_guard<std::mutex> lock(mtx);
    return "Whitespace Characters: " + std::to_string(whitespaceCount);
}

void WhitespaceCounter::setMaxTextLength(size_t length) {
    std::lock_guard<std::mutex> lock(mtx);
    maxTextLength = length;
}

void WhitespaceCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    whitespaceCount = 0;
}

size_t WhitespaceCounter::getMaxTextLength() const {
    std::lock_guard<std::mutex> lock(mtx);
    return maxTextLength;
}

int WhitespaceCounter::getWhitespaceCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return whitespaceCount;
}
