#include <p/utils.hpp>
#include <p/variable.hpp>
#include <p/standard.hpp>
#include <stack>
#include <algorithm>
#include <iostream>

namespace PL{

bool next_expression(std::istream& stream, std::string& out, int& line){
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
    out.erase(std::remove_if(out.begin(), out.end(), [](char c){ return not isprint(c); }), out.end());
    return true;
}

static bool legal(char c){
    return isalnum(c) or c == '_' or c == '.';
}

static bool is_operator(char c){
    return std::string(":=()[]{}+-/*%;,").find(c) != std::string::npos;
}


static bool is_int(const std::string& token){
    if(not isdigit(token.front()) and token.front() != '-'){
        return false;
    }
    return std::all_of(token.begin() + 1, token.end(), [](char c){ return isdigit(c); });
}


static bool is_string(const std::string& token){
    return token.front() == '\"' and token.back() == '\"';
}


bool next_token(std::istream& stream, std::string& out){
    if(stream.peek() == EOF){
        return false;
    }   
    char c;
    while (stream.peek() == ' ' or stream.peek() == '\t'){
        stream.get(c);
    }
    
    std::stringstream token;
    while(legal(stream.peek())){
        stream.get(c);
        token << c;
    }
    if(not token.str().empty()){
        out = token.str();
        return true;  
    }
    if(stream.peek() == '\"'){
        stream.get(c);
        token << c;
        do{
            stream.get(c);
            token << c;
        }while(c != '\"');
        out = token.str();
        return true;
    }

    else if(is_operator(stream.peek())){
        stream.get(c);
        token << c;
        out = token.str();
        if(c == '-' and isdigit(stream.peek())){
            do{
                stream.get(c);
                token << c;
            }while(isdigit(stream.peek()));
            out = token.str();
            return true;
        }
    }
    return true;
}

static std::unordered_map<std::string, std::function<P(P,P)>> operators = {
    {"+", [](P a,P b) ->P { return {pi(a) + pi(b)}; }},
    {"-", [](P a,P b) ->P { return {pi(a) - pi(b)}; }},
    {"*", [](P a,P b) ->P { return {pi(a) * pi(b)}; }},
    {"/", [](P a,P b) ->P { return {pi(a) / pi(b)}; }},
    {"%", [](P a,P b) ->P { return {pi(a) % pi(b)}; }},
};

P evaluate(std::string expression, Scope& scope){
    std::stringstream stream(expression);
    std::string token;
    std::stack<std::string> st;
    while(next_token(stream, token)){
        st.push(token);
    }
    std::stack<P> values;
    while(not st.empty()){
        std::string token = st.top();
        st.pop();
        if(scope.exists(token)){
            if(token == "console"){
               P value = values.top();
                values.pop();
               console(value);
                continue;
            }
            if(token == "system"){
               P value = values.top();
                values.pop();
                std::string command =ps(value);
                FILE* pipe = popen(command.c_str(), "r");
                if(not pipe){
                    values.push(error("Failed to execute command"));
                    continue;
                }
                std::stringstream ss;
                char buffer[128];
                while(fgets(buffer, 128, pipe)){
                    ss << buffer;
                }
                values.push(P(ss.str()));
                pclose(pipe);
                
                continue;
            }
            values.push(scope.get(token));
        }
        else if(token == ":"){
            std::string name = st.top();
            st.pop();
           P value = values.top();
            values.pop();
            scope.set(name, value);
            values.push(value);
        }
        else if(operators.find(token) != operators.end()){
            std::string stop = st.top();
            st.pop();
            P right = values.top();
            values.pop();
            P left = scope.exists(stop) ? scope.get(stop) : P(std::stol(stop));
            
            values.push(operators[token](left, right));
        }
        else if(is_int(token)){
            values.push(P(std::stol(token)));
        }
        else if(is_string(token)){
            std::string str = token.substr(1, token.size() - 2);
            values.push(P(str));
        }
        else{
            return error("Unknown token: " + token);
        }
    }

    return P(0);
}




}