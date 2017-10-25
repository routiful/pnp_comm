#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  dxl_wb_.begin("/dev/ttyUSB0", 1000000);
  dxl_wb_.ping(1);

  ui->lineEdit->setText(QString::fromStdString(dxl_wb_.getModelName((1))));
//  ui->lineEdit->setText(QString::fromStdString("fuck"));
}

MainWindow::~MainWindow()
{
  delete ui;
}
