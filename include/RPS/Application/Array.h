#ifndef RPS_Application_Array_H
#define RPS_Application_Array_H

#include <vector>

#include <ExtendedCpp/Json.h>

namespace RPS::Application
{
    template<typename T>
    class Array final
    {
    public:
        typedef std::shared_ptr<Array<T>> Ptr;

        std::int64_t id{};
        std::vector<T> inner_array;
        bool is_sorted{};
    };

    inline void from_json(const ExtendedCpp::Json& json, Array<double>& object) noexcept
    {
        VALUE_FROM_JSON(id)
        VALUES_FROM_JSON(inner_array)
        VALUE_FROM_JSON(is_sorted)
    }

    inline void to_json(ExtendedCpp::Json& json, const Array<double>& object) noexcept
    {
        VALUE_TO_JSON(id)
        VALUES_TO_JSON(inner_array)
        VALUE_TO_JSON(is_sorted)
    }
}

#endif