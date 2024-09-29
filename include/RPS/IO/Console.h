#ifndef RPS_IO_ConsoleReader_H
#define RPS_IO_ConsoleReader_H

#include <iostream>

namespace RPS::IO::Console
{
    template<typename TSource>
    requires std::same_as<unsigned int, TSource>
    TSource Read() noexcept
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
                return static_cast<unsigned int>(number);
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

    template<typename TSource>
    requires std::same_as<std::size_t, TSource>
    TSource Read() noexcept
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
                return static_cast<std::size_t>(number);
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

    template<typename TSource>
    requires std::same_as<double, TSource>
    TSource Read() noexcept
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

    template<typename TSource>
    std::vector<TSource> Read(std::size_t elementsCount) noexcept
    {
        std::vector<TSource> array(elementsCount);

        for (std::size_t i = 0; i < elementsCount; ++i)
        {
            std::cout << "Введите " << i << " элемент:" << std::endl;
            array[i] = Read<TSource>();
        }

        return array;
    }
}

#endif