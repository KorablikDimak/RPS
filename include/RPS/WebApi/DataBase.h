#ifndef RPS_WebApi_DbRequest_H
#define RPS_WebApi_DbRequest_H

#include "RPS/WebApi/DbProvider.h"

namespace RPS::WebApi
{
    class DataBase
    {
    private:
        static constexpr unsigned char POOL_MAX_SIZE = 2;
        DbProvider::DbProvider::Ptr _dbProvider;

    public:
        typedef std::shared_ptr<DataBase> Ptr;

        explicit DataBase(const std::string& connectionString) noexcept;
        ~DataBase() = default;
    };
}

#endif