#include <stdexcept>
#include <iostream>
#include <format>

#include "RPS/WebApi/Api.h"

RPS::WebApi::Api::Api(const Storage::Ptr& storage, const DataContext::Ptr& dataContext)
{
    _httpServer.route("/GetArray/<arg>", [dataContext](const std::int64_t id)
    {
        auto array = dataContext->Get(id).get().inner_array;
        std::ostringstream stream;
        for (const auto element : array)
            stream << element << "\t";
        stream << "\n";
        return QString(stream.str().c_str());
    });

    _httpServer.route("/GetArrays", [dataContext]()
    {
        auto arrays = dataContext->Get().get();
        std::ostringstream stream;
        for (const auto& array : arrays)
        {
            for (const auto element : array.inner_array)
                stream << element << "\t";
            stream << "\n";
        }
        return QString(stream.str().c_str());
    });

    const quint16 port = _httpServer.listen(QHostAddress(storage->Host().c_str()), storage->Port());

    if (!port)
        throw std::domain_error("Can not startup http server.");
    else
        std::cout << std::format("web api running on http://{}:{}/", storage->Host(), storage->Port()) << std::endl;
}