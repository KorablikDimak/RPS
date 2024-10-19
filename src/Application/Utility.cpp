#include <sstream>
#include <ExtendedCpp/LINQ.h>

#include "Utility.h"

std::vector<std::string> RPS::Application::Utility::SplitString(const std::string& src) noexcept
{
    std::vector<std::string> tokens;
    std::istringstream stream(src);
    std::string part;
    while (std::getline(stream, part, ' '))
        tokens.push_back(std::move(part));
    return tokens;
}

std::vector<std::string> RPS::Application::Utility::SplitString(std::string&& src) noexcept
{
    std::vector<std::string> tokens;
    std::istringstream stream(std::move(src));
    std::string part;
    while (std::getline(stream, part, ' '))
        tokens.push_back(std::move(part));
    return tokens;
}

bool RPS::Application::Utility::IsNumberArray(const std::vector<std::string>& src) noexcept
{
    return ExtendedCpp::LINQ::From(src).All([](const std::string& element) noexcept
    {
        try
        {
            [[maybe_unused]] auto _ = std::stod(element);
            return true;
        }
        catch (const std::invalid_argument&)
        {
            return false;
        }
        catch (const std::out_of_range&)
        {
            return false;
        }
    });
}

std::vector<double> RPS::Application::Utility::ParseArray(const std::vector<std::string>& src) noexcept
{
    return ExtendedCpp::LINQ::From(src)
        .Select([](const std::string& element) noexcept { return std::stod(element); })
        .ToVector();
}