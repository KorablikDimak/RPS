#ifndef RPS_WebApi_Api_H
#define RPS_WebApi_Api_H

#include <QtHttpServer>

#include "RPS/WebApi/Storage.h"

namespace RPS::WebApi
{
    class Api final
    {
    private:
        QHttpServer _httpServer;

    public:
        explicit Api(const Storage::Ptr& storage);
    };
}

#endif