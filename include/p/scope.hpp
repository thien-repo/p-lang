#pragma once
#include <p/variable.hpp>

namespace PL{

class Scope{
    public:
        Scope();
        Scope(Scope* parent);
        void set(std::string name, P value);
        P get(std::string name);
    private:
        Scope* parent;
        std::map<std::string, P> variables;
};

}