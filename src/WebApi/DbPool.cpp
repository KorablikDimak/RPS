#include <thread>

#include "DbPool.h"

RPS::WebApi::DbPool::DbPool(const std::string& connectionString, const unsigned char pollSize) noexcept
{
    _connectionString = connectionString;
    _poolSize = pollSize;
    _activeConnection = 0;
}

RPS::WebApi::DbPool::DbPool(std::string&& connectionString, const unsigned char pollSize) noexcept
{
    _connectionString = std::move(connectionString);
    _poolSize = pollSize;
    _activeConnection = 0;
}

bool RPS::WebApi::DbPool::IsEmpty() const noexcept
{
    return _connections.empty();
}

pqxx::connection RPS::WebApi::DbPool::GetConnection() noexcept
{
    while (true)
    {
        std::unique_lock lock(_queueConnectionMutex);
        if (_activeConnection < _poolSize) break;
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::lock_guard lock(_queueConnectionMutex);

    if (_connections.empty() && _activeConnection < _poolSize)
        _connections.emplace(_connectionString);

    ++_activeConnection;
    pqxx::connection connection = std::move(_connections.front());
    _connections.pop();
    return connection;
}

void RPS::WebApi::DbPool::ReturnInPool(pqxx::connection&& connection) noexcept
{
    std::lock_guard lock(_queueConnectionMutex);

    if (_activeConnection > 0)
    {
        --_activeConnection;
        _connections.push(std::move(connection));
    }
}