#pragma once
#include <sstream>
#include <string>
#include <p/scope.hpp>

namespace PL {
class Lexer {
    public:
        Lexer() = default;
        Lexer(std::istream& stream);
        bool next_expression(std::string&, int& line);
    private:
        std::istream& stream;
};

}



