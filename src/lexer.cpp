#include <p/lexer.hpp>
#include <iostream>
#include <sstream>
#include <stack>
namespace PL{

Lexer::Lexer(std::istream& stream, int line): stream(stream) , line(line) { 
    do{
        stream.get(c);
    }while(isspace(c));
    stream.putback(c);
}

bool Lexer::next_token(Token& token){
    if(stream.eof()){
        return false;
    }
    stream.get(c);
    if(c == '{'){
        return starts_with_curly_bracket(token);
    }
    if(isspace(c)){
        if(c == '\n'){
            line++;
        }
        return next_token(token);
    }
    if(isdigit(c)){
        stream.putback(c);
        return starts_with_digit(token);    
    }
    if(isalpha(c)){
        stream.putback(c);
        return starts_with_letter(token);
    }
    if(operators.find(c) != std::string::npos){
        token.value = c;
        token.type = TOKEN_TYPE::OPERATOR;
        return true;
    }
    return false;
}

bool Lexer::starts_with_digit(Token& token){
    std::stringstream value;
    int dots = 0;
    while(stream.get(c)){
        if(not isdigit(c) and c != '.'){
            stream.putback(c);
            break;
        }
        if(c == '.'){
            if(dots){
                return false;
            }
            dots++;
        }
        value << c;
    };
    token.value = value.str();
    token.type = TOKEN_TYPE::INT;
    return true;
}

bool Lexer::starts_with_letter(Token& token){
    std::stringstream value;
    while(stream.get(c)){
        if(not isalnum(c) and c != '_' and c != '.'){
            stream.putback(c);
            break;
        }
        value << c;
    };
    token.value = value.str();
    token.type = TOKEN_TYPE::IDENTIFIER;
    return true;
}

bool Lexer::starts_with_curly_bracket(Token& token){
    std::stringstream value;
    value << "{";
    std::stack<char> st;
    st.push('}');
    while(not st.empty() and stream.get(c)){
        if(c == '{'){
            st.push('}');
        }
        else if( c == '}'){
            st.pop();
        }
        value << c;
    }
    token.value =  value.str();
    token.type = TOKEN_TYPE::FUNC;

    return st.empty();
}

}
