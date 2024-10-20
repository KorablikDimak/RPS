#ifndef RPS_WebApi_DbProvider_H
#define RPS_WebApi_DbProvider_H

#include <future>

#include "DbPool.h"

namespace RPS::WebApi
{
    class DbProvider final
    {
    private:
        DbPool::Ptr _pool;

    public:
        typedef std::shared_ptr<DbProvider> Ptr;

        inline explicit DbProvider(const DbPool::Ptr& pool) noexcept
        {
            _pool = pool;
        }

        template<typename TTransaction, typename... TParams,
                 typename TResult = std::invoke_result_t<TTransaction, pqxx::work&, TParams&&...>>
        requires (!std::same_as<void, TResult>)
        std::future<TResult> TransactAsync(TTransaction&& transaction, TParams&&... params) const
        {
            return std::async(std::launch::async, [this](TTransaction&& transaction, auto&&... args)->TResult
            {
                std::unique_ptr<pqxx::connection> connection{ nullptr };
                while (!connection)
                    connection = _pool->GetConnection();

                pqxx::work work(*connection);
                TResult result = transaction(work, std::forward<TParams>(args)...);
                work.commit();
                _pool->ReturnInPool(std::move(connection));
                return result;
            }, std::forward<TTransaction>(transaction), std::forward<TParams>(params)...);
        }

        template<typename TTransaction, typename... TParams>
        requires std::same_as<void, std::invoke_result_t<TTransaction, pqxx::work&, TParams&&...>>
        std::future<void> TransactAsync(TTransaction&& transaction, TParams&&... params) const
        {
            return std::async(std::launch::async, [this](TTransaction&& transaction, auto&&... args)
            {
                std::unique_ptr<pqxx::connection> connection{ nullptr };
                while (!connection)
                    connection =  _pool->GetConnection();

                pqxx::work work(*connection);
                transaction(work, std::forward<TParams>(args)...);
                work.commit();
                _pool->ReturnInPool(std::move(connection));
            }, std::forward<TTransaction>(transaction), std::forward<TParams>(params)...);
        }
    };
}

#endif