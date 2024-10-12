#ifndef RPS_WebApi_Api_H
#define RPS_WebApi_Api_H

#include <QtHttpServer>

namespace RPS::WebApi
{
    void Startup(QHttpServer& httpServer);
}

#endif