#ifndef RPS_WebApi_DbUtility_H
#define RPS_WebApi_DbUtility_H

#include <sstream>

namespace RPS::WebApi::DbUtility
{
    template<typename T>
    std::string ToString(const std::vector<T>& array)
    {
        std::ostringstream result;
        result << "'{";

        if (!array.empty())
        {
            for (long long i = 0; i < static_cast<long long>(array.size() - 1); ++i)
                result << array[i] << ",";
            result << array[array.size() - 1];
        }

        result << "}'";
        return result.str();
    }
}

#endif