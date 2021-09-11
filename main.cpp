#include <iostream>
#include <glog/logging.h> 

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QTextStream>
#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QPushButton>

#include "config.h"
#include "dashboard.h"


static const int HEIGHT = 700;
static const int WIDTH = 1100;
static const char *title = "网络接收程序";

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  LOG(INFO) << "begin ";

  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("网络接收程序");

  Dashboard window;

  window.resize(WIDTH, HEIGHT);
  window.setWindowTitle(title);
  window.show();

  Config *c = Config::create(Config::defaultConfigFilePath());
  for(auto fi : c->deviceIp->getIpFields()) {
    std::cout << fi << std::endl;
  }

  return app.exec();
}
