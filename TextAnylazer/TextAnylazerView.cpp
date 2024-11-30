#include "TextAnylazerView.h"
#include <iostream>
#include <iomanip>

void TextAnylazerView::update(const std::string& message) {
    std::cout << "[INFO] View received update: " << message << std::endl;
}

void TextAnylazerView::displayResults(const std::vector<std::string>& results, std::ostream& out) const {
    out << "------------------------------------------" << std::endl;
    out << "          Text Analysis Results           " << std::endl;
    out << "------------------------------------------" << std::endl;

    for (const auto& result : results) {
        out << "| " << std::setw(35) << std::left << result << " |" << std::endl;
    }

    out << "------------------------------------------" << std::endl;
    out << "[END OF RESULTS]" << std::endl;
}