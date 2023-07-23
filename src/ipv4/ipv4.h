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
private:
    struct ipv4_components
    {
        size_t first;
        size_t second;
        size_t third;
        size_t forth;
    };

public:
    // Constants
    const static size_t ip_components_count = 4;

    // Typedefs
    using IpV4ComponentArray = std::array<size_t, IpV4::ip_components_count>;

    enum class IpV4Component { first, second, third, forth };

    // Iterator
    class IpV4ComponentIterator
    {
    public:
        using itr_type = IpV4ComponentIterator;
        using value_type = size_t;
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;

        explicit IpV4ComponentIterator(pointer ptr) : m_ptr{ptr} {}

        itr_type& operator++();
        itr_type operator++(int);
        reference operator*() const;
        pointer operator->() const;
        bool operator==(const itr_type&) const;
        bool operator!=(const itr_type&) const;

    private:
        pointer m_ptr;
    };

    // Ctors
    IpV4(size_t, size_t, size_t, size_t);

    // Methods
    size_t get_component(IpV4Component) const;

    IpV4ComponentArray get_all_components() const;

    std::string to_string() const;

    template <class __OutStream>
    static void print_ips(const std::vector<IpV4> &v, __OutStream &os)
    {
        for (const auto &ip : v) { os << ip.to_string() << std::endl; }
    }

    IpV4ComponentIterator cbegin() const;

    IpV4ComponentIterator cend() const;

    // Operators
    bool operator>(const IpV4 &ip2) const;

private:
    ipv4_components m_ip_components;
};
