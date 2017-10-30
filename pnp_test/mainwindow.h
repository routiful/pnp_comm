#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <DynamixelWorkbench/src/DynamixelWorkbench.h>

#define DEVICE_NAME "/dev/ttyUSB0"

#define DXL_1    1
#define DXL_2    2
#define SENSOR_ID 100

#define DEG2RAD(x)  (x * 0.01745329252)  // *PI/180
#define RAD2DEG(x)  (x * 57.2957795131)  // *180/PI

#define VELOCITY_TO_VALUE_RATIO 42.71

#define BAUDRATE_NUM 5

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool openPort(const char* device_name);
  bool setProtocolVersion(float version);
  bool setBaudrate(uint32_t baud);

  bool writeRegister(uint8_t id, const char *item_name, int32_t data);
  bool readRegister(uint8_t id, const char *item_name, int32_t *data);

  uint8_t findTools(uint8_t id);

  bool jointMode(uint8_t id, uint16_t vel, uint16_t acc);
  bool torque(uint8_t id, bool onoff);

  bool goalPosition(uint8_t id, float deg);

  int32_t readPosition(uint8_t id);
  int32_t readVelocity(uint8_t id);

  void initBulkWrite();
  bool addBulkWriteParam(uint8_t id, const char *item_name, int32_t data);
  bool bulkWrite();

  void initBulkRead();
  bool addBulkReadParam(uint8_t id, const char *item_name);
  bool sendBulkReadPacket();
  int32_t bulkRead(uint8_t id, const char *item_name);

  int32_t convertRadian2Value(int8_t id, float radian);
  float convertValue2Radian(int8_t id, int32_t value);

private slots:

  void on_read_write_button_clicked();

  void on_connect_pushButton_clicked();

  void on_close_pushButton_clicked();

  void on_bulk_read_write_button_clicked();

  void on_radioButton_57600_clicked();

  void on_radioButton_115200_clicked();

  void on_radioButton_1000000_clicked();

  void on_radioButton_2000000_clicked();

  void on_radioButton_3000000_clicked();

private:
  Ui::MainWindow *ui;

  dynamixel::PortHandler   *portHandler_;
  dynamixel::PacketHandler *packetHandler_;

  dynamixel::GroupBulkRead  *groupBulkRead_;
  dynamixel::GroupBulkWrite *groupBulkWrite_;

  DynamixelTool tools_[5];

  uint8_t get_id_[5];
  uint8_t tools_cnt_;

  uint32_t baud_rate_[BAUDRATE_NUM];
};

#endif // MAINWINDOW_H
