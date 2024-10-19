#include <QtCore>
#include <ExtendedCpp/DI.h>

#include "Storage.h"
#include "Api.h"
#include "DbPool.h"
#include "DbProvider.h"
#include "DataContext.h"

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    ExtendedCpp::DI::ServiceProvider serviceProvider;

    serviceProvider.AddSingleton<RPS::WebApi::Storage>(
            [](const ExtendedCpp::DI::ServiceProvider&)
            { return std::make_shared<RPS::WebApi::Storage>("settings.json"); });

    serviceProvider.AddSingleton<RPS::WebApi::DbPool>(
            [](const ExtendedCpp::DI::ServiceProvider& provider)
            { return std::make_shared<RPS::WebApi::DbPool>(provider.GetServiceRequired<RPS::WebApi::Storage>()->ConnectionString(),
                                                           provider.GetServiceRequired<RPS::WebApi::Storage>()->PoolSize()); });

    serviceProvider.AddTransient<RPS::WebApi::DbProvider>(
            [](const ExtendedCpp::DI::ServiceProvider& provider)
            { return std::make_shared<RPS::WebApi::DbProvider>(provider.GetServiceRequired<RPS::WebApi::DbPool>()); });

    serviceProvider.AddTransient<RPS::WebApi::DataContext>(
            [](const ExtendedCpp::DI::ServiceProvider& provider)
            { return std::make_shared<RPS::WebApi::DataContext>(provider.GetServiceRequired<RPS::WebApi::DbProvider>()); });

    RPS::WebApi::Api api(serviceProvider);
    return QCoreApplication::exec();
}