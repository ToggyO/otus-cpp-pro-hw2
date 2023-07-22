#include <gtest/gtest.h>
#include <filesystem>
#include <regex>
#include <sstream>

#include "config.h"

std::string exec(std::string &command)
{
    int buffer_size = 128;
    char buffer[buffer_size];
    std::stringstream ss;

    auto pipe_reader = popen(command.c_str(), "r");
    if (!pipe_reader)
    {
        throw std::runtime_error("Failed to open pipe");
    }

    while (!feof(pipe_reader))
    {
        if (fgets(buffer, buffer_size, pipe_reader) != nullptr)
        {
            ss << buffer;
        }
    }

    pclose(pipe_reader);
    return ss.str();
}

// LINUX SPECIFIC!!!
TEST(IpFilter, Check_Md5Hash) {
    static const std::string k_pipe = " | ";
    static const std::string expected_hash = "24e7a7b2270daee89c64d3ca5fb3da1a";

    auto project_root = getTestProjectRoot();
    auto excecutable = getTestedExecutablePath();
    auto test_data_file_path = std::filesystem::path(project_root) / "ip_filter.tsv";

    std::ostringstream oss;
    oss << "cat "
        << test_data_file_path << k_pipe
        << excecutable << k_pipe
        << "md5sum" << k_pipe
        << "cut -c -32";

    auto cmd = oss.str();
    auto actual_hash = exec(cmd);

    actual_hash = std::regex_replace(actual_hash, std::regex(R"(\r\n|\r|\n)"), "");

    EXPECT_EQ(actual_hash, expected_hash);
}
