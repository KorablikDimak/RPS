#ifndef RPS_WebApi_DbPool_H
#define RPS_WebApi_DbPool_H

#include <queue>
#include <mutex>

#include <pqxx/pqxx>

namespace RPS::WebApi
{
    class DbPool final
    {
    private:
        std::string _connectionString;
        unsigned char _poolSize;
        unsigned char _activeConnection;
        std::queue<pqxx::connection> _connections;
        mutable std::mutex _queueConnectionMutex;

    public:
        typedef std::shared_ptr<DbPool> Ptr;

        explicit DbPool(const std::string& connectionString, unsigned char poolSize) noexcept;
        explicit DbPool(std::string&& connectionString, unsigned char poolSize) noexcept;

        [[nodiscard]]
        bool IsEmpty() const noexcept;
        pqxx::connection GetConnection() noexcept;
        void ReturnInPool(pqxx::connection&& connection) noexcept;
    };
}

#endif