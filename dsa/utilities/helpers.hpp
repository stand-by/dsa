#pragma once
#include <config.hpp>

namespace dsa
{

    namespace utilities
    {

        inline void expect(bool cond_result, const std::string& msg = "")
        {
            if(!cond_result)
                throw std::runtime_error(msg);
        }

        inline void ensure(bool cond_result, const std::string& msg = "")
        {
            if(!cond_result)
                throw std::runtime_error(msg);
        }

    }

}
