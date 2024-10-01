#ifndef RPS_IO_ConsoleReader_H
#define RPS_IO_ConsoleReader_H

#include <iostream>
#include <string>

#include "RPS/Concepts.h"

namespace RPS::IO
{
    class Console final
    {
    public:
        inline Console() noexcept = default;

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
                catch (const std::invalid_argument&)
                {
                    std::cout << "Некорректный ввод" << std::endl;
                }
                catch (const std::out_of_range&)
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
                catch (const std::invalid_argument&)
                {
                    std::cout << "Некорректный ввод" << std::endl;
                }
                catch (const std::out_of_range&)
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
                catch (const std::invalid_argument&)
                {
                    std::cout << "Некорректный ввод" << std::endl;
                }
                catch (const std::out_of_range&)
                {
                    std::cout << "Некорректный ввод" << std::endl;
                }
            }
        }

        template<Concepts::Iterable TCollection, typename TSource = TCollection::value_type>
        TCollection Read() noexcept
        {
            std::cout << "Введите количество элементов." << std::endl;
            const auto size = Read<std::size_t>();

            TCollection collection;

            for (std::size_t i = 1; i <= size; ++i)
            {
                std::cout << "Введите " << i << " элемент:" << std::endl;
                collection.insert(collection.end(), Read<TSource>());
            }

            return collection;
        }
    };
}

#endif