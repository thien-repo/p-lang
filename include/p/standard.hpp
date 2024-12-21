#pragma once

#include <p/variable.hpp>
#include <p/conversions.hpp>

namespace PL{
std::string tos(P);
std::string tocsv(P);
P join(P, P);
P drop(P, P);
P til(P);
P each(std::function<P(P)>, P);
P console(P);
};