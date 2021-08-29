#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>

class Dashboard : public QWidget {
  public:
    Dashboard(QWidget *parent = 0);
    virtual ~Dashboard() = default;

  private slots:
    void onBtnClicked();

  private:
    QPushButton *btn;

    QGridLayout *grid;
    QBoxLayout *left;
    QBoxLayout *right;

    QGroupBox *ipGroup;
    QGroupBox *configGroup;
    QGroupBox *channel1LineChartGroup;
    QGroupBox *channel2LineChartGroup;


};
