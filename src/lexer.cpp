#include <lexer/lexer.hpp>

namespace PL{
Lexer::Lexer(std::istream& stream) : stream(stream) {}

bool Lexer::next_expression(std::string& out, int& line){
    if(stream.eof()){
        return false;
    }
    std::stringstream expression;
    char c;
    char target = ';';
    while(stream.get(c)){
        if(c == '{'){
            target = '}';
        }
        else if(c == '}'){
            target = ';';
        }
        else if(c == '('){
            target = ')';
        }
        else if(c == ')'){
            target = ';';
        }
        else if(c == '['){
            target = ']';
        }
        else if(c == ']'){
            target = '}';
        }
        if(c == target){
            break;
        }
        if(c == '\n'){
            line++;
            continue;
        }
        if(expression.str().empty() and c == ' '){
            continue;
        }
        expression << c;
    }
    if(expression.str().empty()){
        return false;
    }
    out = expression.str();
    out.erase(std::remove_if(out.begin(), out.end(), [](char c){ return not isprint(c); }), out.end());
    return true;
}
}