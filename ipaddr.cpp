#include <sstream>
#include <vector>
#include <iostream>
#include "ipaddr.h"

IpAddr::IpAddr() {
  m_ip = "0.0.0.0";
}

IpAddr::IpAddr(const std::string &ip) {
  m_ip = ip;
}

IpAddr::IpAddr(unsigned short a, unsigned short b, unsigned short c, unsigned short d) {
  std::stringstream ss;
  ss << a << '.' << b << '.' << c << '.' << d;
  m_ip = ss.str();
}


std::string& IpAddr::getIp() { 
  return m_ip;
}

void IpAddr::setIp(std::string &ip) {
  m_ip = ip;
}

std::vector<unsigned short> IpAddr::getIpFields() {
  std::vector<unsigned short> fields;
  std::stringstream ss;
  ss << m_ip;

  std::string field;
  while(getline(ss, field, '.')) {
    fields.push_back((unsigned short)std::stoi(field, nullptr, 0));
  }

  return fields;
}
