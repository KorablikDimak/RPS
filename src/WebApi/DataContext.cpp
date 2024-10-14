#include "RPS/WebApi/DataContext.h"

RPS::WebApi::DataContext::DataContext(const DbProvider::DbProvider::Ptr& dbProvider) noexcept
{
    _dbProvider = dbProvider;
}