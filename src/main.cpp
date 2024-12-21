#include <iostream>
#include <string>
#include <p/core.hpp>
#include <algorithm>
#include <stack>
#include <sstream>
#include <fstream>

bool legal(char c){
    return isalnum(c) or c == '_' or c == '.';
}

bool is_operator(char c){
    return std::string(":=()[]{}+-/%;").find(c) != std::string::npos;
}

bool next_token(std::istream& stream, std::string& out){
    if(stream.peek() == EOF){
        return false;
    }   
    char c;
    std::stringstream token;
    while(legal(stream.peek())){
        stream.get(c);
        token << c;
    }
    if(not token.str().empty()){
        out = token.str();  
    }
    else if(is_operator(stream.peek())){
        stream.get(c);
        token << c;
        out = token.str();
    }
    else if(stream.peek() == ' '){
        stream.get(c);
        return next_token(stream, out);
    }
    return true;
}

bool is_number(const std::string& token){
    return std::all_of(token.begin(), token.end(), [](char c){ return isdigit(c); });
}


bool evaluate(std::string expression, PL::Scope& scope){
    std::stringstream stream(expression);
    std::string token;
    std::stack<std::string> st;
    while(next_token(stream, token)){
        st.push(token);
    }
    std::stack<PL::P> values;
    while(not st.empty()){
        std::string token = st.top();
        st.pop();
        if(token == ":"){
            std::string name = st.top();
            st.pop();
            PL::P value = values.top();
            values.pop();
            scope.set(name, value);
            values.push(value);
        }
        else if(is_number(token)){
            values.push(PL::P(std::stol(token)));
        }
    }

    return true;
}

int main(int argc, char** argv) {
    using namespace PL;
    Scope scope;
    std::string filename = argv[1];
    std::ifstream stream(filename);
    std::string expression;
    Lexer lexer(stream);
    int line = 0;
    while(lexer.next_expression(expression, line)){
        evaluate(expression, scope);
    }

    scope.print();

    return 0;
}
