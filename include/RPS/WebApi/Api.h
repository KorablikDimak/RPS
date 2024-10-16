#ifndef RPS_WebApi_Api_H
#define RPS_WebApi_Api_H

#include <QtHttpServer>

#include "RPS/WebApi/Storage.h"
#include "RPS/WebApi/DataContext.h"

namespace RPS::WebApi
{
    class Api final
    {
    private:
        QHttpServer _httpServer;

    public:
        Api(const Storage::Ptr& storage, const DataContext::Ptr& dataContext);
    };
}

#endif