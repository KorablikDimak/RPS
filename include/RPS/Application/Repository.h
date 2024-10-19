#ifndef RPS_Application_Repository_H
#define RPS_Application_Repository_H

#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>
#include <QByteArray>
#include <QEventLoop>
#include <ExtendedCpp/Json.h>

#include "Storage.h"

namespace RPS::Application
{
    template<typename T>
    class Repository final
    {
    public:
        explicit Repository(const Storage& storage) noexcept
        {
            _networkManager = new QNetworkAccessManager();
            _serverAddress = "http://" + QString(storage.Host().c_str()) + ":" +
                             QString(std::to_string(storage.Port()).c_str()) + "/";
        }

        ~Repository()
        {
            delete _networkManager;
        }

        [[nodiscard]]
        std::vector<T> Get() const
        {
            QNetworkRequest request;
            request.setUrl(QUrl(_serverAddress + "Get"));
            QNetworkReply* reply = _networkManager->get(request);

            QEventLoop eventLoop;
            QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            const auto json = ExtendedCpp::Json::parse(reply->readAll().toStdString());
            return json.get<std::vector<T>>();
        }

        void Add(const T& data) const noexcept
        {
            QNetworkRequest request;
            request.setUrl(QUrl(_serverAddress + "Add"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            const ExtendedCpp::Json jsonRequest = data;
            QNetworkReply* reply = _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                                         static_cast<qsizetype>(jsonRequest.dump().size())));
            QEventLoop eventLoop;
            QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();
        }

        void Update(const T& data) const noexcept
        {
            QNetworkRequest request;
            request.setUrl(QUrl(_serverAddress + "Update"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            const ExtendedCpp::Json jsonRequest = data;
            QNetworkReply* reply = _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                                         static_cast<qsizetype>(jsonRequest.dump().size())));
            QEventLoop eventLoop;
            QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();
        }

        void Delete(const T& data) const noexcept
        {
            QNetworkRequest request;
            request.setUrl(QUrl(_serverAddress + "Delete"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            const ExtendedCpp::Json jsonRequest = data;
            QNetworkReply* reply = _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                                         static_cast<qsizetype>(jsonRequest.dump().size())));
            QEventLoop eventLoop;
            QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();
        }

        T Sort(const T& data) const noexcept
        {
            QNetworkRequest request;
            request.setUrl(QUrl(_serverAddress + "Sort"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            const ExtendedCpp::Json jsonRequest = data;
            QNetworkReply* reply = _networkManager->post(request, QByteArray(jsonRequest.dump().c_str(),
                                                         static_cast<qsizetype>(jsonRequest.dump().size())));

            QEventLoop eventLoop;
            QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
            eventLoop.exec();

            const auto json = ExtendedCpp::Json::parse(reply->readAll().toStdString());
            return json.get<T>();
        }

    private:
        QNetworkAccessManager* _networkManager;
        QString _serverAddress;
    };
}

#endif