#include "ipv4_helpers.h"

void IpV4Helpers::filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1)
{
    IpV4Helpers::m_filter(raw, result, [&p1] (const IpV4 &ip)
    {
        return ip.get_part(IpV4::IpV4Part::first) == p1;
    });
}

void IpV4Helpers::filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1, size_t p2)
{
    IpV4Helpers::m_filter(raw, result, [&p1, &p2] (const IpV4 &ip)
    {
        return ip.get_part(IpV4::IpV4Part::first) == p1
                && ip.get_part(IpV4::IpV4Part::second) == p2;
    });
}

void IpV4Helpers::filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1, size_t p2, size_t p3)
{
    IpV4Helpers::m_filter(raw, result, [&p1, &p2, &p3] (const IpV4 &ip)
    {
        return ip.get_part(IpV4::IpV4Part::first) == p1
                && ip.get_part(IpV4::IpV4Part::second) == p2
                && ip.get_part(IpV4::IpV4Part::third) == p3;
    });
}

void IpV4Helpers::filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1, size_t p2, size_t p3, size_t p4)
{
    IpV4Helpers::m_filter(raw, result, [&p1, &p2, &p3, &p4] (const IpV4 &ip)
    {
        return ip.get_part(IpV4::IpV4Part::first) == p1
                && ip.get_part(IpV4::IpV4Part::second) == p2
                && ip.get_part(IpV4::IpV4Part::third) == p3
                && ip.get_part(IpV4::IpV4Part::forth) == p4;
    });
}

void IpV4Helpers::filter_any(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t byte)
{
    IpV4Helpers::m_filter(raw, result, [&byte] (const IpV4 &ip)
    {
        auto ip_parts = ip.get_all_parts();
        return std::any_of(ip_parts.begin(), ip_parts.end(), [&byte](const size_t &part)
        {
            return part == byte;
        });
    });
}

template <class Action>
void IpV4Helpers::m_filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, Action action)
{
    std::copy_if(raw.begin(), raw.end(), std::back_inserter(result), action);
}
