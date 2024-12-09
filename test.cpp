#include <any>
#include <fmt/core.h>
int main(int argc, char *argv[]) {
    std::any a = 1;
    fmt::print("a: {}\n", std::any_cast<int>(a));
    return 0;
}