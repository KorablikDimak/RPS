#include <stdexcept>
#include <iostream>
#include <format>

#include "RPS/WebApi/Api.h"

RPS::WebApi::Api::Api(const ExtendedCpp::DI::ServiceProvider& serverProvider)
{
    _httpServer.route("/GetArray/<arg>", [serverProvider](const std::int64_t id)
    {
        auto array = serverProvider.GetServiceRequired<DataContext>()->Get(id).get().inner_array;
        std::ostringstream stream;
        for (const auto element : array)
            stream << element << "\t";
        stream << "\n";
        return QString(stream.str().c_str());
    });

    _httpServer.route("/GetArrays", [serverProvider]()
    {
        auto arrays = serverProvider.GetServiceRequired<DataContext>()->Get().get();
        std::ostringstream stream;
        for (const auto& array : arrays)
        {
            for (const auto element : array.inner_array)
                stream << element << "\t";
            stream << "\n";
        }
        return QString(stream.str().c_str());
    });

    auto storage = serverProvider.GetServiceRequired<Storage>();
    if (!_tcpserver.listen(QHostAddress(storage->Host().c_str()), storage->Port()) || !_httpServer.bind(&_tcpserver))
        throw std::domain_error("Can not startup http server.");
    else
        std::cout << std::format("web api running on http://{}:{}/", storage->Host(), storage->Port()) << std::endl;
}