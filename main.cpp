#include <p/core.hpp>
#include <sstream>

using namespace PL;


int main(int argc, char** argv){
    using namespace PL;
    std::string content = "a:1;b:1;";
    std::stringstream stream(content);
    std::string expression;
    int line = 1;
    Scope scope;
    Parser parser(stream, line);
    while(parser.next_expression(expression)){
        std::stringstream estream(expression);
        Token token;
        Lexer lexer(estream, line);
        std::stack<Token> tokens;
        while(lexer.next_token(token)){
            tokens.push(token);
        }
        Interpreter interpreter(&scope);
        P res = interpreter.interpret(tokens);
        if(res.type == DATATYPE::ERRORVALUE){
            std::cout << tos(res) << std::endl;
            return 1;
        }
    }
    scope.print();
    return 0;
}
