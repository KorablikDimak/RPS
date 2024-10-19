#include <stdexcept>
#include <iostream>
#include <format>

#include <ExtendedCpp/LINQ/Sort.h>

#include "Api.h"

RPS::WebApi::Api::Api(const ExtendedCpp::DI::ServiceProvider& serverProvider)
{
    _httpServer.route("/Get/<arg>", QHttpServerRequest::Method::Get, [serverProvider](const std::int64_t id)
    {
        const auto array = serverProvider.GetServiceRequired<DataContext>()->Get(id).get();
        if (!array.has_value())
            return QHttpServerResponse(QHttpServerResponder::StatusCode::NoContent);
        const ExtendedCpp::Json json = array.value();
        return QHttpServerResponse(QString(json.dump().c_str()));
    });

    _httpServer.route("/Get", QHttpServerRequest::Method::Get, [serverProvider]()
    {
        const auto arrays = serverProvider.GetServiceRequired<DataContext>()->Get().get();
        const ExtendedCpp::Json json = arrays;
        return QHttpServerResponse(QString(json.dump().c_str()));
    });

    _httpServer.route("/Add", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            const auto array = json.get<DbArray<double>>();
            serverProvider.GetServiceRequired<DataContext>()->Add(array);
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Created);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    _httpServer.route("/Add", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            const auto arrays = json.get<std::vector<DbArray<double>>>();
            serverProvider.GetServiceRequired<DataContext>()->Add(arrays);
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Created);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    _httpServer.route("/Update", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            const auto array = json.get<DbArray<double>>();
            serverProvider.GetServiceRequired<DataContext>()->Update(array);
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    _httpServer.route("/Update", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            const auto arrays = json.get<std::vector<DbArray<double>>>();
            serverProvider.GetServiceRequired<DataContext>()->Update(arrays);
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    _httpServer.route("/Delete", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            const auto array = json.get<DbArray<double>>();
            serverProvider.GetServiceRequired<DataContext>()->Delete(array);
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    _httpServer.route("/Delete", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            const auto arrays = json.get<std::vector<DbArray<double>>>();
            serverProvider.GetServiceRequired<DataContext>()->Delete(arrays);
            return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    _httpServer.route("/Sort/<arg>", QHttpServerRequest::Method::Post, [serverProvider](const std::int64_t id)
    {
        auto optArray = serverProvider.GetServiceRequired<DataContext>()->Get(id).get();
        if (!optArray.has_value())
            return QHttpServerResponse(QHttpServerResponder::StatusCode::NoContent);

        auto array = optArray.value();
        if (!array.inner_array.empty())
            ExtendedCpp::LINQ::Sort::QuickSort(array.inner_array.data(), 0, array.inner_array.size() - 1);
        array.is_sorted = true;

        serverProvider.GetServiceRequired<DataContext>()->Update(array);
        return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
    });

    _httpServer.route("/Sort", QHttpServerRequest::Method::Post, [serverProvider](const QHttpServerRequest& request)
    {
        try
        {
            const auto json = ExtendedCpp::Json::parse(request.body().toStdString());
            auto array = json.get<DbArray<double>>();

            if (!array.inner_array.empty())
                ExtendedCpp::LINQ::Sort::QuickSort(array.inner_array.data(), 0, array.inner_array.size() - 1);
            array.is_sorted = true;

            auto optArray = serverProvider.GetServiceRequired<DataContext>()->Get(array.id).get();
            if (optArray.has_value())
                serverProvider.GetServiceRequired<DataContext>()->Update(array);
            else
                serverProvider.GetServiceRequired<DataContext>()->Add(array);

            return QHttpServerResponse(QHttpServerResponder::StatusCode::Ok);
        }
        catch (const ExtendedCpp::Json::parse_error& ex)
        {
            return QHttpServerResponse(ex.what(), QHttpServerResponder::StatusCode::Conflict);
        }
    });

    const auto storage = serverProvider.GetServiceRequired<Storage>();
    if (!_tcpserver.listen(QHostAddress(storage->Host().c_str()), storage->Port()))
        throw std::domain_error("Can not startup http server.");
    else
    {
        _httpServer.bind(&_tcpserver);
        std::cout << std::format("WebApi running on http://{}:{}/", storage->Host(), storage->Port()) << std::endl;
    }
}