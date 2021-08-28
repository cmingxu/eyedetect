#include <iostream>
#include <fstream>
#include <QDir>

#include "config.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Config * Config::instance = nullptr;

Config *Config::create(const std::string &configPath) {
  if(Config::instance == nullptr) {
    Config::instance = new Config(configPath);
  }

  return Config::instance;
}

std::string Config::defaultConfigFilePath() {
  return std::string("/") + \
    QDir::home().dirName().toStdString()  + \
    std::string("/") + \
    std::string(defaultAppName) + \
    std::string( "/") + \
    std::string(defaultConfig) ;
}

bool Config::defaultConfigFileExist() {
  std::ifstream file(Config::defaultConfigFilePath());
  return file.good();
}


Config::Config(const std::string &configPath) {
  sampleRate = defaultSampleRate;
  repeat = defaultRepeat;
  deviceIp = new IpAddr(defaultRemoteIpAddr);
  hostIp = new IpAddr(defaultLocalIpAddr);

  std::ifstream f;
  f.open(configPath);
  if(f.good() ) {
    json j;
    f >> j;

    j.at("repeat").get_to(repeat);
    j.at("sampleRate").get_to(sampleRate);
    std::string deviceIpTmp;
    j.at("deviceip").get_to(deviceIpTmp);
    deviceIp = new IpAddr(deviceIpTmp);
    f.close();
  }
}


