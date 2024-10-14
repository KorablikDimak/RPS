#ifndef RPS_WebApi_DbArray_H
#define RPS_WebApi_DbArray_H

#include <vector>

#include "RPS/WebApi/DbMacros.h"

namespace RPS::WebApi
{
    class DbArray final
    {
    public:
        std::int64_t id{};
        std::vector<double> innerArray;
        bool isSorted{};
    };

    inline void FromDbRow(const pqxx::row& row, DbArray& object)
    {
        GET_VALUE(id)
        GET_ARRAY(innerArray)
        GET_VALUE(isSorted)
    }

    inline void FromDbResult(const pqxx::result& result, std::vector<DbArray>& arrays)
    {
        for (const pqxx::row& row : result)
        {
            DbArray object;
            FromDbRow(row, object);
            arrays.push_back(std::move(object));
        }
    }
}

#endif