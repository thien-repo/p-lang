#pragma once


#include <exception>
#include <string>

namespace PL{
class Exception : public std::exception{
    public:
        Exception(const char* message) : message(message) {}
        Exception(std::string message) : message(message.c_str()) {}
        const char* what() const noexcept override {
           return message;
        }
    private:
        const char* message;
};
}