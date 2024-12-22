#pragma once
#include <sstream>
#include <string>
#include <p/scope.hpp>

namespace PL {

bool next_token(std::istream& stream, std::string& out);
bool next_expression(std::istream& stream, std::string& out, int& line);

P evaluate(std::string expression, Scope& scope);

}

