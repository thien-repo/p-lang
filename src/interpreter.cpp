#include <p/interpreter.hpp>
#include <iostream>
#include <sstream>
#include <p/standard.hpp>

namespace PL{

const std::vector<std::string> keywords = {
    "console", "system",
};

P system_call(P value){
    std::string command = ps(value);
    FILE* pipe = popen(command.c_str(), "r");
    if(pipe == nullptr){
        return error("Error executing command: " + command);
    }
    std::stringstream ss;
    char buffer[128];
    while(fgets(buffer, 128, pipe)){
        ss << buffer;
    }
    std::string line;
    std::vector<P> lines;
    while(std::getline(ss, line)){
        lines.push_back(P(line));
    }
    return P(lines);
}

P Interpreter::interpret(std::stack<Token>& tokens){
            while(not tokens.empty()){
                Token token = tokens.top();
                tokens.pop();
                if(token.type == TOKEN_TYPE::INT){
                    values.push(P(std::stol(token.value)));
                }
                if(token.type == TOKEN_TYPE::DECIMAL){
                    values.push(P(std::stod(token.value)));
                }
                if(token.type == TOKEN_TYPE::BOOL){
                    values.push(P(token.value == "1b"));
                }
                if(token.type == TOKEN_TYPE::OPERATOR){
                    if(token.value == ":"){
                        if(tokens.empty()){
                            return error("Unexpected end of expression");
                        }
                        Token name = tokens.top();
                        tokens.pop();
                        if(name.type != TOKEN_TYPE::IDENTIFIER){
                            return error("Expected identifier, got " + TOKEN_STRINGS[name.type]);
                        }
                        if(std::find(keywords.begin(), keywords.end(), name.value) != keywords.end()){
                            return error("Invalid variable name: " + name.value);
                        }
                        if(values.empty()){
                            return error("Unexpected end of expression");
                        }
                        P value = values.top();
                        values.pop();
                        scope->set(name.value, value);
                    }
                    if(token.value == "+" or token.value == "-" or token.value == "*" or token.value == "/" or token.value == "%"){
                        if(tokens.empty()){
                            return error("not enough values for operation " + token.value);
                        }
                        Token l = tokens.top();
                        tokens.pop();
                        P left;
                        if(l.type != TOKEN_TYPE::INT and l.type != TOKEN_TYPE::DECIMAL){
                            if(l.type == TOKEN_TYPE::IDENTIFIER){
                                if(scope->exists(l.value)){
                                    left = scope->get(l.value);
                                }
                                else{
                                    return error("Undefined variable: " + l.value);
                                }
                            }
                            else{
                                return error("Expected number, got " + TOKEN_STRINGS[l.type]);
                            }
                        }
                        if(left.type == DATATYPE::NULLVALUE){
                            left = l.type == TOKEN_TYPE::INT ? P(std::stol(l.value)) : P(std::stod(l.value));
                        }
                        P right = values.top();
                        values.pop();
                        P res = handle_math(token.value, left, right);
                        if(res.type == DATATYPE::ERRORVALUE){
                            return res;
                        }
                        values.push(res);
                    }
                }
                if(token.type == TOKEN_TYPE::IDENTIFIER){
                    if(std::find(keywords.begin(), keywords.end(), token.value) != keywords.end()){
                        P res = handle_keyword(token.value);
                        if(res.type == DATATYPE::ERRORVALUE){
                            return res;
                        }
                        values.push(res);
                    }
                    else if(scope->exists(token.value)){
                        values.push(scope->get(token.value));
                    }
                    else{
                        return error("Undefined variable: " + token.value);
                    }
                }
            }
            return P();
}



        P Interpreter::handle_keyword(std::string keyword){
            P value = values.top();
            values.pop();
            if(keyword == "system"){
                P res = system_call(value);
                if(res.type == DATATYPE::ERRORVALUE){
                    return res;
                }
                values.push(res);
            }
            if(keyword == "console"){
                std::cout << tos(value) << std::endl;
            }
            return P();
        }

        P Interpreter::handle_math(std::string& op, P& left, P& right){
            if(left.type == DATATYPE::INTEGER and right.type == DATATYPE::INTEGER){
                long l = pi(left);
                long r = pi(right);
                if(op == "+") return P(l + r);
                if(op == "-") return P(l - r);
                if(op == "*") return P(l * r);
                if(op == "/") return P(l / r);
                if(op == "%") return P(l % r);

            }
            if(left.type == DATATYPE::FLOAT or right.type == DATATYPE::FLOAT){
                double l = pi(left);
                double r = pi(right);
                if(op == "+") return P(l + r);
                if(op == "-") return P(l - r); 
                if(op == "*") return P(l * r);
                if(op == "/") return P(l / r);

            }

            return error("Invalid operation: " + tos(left) + " " + op + " " + tos(right));
        }


}