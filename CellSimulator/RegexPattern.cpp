#include "RegexPattern.h"

const std::string RegexPattern::Word = R"([a-zA-Z_]+)";
const std::string RegexPattern::Double = R"([+-]?\d+(\.\d+)?)";
const std::string RegexPattern::Vector = R"((\{[+-]?\d+(\.\d+)?(, [+-]?\d+(\.\d+)?)*\}))";
