#ifndef RPS_WebApi_DataContext_H
#define RPS_WebApi_DataContext_H

#include <future>
#include <format>
#include <optional>

#include <ExtendedCpp/LINQ/Concepts.h>

#include "DbProvider.h"
#include "DbArray.h"
#include "DbUtility.h"

namespace RPS::WebApi
{
    class DataContext final
    {
    private:
        DbProvider::DbProvider::Ptr _dbProvider;

    public:
        typedef std::shared_ptr<DataContext> Ptr;

        explicit DataContext(const DbProvider::DbProvider::Ptr& dbProvider) noexcept;

        [[nodiscard]]
        std::future<std::optional<DbArray<double>>> Get(std::int64_t id) const noexcept;
        [[nodiscard]]
        std::future<std::vector<DbArray<double>>> Get() const noexcept;

        [[nodiscard]]
        std::future<void> Add(const DbArray<double>& array) const noexcept;

        template<typename TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, DbArray<double>> &&
                 ExtendedCpp::LINQ::Concepts::Iterable<std::decay_t<TCollection>>
        std::future<void> Add(TCollection&& arrays) const noexcept
        {
            return _dbProvider->TransactAsync([](pqxx::work& work, auto&& arrays)
            {
                for (const auto& array : arrays)
                {
                    std::string query = std::format("INSERT INTO arrays (inner_array) VALUES ({})",
                                                    DbUtility::ToString(array.inner_array));
                    work.exec(std::move(query));
                }
            }, std::forward<TCollection>(arrays));
        }

        [[nodiscard]]
        std::future<void> Update(const DbArray<double>& array) const noexcept;

        template<typename TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, DbArray<double>> &&
                 ExtendedCpp::LINQ::Concepts::Iterable<std::decay_t<TCollection>>
        std::future<void> Update(TCollection&& arrays) const noexcept
        {
            return _dbProvider->TransactAsync([](pqxx::work& work, auto&& arrays)
            {
                for (const auto& array : arrays)
                {
                    const std::string query = std::format("UPDATE arrays SET inner_array = {} WHERE id = {}",
                                                          DbUtility::ToString(array.inner_array),
                                                          array.id);
                    work.exec(query);
                }
            }, std::forward<TCollection>(arrays));
        }

        [[nodiscard]]
        std::future<void> Delete(const DbArray<double>& array) const noexcept;

        [[nodiscard]]
        std::future<void> Delete(const std::int64_t id) const noexcept;

        template<typename TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, DbArray<double>> &&
                 ExtendedCpp::LINQ::Concepts::Iterable<std::decay_t<TCollection>>
        std::future<void> Delete(TCollection&& arrays) const noexcept
        {
            return _dbProvider->TransactAsync([](pqxx::work& work, auto&& arrays)
            {
                for (const auto& array : arrays)
                {
                    const std::string query = std::format("DELETE FROM arrays WHERE id = {}",
                                                          array.id);
                    work.exec(query);
                }
            }, std::forward<TCollection>(arrays));
        }

        template<typename TCollection>
        requires std::same_as<typename std::decay_t<TCollection>::value_type, std::int64_t> &&
                 ExtendedCpp::LINQ::Concepts::Iterable<std::decay_t<TCollection>>
        std::future<void> Delete(TCollection&& ids) const noexcept
        {
            return _dbProvider->TransactAsync([](pqxx::work& work, auto&& ids)
            {
                for (const auto& id : ids)
                {
                    const std::string query = std::format("DELETE FROM arrays WHERE id = {}",
                                                          id);
                    work.exec(query);
                }
            }, std::forward<TCollection>(ids));
        }
    };
}

#endif