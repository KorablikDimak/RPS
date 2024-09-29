#ifndef RPS_Random_H
#define RPS_Random_H

#include <random>
#include <vector>

namespace RPS::Random
{
    template<typename TReal = double>
    TReal RandomReal(const TReal min, const TReal max) noexcept
    {
        std::random_device device;
        std::mt19937 generator(device());
        generator.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        std::uniform_real_distribution distribution(min, max);
        return distribution(generator);
    }

    template<typename TInteger = int>
    TInteger RandomInt(const TInteger min, const TInteger max) noexcept
    {
        std::random_device device;
        std::mt19937 generator(device());
        generator.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution distribution(min, max);
        return distribution(generator);
    }

    template<typename TNumber>
    TNumber Random(const TNumber min, const TNumber max) noexcept
    {
        if constexpr (std::is_floating_point_v<TNumber>)
            return RandomReal<TNumber>(min, max);
        else
            return RandomInt<TNumber>(min, max);
    }

    template<typename TNumber>
    std::vector<TNumber> RandomSequence(const TNumber min, const TNumber max, const std::size_t size) noexcept
    {
        std::vector<TNumber> sequence(size);
        for (std::size_t i = 0; i < size; ++i)
            sequence[i] = Random<TNumber>(min, max);
        return sequence;
    }
}

#endif