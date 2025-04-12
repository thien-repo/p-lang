#include <p/parser.hpp>
#include <iostream>
#include <sstream>

namespace PL{

Parser::Parser(): stream(std::cin), line(1) {}
Parser::Parser(std::istream& stream, int line): stream(stream) , line(line) { 
    do{
        stream.get(c);
    }while(isspace(c));
    stream.putback(c);
}

bool Parser::next_expression(std::string& out){
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
        if(c == '/' and stream.peek() == '/'){
            do{
                stream.get(c);
            }while(c != '\n');
            expression << ' ';
            line++;
            continue;
        }
        if(c == '\n'){
            line++;
            expression << ' ';
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
    return true;
}
}
