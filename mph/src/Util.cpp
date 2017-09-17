/*
 * Util.cpp
 *
 *  Created on: Aug 27, 2017
 *      Author: butters
 */

#include "Util.hpp"

namespace mph
{

int stoi(int& value, const std::string& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoi(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoi(int& value, const std::wstring& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoi(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stol(long & value, const std::string& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stol(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stol(long & value, const std::wstring& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stol(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoll(long long & value, const std::string& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoll(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoll(long long & value, const std::wstring& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoll(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoui(unsigned int& value, const std::string& str, std::size_t* pos, int base) noexcept
{
    unsigned long result;
    int eCode = stoul(result, str, pos, base);
    if (eCode)
        return eCode;

    if (result > std::numeric_limits<unsigned int>::max())
        return static_cast<int>(std::errc::result_out_of_range);

    value = (unsigned int) ((result));
    return eCode;
}

int stoui(unsigned int& value, const std::wstring& str, std::size_t* pos, int base) noexcept
{
    unsigned long result;
    int eCode = stoul(result, str, pos, base);
    if (eCode)
        return eCode;

    if (result > std::numeric_limits<unsigned int>::max())
        return static_cast<int>(std::errc::result_out_of_range);

    value = (unsigned int) ((result));
    return eCode;
}

int stoul(unsigned long & value, const std::string& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoul(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoul(unsigned long & value, const std::wstring& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoul(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoull(unsigned long long & value, const std::string& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoull(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stoull(unsigned long long & value, const std::wstring& str, std::size_t* pos, int base) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stoull(str, pos, base);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stof(float& value, const std::string& str, std::size_t* pos) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stof(str, pos);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stof(float& value, const std::wstring& str, std::size_t* pos) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stof(str, pos);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stod(double& value, const std::wstring& str, std::size_t* pos) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stod(str, pos);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stod(double& value, const std::string& str, std::size_t* pos) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stod(str, pos);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stold(long double& value, const std::string& str, std::size_t* pos) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stold(str, pos);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

int stold(long double& value, const std::wstring& str, std::size_t* pos) noexcept
{
    int eCode = 0;
    try
    {
        value = std::stold(str, pos);
    }
    catch (std::invalid_argument&)
    {
        eCode = static_cast<int>(std::errc::invalid_argument);
    }
    catch (std::out_of_range&)
    {
        eCode = static_cast<int>(std::errc::result_out_of_range);
    }
    return eCode;
}

}
