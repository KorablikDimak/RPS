#include <fstream>
#include <filesystem>
#include <format>
#include <stdexcept>
#include <sstream>

#include <ExtendedCpp/Json.h>

#include "RPS/WebApi/Storage.h"

RPS::WebApi::Storage::Storage(std::string_view filePath)
{
    std::filesystem::path path(filePath);
    if (!exists(path))
        throw std::invalid_argument(std::format("File {} does not exist.", filePath));

    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error(std::format("File {} can not be opened in read mode.", filePath));

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
        throw std::runtime_error(std::format("{} has incorrect json format file. Detailed: {}.", filePath, ex.what()));
    }
}

std::string RPS::WebApi::Storage::Variable(const std::string& key)
{
    if (!_storage.contains(key))
        throw std::invalid_argument(std::format("Environment storage does not contains key {}", key));
    return _storage.at(key);
}

std::string RPS::WebApi::Storage::ConnectionString()
{
    return Variable("connection-string");
}

std::string RPS::WebApi::Storage::Host()
{
    return Variable("host");
}

std::uint16_t RPS::WebApi::Storage::Port()
{
    return std::stoul(Variable("port"));
}