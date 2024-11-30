#ifndef TEXT_ANALYZER_VIEW_H
#define TEXT_ANALYZER_VIEW_H

#include "Observer.h"
#include <iostream>
#include <vector>
#include <string>

class TextAnylazerView : public Observer {
public:
    void update(const std::string& message) override;
    void displayResults(const std::vector<std::string>& results, std::ostream& out) const;
};

#endif