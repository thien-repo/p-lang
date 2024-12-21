#include <p/exception.hpp>
#include <p/conversions.hpp>

namespace PL{
    
bool& pb(P& p){
    if(p.type != DATATYPE::BOOLEAN) throw Exception("type");
    return std::get<bool>(p.data);
}

long& pi(P& p){
    if(p.type != DATATYPE::INTEGER) throw Exception("type");
    return std::get<long>(p.data);
}

double& pf(P& p){
    if(p.type != DATATYPE::FLOAT) throw Exception("type");
    return std::get<double>(p.data);
}

std::string& ps(P& p){
    if(p.type != DATATYPE::STRING) throw Exception("type");
    return std::get<std::string>(p.data);
}

List& pl(P& p){
    if(p.type != DATATYPE::LIST) throw Exception("type");
    return std::get<List>(p.data);
}

Dict& pd(P& p){
    if(p.type != DATATYPE::DICTIONARY) throw Exception("type");
    return std::get<Dict>(p.data);
}

};