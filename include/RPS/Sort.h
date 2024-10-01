#ifndef RPS_Sort_H
#define RPS_Sort_H

#include "Concepts.h"

namespace RPS::Sort
{
    template<Concepts::RandomAccess TCollection,
             Concepts::Comparable TValue = std::decay_t<TCollection>::value_type>
    std::size_t Partition(TCollection&& collection, const std::size_t start, const std::size_t end) noexcept
    {
        auto i = static_cast<long long>(start);
        auto j = static_cast<long long>(end);
        const TValue pivot = collection[(start + end) / 2];

        while (i <= j)
        {
            while (collection[i] < pivot)
                ++i;
            while (collection[j] > pivot)
                --j;

            if (i <= j)
            {
                std::swap(collection[i], collection[j]);
                ++i;
                --j;
            }
        }

        return i;
    }

    template<typename TCollection>
    void QuickSort(TCollection&& collection, const std::size_t start, const std::size_t end) noexcept
    {
        if (collection.size() <= 1)
            return;

        const std::size_t mid = Partition(std::forward<TCollection>(collection), start, end);
        if (mid == 0)
            return;

        if (start < mid - 1)
            QuickSort(std::forward<TCollection>(collection), start, mid - 1);
        if (mid < end)
            QuickSort(std::forward<TCollection>(collection), mid, end);
    }

    template<Concepts::Iterable TCollection>
    void QuickSort(TCollection&& collection) noexcept
    {
        if (collection.size() <= 1)
            return;

        QuickSort(std::forward<TCollection>(collection), 0, collection.size() - 1);
    }
}

#endif