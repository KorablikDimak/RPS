#include <QtCore>
#include <ExtendedCpp/DI.h>

#include "RPS/WebApi/Storage.h"
#include "RPS/WebApi/Api.h"
#include "RPS/WebApi/DbPool.h"
#include "RPS/WebApi/DbProvider.h"
#include "RPS/WebApi/DataContext.h"

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    ExtendedCpp::DI::ServiceProvider serviceProvider;

    serviceProvider.AddSingleton<RPS::WebApi::Storage>(
            [](const ExtendedCpp::DI::ServiceProvider&)
            { return std::make_shared<RPS::WebApi::Storage>("variables.json"); });

    serviceProvider.AddSingleton<RPS::WebApi::DbPool>(
            [](const ExtendedCpp::DI::ServiceProvider& provider)
            { return std::make_shared<RPS::WebApi::DbPool>(provider.GetServiceRequired<RPS::WebApi::Storage>()->ConnectionString(), 2); });

    serviceProvider.AddTransient<RPS::WebApi::DbProvider>(
            [](const ExtendedCpp::DI::ServiceProvider& provider)
            { return std::make_shared<RPS::WebApi::DbProvider>(provider.GetServiceRequired<RPS::WebApi::DbPool>()); });

    serviceProvider.AddTransient<RPS::WebApi::DataContext>(
            [](const ExtendedCpp::DI::ServiceProvider& provider)
            { return std::make_shared<RPS::WebApi::DataContext>(provider.GetServiceRequired<RPS::WebApi::DbProvider>()); });

    RPS::WebApi::Api api(serviceProvider.GetServiceRequired<RPS::WebApi::Storage>(),
                         serviceProvider.GetServiceRequired<RPS::WebApi::DataContext>());
    return QCoreApplication::exec();
}