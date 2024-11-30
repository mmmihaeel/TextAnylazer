#include "BracketCounter.h"

BracketCounter::BracketCounter(TextAnylazerModel& model, size_t maxTextLength)
    : roundBracketCount(0), squareBracketCount(0), curlyBracketCount(0), maxTextLength(maxTextLength), model(model) {}

void BracketCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    roundBracketCount = squareBracketCount = curlyBracketCount = 0;

    for (char ch : text) {
        switch (ch) {
        case '(':
        case ')':
            ++roundBracketCount;
            break;
        case '[':
        case ']':
            ++squareBracketCount;
            break;
        case '{':
        case '}':
            ++curlyBracketCount;
            break;
        default:
            break;
        }
    }

    model.addResult("Round Brackets: " + std::to_string(roundBracketCount));
    model.addResult("Square Brackets: " + std::to_string(squareBracketCount));
    model.addResult("Curly Brackets: " + std::to_string(curlyBracketCount));
}

bool BracketCounter::validate(const std::string& text) const {
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

void BracketCounter::update(const std::string& message) {
    std::cout << "BracketCounter received update: " << message << std::endl;
}

void BracketCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Round Brackets: " << roundBracketCount << "\n"
        << "Square Brackets: " << squareBracketCount << "\n"
        << "Curly Brackets: " << curlyBracketCount << std::endl;
}

void BracketCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    roundBracketCount = squareBracketCount = curlyBracketCount = 0;
}

void BracketCounter::setMaxTextLength(size_t length) {
    std::lock_guard<std::mutex> lock(mtx);
    maxTextLength = length;
}

size_t BracketCounter::getMaxTextLength() const {
    std::lock_guard<std::mutex> lock(mtx);
    return maxTextLength;
}

int BracketCounter::getRoundBracketCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return roundBracketCount;
}

int BracketCounter::getSquareBracketCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return squareBracketCount;
}

int BracketCounter::getCurlyBracketCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return curlyBracketCount;
}