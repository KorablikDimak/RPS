#ifndef RPS_IO_FileReader_H
#define RPS_IO_FileReader_H

#include <filesystem>
#include <fstream>
#include <sstream>
#include <format>

#include "../Concepts.h"

namespace RPS::IO::File
{
    template<typename TSource>
    std::vector<TSource> Read(const std::string_view& fileName)
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

        std::vector<TSource> array;
        std::istringstream stream(std::move(line));
        TSource number;
        while (stream >> number)
            array.push_back(number);

        return array;
    }

    template<Concepts::Iterable TCollection>
    void Write(const std::string_view& fileName, const TCollection& collection)
    {
        std::ofstream file(fileName);
        if (!file.is_open())
            throw std::runtime_error(std::format("Невозможно открыть файл {}", fileName));

        std::ostringstream stream;
        for (const auto& element : collection)
            stream << element << "\t";
        const std::string line = stream.str();

        file << line;
        file.close();
    }
}

#endif