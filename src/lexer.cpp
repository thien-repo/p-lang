#include <lexer/lexer.hpp>
#include <fstream>
#include <fmt/core.h>
#include <sstream>
#include <regex>
namespace Lexer {


static bool is_integer(const std::string& str) {
    std::regex pattern(R"(^\s*-?\d+(\.\d+)?\s*$)"); 
    // ^       : Start of the string
    // \s*     : Match zero or more spaces
    // -?      : Match an optional negative sign
    // \d+     : Match one or more digits
    // (\.\d+)?: Optionally match a period followed by one or more digits (for decimals)
    // \s*     : Match zero or more trailing spaces
    // $       : End of the string
    return std::regex_match(str, pattern);
}

bool is_boolean(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    std::string clean = str.substr(start);
    std::regex pattern(R"(^[01]b$)");
    // ^    : Start of the string
    // [01] : Match either '0' or '1'
    // b    : Match the literal 'b'
    // $    : End of the string
    return std::regex_match(clean, pattern);
}

P::Dict create_context(std::string fpath){
    std::fstream ifs(fpath);
    std::string line;
    P::Dict ctx;
    while(std::getline(ifs, line, ';')){
        std::string clean = std::regex_replace(line, std::regex("[\n\r]"), "");
        if(clean.find(':') != std::string::npos){
            std::string key, value;
            std::stringstream ss(clean);
            std::getline(ss, key, ':');
            std::getline(ss, value);
            if(is_integer(value)){
                ctx[key] = {std::stol(value)};
                fmt::print("{} can be assigned\n", value);
            }
            else if(is_boolean(value)){
                ctx[key] = (value.find("0b") == std::string::npos) ? P::P{true} : P::P{false};
            }
        }
    }
    
    return ctx;
}

}