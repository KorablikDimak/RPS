#include <iostream>

#include <gtest/gtest.h>
#include <ExtendedCpp/Random.h>
#include <ExtendedCpp/LINQ.h>

#include "Storage.h"
#include "DataContext.h"

std::mutex mutex;

const RPS::WebApi::Storage storage("settings.json");

RPS::WebApi::DataContext GetDataContext() noexcept
{
    const auto dbPool = std::make_shared<RPS::WebApi::DbPool>(storage.ConnectionString(),
                                                                                      storage.PoolSize());
    const auto dbProvider = std::make_shared<RPS::WebApi::DbProvider>(dbPool);
    return RPS::WebApi::DataContext(dbProvider);
}

const RPS::WebApi::DataContext dataContext = GetDataContext();

TEST(DatabaseTests, TestAdd100)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 100;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));

    const auto start = std::chrono::system_clock::now();
    dataContext.Add(arrays).get();
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    std::cout << std::format("{} saves, time in milliseconds: {}",
                             DATABASE_SIZE,
                             std::chrono::duration_cast<std::chrono::milliseconds>(timeResult).count())
                             << std::endl;

    const auto savedResult = dataContext.Get().get();
    ASSERT_EQ(arrays.size(), savedResult.size());
    GetDataContext().Delete(savedResult);
}

TEST(DatabaseTests, TestAdd1000)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 1000;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));

    const auto start = std::chrono::system_clock::now();
    dataContext.Add(arrays).get();
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    std::cout << std::format("{} saves, time in milliseconds: {}",
                             DATABASE_SIZE,
                             std::chrono::duration_cast<std::chrono::milliseconds>(timeResult).count())
                             << std::endl;

    const auto savedResult = dataContext.Get().get();
    ASSERT_EQ(arrays.size(), savedResult.size());
    dataContext.Delete(savedResult);
}

TEST(DatabaseTests, TestAdd10000)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 10000;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));

    const auto start = std::chrono::system_clock::now();
    dataContext.Add(arrays).get();
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    std::cout << std::format("{} saves, time in milliseconds: {}",
                             DATABASE_SIZE,
                             std::chrono::duration_cast<std::chrono::milliseconds>(timeResult).count())
                             << std::endl;

    const auto savedResult = dataContext.Get().get();
    ASSERT_EQ(arrays.size(), savedResult.size());
    dataContext.Delete(savedResult);
}

TEST(DatabaseTests, TestSort100)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 100;
    constexpr std::size_t SORT_SIZE = 100;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));
    dataContext.Add(arrays).get();

    const auto ids = ExtendedCpp::LINQ::From(dataContext.Get().get())
            .Select([](const RPS::WebApi::DbArray<double>& array){ return array.id; })
            .ToVector();

    ASSERT_EQ(ids.size(), SORT_SIZE);

    const auto start = std::chrono::system_clock::now();
    for (const auto id : ids)
    {
        auto array = dataContext.Get(id).get().value();
        ExtendedCpp::LINQ::Sort::QuickSort(array.inner_array.data(), 0, array.inner_array.size() - 1);
    }
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    std::cout << std::format("{} row database, {} arrays sorts, all time in microseconds: {}\n"
                             "Average time for 1 array: {}",
                             DATABASE_SIZE, SORT_SIZE,
                             std::chrono::duration_cast<std::chrono::microseconds>(timeResult).count(),
                             std::chrono::duration_cast<std::chrono::microseconds>(timeResult).count() / SORT_SIZE)
                             << std::endl;

    dataContext.Delete(dataContext.Get().get());
}

TEST(DatabaseTests, TestSort1000)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 1000;
    constexpr std::size_t SORT_SIZE = 100;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));
    dataContext.Add(arrays).get();

    const auto ids = ExtendedCpp::LINQ::From(dataContext.Get().get())
            .Select([](const RPS::WebApi::DbArray<double>& array){ return array.id; })
            .Take(SORT_SIZE)
            .ToVector();

    ASSERT_EQ(ids.size(), SORT_SIZE);

    const auto start = std::chrono::system_clock::now();
    for (const auto id : ids)
    {
        auto array = dataContext.Get(id).get().value();
        ExtendedCpp::LINQ::Sort::QuickSort(array.inner_array.data(), 0, array.inner_array.size() - 1);
    }
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    std::cout << std::format("{} row database, {} arrays sorts, all time in microseconds: {}\n"
                             "Average time for 1 array: {}",
                             DATABASE_SIZE, SORT_SIZE,
                             std::chrono::duration_cast<std::chrono::microseconds>(timeResult).count(),
                             std::chrono::duration_cast<std::chrono::microseconds>(timeResult).count() / SORT_SIZE)
                             << std::endl;

    dataContext.Delete(dataContext.Get().get());
}

TEST(DatabaseTests, TestSort10000)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 10000;
    constexpr std::size_t SORT_SIZE = 100;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));
    dataContext.Add(arrays).get();

    const auto ids = ExtendedCpp::LINQ::From(dataContext.Get().get())
            .Select([](const RPS::WebApi::DbArray<double>& array){ return array.id; })
            .Take(SORT_SIZE)
            .ToVector();

    ASSERT_EQ(ids.size(), SORT_SIZE);

    const auto start = std::chrono::system_clock::now();
    for (const auto id : ids)
    {
        auto array = dataContext.Get(id).get().value();
        ExtendedCpp::LINQ::Sort::QuickSort(array.inner_array.data(), 0, array.inner_array.size() - 1);
    }
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    std::cout << std::format("{} row database, {} arrays sorts, all time in microseconds: {}\n"
                             "Average time for 1 array: {}",
                             DATABASE_SIZE, SORT_SIZE,
                             std::chrono::duration_cast<std::chrono::microseconds>(timeResult).count(),
                             std::chrono::duration_cast<std::chrono::microseconds>(timeResult).count() / SORT_SIZE)
                             << std::endl;

    dataContext.Delete(dataContext.Get().get());
}

TEST(DatabaseTests, TestDelete100)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 100;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));
    dataContext.Add(arrays).get();

    const auto dbArrays = dataContext.Get().get();
    ASSERT_EQ(dbArrays.size(), DATABASE_SIZE);

    const auto start = std::chrono::system_clock::now();
    dataContext.Delete(dbArrays);
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    ASSERT_EQ(dataContext.Get().get().size(), 0);

    std::cout << std::format("{} deletes, time in milliseconds: {}",
                             DATABASE_SIZE,
                             std::chrono::duration_cast<std::chrono::milliseconds>(timeResult).count())
                             << std::endl;
}

TEST(DatabaseTests, TestDelete1000)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 1000;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));
    dataContext.Add(arrays).get();

    const auto dbArrays = dataContext.Get().get();
    ASSERT_EQ(dbArrays.size(), DATABASE_SIZE);

    const auto start = std::chrono::system_clock::now();
    dataContext.Delete(dbArrays);
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    ASSERT_EQ(dataContext.Get().get().size(), 0);

    std::cout << std::format("{} deletes, time in milliseconds: {}",
                             DATABASE_SIZE,
                             std::chrono::duration_cast<std::chrono::milliseconds>(timeResult).count())
              << std::endl;
}

TEST(DatabaseTests, TestDelete10000)
{
    std::lock_guard lock(mutex);
    constexpr std::size_t DATABASE_SIZE = 10000;

    std::vector<RPS::WebApi::DbArray<double>> arrays(DATABASE_SIZE);
    for (std::size_t i = 0; i < DATABASE_SIZE; ++i)
        arrays[i].inner_array = ExtendedCpp::Random::RandomSequence(0., 100., ExtendedCpp::Random::Random(10, 20));
    dataContext.Add(arrays).get();

    const auto dbArrays = dataContext.Get().get();
    ASSERT_EQ(dbArrays.size(), DATABASE_SIZE);

    const auto start = std::chrono::system_clock::now();
    dataContext.Delete(dbArrays);
    const auto end = std::chrono::system_clock::now();
    const auto timeResult = end - start;

    ASSERT_EQ(dataContext.Get().get().size(), 0);

    std::cout << std::format("{} deletes, time in milliseconds: {}",
                             DATABASE_SIZE,
                             std::chrono::duration_cast<std::chrono::milliseconds>(timeResult).count())
              << std::endl;
}