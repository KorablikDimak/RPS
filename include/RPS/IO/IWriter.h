#ifndef RPS_IO_IWriter_H
#define RPS_IO_IWriter_H

#include <vector>

namespace RPS::IO
{
    template<typename TSource>
    class IWriter
    {
    public:
        virtual ~IWriter() = default;
        virtual void WriteArray(const std::vector<TSource>& array) const = 0;
    };
}

#endif