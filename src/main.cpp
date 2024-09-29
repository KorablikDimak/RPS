#include <iostream>
#include <memory>

#include "../include/RPS/IO/Console.h"
#include "../include/RPS/IO/File.h"
#include "../include/RPS/Random.h"
#include "../include/RPS/Sort.h"

int main()
{
    using TSource = double;
    using namespace RPS;

    while (true)
    {
        std::vector<TSource> array;

        while (true)
        {
            std::cout << "1- сгенерировать массив, 2- прочитать из файла, 3- ручной ввод." << std::endl;
            const auto choice = IO::Console::Read<unsigned int>();

            if (choice == 1)
            {
                std::cout << "Введите нижнюю границу генерации." << std::endl;
                const auto min = IO::Console::Read<TSource>();

                std::cout << "Введите верхнюю границу генерации." << std::endl;
                const auto max = IO::Console::Read<TSource>();

                std::cout << "Введите длину генерируемого массива." << std::endl;
                const auto size = IO::Console::Read<std::size_t>();

                array = Random::RandomSequence(min, max, size);
                break;
            }
            else if (choice == 2)
            {
                std::cout << "Введите путь к файлу." << std::endl;
                std::string filePath;
                std::getline(std::cin, filePath);

                try
                {
                    array = IO::File::Read<TSource>(filePath);
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
                std::cout << "Введите количество элементов." << std::endl;
                const auto size = IO::Console::Read<std::size_t>();

                array = IO::Console::Read<TSource>(size);
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

        Sort::QuickSort(array);

        std::cout << "Отсортированный массив:" << std::endl;
        for (const auto element : array)
            std::cout << element << "\t";
        std::cout << std::endl;

        while (true)
        {
            std::cout << "Выберете 1 чтобы сохранить отсортированный массив в файл "
                         "или любые другие символы чтобы завершить программу" << std::endl;
            const auto choice = IO::Console::Read<unsigned int>();

            if (choice == 1)
            {
                std::cout << "Введите путь к файлу." << std::endl;
                std::string filePath;
                std::getline(std::cin, filePath);

                try
                {
                    IO::File::Write(filePath, array);
                    std::cout << "Файл сохранен." << std::endl;
                    return EXIT_SUCCESS;
                }
                catch (const std::runtime_error& ex)
                {
                    std::cout << ex.what() << std::endl;
                    continue;
                }
            }
            else
            {
                return EXIT_SUCCESS;
            }
        }
    }
}