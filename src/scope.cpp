#include <p/scope.hpp>

#include <p/exception.hpp>

namespace PL{

Scope::Scope() : parent(nullptr) {}
Scope::Scope(Scope* parent) : parent(parent) {}

void Scope::set(std::string name, P value){
    variables[name] = value;
}

P Scope::get(std::string name){
    if(variables.find(name) != variables.end()){
        return variables[name];
    }
    if(parent != nullptr){
        return parent->get(name);
    }
    throw Exception(name + " variable not found");
}

}