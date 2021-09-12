#include <iostream>
#include <glog/logging.h> 

#include <QtCharts>
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QLabel>

#include "dashboard.h"

#include "ed.h"

QChartView *createChannel1ChartView();

Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
  cfg = (config_t *)malloc(sizeof(config_t));
  load_default_config(cfg);

  grid = new QGridLayout(this);
  setLayout(grid);

  setWindowTitle( QCoreApplication::applicationName() );

  left = new QVBoxLayout(this);
  right = new QVBoxLayout(this);
  grid->addLayout(left, 0, 0);
  grid->addLayout(right, 0, 1, 1, 2);

  // setup all group boxes
  QGroupBox *ipGroup = new QGroupBox("网络配置", this);
  QGroupBox *configGroup = new QGroupBox("配置模块", this);
  QGroupBox *dataReceiveGroup = new QGroupBox("数据接收", this);
  QGroupBox *channel1LineChartGroup = new QGroupBox("通道1波形图", this);
  QGroupBox *channel2LineChartGroup = new QGroupBox("通道2波形图", this);

  // setup ip group box widgets
  QGridLayout *ipGridLayout = new QGridLayout(this);
  QLabel *deviceIpLabel = new QLabel("目的IP", this);
  ipGridLayout->addWidget(deviceIpLabel, 0, 0, 1, 2);
  deviceIPLineEdit = new QLineEdit(cfg->device_ip, this);
  ipGridLayout->addWidget(deviceIPLineEdit, 0, 2, 1, 4);
  QLabel *devicePortLabel = new QLabel("目的端口", this);
  ipGridLayout->addWidget(devicePortLabel, 0, 6, 1, 2);
  devicePortLineEdit = new QLineEdit(QString::number(cfg->device_port), this);
  ipGridLayout->addWidget(devicePortLineEdit, 0, 8, 1, 2);

  QLabel *newDeviceIpLabel = new QLabel("目的IP更新", this);
  ipGridLayout->addWidget(newDeviceIpLabel, 1, 0, 1, 2);
  newDeviceIPLineEdit = new QLineEdit(cfg->device_ip, this);
  ipGridLayout->addWidget(newDeviceIPLineEdit, 1, 2, 1, 4);
  QLabel *newDevicePortLabel = new QLabel("目的端口更新", this);
  ipGridLayout->addWidget(newDevicePortLabel, 1, 6, 1, 2);
  newDevicePortLineEdit = new QLineEdit(QString::number(cfg->device_port), this);
  ipGridLayout->addWidget(newDevicePortLineEdit, 1, 8, 1, 2);

  QLabel *localIPLabel = new QLabel("本地IP", this);
  ipGridLayout->addWidget(localIPLabel, 2, 0, 1, 2);
  localIPLineEdit = new QLineEdit(cfg->local_ip, this);
  ipGridLayout->addWidget(localIPLineEdit, 2, 2, 1, 4);
  QLabel *localPortLabel = new QLabel("本地端口", this);
  ipGridLayout->addWidget(localPortLabel, 2, 6, 1, 2);
  localPortLineEdit = new QLineEdit(QString::number(cfg->local_port), this);
  ipGridLayout->addWidget(localPortLineEdit, 2, 8, 1, 2);

  QLabel *newLocalIPLabel = new QLabel("本地IP更新", this);
  ipGridLayout->addWidget(newLocalIPLabel, 3, 0, 1, 2);
  newLocalIPLineEdit = new QLineEdit(cfg->local_ip, this);
  ipGridLayout->addWidget(newLocalIPLineEdit, 3, 2, 1, 4);
  QLabel *newLocalPortLabel = new QLabel("本地端口更新", this);
  ipGridLayout->addWidget(newLocalPortLabel, 3, 6, 1, 2);
  newLocalPortLineEdit = new QLineEdit(QString::number(cfg->local_port), this);
  ipGridLayout->addWidget(newLocalPortLineEdit, 3, 8, 1, 2);

  startConnectBtn = new QPushButton("建立连接", this);
  ipGridLayout->addWidget(startConnectBtn, 4, 1, 1, 3);
  ipGroup->setLayout(ipGridLayout);

  // setup config group box
  QGridLayout *configGridLayout = new QGridLayout(this);

  QLabel *sampleCountLabel = new QLabel("采样个数", this);
  sampleCountLineEdit = new QLineEdit(QString::number(cfg->sample_count), this);
  QLabel *triggerLabel = new QLabel("触发模式", this);
  triggerCombo = new QComboBox(this);
  triggerCombo->addItem("内触发");
  triggerCombo->addItem("外触发");
  configGridLayout->addWidget(sampleCountLabel, 0, 0, 1, 2);
  configGridLayout->addWidget(sampleCountLineEdit, 0, 3, 1, 2);
  configGridLayout->addWidget(triggerLabel, 0, 5, 1, 2);
  configGridLayout->addWidget(triggerCombo, 0, 7, 1, 2);

  QLabel *delayCountLabel = new QLabel("延时个数", this);
  delayCountLineEdit = new QLineEdit(QString::number(cfg->delay_count), this);
  QLabel *outerTriggerLabel = new QLabel("外触发边沿", this);
  outerTriggerCombo = new QComboBox(this);
  outerTriggerCombo->addItem("下降沿");
  outerTriggerCombo->addItem("上升沿");
  configGridLayout->addWidget(delayCountLabel, 1, 0, 1, 2);
  configGridLayout->addWidget(delayCountLineEdit, 1, 3, 1, 2);
  configGridLayout->addWidget(outerTriggerLabel, 1, 5, 1, 2);
  configGridLayout->addWidget(outerTriggerCombo, 1, 7, 1, 2);

  QLabel *repeatLabel = new QLabel("重复次数", this);
  repeatLineEdit = new QLineEdit(QString::number(cfg->repeat_count), this);
  QLabel *channelCountLabel = new QLabel("通道个数", this);
  channelCountCombo = new QComboBox(this);
  channelCountCombo->addItem("单通道");
  channelCountCombo->addItem("双通道");
  configGridLayout->addWidget(repeatLabel, 2, 0, 1, 2);
  configGridLayout->addWidget(repeatLineEdit, 2, 3, 1, 2);
  configGridLayout->addWidget(channelCountLabel, 2, 5, 1, 2);
  configGridLayout->addWidget(channelCountCombo, 2, 7, 1, 2);

  QLabel *sampleCount2Label = new QLabel("降采样个数", this);
  sampleCount2LineEdit = new QLineEdit(QString::number(cfg->sample_count2), this);
  QLabel *adBitLabel = new QLabel("AD Bit", this);
  adBitCombo = new QComboBox(this);
  adBitCombo->addItem("12");
  adBitCombo->addItem("14");
  configGridLayout->addWidget(sampleCount2Label, 3, 0, 1, 2);
  configGridLayout->addWidget(sampleCount2LineEdit, 3, 3, 1, 2);
  configGridLayout->addWidget(adBitLabel, 3, 5, 1, 2);
  configGridLayout->addWidget(adBitCombo, 3, 7, 1, 2);

  packageCountBtn = new QPushButton("计算包数量", this);
  configGridLayout->addWidget(packageCountBtn, 4, 1, 1, 2);
  QLabel *packageCountLabel = new QLabel("包数量", this);
  configGridLayout->addWidget(packageCountLabel, 4, 5, 1, 2);
  packageCountLineEdit = new QLineEdit(QString::number(package_count(cfg)), this);
  packageCountLineEdit->setReadOnly(true);
  configGridLayout->addWidget(packageCountLineEdit, 4, 7, 1, 2);

  writeConfigBtn = new QPushButton("存储配置", this);
  sendConfigBtn = new QPushButton("发送配置", this);
  configGridLayout->addWidget(writeConfigBtn, 5, 1, 1, 2);
  configGridLayout->addWidget(sendConfigBtn, 5, 6, 1, 2);
  configGroup->setLayout(configGridLayout);

  QGridLayout *dataReceiveGridLayout = new QGridLayout(this);
  startCollectBtn = new QPushButton("开始采集", this);
  stopCollectBtn = new QPushButton("停止采集", this);
  dataReceiveGridLayout->addWidget(startCollectBtn);
  dataReceiveGridLayout->addWidget(stopCollectBtn);
  dataReceiveGroup->setLayout(dataReceiveGridLayout);

  QVBoxLayout *box1 = new QVBoxLayout(this);
  box1->addWidget(createChannel1ChartView());
  channel1LineChartGroup->setLayout(box1);

  QVBoxLayout *box2 = new QVBoxLayout(this);
  box2->addWidget(createChannel1ChartView());
  channel2LineChartGroup->setLayout(box2);

  setupValidatorForUIFields();
  setupConnections();

  left->addWidget(ipGroup);
  left->addWidget(configGroup);
  left->addWidget(dataReceiveGroup);

  right->addWidget(channel1LineChartGroup);
  right->addWidget(channel2LineChartGroup);
}


QChartView* createChannel1ChartView() {
  QLineSeries *series = new QLineSeries();
  series->append(0, 6);
  series->append(2, 4);
  series->append(3, 8);
  series->append(7, 4);
  series->append(10, 5);
  *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

  QChart *chart = new QChart();
  chart->legend()->hide();
  chart->addSeries(series);
  chart->createDefaultAxes();
  chart->setTitle("Simple line chart example");

  QChartView *chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  return chartView;
}

void Dashboard::onBtnClicked() {
  std::cout << "on btnc clicked" << std::endl;
}

void Dashboard::setupValidatorForUIFields() {
  localPortLineEdit->setValidator(new QIntValidator(0, 65535));
  devicePortLineEdit->setValidator(new QIntValidator(0, 65535));
  newLocalPortLineEdit->setValidator(new QIntValidator(0, 65535));
  newDevicePortLineEdit->setValidator(new QIntValidator(0, 65535));

  QString ipRange = "(([ 0]+)|([ 0]*[0-9] *)|([0-9][0-9] )|([ 0][0-9][0-9])|(1[0-9][0-9])|([2][0-4][0-9])|(25[0-5]))";
  QRegExp ipRegex ("^" + ipRange
      + "\\." + ipRange
      + "\\." + ipRange
      + "\\." + ipRange + "$");
  QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

  localIPLineEdit->setValidator(ipValidator);
  localIPLineEdit->setInputMask("000.000.000.000");
  localIPLineEdit->setCursorPosition(0);

  newLocalIPLineEdit->setValidator(ipValidator);
  newLocalIPLineEdit->setInputMask("000.000.000.000");
  newLocalIPLineEdit->setCursorPosition(0);

  deviceIPLineEdit->setValidator(ipValidator);
  deviceIPLineEdit->setInputMask("000.000.000.000");
  deviceIPLineEdit->setCursorPosition(0);

  newDeviceIPLineEdit->setValidator(ipValidator);
  newDeviceIPLineEdit->setInputMask("000.000.000.000");
  newDeviceIPLineEdit->setCursorPosition(0);

  // 1073741824
  sampleCountLineEdit->setValidator(new QIntValidator(0, std::pow(2, 30)));
  delayCountLineEdit->setValidator(new QIntValidator(0, std::pow(2, 30)));
  repeatLineEdit->setValidator(new QIntValidator(0, std::pow(2, 10)));
  sampleCount2LineEdit->setValidator(new QIntValidator(0, std::pow(2, 10)));
}

void Dashboard::setupConnections() {
  LOG(INFO) << "Dashboard::setupConnections";

  connect(startConnectBtn, &QPushButton::clicked, this, &Dashboard::onStartConnectBtnClicked);
  connect(packageCountBtn, &QPushButton::clicked, this, &Dashboard::onPackageCountBtnClicked);
  connect(writeConfigBtn, &QPushButton::clicked, this, &Dashboard::onWriteConfigBtnClicked);
  connect(sendConfigBtn, &QPushButton::clicked, this, &Dashboard::onSendConfigBtnClicked);
  connect(startCollectBtn, &QPushButton::clicked, this, &Dashboard::onStartReceiveBtnClicked);
  connect(stopCollectBtn, &QPushButton::clicked, this, &Dashboard::onStopReceiveBtnClicked);
}

void Dashboard::onStartConnectBtnClicked(){
  LOG(INFO) << "Dashboard::onStartConnectBtnClicked";
}

void Dashboard::onPackageCountBtnClicked(){
  LOG(INFO) << "Dashboard::onPackageCountBtnClicked";
  packageCountLineEdit->setText(QString::number(package_count(cfg)));
}

void Dashboard::onWriteConfigBtnClicked(){
  LOG(INFO) << "Dashboard::onWriteConfigBtnClicked";
}

void Dashboard::onSendConfigBtnClicked(){
  LOG(INFO) << "Dashboard::onSendConfigBtnClicked";
}

void Dashboard::onStartReceiveBtnClicked(){
  LOG(INFO) << "Dashboard::onStartReceiveBtnClicked";
}

void Dashboard::onStopReceiveBtnClicked(){
  LOG(INFO) << "Dashboard::onStopReceiveBtnClicked";
}
