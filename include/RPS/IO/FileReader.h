#ifndef RPS_IO_FileReader_H
#define RPS_IO_FileReader_H

#include <filesystem>
#include <fstream>
#include <sstream>

#include "IReader.h"

namespace RPS::IO
{
    template<typename TSource>
    class FileReader final : public IReader<TSource>
    {
    private:
        std::string _fileName;

    public:
        explicit FileReader(const std::string& fileName) noexcept : _fileName(fileName) {}
        explicit FileReader(std::string&& fileName) noexcept : _fileName(std::move(fileName)) {}

        ~FileReader() override = default;

        std::vector<TSource> ReadArray() const override
        {
            const std::filesystem::path path(_fileName);
            if (!std::filesystem::exists(path))
                throw std::runtime_error(_fileName + std::string(" does not exist."));

            std::ifstream file(_fileName);
            if (!file.is_open())
                throw std::runtime_error(std::string("Unable to open file ") + _fileName);

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
    };
}

#endif