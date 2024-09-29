#ifndef RPS_IO_H
#define RPS_IO_H

#include <iostream>

#include "IO/FileReader.h"
#include "IO/RandomReader.h"
#include "IO/FileWriter.h"

namespace RPS::IO
{
    template<typename T>
    requires std::same_as<unsigned int, T>
    T Get() noexcept
    {
        while (true)
        {
            std::string input;
            std::getline(std::cin, input);

            try
            {
                const int number = std::stoi(input);
                if (number < 0)
                {
                    std::cout << "Некорректный ввод" << std::endl;
                    continue;
                }
                return static_cast<T>(number);
            }
            catch (const std::invalid_argument &)
            {
                std::cout << "Некорректный ввод" << std::endl;
            }
            catch (const std::out_of_range &)
            {
                std::cout << "Некорректный ввод" << std::endl;
            }
        }
    }

    template<typename T>
    requires std::same_as<std::size_t, T>
    T Get() noexcept
    {
        while (true)
        {
            std::string input;
            std::getline(std::cin, input);

            try
            {
                const long long number = std::stoll(input);
                if (number < 0)
                {
                    std::cout << "Некорректный ввод" << std::endl;
                    continue;
                }
                return static_cast<T>(number);
            }
            catch (const std::invalid_argument &)
            {
                std::cout << "Некорректный ввод" << std::endl;
            }
            catch (const std::out_of_range &)
            {
                std::cout << "Некорректный ввод" << std::endl;
            }
        }
    }

    template<typename T>
    requires std::same_as<double, T>
    T Get() noexcept
    {
        while (true)
        {
            std::string input;
            std::getline(std::cin, input);

            try
            {
                return std::stod(input);
            }
            catch (const std::invalid_argument &)
            {
                std::cout << "Некорректный ввод" << std::endl;
            }
            catch (const std::out_of_range &)
            {
                std::cout << "Некорректный ввод" << std::endl;
            }
        }
    }

    inline std::string GetFilePath() noexcept
    {
        while (true)
        {
            std::string filePath;
            std::getline(std::cin, filePath);
            if (exists(std::filesystem::path(filePath)))
                return filePath;
            std::cout << "Данный файл не существует." << std::endl;
        }
    }
}

#endif