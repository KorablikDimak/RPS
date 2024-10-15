#include <stdexcept>

#include "RPS/WebApi/Api.h"

void RPS::WebApi::Api::Startup(QHttpServer& httpServer)
{
    const quint16 port = httpServer.listen(QHostAddress::Any);

    if (!port)
        throw std::domain_error("Can not startup http server.");

    // TODO Route

    qDebug() << QCoreApplication::translate("WebApi", "Running on http://127.0.0.1:%1/").arg(port);
}