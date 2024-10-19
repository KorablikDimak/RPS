#ifndef RPS_WebApi_Storage_H
#define RPS_WebApi_Storage_H

#include <string>
#include <map>
#include <memory>
#include <cstdint>

namespace RPS::WebApi
{
    class Storage final
    {
    private:
        std::map<std::string, std::string> _storage;

    public:
        typedef std::shared_ptr<Storage> Ptr;

        explicit Storage(const std::string& fileName);
        [[nodiscard]]
        std::string Variable(const std::string& key) const;

        [[nodiscard]]
        std::string ConnectionString() const;
        [[nodiscard]]
        std::string Host() const;
        [[nodiscard]]
        std::uint16_t Port() const;
    };
}

#endif