#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>

#define DEVICE_NAME "/dev/ttyUSB0"
#define BAUD_RATE 1000000

#define DXL_ID    1
#define IMU_ID    2
#define SONIC_ID  3
#define TEMPER_ID 4

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  // Do not delete this

  uint16_t dxl_model_num = 0;

  dxl_driver_.begin(DEVICE_NAME, BAUD_RATE);

  dxl_model_num = dxl_driver_.ping(DXL_ID);

  if (dxl_model_num)
  {
    ui->dxl_model_name_edit->setText(QString::fromStdString(dxl_driver_.getModelName(1)));

    showControlTable(DXL_ID);
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::showControlTable(uint8_t id)
{
  DynamixelTool* dxl = dxl_driver_.getTool(id);
  uint16_t item_num = dxl->getControlTableSize();
  ControlTableItem item[item_num];

  QStandardItemModel *model = new QStandardItemModel(item_num , 2, this);
  model->setHorizontalHeaderItem(0, new QStandardItem(QString("Address Name")));
  model->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));

  ui->control_table_view->setModel(model);

  for (int index = 0; index < item_num; index++)
  {
//    QStandardItem *firstRow = new QStandardItem(QString(item[index].item_name));
//    model->setItem(index,0,firstRow);
  }
}
