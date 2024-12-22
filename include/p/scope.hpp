#pragma once
#include <p/variable.hpp>

namespace PL{

class Scope{
    public:
        Scope();
        Scope(Scope* parent);
        void set(std::string name, P value);
        P get(std::string name);
        bool exists(const std::string& name);
        void print();
    private:
        Scope* parent;
        std::unordered_map<std::string, P> variables;
};

}