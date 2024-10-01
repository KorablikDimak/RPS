#ifndef RPS_IO_FileReader_H
#define RPS_IO_FileReader_H

#include <filesystem>
#include <fstream>
#include <sstream>
#include <format>

#include "RPS/Concepts.h"

namespace RPS::IO::File
{
    template<Concepts::Iterable TCollection,
             Concepts::FromStringStream TSource = typename std::decay_t<TCollection>::value_type>
    TCollection Read(const std::string& fileName)
    {
        const std::filesystem::path path(fileName);
        if (!std::filesystem::exists(path))
            throw std::runtime_error(std::format("Файл {} не существует.", fileName));

        std::ifstream file(fileName);
        if (!file.is_open())
            throw std::runtime_error(std::format("Невозможно открыть файл {}", fileName));

        std::string line;
        std::getline(file, line);
        file.close();

        TCollection collection;
        std::istringstream stream(std::move(line));
        TSource value;
        while (stream >> value)
            collection.insert(collection.end(), value);

        return collection;
    }

    template<Concepts::Iterable TCollection,
            Concepts::FromStringStream TSource = typename std::decay_t<TCollection>::value_type>
    TCollection Read(std::string&& fileName)
    {
        const std::filesystem::path path(fileName);
        if (!std::filesystem::exists(path))
            throw std::runtime_error(std::format("Файл {} не существует.", std::move(fileName)));

        std::ifstream file(fileName);
        if (!file.is_open())
            throw std::runtime_error(std::format("Невозможно открыть файл {}", std::move(fileName)));

        std::string line;
        std::getline(file, line);
        file.close();

        TCollection collection;
        std::istringstream stream(std::move(line));
        TSource value;
        while (stream >> value)
            collection.insert(collection.end(), value);

        return collection;
    }

    template<Concepts::Iterable TCollection>
    requires Concepts::ToStringStream<typename std::decay_t<TCollection>::value_type>
    void Write(const std::string& fileName, TCollection&& collection)
    {
        std::ofstream file(fileName);
        if (!file.is_open())
            throw std::runtime_error(std::format("Невозможно открыть файл {}", fileName));

        std::ostringstream stream;
        for (auto&& element : collection)
            stream << element << "\t";
        const std::string line = stream.str();

        file << line;
        file.close();
    }

    template<Concepts::Iterable TCollection>
    requires Concepts::ToStringStream<typename std::decay_t<TCollection>::value_type>
    void Write(std::string&& fileName, TCollection&& collection)
    {
        std::ofstream file(fileName);
        if (!file.is_open())
            throw std::runtime_error(std::format("Невозможно открыть файл {}", std::move(fileName)));

        std::ostringstream stream;
        for (auto&& element : collection)
            stream << element << "\t";
        const std::string line = stream.str();

        file << line;
        file.close();
    }
}

#endif