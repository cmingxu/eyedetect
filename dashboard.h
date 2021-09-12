#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include "ed.h"

class Dashboard : public QWidget {
  public:
    Dashboard(QWidget *parent = 0);
    virtual ~Dashboard() = default;

  private slots:
    void onBtnClicked();
    void onConnectDeviceBtnClicked();
    void onDisconnectDeviceBtnClicked();
    void onPackageCountBtnClicked();
    void onWriteConfigBtnClicked();
    void onSendConfigBtnClicked();
    void onStartReceiveBtnClicked();
    void onStopReceiveBtnClicked();

  private:
    config_t *cfg;
    addr_t *addr;

    bool deviceConnected;
    bool receiving;
    bool configDirty;

  private:
    void setupUIs();
    void setupValues(config_t *);
    void setupValidatorForUIFields();
    void setupConnections();

  private:
    QPushButton *btn;
    QPushButton *connectDeviceBtn;
    QPushButton *disconnectDeviceBtn;

    QGridLayout *grid;
    QBoxLayout *left;
    QBoxLayout *right;

    QLineEdit *sampleCountLineEdit;
    QLineEdit *delayCountLineEdit;
    QLineEdit *repeatLineEdit;
    QLineEdit *sampleCount2LineEdit;
    QComboBox *triggerCombo;
    QComboBox *outerTriggerCombo;
    QComboBox *channelCountCombo;
    QComboBox *adBitCombo;

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
