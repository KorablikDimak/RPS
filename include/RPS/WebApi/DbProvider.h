#ifndef RPS_WebApi_DbProvider_H
#define RPS_WebApi_DbProvider_H

#include <future>

#include "RPS/WebApi/DbPool.h"

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

        template<typename TTransaction, typename ...TParams,
                 typename TResult = std::invoke_result_t<TTransaction, pqxx::work&, TParams...>>
        std::future<TResult> TransactAsync(TTransaction&& transaction, TParams&&... params) const
        {
            return std::async(std::launch::async, [this, transaction](auto&&... args)->TResult
            {
                pqxx::connection connection = _pool->GetConnection();
                pqxx::work work{connection};
                TResult result = transaction(work, std::forward<TParams>(args)...);
                work.commit();
                _pool->ReturnInPool(std::move(connection));
                return result;
            }, params...);
        }
    };
}

#endif