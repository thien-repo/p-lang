#pragma once
#include <istream>

namespace PL{
enum TOKEN_TYPE {
    IDENTIFIER,
    INT,
    DECIMAL,
    BOOL,
    OPERATOR,
};

const std::string TOKEN_STRINGS[] = {
    "IDENTIFIER",
    "INT",
    "DECIMAL",
    "BOOL",
    "OPERATOR",
};

struct Token {
    std::string value;
    TOKEN_TYPE type;
};

class Tokenizer {
    public:
        Tokenizer() = delete;
        Tokenizer(std::istream& stream, int line);
        bool next_token(Token& token);
    private:
        std::string operators = ":+-*/%=";
        std::istream& stream;
        int line;
        char c;
        bool starts_with_digit(Token& token);
        bool starts_with_letter(Token& token);
};

}