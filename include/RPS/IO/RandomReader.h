#ifndef RPS_IO_RandomReader_H
#define RPS_IO_RandomReader_H

#include <functional>

#include "IReader.h"

namespace RPS::IO
{
    template<typename TSource>
    class RandomReader final : public IReader<TSource>
    {
    private:
        std::function<std::vector<TSource>()> _generator;

    public:
        explicit RandomReader(std::function<std::vector<TSource>()> generator) noexcept :
            _generator(std::move(generator)) {}

        ~RandomReader() override = default;

        std::vector<TSource> ReadArray() const override
        {
            return _generator();
        }
    };
}

#endif