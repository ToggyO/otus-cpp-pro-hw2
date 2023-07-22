#include "ipv4.h"

IpV4::IpV4(std::size_t first, std::size_t second, std::size_t third, std::size_t forth)
    : m_ip_parts{}
{
    m_ip_parts.reserve(IpV4::ip_parts_count);
    m_ip_parts.push_back(first);
    m_ip_parts.push_back(second);
    m_ip_parts.push_back(third);
    m_ip_parts.push_back(forth);
}

IpV4::IpV4(const std::vector<size_t> &ip_parts)
    : IpV4(std::move(std::vector<size_t>{ip_parts}))
{}

IpV4::IpV4(std::vector<size_t> &&ip_parts) : m_ip_parts{std::move(ip_parts)}
{
    if (m_ip_parts.size() < IpV4::ip_parts_count)
    {
        throw std::runtime_error("IpV4 must contain exact " + std::to_string(IpV4::ip_parts_count) + " components");
    }

    m_ip_parts.reserve(IpV4::ip_parts_count);
}

size_t IpV4::get_part(IpV4Part part) const
{
    switch (part)
    {
        case IpV4::IpV4Part::second:
            return m_ip_parts[1];
        case IpV4::IpV4Part::third:
            return m_ip_parts[2];
        case IpV4::IpV4Part::forth:
            return m_ip_parts[3];
        default:
            return m_ip_parts[0];
    }
}

std::array<size_t, IpV4::ip_parts_count> IpV4::get_all_parts() const
{
    return {m_ip_parts[0], m_ip_parts[1], m_ip_parts[2], m_ip_parts[3]};
}

std::string IpV4::to_string() const
{
    std::ostringstream oss;
    for (int i = 0; i != m_ip_parts.size(); ++i)
    {
        if (i > 0)
        {
            oss << ".";
        }
        oss << m_ip_parts[i];
    }
    return oss.str();
}

bool IpV4::operator>(const IpV4 &other) const
{
    for (int i = 0; i < IpV4::ip_parts_count; ++i)
    {
        auto part1 = m_ip_parts[i];
        auto part2 = other.m_ip_parts[i];

        if (part1 == part2) { continue; }

        return part2 < part1;
    }

    return false;
}
