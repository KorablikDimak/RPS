#include "RPS/WebApi/DataBase.h"

RPS::WebApi::DataBase::DataBase(const std::string &connectionString) noexcept
{
    _dbProvider = std::make_unique<RPS::WebApi::DbProvider>(connectionString, POOL_MAX_SIZE);
}