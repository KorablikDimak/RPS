#ifndef RPS_Application_Storage_H
#define RPS_Application_Storage_H

#include <string>
#include <map>
#include <memory>
#include <cstdint>

namespace RPS::Application
{
    class Storage final
    {
    private:
        std::map<std::string, std::string> _storage;

    public:
        explicit Storage(const std::string& fileName);
        [[nodiscard]]
        std::string Variable(const std::string& key) const;

        [[nodiscard]]
        std::string Host() const;
        [[nodiscard]]
        std::uint16_t Port() const;
    };
}

#endif