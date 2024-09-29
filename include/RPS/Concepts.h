#ifndef RPS_Concepts_H
#define RPS_Concepts_H

#include <utility>

namespace RPS::Concepts
{
    template<typename T>
    concept Comparable = requires(T value)
    {
        { value < value } -> std::convertible_to<bool>;
        { value > value } -> std::convertible_to<bool>;
        { value <= value } -> std::convertible_to<bool>;
        { value >= value } -> std::convertible_to<bool>;
        { value == value } -> std::convertible_to<bool>;
        { value != value } -> std::convertible_to<bool>;
    };

    template<typename TCollection>
    concept Iterable = requires(TCollection value)
    {
        value.begin();
        value.end();
        value.size();
        typename std::decay_t<TCollection>::value_type;
        typename std::decay_t<TCollection>::iterator;
    };

    template<typename TCollection>
    concept RandomAccess = requires(TCollection value)
    {
        value[std::declval<std::size_t>()];
        typename std::decay_t<TCollection>::value_type;
    };
}

#endif