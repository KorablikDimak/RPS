#include <iostream>
#include <memory>

#include "../include/RPS/IO.h"
#include "../include/RPS/Random.h"
#include "../include/RPS/Sort.h"

int main()
{
    using TSource = double;

    while (true)
    {
        std::unique_ptr<RPS::IO::IReader<TSource>> reader;

        while (true)
        {
            std::cout << "1- сгенерировать массив, 2- прочитать из файла" << std::endl;
            const auto choice = RPS::IO::Get<unsigned int>();

            if (choice == 1)
            {
                std::cout << "Введите нижнюю границу генерации." << std::endl;
                const auto min = RPS::IO::Get<TSource>();

                std::cout << "Введите верхнюю границу генерации." << std::endl;
                const auto max = RPS::IO::Get<TSource>();

                std::cout << "Введите длину генерируемого массива." << std::endl;
                const auto size = RPS::IO::Get<std::size_t>();

                std::unique_ptr<RPS::IO::IReader<TSource>> temp =
                        std::make_unique<RPS::IO::RandomReader<TSource>>(
                                [min, max, size]{ return RPS::Random::RandomSequence(min, max, size); });
                reader.swap(temp);
                break;
            }
            else if (choice == 2)
            {
                std::cout << "Введите путь к файлу." << std::endl;
                std::string filePath = RPS::IO::GetFilePath();

                std::unique_ptr<RPS::IO::IReader<TSource>> temp =
                        std::make_unique<RPS::IO::FileReader<TSource>>(std::move(filePath));
                reader.swap(temp);
                break;
            }
            else
            {
                std::cout << "Некорректный ввод." << std::endl;
                continue;
            }
        }

        std::vector<TSource> array;

        try
        {
            array = reader->ReadArray();
        }
        catch (const std::runtime_error& ex)
        {
            std::cout << ex.what() << std::endl;
            break;
        }

        std::cout << "Исходный массив:" << std::endl;
        for (const auto element : array)
            std::cout << element << "\t";
        std::cout << std::endl;

        RPS::Sort::QuickSort(array);

        std::cout << "Отсортированный массив:" << std::endl;
        for (const auto element : array)
            std::cout << element << "\t";
        std::cout << std::endl;

        while (true)
        {
            std::cout << "Выберете 1 чтобы сохранить отсортированный массив в файл "
                         "или любые другие символы чтобы завершить программу" << std::endl;
            const auto choice = RPS::IO::Get<unsigned int>();

            if (choice == 1)
            {
                std::cout << "Введите путь к файлу." << std::endl;
                std::string filePath = RPS::IO::GetFilePath();
                RPS::IO::FileWriter<TSource> writer(std::move(filePath));

                try
                {
                    writer.WriteArray(array);
                }
                catch (const std::runtime_error& ex)
                {
                    std::cout << ex.what() << std::endl;
                    continue;
                }

                return EXIT_SUCCESS;
            }
            else
            {
                return EXIT_SUCCESS;
            }
        }
    }
}