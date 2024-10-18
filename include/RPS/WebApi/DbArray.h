#ifndef RPS_WebApi_DbArray_H
#define RPS_WebApi_DbArray_H

#include <vector>

#include <ExtendedCpp/Json.h>

#include "DbMacros.h"

namespace RPS::WebApi
{
    template<typename T>
    class DbArray final
    {
    public:
        typedef std::shared_ptr<DbArray<T>> Ptr;

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

    inline void from_json(const ExtendedCpp::Json& json, DbArray<double>& object) noexcept
    {
        VALUE_FROM_JSON(id)
        VALUES_FROM_JSON(inner_array)
        VALUE_FROM_JSON(is_sorted)
    }

    inline void to_json(ExtendedCpp::Json& json, const DbArray<double>& object) noexcept
    {
        VALUE_TO_JSON(id)
        VALUES_TO_JSON(inner_array)
        VALUE_TO_JSON(is_sorted)
    }
}

#endif