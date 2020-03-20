#pragma once

#include <string>
#include <vector>

class IPv4Address {
public:
    IPv4Address(const std::string& address);
    ~IPv4Address() = default;

    friend std::ostream& operator<<(std::ostream& os, const IPv4Address& obj);
    friend std::istream& operator>>(std::istream& is, IPv4Address& obj);

    void from_str(const std::string& address);
    std::string to_str() const;

private:
    std::vector<std::uint8_t> m_address;
    const char m_delimiter = '.';
};

std::vector<std::string> split(const std::string& s, char delimiter);