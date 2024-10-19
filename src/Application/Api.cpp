#include <QNetworkReply>
#include <QByteArray>
#include <ExtendedCpp/Json.h>

#include "Api.h"

RPS::Application::Api::Api(const Storage& storage) noexcept
{
    _networkManager = new QNetworkAccessManager();
    _serverAddress = "http://" + QString(storage.Host().c_str()) + ":" + QString(storage.Port()) + "/";
}

RPS::Application::Api::~Api()
{
    delete _networkManager;
}

std::vector<RPS::Application::Array<double>> RPS::Application::Api::GetArrays() const noexcept
{
    QNetworkRequest request;
    request.setUrl(QUrl(_serverAddress + "Get"));
    QNetworkReply* reply = _networkManager->get(request);
    const auto json = ExtendedCpp::Json::parse(reply->readAll().toStdString());
    return json.get<std::vector<Array<double>>>();
}

void RPS::Application::Api::AddArray(const RPS::Application::Array<double>& array) const noexcept
{
    QNetworkRequest request;
    request.setUrl(QUrl(_serverAddress + "Add"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    const ExtendedCpp::Json jsonRequest = array;
    _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                              static_cast<qsizetype>(jsonRequest.dump().size())));
}

void RPS::Application::Api::UpdateArray(const RPS::Application::Array<double>& array) const noexcept
{
    QNetworkRequest request;
    request.setUrl(QUrl(_serverAddress + "Update"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    const ExtendedCpp::Json jsonRequest = array;
    _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                              static_cast<qsizetype>(jsonRequest.dump().size())));
}

void RPS::Application::Api::DeleteArray(const RPS::Application::Array<double>& array) const noexcept
{
    QNetworkRequest request;
    request.setUrl(QUrl(_serverAddress + "Delete"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    const ExtendedCpp::Json jsonRequest = array;
    _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                              static_cast<qsizetype>(jsonRequest.dump().size())));
}

void RPS::Application::Api::SortArray(const RPS::Application::Array<double>& array) const noexcept
{
    QNetworkRequest request;
    request.setUrl(QUrl(_serverAddress + "Sort"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    const ExtendedCpp::Json jsonRequest = array;
    _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                              static_cast<qsizetype>(jsonRequest.dump().size())));
}