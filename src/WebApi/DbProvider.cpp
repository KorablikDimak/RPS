#include "RPS/WebApi/DbProvider.h"

RPS::WebApi::DbProvider::DbProvider(const std::string& connectionString, unsigned char poolSize) noexcept
{
    _pool = std::make_unique<DbPool>(connectionString, poolSize);
}

RPS::WebApi::DbProvider::DbProvider(DbProvider&& dbProvider) noexcept
{
    _pool = std::move(dbProvider._pool);
}

RPS::WebApi::DbProvider::DbProvider(DbPool::Ptr&& pool) noexcept
{
    _pool = std::move(pool);
}

RPS::WebApi::DbProvider &RPS::WebApi::DbProvider::operator=(DbProvider&& dbProvider) noexcept
{
    _pool = std::move(dbProvider._pool);
    return *this;
}