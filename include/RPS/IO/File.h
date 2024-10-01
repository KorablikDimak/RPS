#ifndef RPS_IO_FileReader_H
#define RPS_IO_FileReader_H

#include <filesystem>
#include <fstream>
#include <sstream>
#include <format>

#include "RPS/Concepts.h"

namespace RPS::IO
{
    class File
    {
    private:
        std::string _fileName;

    public:
        template<std::convertible_to<std::string> TString>
        explicit File(TString&& fileName) noexcept : _fileName(std::forward<TString>(fileName)) {}

        template<Concepts::Iterable TCollection,
                 Concepts::FromStringStream TSource = typename std::decay_t<TCollection>::value_type>
        TCollection Read()
        {
            const std::filesystem::path path(_fileName);
            if (!std::filesystem::exists(path))
                throw std::runtime_error(std::format("Файл {} не существует.", _fileName));

            std::ifstream file(_fileName);
            if (!file.is_open())
                throw std::runtime_error(std::format("Невозможно открыть файл {}", _fileName));

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
        void Write(TCollection&& collection)
        {
            std::ofstream file(_fileName);
            if (!file.is_open())
                throw std::runtime_error(std::format("Невозможно открыть файл {}", _fileName));

            std::ostringstream stream;
            for (auto&& element : collection)
                stream << element << "\t";
            const std::string line = stream.str();

            file << line;
            file.close();
        }
    };
}

#endif