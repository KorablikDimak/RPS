#ifndef RPS_IO_IReader_H
#define RPS_IO_IReader_H

#include <vector>

namespace RPS::IO
{
    template<typename TSource>
    class IReader
    {
    public:
        virtual ~IReader() = default;
        virtual std::vector<TSource> ReadArray() const = 0;
    };
}

#endif