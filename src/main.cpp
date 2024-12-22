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
        evaluate(expression, scope);
    }

    //scope.print();

    return 0;
}
