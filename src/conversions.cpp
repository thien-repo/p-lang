#include <p/exception.hpp>
#include <p/conversions.hpp>

namespace PL{
    
bool& pb(P& p){
    return std::get<bool>(p.data);
}

long& pi(P& p){
    return std::get<long>(p.data);
}

double& pf(P& p){
    return std::get<double>(p.data);
}

std::string& ps(P& p){
    return std::get<std::string>(p.data);
}

List& pl(P& p){
    return std::get<List>(p.data);
}

Dict& pd(P& p){
    return std::get<Dict>(p.data);
}

};