#pragma once
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <variant>
#include <iostream>

namespace PL{

enum DATATYPE {
    BOOLEAN,
    INTEGER,
    FLOAT,
    STRING,
    LIST,
    FUNCTION,
    DICTIONARY,
    NULLVALUE,
    ERRORVALUE,
};

struct P;

using List = std::vector<P>;
using Dict = std::map<std::string, P>;

struct Function {
    std::vector<std::string> args;
    std::string body;
    int line;
};


using Data = std::variant<bool, long, double, std::string, List, Function, Dict>;

struct P {
    DATATYPE type;
    Data data;
    P(DATATYPE, Data);
    P();
    P(bool);
    P(long);
    P(int);
    P(double);
    P(std::string);
    P(const char*);
    P(List);
    P(Function);
    P(Dict);
};

P error(std::string);


};


