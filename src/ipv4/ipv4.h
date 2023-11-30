#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

class IpV4
{
public:
    // Constants
    const static size_t ip_components_count = 4;

    // Typedefs
    using IpV4ComponentArray = std::array<size_t, IpV4::ip_components_count>;

    using IpV4ComponentIterator = std::array<size_t, IpV4::ip_components_count>::const_iterator;

    enum class IpV4Component { first, second, third, forth };

    // Ctors
    IpV4(size_t, size_t, size_t, size_t);

    // Methods
    [[nodiscard]] size_t get_component(IpV4Component) const;

    [[nodiscard]] IpV4ComponentArray get_all_components() const;

    [[nodiscard]] std::string to_string() const;

    template <class __OutStream>
    static void print_ips(const std::vector<IpV4> &v, __OutStream &os)
    {
        for (const auto &ip : v) { os << ip.to_string() << std::endl; }
    }

    [[nodiscard]] IpV4ComponentIterator cbegin() const;

    [[nodiscard]] IpV4ComponentIterator cend() const;

    // Operators
    bool operator>(const IpV4 &ip2) const;

private:
    IpV4ComponentArray m_ip_components;
};
