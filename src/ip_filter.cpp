#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "ipv4/ipv4.h"
#include "ipv4/ipv4_helpers.h"
#include "utils/utils.h"

void fill_ip_pool(std::vector<IpV4> &ip_pool)
{
    std::vector<std::string> split_result;
    std::vector<size_t> ipv4_parts;
    ipv4_parts.reserve(IpV4::ip_parts_count);

    for(std::string line; std::getline(std::cin, line);)
    {
        ipv4_parts.clear();

        split_result = std::move(Utils::split(line, '\t'));
        split_result = std::move(Utils::split(split_result.at(0), '.'));

        std::transform(split_result.begin(), split_result.end(), std::back_inserter(ipv4_parts),
            [&](std::string str) { return std::stoi(str); });

        if (ipv4_parts.size() < IpV4::ip_parts_count)
        {
            throw std::runtime_error("IpV4 must contain exact " + std::to_string(IpV4::ip_parts_count) + " components");
        }

        ip_pool.push_back(std::move(IpV4(ipv4_parts[0], ipv4_parts[1], ipv4_parts[2], ipv4_parts[3])));
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<IpV4> ip_pool;
        fill_ip_pool(ip_pool);

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](const auto &ip1, const auto &ip2)
        {
            return ip1 > ip2;
        });

        IpV4::print_ips(ip_pool, std::cout);

        // TODO: filter by first byte and output
        // ip = filter(1)
        std::vector<IpV4> filtered;
        IpV4Helpers::filter(ip_pool, filtered, 1);
        IpV4::print_ips(filtered, std::cout);

        // TODO: filter by first and second bytes and output
        // ip = filter(46, 70)
        filtered.clear();
        IpV4Helpers::filter(ip_pool, filtered, 46, 70);
        IpV4::print_ips(filtered, std::cout);

        // TODO: filter by any byte and output
        // ip = filter_any(46)
        filtered.clear();
        IpV4Helpers::filter_any(ip_pool, filtered, 46);
        IpV4::print_ips(filtered, std::cout);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
