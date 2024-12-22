#include <iostream>
#include <string>
#include <p/core.hpp>
#include <algorithm>
#include <stack>
#include <sstream>
#include <fstream>
#include <cstdlib>

const std::vector<std::string> keywords = {
    "console", "if", "each", "system",
};

int main(int argc, char** argv) {
    using namespace PL;
    Scope scope;
    std::string filename = argv[1];
    std::ifstream stream(filename);
    std::string expression;
    int line = 0;
    for(auto keyword : keywords){
        scope.set(keyword, P());
    }
    while(PL::next_expression(stream, expression, line)){

        P result = evaluate(expression, scope);
        if( result.type == DATATYPE::ERRORVALUE){
            std::cerr << "Error on line " << line << ": " << ps(result) << std::endl;
            return 1;
        }
    }

    //scope.print();

    return 0;
}
