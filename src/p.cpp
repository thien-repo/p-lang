#include <iostream>
#include <string>
#include <fmt/core.h>
#include <p/core.hpp>
#include <fmt/format.h>
#include <algorithm>
#include <lexer/core.hpp>
int main() {
    P::Dict context = Lexer::create_context("../example/assignment.p");
    P::console(context);
    return 0;
}
