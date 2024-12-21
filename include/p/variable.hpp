#pragma once
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <variant>

namespace PL{

enum DATATYPE {
    BOOLEAN,
    INTEGER,
    FLOAT,
    STRING,
    LIST,
    DICTIONARY,
    NULLVALUE,
    ERRORVALUE
};

struct P;

using List = std::vector<P>;
using Dict = std::map<std::string, P>;

using Data = std::variant<bool, long, double, std::string, List, Dict>;

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
    P(Dict);
};

P error(std::string);


};


