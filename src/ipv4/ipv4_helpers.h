#pragma once

#include <tuple>

#include "ipv4.h"

class IpV4Helpers
{
public:
    static void filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1);

    static void filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1, size_t p2);

    static void filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1, size_t p2, size_t p3);

    static void filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t p1, size_t p2, size_t p3, size_t p4);

    static void filter_any(const std::vector<IpV4> &raw, std::vector<IpV4> &result, size_t byte);

private:
    template<class Action>
    static void m_filter(const std::vector<IpV4> &raw, std::vector<IpV4> &result, Action action);
};
