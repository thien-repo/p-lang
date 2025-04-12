#pragma once
#include <istream>

namespace PL{
enum TOKEN_TYPE {
    IDENTIFIER,
    INT,
    DECIMAL,
    BOOL,
    OPERATOR,
    FUNC
};

const std::string TOKEN_STRINGS[] = {
    "IDENTIFIER",
    "INT",
    "DECIMAL",
    "BOOL",
    "OPERATOR",
    "FUNC"
};

struct Token {
    std::string value;
    TOKEN_TYPE type;
};

class Lexer {
    public:
        Lexer() = delete;
        Lexer(std::istream& stream, int line);
        bool next_token(Token& token);
    private:
        std::string operators = ":+-*/%=";
        std::istream& stream;
        int line;
        char c;
        bool starts_with_digit(Token&);
        bool starts_with_curly_bracket(Token&);
        bool starts_with_letter(Token&);
};

}
