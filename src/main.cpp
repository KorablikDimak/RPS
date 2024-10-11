#include <iostream>
#include <memory>

#include <ExtendedCpp/LINQ.h>
#include <ExtendedCpp/Random.h>

#include "RPS/IO/Console.h"
#include "RPS/IO/File.h"

int main()
{
    using TSortedType = double;

    while (true)
    {
        std::vector<TSortedType> array;

        while (true)
        {
            std::cout << "1- сгенерировать массив, 2- прочитать из файла, 3- ручной ввод." << std::endl;
            const auto choice = RPS::IO::Console().Read<unsigned int>();

            if (choice == 1)
            {
                std::cout << "Введите нижнюю границу генерации." << std::endl;
                const auto min = RPS::IO::Console().Read<TSortedType>();

                std::cout << "Введите верхнюю границу генерации." << std::endl;
                const auto max = RPS::IO::Console().Read<TSortedType>();

                std::cout << "Введите длину генерируемого массива." << std::endl;
                const auto size = RPS::IO::Console().Read<std::size_t>();

                array = ExtendedCpp::Random::RandomSequence(min, max, size);
                break;
            }
            else if (choice == 2)
            {
                std::cout << "Введите путь к файлу." << std::endl;
                std::string filePath;
                std::getline(std::cin, filePath);

                try
                {
                    array = RPS::IO::File(std::move(filePath)).Read<std::vector<TSortedType>>();
                    break;
                }
                catch (const std::runtime_error& ex)
                {
                    std::cout << ex.what() << std::endl;
                    continue;
                }
            }
            else if (choice == 3)
            {
                array = RPS::IO::Console().Read<std::vector<TSortedType>>();
                break;
            }
            else
            {
                std::cout << "Некорректный ввод." << std::endl;
                continue;
            }
        }

        std::cout << "Исходный массив:" << std::endl;
        for (const auto element : array)
            std::cout << element << "\t";
        std::cout << std::endl;

        ExtendedCpp::LINQ::Sort::QuickSort(array.data(), 0, array.size() - 1);

        std::cout << "Отсортированный массив:" << std::endl;
        for (const auto element : array)
            std::cout << element << "\t";
        std::cout << std::endl;

        while (true)
        {
            std::cout << "Выберете 1 чтобы сохранить отсортированный массив в файл, "
                         "2 чтобы повторить работу программы "
                         "или любые другие символы чтобы завершить программу" << std::endl;
            const auto choice = RPS::IO::Console().Read<unsigned int>();

            if (choice == 1)
            {
                std::cout << "Введите путь к файлу." << std::endl;
                std::string filePath;
                std::getline(std::cin, filePath);

                try
                {
                    RPS::IO::File(std::move(filePath)).Write(std::move(array));
                    std::cout << "Файл сохранен." << std::endl;
                }
                catch (const std::runtime_error& ex)
                {
                    std::cout << ex.what() << std::endl;
                    continue;
                }

                std::cout << "Выберете 1 чтобы повторить работу программы "
                             "или любые другие символы чтобы завершить программу" << std::endl;
                const auto quitChoice = RPS::IO::Console().Read<unsigned int>();

                if (quitChoice == 1)
                {
                    break;
                }
                else
                {
                    return EXIT_SUCCESS;
                }
            }
            else if (choice == 2)
            {
                break;
            }
            else
            {
                return EXIT_SUCCESS;
            }
        }
    }
}