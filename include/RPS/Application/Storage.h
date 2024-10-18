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
        typedef std::shared_ptr<Storage> Ptr;

        explicit Storage(const std::string& fileName);
        std::string Variable(const std::string& key);

        std::string Host();
        std::uint16_t Port();
    };
}

#endif