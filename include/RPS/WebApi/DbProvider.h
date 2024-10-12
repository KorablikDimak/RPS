#ifndef RPS_WebApi_DbProvider_H
#define RPS_WebApi_DbProvider_H

#include <future>

#include "RPS/WebApi/DbPool.h"

namespace RPS::WebApi
{
    class DbProvider
    {
    private:
        DbPool::Ptr _pool;

    public:
        typedef std::unique_ptr<DbProvider> Ptr;

        explicit DbProvider(const std::string& connectionString, unsigned char poolSize = 1) noexcept;
        explicit DbProvider(const DbProvider& pool) noexcept = delete;
        DbProvider(DbProvider&& pool) noexcept;
        explicit DbProvider(const DbPool::Ptr& pool) noexcept = delete;
        explicit DbProvider(DbPool::Ptr&& pool) noexcept;
        ~DbProvider() = default;

        DbProvider& operator=(const DbProvider& dbProvider) noexcept = delete;
        DbProvider& operator=(DbProvider&& dbProvider) noexcept;

        template<typename TTransaction, typename ...TParams,
                 typename TResult = std::invoke_result_t<TTransaction, pqxx::work&, TParams...>>
        std::future<TResult> TransactAsync(TTransaction&& transaction, TParams&&... params) const
        {
            return std::async(std::launch::async, [this, transaction](auto&&... args)->TResult
            {
                std::unique_ptr<pqxx::connection> connection = _pool->GetConnection();
                pqxx::work work{*connection};
                TResult result = transaction(work, std::forward<TParams>(args)...);
                work.commit();
                _pool->ReturnInPool(std::move(connection));
                return result;
            }, params...);
        }
    };
}

#endif