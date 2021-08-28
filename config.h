#pragma once

#include <fstream>
#include "ipaddr.h"

static const char *defaultConfig = "config.json";
static const char *defaultAppName = "eyedetect";

static const uint32_t defaultSampleRate = 10000;
static const uint32_t defaultRepeat = 10000;

static const char *defaultRemoteIpAddr = "192.168.0.3";
static const char *defaultLocalIpAddr = "192.168.0.4";


class Config {
  public:
    // create config instance
    static Config* create(const std::string &configPath);
    // return default config file path
    static std::string defaultConfigFilePath();
    // to check if the config file exists
    static bool defaultConfigFileExist();

  private: 
    Config(const std::string &configPath);

  private:
  static Config *instance;

  public:
  IpAddr *deviceIp;
  IpAddr *hostIp;

  uint32_t sampleRate;
  uint32_t repeat;
};
