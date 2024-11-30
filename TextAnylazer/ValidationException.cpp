#include "ValidationException.h"

ValidationException::ValidationException(const std::string& message)
    : std::runtime_error(message) {}