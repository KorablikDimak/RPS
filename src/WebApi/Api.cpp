#include <stdexcept>
#include <iostream>
#include <format>

#include "RPS/WebApi/Api.h"

RPS::WebApi::Api::Api(const Storage::Ptr& storage)
{
    const quint16 port = _httpServer.listen(QHostAddress(storage->Host().c_str()), storage->Port());

    if (!port)
        throw std::domain_error("Can not startup http server.");

    // TODO Route

    std::cout << std::format("web api running on http://{}:{}/", storage->Host(), storage->Port()) << std::endl;
}