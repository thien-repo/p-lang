#pragma once

#include <p/variable.hpp>
#include <p/conversions.hpp>

namespace PL{
std::string tojs(P);

P join(P, P);
P drop(P, P);
P til(P);
P each(std::function<P(P)> func, P p);
P console(P);

};