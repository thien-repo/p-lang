#include <p/variable.hpp>

namespace PL{


P::P(DATATYPE type, Data data) : type(type), data(data) {};
P::P() : type(NULLVALUE){}
P::P(bool data) : type(DATATYPE::BOOLEAN) , data(data) {};
P::P(long data) : type(DATATYPE::INTEGER) , data(data) {}
P::P(int data) : type(DATATYPE::INTEGER) , data((long)data) {}
P::P(double data) : type(DATATYPE::FLOAT) , data(data) {}
P::P(std::string data) : type(DATATYPE::STRING) , data(data) {}
P::P(const char* data) : type(DATATYPE::STRING) , data(data) {}
P::P(List data) : type(DATATYPE::LIST) , data(data) {}
P::P(Dict data) : type(DATATYPE::DICTIONARY) , data(data){}
P::P(Function data) : type(DATATYPE::FUNCTION) , data(data){}
P error(std::string msg){ return P(DATATYPE::ERRORVALUE, msg); };

}