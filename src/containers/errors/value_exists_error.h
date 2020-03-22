#pragma once
#include <exception>

namespace containers::errors
{
    class value_exists_error : public std::exception
    {
    public:
        using std::exception::exception;
    };
}
