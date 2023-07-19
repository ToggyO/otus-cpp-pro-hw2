#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

class IpV4
{
public:
    enum class IpV4Part { first, second, third, forth };

    const static size_t ip_parts_count = 4;

    IpV4(size_t, size_t, size_t, size_t);

    IpV4(const std::vector<size_t> &);

    IpV4(std::vector<size_t> &&);

    size_t get_part(IpV4Part) const;

    std::array<size_t, IpV4::ip_parts_count> get_all_parts() const;

    std::string to_string() const;

    template <class __OutputStream>
    static void print_ips(const std::vector<IpV4> &v, __OutputStream &os)
    {
        for (const auto &ip : v) { os << ip.to_string() << std::endl; }
    }

    bool operator>(const IpV4 &ip2) const;

private:
    std::vector<size_t> m_ip_parts;
};
