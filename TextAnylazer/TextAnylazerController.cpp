#include "TextAnylazerController.h"
#include "LetterCounter.h"
#include "DigitCounter.h"
#include "BracketCounter.h"
#include "PunctuationCounter.h"
#include "SpecialSymbolCounter.h"
#include "WhitespaceCounter.h"
#include "WordCounter.h"
#include <fstream>
#include <iostream>
#include <set>
#include <regex>
#include "TextAnylazerView.h"

TextAnylazerController::TextAnylazerController() {
    model.addObserver(&view);

    operations.push_back(std::make_unique<LetterCounter>(model));
    operations.push_back(std::make_unique<DigitCounter>(model));
    operations.push_back(std::make_unique<BracketCounter>(model));
    operations.push_back(std::make_unique<PunctuationCounter>(model));
    operations.push_back(std::make_unique<SpecialSymbolCounter>(model));
    operations.push_back(std::make_unique<WhitespaceCounter>(model));

    std::set<std::string> stopwords = { "and", "the", "of", "to", "a", "in" };
    operations.push_back(std::make_unique<WordCounter>(model, stopwords));
}

void TextAnylazerController::analyze(const std::string& inputFile, const std::string& outputFile) {
    try {
        if (!isTxtFile(inputFile)) {
            throw ValidationException("Input file must have a .txt extension.");
        }

        std::ifstream file(inputFile);
        if (!file.is_open()) {
            throw ValidationException("Could not open input file: " + inputFile);
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        for (const auto& operation : operations) {
            operation->calculate(content);
        }

        if (!isTxtFile(outputFile)) {
            throw ValidationException("Output file must have a .txt extension.");
        }


        std::ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            throw ValidationException("Could not open output file: " + outputFile);
        }

        const auto& results = model.getResults();

        std::cout << "Results:" << std::endl;
        view.displayResults(results, std::cout);
        view.displayResults(results, outFile);

        outFile.close();
    }
    catch (const ValidationException& ex) {
        std::cerr << "Validation Error: " << ex.what() << std::endl;
        throw;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        throw;
    }
}

bool TextAnylazerController::isTxtFile(const std::string& filename) const {
    std::regex txtRegex(R"((.+)\.txt$)", std::regex_constants::icase);
    return std::regex_match(filename, txtRegex);
}