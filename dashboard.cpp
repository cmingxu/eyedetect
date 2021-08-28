#include "dashboard.h"
#include <iostream>

Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
  btn = new QPushButton("Push", this);
  connect(btn, &QPushButton::clicked, this, &Dashboard::onBtnClicked);
}

void Dashboard::onBtnClicked() {
  std::cout << "on btnc clicked" << std::endl;
}

