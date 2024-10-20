#include <thread>

#include "DbPool.h"

RPS::WebApi::DbPool::DbPool(const std::string& connectionString, const unsigned char pollSize) noexcept
{
    _connectionString = connectionString;
    _poolSize = pollSize;

    for (unsigned char i = 0; i < _poolSize; ++i)
        _connections.push(std::make_unique<pqxx::connection>(_connectionString));
}

RPS::WebApi::DbPool::DbPool(std::string&& connectionString, const unsigned char pollSize) noexcept
{
    _connectionString = std::move(connectionString);
    _poolSize = pollSize;

    for (unsigned char i = 0; i < _poolSize; ++i)
        _connections.push(std::make_unique<pqxx::connection>(_connectionString));
}

std::unique_ptr<pqxx::connection> RPS::WebApi::DbPool::GetConnection() noexcept
{
    std::lock_guard lock(_queueConnectionMutex);
    if (_connections.empty())
        return { nullptr };
    std::unique_ptr<pqxx::connection> connection = std::move(_connections.front());
    _connections.pop();
    return connection;
}

void RPS::WebApi::DbPool::ReturnInPool(std::unique_ptr<pqxx::connection>&& connection) noexcept
{
    std::lock_guard lock(_queueConnectionMutex);
    _connections.push(std::move(connection));
}