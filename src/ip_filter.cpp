#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "ipv4/ipv4.h"
#include "ipv4/ipv4_helpers.h"
#include "utils/utils.h"

void fill_ip_pool(std::vector<IpV4> &ip_pool)
{
    std::vector<std::string> split_result;
    std::string line;
    while (std::getline(std::cin, line))
    {
        split_result = std::move(Utils::split(line, '\t'));
        split_result = std::move(Utils::split(split_result.at(0), '.'));
        ip_pool.emplace_back(std::stoi(split_result[0]), std::stoi(split_result[1]), std::stoi(split_result[2]), std::stoi(split_result[3]));
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
