#ifndef RPS_WebApi_DbArray_H
#define RPS_WebApi_DbArray_H

#include <vector>

#include "RPS/WebApi/DbMacros.h"

namespace RPS::WebApi
{
    template<typename T>
    class DbArray final
    {
    public:
        std::int64_t id{};
        std::vector<T> inner_array;
        bool is_sorted{};
    };

    template<typename T>
    inline void FromDbRow(const pqxx::row& row, DbArray<T>& object)
    {
        GET_VALUE(id)
        GET_ARRAY(inner_array)
        GET_VALUE(is_sorted)
    }

    template<typename T>
    inline void FromDbResult(const pqxx::result& result, std::vector<DbArray<T>>& objects)
    {
        objects.clear();
        for (const pqxx::row& row : result)
        {
            DbArray<T> object;
            FromDbRow(row, object);
            objects.push_back(std::move(object));
        }
    }
}

#endif