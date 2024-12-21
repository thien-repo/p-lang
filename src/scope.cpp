#include <p/scope.hpp>

#include <p/exception.hpp>
#include <p/standard.hpp>

#include <iostream>

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
    return error(name + " undefined");
}

bool Scope::exists(const std::string& name){
    if(variables.find(name) != variables.end()){
        return true;
    }
    if(parent != nullptr){
        return parent->exists(name);
    }
    return false;
}

void Scope::print(){
    for(auto& [name, value] : variables){
        std::cout << name << " | " << tos(value) << std::endl;
    }
}

}