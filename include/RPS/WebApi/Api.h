#ifndef RPS_WebApi_Api_H
#define RPS_WebApi_Api_H

#include <QtHttpServer>
#include <ExtendedCpp/DI.h>

#include "RPS/WebApi/Storage.h"
#include "RPS/WebApi/DataContext.h"

namespace RPS::WebApi
{
    class Api final
    {
    private:
        QHttpServer _httpServer;
        QTcpServer _tcpserver;

    public:
        explicit Api(const ExtendedCpp::DI::ServiceProvider& serverProvider);
    };
}

#endif