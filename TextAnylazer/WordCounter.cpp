#include "WordCounter.h"

WordCounter::WordCounter(TextAnylazerModel& model, const std::set<std::string>& stopwordsList)
    : wordCount(0), stopwords(stopwordsList), model(model) {}

std::string WordCounter::normalizeWord(const std::string& word) const {
    std::string normalized;
    for (char c : word) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return normalized;
}

void WordCounter::calculate(const std::string& text) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!validate(text)) {
        throw ValidationException("Invalid input text: Validation failed.");
    }

    wordCount = 0;
    std::istringstream stream(text);
    std::string word;

    while (stream >> word) {
        word = normalizeWord(word);

        if (!word.empty() && stopwords.find(word) == stopwords.end()) {
            ++wordCount;
        }
    }

    model.addResult("Word Count: " + std::to_string(wordCount));
}

void WordCounter::printResults(std::ostream& out) const {
    std::lock_guard<std::mutex> lock(mtx);
    out << "Word Count: " << wordCount << std::endl;
}

bool WordCounter::validate(const std::string& text) const {
    if (text.empty()) {
        throw ValidationException("Validation failed: Input text is empty.");
    }

    for (char c : text) {
        if (std::iscntrl(static_cast<unsigned char>(c)) &&
            !std::isspace(static_cast<unsigned char>(c))) {
            throw ValidationException("Validation failed: Text contains invalid control characters.");
        }
    }

    return true;
}

void WordCounter::update(const std::string& message) {
    std::cout << "WordCounter received update: " << message << std::endl;
}

int WordCounter::getWordCount() const {
    std::lock_guard<std::mutex> lock(mtx);
    return wordCount;
}

void WordCounter::addStopword(const std::string& stopword) {
    std::lock_guard<std::mutex> lock(mtx);
    stopwords.insert(normalizeWord(stopword));
}

void WordCounter::reset() {
    std::lock_guard<std::mutex> lock(mtx);
    wordCount = 0;
}