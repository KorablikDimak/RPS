#ifndef RPS_STORAGE_H
#define RPS_STORAGE_H

#include <string>
#include <map>
#include <memory>

namespace RPS::WebApi
{
    class Storage final
    {
    private:
        std::map<std::string, std::string> _storage;

    public:
        typedef std::shared_ptr<Storage> Ptr;

        explicit Storage(std::string_view file);
        std::string Variable(const std::string& key);

        std::string ConnectionString();
        std::string Host();
        std::uint16_t Port();
    };
}

#endif