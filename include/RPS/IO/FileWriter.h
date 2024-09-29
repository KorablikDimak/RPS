#ifndef RPS_IO_FileWriter_H
#define RPS_IO_FileWriter_H

#include <filesystem>
#include <fstream>
#include <sstream>

#include "IWriter.h"

namespace RPS::IO
{
    template<typename TSource>
    class FileWriter final : public IWriter<TSource>
    {
    private:
        std::string _fileName;

    public:
        explicit FileWriter(const std::string& fileName) noexcept : _fileName(fileName) {}
        explicit FileWriter(std::string&& fileName) noexcept : _fileName(std::move(fileName)) {}

        ~FileWriter() override = default;

        void WriteArray(const std::vector<TSource>& array) const override
        {
            const std::filesystem::path path(_fileName);
            if (!std::filesystem::exists(path))
                throw std::runtime_error(_fileName + std::string(" does not exist."));

            std::ofstream file(_fileName);
            if (!file.is_open())
                throw std::runtime_error(std::string("Unable to open file ") + _fileName);

            std::ostringstream stream;
            for (const auto& element : array)
                stream << std::to_string(element);
            std::string line = stream.str();

            file << line;
            file.close();
        }
    };
}

#endif