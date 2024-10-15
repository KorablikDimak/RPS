#include <format>

#include <ExtendedCpp/LINQ.h>

#include "RPS/WebApi/DataContext.h"
#include "RPS/WebApi/DbUtility.h"

RPS::WebApi::DataContext::DataContext(const DbProvider::DbProvider::Ptr& dbProvider) noexcept
{
    _dbProvider = dbProvider;
}

std::future<RPS::WebApi::DbArray<double>> RPS::WebApi::DataContext::Get(std::int64_t id)
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const std::int64_t id)->DbArray<double>
    {
        const std::string query = std::format("SELECT * FROM Arrays WHERE id = {}", id);
        const pqxx::result result = work.exec(std::move(query));
        const pqxx::row row = result.front();

        DbArray<double> array;
        FromDbRow(row, array);
        return array;
    }, id);
}

std::future<std::vector<RPS::WebApi::DbArray<double>>> RPS::WebApi::DataContext::Get()
{
    return _dbProvider->TransactAsync([](pqxx::work& work)->std::vector<DbArray<double>>
    {
        const std::string query = "SELECT * FROM Arrays";
        const pqxx::result result = work.exec(std::move(query));

        std::vector<DbArray<double>> arrays;
        FromDbResult(result, arrays);
        return arrays;
    });
}

std::future<void> RPS::WebApi::DataContext::Add(const DbArray<double>& array)
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const DbArray<double>& array)
    {

        std::string query = std::format("INSERT INTO Arrays (array, isSorted) VALUES ({},{})",
                                        DbUtility::ToString(array.innerArray), array.isSorted);
        work.exec(std::move(query));
    }, array);
}

std::future<void> RPS::WebApi::DataContext::Update(const DbArray<double>& array)
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const DbArray<double>& array)
    {
        const std::string query = std::format("UPDATE Arrays SET (array, isSorted) VALUES ({},{}) WHERE id = {}",
                                              DbUtility::ToString(array.innerArray),
                                              array.isSorted,
                                              array.id);
        work.exec(query);
    }, array);
}

std::future<void> RPS::WebApi::DataContext::Delete(const DbArray<double>& array)
{
    return _dbProvider->TransactAsync([](pqxx::work& work, const DbArray<double>& array)
    {
        const std::string query = std::format("DELETE FROM \"Arrays\" WHERE id = {}", array.id);
        work.exec(query);
    }, array);
}