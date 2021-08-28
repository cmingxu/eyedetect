#pragma once

#include <QWidget>
#include<QPushButton>

class Dashboard : public QWidget {
  public:
    Dashboard(QWidget *parent = 0);
    virtual ~Dashboard() = default;

  private slots:
    void onBtnClicked();

  private:
    QPushButton *btn;
};
