#include <p/standard.hpp>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <p/exception.hpp>
#include <p/conversions.hpp>
#include <iostream>
namespace PL{
    

std::string tojs(P p) {
    switch (p.type) {
        case DATATYPE::BOOLEAN: { 
            return std::get<bool>(p.data) ? "1b" : "0b"; 
        }
        case DATATYPE::INTEGER: { 
            return std::to_string(std::get<long>(p.data)); 
        }
        case DATATYPE::FLOAT: { 
            return std::to_string(std::get<double>(p.data)); 
        }
        case DATATYPE::STRING: { 
            return "\"" + std::get<std::string>(p.data) + "\""; 
        }
        case DATATYPE::LIST: { 
            List& lst = std::get<List>(p.data);
            std::stringstream ss;
            ss << "[";
            for(int i = 0; i < lst.size(); i++){
                ss << tojs(lst[i]);
                if(i < lst.size() - 1){
                    ss << ",";
                }
            } 
            ss << "]";
            return ss.str();
        }
        case DATATYPE::DICTIONARY: {
            Dict& m = std::get<Dict>(p.data); 
            std::stringstream ss;
             ss << "{";
            size_t size = m.size();
            for(auto& kv : m){
                ss << "\"" << kv.first << "\":";
                ss << tojs(kv.second);
                if(size > 1){
                    ss << ",";
                }
                size--;
            }
            ss << "}";
            return ss.str();
        }
    }
    return "null";
}

P join(P l, P r){
    List rdata = pl(r);

    std::copy(rdata.begin(), rdata.end(), std::back_inserter(
        std::get<List>(l.data)
    ));
    return l;
}

P til(P p){
    long size = pi(p);
    std::vector<long> nums(size);
    std::iota(nums.begin(), nums.end(), 0);
    List pnums(size);
    std::transform(nums.begin(), nums.end(), pnums.begin(), [](long num){
        return P(num);
    });

    return P(pnums);
}

P drop(P ndrops, P p){
    long n = pi(ndrops);
    List pdata = pl(p);
    if(pdata.size() > n){
        pdata.erase(pdata.begin(), pdata.begin() + n);
    }
    else{
        pdata.clear();
    }
    return P(pdata);
}

P console(P p){
    std::cout << tojs(p) << std::endl;
    return P();
}

P each(std::function<P(P)> func, P p){
    List& pdata = pl(p);
    List result( pl(p).size());
    std::transform(pdata.begin(), pdata.end(), result.begin(), func);
    return P(result);
}

}