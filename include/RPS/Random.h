#ifndef RPS_Random_H
#define RPS_Random_H

#include <random>
#include <vector>

namespace RPS::Random
{
    inline static std::mt19937 SetGenerator()
    {
        std::random_device device;
        std::mt19937 generator(device());
        generator.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
        return generator;
    }

    inline static std::mt19937 generator = SetGenerator();

    template<typename TNumber>
    TNumber Random(const TNumber min, const TNumber max) noexcept
    {
        if constexpr (std::is_floating_point_v<TNumber>)
        {
            std::uniform_real_distribution distribution(min, max);
            return distribution(generator);
        }
        else
        {
            std::uniform_int_distribution distribution(min, max);
            return distribution(generator);
        }
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