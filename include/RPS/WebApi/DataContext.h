#ifndef RPS_WebApi_DataContext_H
#define RPS_WebApi_DataContext_H

#include "RPS/WebApi/DbProvider.h"
#include "RPS/WebApi/DbArray.h"

namespace RPS::WebApi
{
    class DataContext final
    {
    private:
        DbProvider::DbProvider::Ptr _dbProvider;
        std::vector<DbArray> _arrays;

    public:
        typedef std::shared_ptr<DataContext> Ptr;

        explicit DataContext(const DbProvider::DbProvider::Ptr& dbProvider) noexcept;
    };
}

#endif