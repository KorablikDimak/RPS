#include <thread>

#include "RPS/WebApi/DbPool.h"

RPS::WebApi::DbPool::DbPool(const std::string& connectionString, const unsigned char pollSize) noexcept
{
    _connectionString = connectionString;
    _poolSize = pollSize;
    _activeConnection = 0;
}

RPS::WebApi::DbPool::DbPool(RPS::WebApi::DbPool&& dbPool) noexcept
{
    _connectionString = dbPool._connectionString;
    _poolSize = dbPool._poolSize;
    _activeConnection = dbPool._activeConnection;
    _connections = std::move(dbPool._connections);
}

RPS::WebApi::DbPool& RPS::WebApi::DbPool::operator=(RPS::WebApi::DbPool&& dbPool) noexcept
{
    _connectionString = dbPool._connectionString;
    _poolSize = dbPool._poolSize;
    _activeConnection = dbPool._activeConnection;
    _connections = std::move(dbPool._connections);
    return *this;
}

bool RPS::WebApi::DbPool::IsEmpty() const noexcept
{
    return _connections.empty();
}

std::unique_ptr<pqxx::connection> RPS::WebApi::DbPool::GetConnection() noexcept
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
        _connections.push(std::make_unique<pqxx::connection>(_connectionString));

    ++_activeConnection;
    std::unique_ptr<pqxx::connection> connection = std::move(_connections.front());
    _connections.pop();
    return connection;
}

void RPS::WebApi::DbPool::ReturnInPool(std::unique_ptr<pqxx::connection>&& connection) noexcept
{
    std::lock_guard lock(_queueConnectionMutex);

    if (_activeConnection > 0)
    {
        --_activeConnection;
        _connections.push(std::move(connection));
    }
}