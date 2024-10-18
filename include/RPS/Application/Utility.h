#ifndef RPS_Application_Utility_H
#define RPS_Application_Utility_H

#include <vector>
#include <string>

namespace RPS::Application::Utility
{
    std::vector<std::string> SplitString(const std::string& src) noexcept;
    std::vector<std::string> SplitString(std::string&& src) noexcept;
    bool IsNumberArray(const std::vector<std::string>& src) noexcept;
    std::vector<double> ParseArray(const std::vector<std::string>& src) noexcept;
}

#endif