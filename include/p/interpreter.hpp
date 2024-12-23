#pragma once

#include <stack>
#include <p/variable.hpp>
#include <p/scope.hpp>
#include <p/tokenizer.hpp>

namespace PL{
class Interpreter {
    public:
        Interpreter(Scope* scope) : scope(scope) {}
        P interpret(std::stack<Token>& tokens);
    private:
        std::stack<P> values;
        Scope* scope;
        P handle_keyword(std::string keyword);
        P handle_math(std::string& op, P& left, P& right);
};

}