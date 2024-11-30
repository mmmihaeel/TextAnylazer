#include "gtest/gtest.h"
#include "TextAnylazerModel.h"
#include "WordCounter.h"
#include "LetterCounter.h"
#include "BracketCounter.h"
#include "DigitCounter.h"
#include "PunctuationCounter.h"
#include "SpecialSymbolCounter.h"
#include "WhitespaceCounter.h"
#include "ValidationException.h"
#include "TextAnylazerController.h"
#include "TextAnylazerModel.cpp"
#include "WordCounter.cpp"
#include "LetterCounter.cpp"
#include "BracketCounter.cpp"
#include "DigitCounter.cpp"
#include "PunctuationCounter.cpp"
#include "SpecialSymbolCounter.cpp"
#include "WhitespaceCounter.cpp"
#include "ValidationException.cpp"
#include "TextAnylazerController.cpp"
#include "TextAnylazerView.h"
#include "TextAnylazerView.cpp"
#include "Observer.h"
#include "Observable.h"
#include "Observable.cpp"
#include <fstream>
#include <iostream>


class TextAnalyzerTest : public ::testing::Test {
protected:
    TextAnylazerModel model;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(TextAnalyzerTest, WordCounterCountsWordsCorrectly) {
    WordCounter wordCounter(model);
    std::string text = "This is a simple text with seven words.";
    wordCounter.calculate(text);

    EXPECT_EQ(wordCounter.getWordCount(), 8);
}

TEST_F(TextAnalyzerTest, WordCounterWithStopWords) {
    std::set<std::string> stopwords = { "is", "a", "with" };
    WordCounter wordCounter(model, stopwords);
    std::string text = "This is a simple text with seven words.";
    wordCounter.calculate(text);

    EXPECT_EQ(wordCounter.getWordCount(), 5);
}


TEST_F(TextAnalyzerTest, LetterCounterCaseInsensitive) {
    LetterCounter letterCounter(model, true);
    std::string text = "Hello World";
    letterCounter.calculate(text);

    EXPECT_EQ(letterCounter.getLetterCount(), 10);
}

TEST_F(TextAnalyzerTest, LetterCounterCaseSensitive) {
    LetterCounter letterCounter(model, false);
    std::string text = "AaBbCc";
    letterCounter.calculate(text);

    EXPECT_EQ(letterCounter.getLetterCount(), 6);
}

TEST_F(TextAnalyzerTest, BracketCounterCountsCorrectly) {
    BracketCounter bracketCounter(model);
    std::string text = "( [ { } ] )";
    bracketCounter.calculate(text);

    EXPECT_NO_THROW(bracketCounter.validate(text));
}

TEST_F(TextAnalyzerTest, DigitCounterCountsDigits) {
    DigitCounter digitCounter(model);
    std::string text = "12345 and some text 6789";
    digitCounter.calculate(text);

    EXPECT_EQ(digitCounter.getDigitCount(), 9);
}

TEST_F(TextAnalyzerTest, PunctuationCounterCountsCorrectly) {
    PunctuationCounter punctuationCounter(model);
    std::string text = "Hello, world! How are you?";
    punctuationCounter.calculate(text);

    EXPECT_EQ(punctuationCounter.getPunctuationCount(), 3);
}


TEST_F(TextAnalyzerTest, SpecialSymbolCounterCountsCorrectly) {
    SpecialSymbolCounter specialSymbolCounter(model);
    std::string text = "@#$%";
    specialSymbolCounter.calculate(text);

    EXPECT_EQ(specialSymbolCounter.getSpecialSymbolCount(), 4);
}

TEST_F(TextAnalyzerTest, WhitespaceCounterCountsSpaces) {
    WhitespaceCounter whitespaceCounter(model);
    std::string text = "This is a test with spaces.";
    whitespaceCounter.calculate(text);

    EXPECT_EQ(whitespaceCounter.getWhitespaceCount(), 5);
}

TEST(TextAnalyzerStandaloneTest, ValidationExceptionThrown) {
    EXPECT_THROW(
        throw ValidationException("Validation error"),
        ValidationException
    );
}

TEST_F(TextAnalyzerTest, TextAnylazerModelStoresResults) {
    model.addResult("Test result 1");
    model.addResult("Test result 2");

    const auto& results = model.getResults();
    EXPECT_EQ(results.size(), 2);
    EXPECT_EQ(results[0], "Test result 1");
    EXPECT_EQ(results[1], "Test result 2");
}

TEST(TextAnalyzerIntegrationTest, AnalyzeTextFile) {
    TextAnylazerController controller;
    std::string inputFile = "test_input.txt";
    std::string outputFile = "test_output.txt";

    std::ofstream input(inputFile);
    input << "Hello, world! 12345";
    input.close();

    EXPECT_NO_THROW(controller.analyze(inputFile, outputFile));

    std::ifstream output(outputFile);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(output, line)) {
        lines.push_back(line);
    }
    output.close();

    EXPECT_EQ(lines.size(), 14);

    EXPECT_EQ(lines[0], "------------------------------------------");
    EXPECT_EQ(lines[1], "          Text Analysis Results           ");
    EXPECT_EQ(lines[2], "------------------------------------------");
    EXPECT_EQ(lines[3], "| Letters: 10                         |");
    EXPECT_EQ(lines[4], "| Digits: 5                           |");
    EXPECT_EQ(lines[5], "| Round Brackets: 0                   |");
    EXPECT_EQ(lines[6], "| Square Brackets: 0                  |");
    EXPECT_EQ(lines[7], "| Curly Brackets: 0                   |");
    EXPECT_EQ(lines[8], "| Punctuation Marks: 2                |");
    EXPECT_EQ(lines[9], "| Special Symbols: 0                  |");
    EXPECT_EQ(lines[10], "| Whitespace Characters: 2            |");
    EXPECT_EQ(lines[11], "| Word Count: 3                       |");
    EXPECT_EQ(lines[12], "------------------------------------------");
    EXPECT_EQ(lines[13], "[END OF RESULTS]");
}