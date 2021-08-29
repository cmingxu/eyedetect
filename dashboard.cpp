#include "dashboard.h"
#include <iostream>

#include <QtCharts>
#include <QChart>
#include <QLineSeries>
#include <QChartView>

QChartView *createChannel1ChartView();

Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
  grid = new QGridLayout(this);
  setLayout(grid);

  left = new QVBoxLayout(this);
  right = new QVBoxLayout(this);
  grid->addLayout(left, 0, 0);
  grid->addLayout(right, 0, 1, 1, 2);

  ipGroup = new QGroupBox("IP Setting", this);
  configGroup = new QGroupBox("Config", this);
  channel1LineChartGroup = new QGroupBox("Channel 1", this);
  channel2LineChartGroup = new QGroupBox("Channel 2", this);

  QVBoxLayout *box = new QVBoxLayout;
  box->addWidget(createChannel1ChartView());
  channel1LineChartGroup->setLayout(box);

  QVBoxLayout *boxForChannel2 = new QVBoxLayout;
  boxForChannel2->addWidget(createChannel1ChartView());
  channel2LineChartGroup->setLayout(boxForChannel2);

  left->addWidget(ipGroup);
  left->addWidget(configGroup);

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

