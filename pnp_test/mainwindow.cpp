#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QMessageBox"
#include "QTime"

#define DEVICE_NAME "/dev/ttyUSB1"

#define DXL_1    1
#define DXL_2    2
#define SENSOR_ID 100

#define DEG2RAD(x)  (x * 0.01745329252)  // *PI/180
#define RAD2DEG(x)  (x * 57.2957795131)  // *180/PI

#define VELOCITY_TO_VALUE_RATIO 42.71

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);  // Do not delete this

  tool_cnt_ = 0;

  baud_rate_[0] = 57600;
  baud_rate_[1] = 115200;
  baud_rate_[2] = 1000000;
  baud_rate_[3] = 2000000;
  baud_rate_[4] = 3000000;

  ui->read_write_button->setText("Read/Write");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_baudrate_button_57600_clicked()
{
  if (!dxl_driver_.begin(DEVICE_NAME, baud_rate_[0]))
    tool_cnt_ = dxl_driver_.scan(get_id_, 100);
  else
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Begin Failed!!</p>"));

  if (tool_cnt_ != 0)
  {
    QMessageBox::about(this, tr("INFO"),tr("<h2>DYNAMIXEL</h2><p>Initialization Succeed!!</p>"));
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::on_baudrate_button_115200_clicked()
{
  if (!dxl_driver_.begin(DEVICE_NAME, baud_rate_[1]))
    tool_cnt_ = dxl_driver_.scan(get_id_, 100);
  else
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Begin Failed!!</p>"));

  if (tool_cnt_ != 0)
  {
    QMessageBox::about(this, tr("INFO"),tr("<h2>DYNAMIXEL</h2><p>Initialization Succeed!!</p>"));
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::on_baudrate_button_1000000_clicked()
{
  if (!dxl_driver_.begin(DEVICE_NAME, baud_rate_[2]))
    tool_cnt_ = dxl_driver_.scan(get_id_, 100);
  else
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Begin Failed!!</p>"));

  if (tool_cnt_ != 0)
  {
    QMessageBox::about(this, tr("INFO"),tr("<h2>DYNAMIXEL</h2><p>Initialization Succeed!!</p>"));
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::on_baudrate_button_2000000_clicked()
{
  if (!dxl_driver_.begin(DEVICE_NAME, baud_rate_[3]))
    tool_cnt_ = dxl_driver_.scan(get_id_, 100);
  else
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Begin Failed!!</p>"));

  if (tool_cnt_ != 0)
  {
    QMessageBox::about(this, tr("INFO"),tr("<h2>DYNAMIXEL</h2><p>Initialization Succeed!!</p>"));
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::on_baudrate_button_3000000_clicked()
{
  if (!dxl_driver_.begin(DEVICE_NAME, baud_rate_[4]))
    tool_cnt_ = dxl_driver_.scan(get_id_, 100);
  else
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Begin Failed!!</p>"));

  if (tool_cnt_ != 0)
  {
    QMessageBox::about(this, tr("INFO"),tr("<h2>DYNAMIXEL</h2><p>Initialization Succeed!!</p>"));
  }
  else
  {
    QMessageBox::about(this, tr("ERROR"),tr("<h2>DYNAMIXEL</h2><p>Initialization Failed!!</p>"));
  }
}

void MainWindow::on_read_write_button_clicked()
{
  jointMode(get_id_[0], 200, 50);

  static int index = 0;
  int32_t present_position = 0, present_velocity = 0;
  float goal_degree[2] = {90.0, -90.0};

  QTime timer;

  while (timer.elapsed() < 5000)
  {
    timer.start();
    uint16_t goal_position = dxl_driver_.convertRadian2Value(get_id_[0], DEG2RAD(goal_degree[index]));
    goalPosition(get_id_[0], goal_degree[index]);

    do
    {
      present_position = readPosition(get_id_[0]);
      present_velocity = readVelocity(get_id_[0]);
      showReadData(present_position, present_velocity);
    }while(abs(goal_position - present_position) > 20);

    if (index == 0)
      index = 1;
    else
      index = 0;
  }

  goalPosition(get_id_[0], 0.0);
  torque(get_id_[0], false);
}

bool MainWindow::jointMode(uint8_t id, uint16_t vel, uint16_t acc)
{
  bool error = false;
  const uint8_t position_control_mode = 3;

  torque(id, false);

  error = dxl_driver_.writeRegister(id, "Operating Mode", position_control_mode);

  torque(id, true);

  error = dxl_driver_.writeRegister(id, "Profile Acceleration", acc);
  error = dxl_driver_.writeRegister(id, "Profile Velocity", vel);

  return error;
}

bool MainWindow::torque(uint8_t id, bool onoff)
{
  bool error = false;
  error = dxl_driver_.writeRegister(id, "Torque Enable", onoff);

  return error;
}

bool MainWindow::goalPosition(uint8_t id, float deg)
{
  bool error = false;
  uint16_t goal = dxl_driver_.convertRadian2Value(get_id_[0], DEG2RAD(deg));

  error = dxl_driver_.writeRegister(id, "Goal Position", goal);

  return error;
}

int32_t MainWindow::readPosition(uint8_t id)
{
  static int32_t value = 0;

  if (dxl_driver_.readRegister(id, "Present Position", &value))
    return value;

  return 0;
}

int32_t MainWindow::readVelocity(uint8_t id)
{
  static int32_t value = 0;

  if (dxl_driver_.readRegister(id, "Present Velocity", &value))
    return value;

  return 0;
}

bool MainWindow::showReadData(int32_t pos, int32_t vel)
{
  float rad = dxl_driver_.convertValue2Radian(get_id_[0], pos);

  ui->id_1_position_lineedit->setText(QString::number(RAD2DEG(rad)));
  ui->id_1_velocity_lineedit->setText(QString::number(vel / VELOCITY_TO_VALUE_RATIO));
}


