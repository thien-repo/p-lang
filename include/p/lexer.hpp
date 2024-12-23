#pragma once
#include <istream>

namespace PL{

class Lexer {
    public:
        Lexer();
        Lexer(std::istream& stream, int line);
        bool next_expression(std::string& out);
    private:
        std::istream& stream;
        int line;
        char c;
};

}