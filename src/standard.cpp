#include <p/standard.hpp>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <fmt/format.h>

namespace P{
    

std::string tos(P p) {
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
                ss << tos(lst[i]);
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
                ss << tos(kv.second);
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
    List rdata = std::get<List>(r.data);

    std::copy(rdata.begin(), rdata.end(), std::back_inserter(
        std::get<List>(l.data)
    ));
    return l;
}

P til(P p){
    long size = std::get<long>(p.data);
    std::vector<long> nums(size);
    std::iota(nums.begin(), nums.end(), 0);
    List pnums(size);
    std::transform(nums.begin(), nums.end(), pnums.begin(), [](long num){
        return P(num);
    });

    return P(pnums);
}

P drop(P ndrops, P p){
    long n = std::get<long>(ndrops.data);
    List pdata = std::get<List>(p.data);
    if(pdata.size() > n){
        pdata.erase(pdata.begin(), pdata.begin() + n);
    }
    else{
        pdata.clear();
    }
    return P(pdata);
}

P console(P p){
    fmt::print("{}\n", tos(p));
    return P();
}

}