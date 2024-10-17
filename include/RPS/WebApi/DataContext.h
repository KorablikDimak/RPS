#ifndef RPS_WebApi_DataContext_H
#define RPS_WebApi_DataContext_H

#include <future>

#include <ExtendedCpp/LINQ/Concepts.h>

#include "RPS/WebApi/DbProvider.h"
#include "RPS/WebApi/DbArray.h"

namespace RPS::WebApi
{
    class DataContext final
    {
    private:
        DbProvider::DbProvider::Ptr _dbProvider;

    public:
        typedef std::shared_ptr<DataContext> Ptr;

        explicit DataContext(const DbProvider::DbProvider::Ptr& dbProvider) noexcept;

        std::future<DbArray<double>> Get(std::int64_t id);
        std::future<std::vector<DbArray<double>>> Get();

        std::future<void> Add(const DbArray<double>& array);

        template<ExtendedCpp::LINQ::Concepts::Iterable TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, DbArray<double>>
        std::future<void> Add(TCollection&& arrays)
        {
            std::list<std::future<void>> tasks;
            for (const DbArray<double>& array : arrays)
                Add(array);
            return {};
        }

        std::future<void> Update(const DbArray<double>& array);

        template<ExtendedCpp::LINQ::Concepts::Iterable TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, DbArray<double>>
        std::future<void> Update(TCollection&& arrays)
        {
            std::list<std::future<void>> tasks;
            for (const DbArray<double>& array : arrays)
                Update(array);
            return {};
        }

        std::future<void> Delete(const DbArray<double>& array);

        template<ExtendedCpp::LINQ::Concepts::Iterable TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, DbArray<double>>
        std::future<void> Delete(TCollection&& arrays)
        {
            std::list<std::future<void>> tasks;
            for (const DbArray<double>& array : arrays)
                tasks.push_back(Delete(array));
            return {};
        }
    };
}

#endif