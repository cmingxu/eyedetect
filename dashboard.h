#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>

class Dashboard : public QWidget {
  public:
    Dashboard(QWidget *parent = 0);
    virtual ~Dashboard() = default;

  private slots:
    void onBtnClicked();

  private:
    QPushButton *btn;
    QPushButton *startConnectBtn;

    QGridLayout *grid;
    QBoxLayout *left;
    QBoxLayout *right;

    QLineEdit *sampleCountLineEdit;
    QLineEdit *delayCountLineEdit;
    QLineEdit *repeatLineEdit;
    QLineEdit *sampleCount2LineEdit;
    QComboBox *triggerCombo;
    QComboBox *outerTriggerCombo;
    QLineEdit *channelCountLineEdit;
    QLineEdit *adBitLineEdit;

    QLineEdit *packageCountLineEdit;
    QPushButton *packageCountBtn;
    QPushButton *writeConfigBtn;
    QPushButton *sendConfigBtn;

    QPushButton *startCollectBtn;
    QPushButton *stopCollectBtn;

    QLineEdit *localIPLineEdit;
    QLineEdit *localPortLineEdit;
    QLineEdit *newLocalIPLineEdit;
    QLineEdit *newLocalPortLineEdit;

    QLineEdit *deviceIPLineEdit;
    QLineEdit *devicePortLineEdit;
    QLineEdit *newDeviceIPLineEdit;
    QLineEdit *newDevicePortLineEdit;

};
