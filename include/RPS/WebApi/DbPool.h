#ifndef RPS_WebApi_DbPool_H
#define RPS_WebApi_DbPool_H

#include <queue>
#include <mutex>

#include <pqxx/pqxx>

namespace RPS::WebApi
{
    class DbPool
    {
    private:
        std::string _connectionString;
        unsigned char _poolSize;
        unsigned char _activeConnection;
        std::queue<std::unique_ptr<pqxx::connection>> _connections;
        mutable std::mutex _queueConnectionMutex;

    public:
        typedef std::unique_ptr<DbPool> Ptr;

        explicit DbPool(const std::string& connectionString, unsigned char poolSize = 1) noexcept;
        explicit DbPool(const DbPool& dbPool) noexcept = delete;
        DbPool(DbPool&& dbPool) noexcept;
        ~DbPool() = default;

        DbPool& operator=(const DbPool& dbPool) = delete;
        DbPool& operator=(DbPool&& dbPool) noexcept;

        [[nodiscard]]
        bool IsEmpty() const noexcept;
        std::unique_ptr<pqxx::connection> GetConnection() noexcept;
        void ReturnInPool(std::unique_ptr<pqxx::connection>&& connection) noexcept;
    };
}

#endif