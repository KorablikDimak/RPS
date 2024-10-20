#include "DataContext.h"

RPS::WebApi::DataContext::DataContext(const DbProvider::DbProvider::Ptr& dbProvider) noexcept
{
    _dbProvider = dbProvider;
}

std::future<std::optional<RPS::WebApi::DbArray<double>>> RPS::WebApi::DataContext::Get(std::int64_t id) const noexcept
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const std::int64_t id)->std::optional<DbArray<double>>
    {
        const std::string query = std::format("SELECT * FROM arrays WHERE id = {}",
                                              id);
        const pqxx::result result = work.exec(std::move(query));
        if (result.empty())
            return std::nullopt;

        const pqxx::row row = result.front();
        DbArray<double> array;
        FromDbRow(row, array);
        return array;
    }, id);
}

std::future<std::vector<RPS::WebApi::DbArray<double>>> RPS::WebApi::DataContext::Get() const noexcept
{
    return _dbProvider->TransactAsync([](pqxx::work& work)->std::vector<DbArray<double>>
    {
        const std::string query = "SELECT * FROM arrays";
        const pqxx::result result = work.exec(std::move(query));

        std::vector<DbArray<double>> arrays;
        FromDbResult(result, arrays);
        return arrays;
    });
}

std::future<void> RPS::WebApi::DataContext::Add(const DbArray<double>& array) const noexcept
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const DbArray<double>& array)
    {
        std::string query = std::format("INSERT INTO arrays (inner_array) VALUES ({})",
                                        DbUtility::ToString(array.inner_array));
        work.exec(std::move(query));
    }, array);
}

std::future<void> RPS::WebApi::DataContext::Update(const DbArray<double>& array) const noexcept
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const DbArray<double>& array)
    {
        const std::string query = std::format("UPDATE arrays SET inner_array = {} WHERE id = {}",
                                              DbUtility::ToString(array.inner_array),
                                              array.id);
        work.exec(query);
    }, array);
}

std::future<void> RPS::WebApi::DataContext::Delete(const DbArray<double>& array) const noexcept
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const DbArray<double>& array)
    {
        const std::string query = std::format("DELETE FROM arrays WHERE id = {}",
                                              array.id);
        work.exec(query);
    }, array);
}

std::future<void> RPS::WebApi::DataContext::Delete(const std::int64_t id) const noexcept
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const std::int64_t id)
    {
        const std::string query = std::format("DELETE FROM arrays WHERE id = {}",
                                              id);
        work.exec(query);
    }, id);
}