#ifndef TEXT_ANALYZER_CONTROLLER_H
#define TEXT_ANALYZER_CONTROLLER_H

#include "TextAnylazerModel.h"
#include "TextAnylazerView.h"
#include "Operation.h"
#include "ValidationException.h"
#include <vector>
#include <memory>
#include <string>

class TextAnylazerController {
private:
    TextAnylazerModel model;
    TextAnylazerView view;
    std::vector<std::unique_ptr<Operation>> operations;

    bool isTxtFile(const std::string& filename) const;

public:
    TextAnylazerController();
    void analyze(const std::string& inputFile, const std::string& outputFile);
};

#endif