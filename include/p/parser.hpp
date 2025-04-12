#pragma once
#include <istream>

namespace PL{

class Parser {
    public:
        Parser();
        Parser(std::istream& stream, int line);
        bool next_expression(std::string& out);
    private:
        std::istream& stream;
        int line;
        char c;
};

}
