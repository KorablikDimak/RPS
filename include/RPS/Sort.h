#ifndef RPS_Sort_H
#define RPS_Sort_H

#include <vector>

#include "Concepts.h"

namespace RPS::Sort
{
    enum class OrderType
    {
        ASC,
        DESC
    };

    template<Concepts::Comparable T>
    std::size_t Partition(std::vector<T>& collection, const std::size_t start, const std::size_t end,
                          const OrderType orderType) noexcept
    {
        auto i = static_cast<long long>(start);
        auto j = static_cast<long long>(end);
        const T pivot = collection[(start + end) / 2];

        if (orderType == OrderType::ASC)
        {
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
        }
        else
        {
            while (i <= j)
            {
                while (collection[i] > pivot)
                    ++i;
                while (collection[j] < pivot)
                    --j;

                if (i <= j)
                {
                    std::swap(collection[i], collection[j]);
                    ++i;
                    --j;
                }
            }
        }

        return i;
    }

    template<Concepts::Comparable T>
    void QuickSort(std::vector<T>& collection, const std::size_t start, const std::size_t end,
                   const OrderType orderType) noexcept
    {
        const std::size_t mid = Partition(collection, start, end, orderType);

        if (start < mid - 1)
            QuickSort(collection, start, mid - 1, orderType);
        if (mid < end)
            QuickSort(collection, mid, end, orderType);
    }

    template<Concepts::Comparable T>
    void QuickSort(std::vector<T>& collection, const OrderType orderType = OrderType::ASC) noexcept
    {
        if (collection.size() <= 1)
            return;
        QuickSort(collection, 0, collection.size() - 1, orderType);
    }
}

#endif