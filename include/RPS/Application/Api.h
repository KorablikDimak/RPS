#ifndef RPS_API_H
#define RPS_API_H

#include <QtNetwork/QNetworkAccessManager>

#include "Array.h"
#include "Storage.h"

namespace RPS::Application
{
    class Api
    {
    public:
        explicit Api(const Storage& storage) noexcept;
        ~Api();

        [[nodiscard]]
        std::vector<Array<double>> GetArrays() const noexcept;
        void AddArray(const Array<double>& array) const noexcept;
        void UpdateArray(const Array<double>& array) const noexcept;
        void DeleteArray(const Array<double>& array) const noexcept;
        void SortArray(const Array<double>& array) const noexcept;

    private:
        QNetworkAccessManager* _networkManager;
        QString _serverAddress;
    };
}

#endif