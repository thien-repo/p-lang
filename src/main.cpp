#include <iostream>
#include <string>
#include <p/core.hpp>
#include <algorithm>


int main() {
    using namespace PL;
    P p = { std::vector<P>{{1}}};
    console(p);
    P nums = til({10});
    console(nums);
    P dropped = drop({5}, nums);
    console(dropped);
    P joined = join(nums, dropped);
    console(joined);
    auto mapper = [](P p) -> P { return { Dict{ {"num", tojs(pi(p) * 2 )}} }; };
    P mapped = each(mapper, joined);
    console(mapped);
    Scope scope;
    scope.set("nums", nums);
    scope.set("mapped", mapped);
    console(scope.get("nums"));
    console(scope.get("mapped"));
    Scope child(&scope);
    console(child.get("nums"));
    console(child.get("mapped"));
    child.set("nums", dropped);
    console(child.get("nums"));
    console(scope.get("nums"));
    

    return 0;
}
