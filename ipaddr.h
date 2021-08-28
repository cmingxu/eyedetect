#pragma once

#include <vector>

class IpAddr {
  public:
    IpAddr();
    IpAddr(const std::string &ip);

    IpAddr(unsigned short a,
        unsigned short b,
        unsigned short c,
        unsigned short d);

    std::string& getIp();
    void setIp(std::string &);
    std::vector<unsigned short> getIpFields();
    std::vector<std::string> getIpFieldInString();

    virtual ~IpAddr() = default;

  private:
    std::string m_ip;
};
