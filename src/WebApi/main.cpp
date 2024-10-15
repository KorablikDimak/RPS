#include <iostream>
#include <stdexcept>

#include <QtCore>

#include "RPS/WebApi/Api.h"

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);
    QHttpServer httpServer;

    try
    {
        RPS::WebApi::Api::Startup(httpServer);
    }
    catch (const std::domain_error& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return QCoreApplication::exec();
}