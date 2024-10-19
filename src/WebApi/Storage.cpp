#include <fstream>
#include <filesystem>
#include <format>
#include <stdexcept>
#include <sstream>

#include <ExtendedCpp/Json.h>
#ifdef __APPLE__
    #include <CoreFoundation/CFBundle.h>
#endif

#include "Storage.h"

RPS::WebApi::Storage::Storage(const std::string& fileName)
{
#ifdef __APPLE__
    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
    char resourcePath[PATH_MAX];
    if (CFURLGetFileSystemRepresentation(resourceURL, true, reinterpret_cast<UInt8*>(resourcePath), PATH_MAX))
    {
        if (resourceURL != nullptr)
            CFRelease(resourceURL);
    }
    std::filesystem::path path(std::string(resourcePath) + "/" + fileName);
#else
    std::filesystem::path path(fileName);
#endif

    if (!exists(path))
        throw std::invalid_argument(std::format("File {} does not exist.", path.string()));

    std::ifstream file(path.string());
    if (!file.is_open())
        throw std::runtime_error(std::format("File {} can not be opened in read mode.", path.string()));

    std::ostringstream stream;
    std::string line;
    while (std::getline(file, line))
        stream << line;

    try
    {
        ExtendedCpp::Json json = ExtendedCpp::Json::parse(stream.str());
        _storage.clear();
        for (const auto& element : json.items())
            _storage.insert(std::make_pair(element.key(), element.value()));
    }
    catch (const ExtendedCpp::Json::parse_error& ex)
    {
        throw std::runtime_error(std::format("{} has incorrect json format file. Detailed: {}.", path.string(), ex.what()));
    }
}

std::string RPS::WebApi::Storage::Variable(const std::string& key) const
{
    if (!_storage.contains(key))
        throw std::invalid_argument(std::format("Environment storage does not contains key {}", key));
    return _storage.at(key);
}

std::string RPS::WebApi::Storage::ConnectionString() const
{
    return Variable("connection-string");
}

std::string RPS::WebApi::Storage::Host() const
{
    return Variable("host");
}

std::uint16_t RPS::WebApi::Storage::Port() const
{
    return static_cast<std::uint16_t>(std::stoul(Variable("port")));
}