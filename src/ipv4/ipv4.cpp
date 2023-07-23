#include "ipv4.h"

IpV4::IpV4(std::size_t first, std::size_t second, std::size_t third, std::size_t forth)
    : m_ip_components{first, second, third, forth}
{
//    auto *ptr = &ipv4_components{first, second, third, forth};
//    m_ip_components = std::unique_ptr<IpV4::ipv4_components>();
//    m_ip_parts.reserve(IpV4::ip_components_count);
//    m_ip_parts.push_back(first);
//    m_ip_parts.push_back(second);
//    m_ip_parts.push_back(third);
//    m_ip_parts.push_back(forth);
}

// TODO: remove
//IpV4::IpV4(const std::vector<size_t> &ip_parts)
//    : IpV4(std::move(std::vector<size_t>{ip_parts}))
//{}

//IpV4::IpV4(std::vector<size_t> &&ip_parts) : m_ip_parts{std::move(ip_parts)}
//{
//    if (m_ip_parts.size() < IpV4::ip_components_count)
//    {
//        throw std::runtime_error("IpV4 must contain exact " + std::to_string(IpV4::ip_components_count) + " components");
//    }

//    m_ip_parts.reserve(IpV4::ip_components_count);
//}

size_t IpV4::get_component(IpV4Component part) const
{
    switch (part)
    {
        case IpV4Component::second:
            return m_ip_components.second;
        case IpV4::IpV4Component::third:
            return m_ip_components.third;
        case IpV4::IpV4Component::forth:
            return m_ip_components.forth;
        default:
            return m_ip_components.first;
    }
    // TODO: remove
//    switch (part)
//    {
//        case IpV4::IpV4Part::second:
//            return m_ip_parts[1];
//        case IpV4::IpV4Part::third:
//            return m_ip_parts[2];
//        case IpV4::IpV4Part::forth:
//            return m_ip_parts[3];
//        default:
//            return m_ip_parts[0];
//    }
}

std::array<size_t, IpV4::ip_components_count> IpV4::get_all_components() const
{
    return {m_ip_components.first, m_ip_components.second, m_ip_components.third, m_ip_components.forth};
    // TODO: remove
//    return {m_ip_parts[0], m_ip_parts[1], m_ip_parts[2], m_ip_parts[3]};
}

std::string IpV4::to_string() const
{
    std::ostringstream oss;

    auto begin = this->cbegin();
    for (auto iter = begin; iter != cend(); ++iter)
    {
        if (iter != begin)
        {
            oss << ".";
        }
        oss << *iter;
    }
    // TODO: remove
//    for (int i = 0; i != m_ip_parts.size(); ++i)
//    {
//        if (i > 0)
//        {
//            oss << ".";
//        }
//        oss << m_ip_parts[i];
//    }
    return oss.str();
}

// Operators
bool IpV4::operator>(const IpV4 &other) const
{
    for (auto iter1 = cbegin(), iter2 = other.cbegin(); iter1 != cend() && iter2 != cend(); ++iter1, ++iter2)
    {
        auto component1 = *iter1;
        auto component2 = *iter2;

        if (component1 == component2) { continue; }

        return component2 < component1;

    }
// TODO: remove
//    for (int i = 0; i < IpV4::ip_components_count; ++i)
//    {
//        auto component1 = m_ip_parts[i];
//        auto component2 = other.m_ip_parts[i];

//        if (part1 == part2) { continue; }

//        return part2 < part1;
//    }

    return false;
}

IpV4::IpV4ComponentIterator IpV4::cbegin() const
{
   return IpV4ComponentIterator((size_t*)&m_ip_components.first);
}

IpV4::IpV4ComponentIterator IpV4::cend() const
{
   return IpV4ComponentIterator((size_t*)&m_ip_components.first + 4);
}

// Iterators
IpV4::IpV4ComponentIterator::itr_type& IpV4::IpV4ComponentIterator::operator++()
{
    m_ptr++;
    return *this;
}

IpV4::IpV4ComponentIterator::itr_type IpV4::IpV4ComponentIterator::operator++(int)
{
    return IpV4ComponentIterator(m_ptr++);
}

IpV4::IpV4ComponentIterator::reference IpV4::IpV4ComponentIterator::operator*() const
{
    return *m_ptr;
}

IpV4::IpV4ComponentIterator::pointer IpV4::IpV4ComponentIterator::operator->() const
{
    return m_ptr;
}

bool IpV4::IpV4ComponentIterator::operator==(const itr_type& other) const
{
    return m_ptr == other.m_ptr;
}

bool IpV4::IpV4ComponentIterator::operator!=(const itr_type& other) const
{
    return m_ptr != other.m_ptr;
}
