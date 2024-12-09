#pragma once

#include <p/variable.hpp>

namespace P{
std::string tos(P);

P join(P, P);
P drop(P, P);
P til(P);
P each(P, P);
P console(P);

template<typename Func>
P each(Func func, P p){
    List lst = std::get<List>(p.data);
    for(auto& ele : lst){
        ele = func(ele);
    }
    return {lst};
}

};