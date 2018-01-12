#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTimer>
#include <QMessageBox>
#include <QTime>
#include <QStringListModel>
#include <sstream>
#include <QFile>

#include <sys/time.h>

#include <DynamixelWorkbench/src/DynamixelWorkbench.h>

#define DEVICE_NAME "/dev/ttyUSB0"

#define DXL_CON_NUM  24
#define SENSOR_1     124
#define SENSOR_2     125
#define SENSOR_3     102
#define SENSOR_4     126

#define INITIAL_DEGREE 90.0f
#define GOAL_DEGREE -90.0f
#define ZERO_DEGREE 0.0f

#define DEG2RAD(x)  (x * 0.01745329252)  // *PI/180
#define RAD2DEG(x)  (x * 57.2957795131)  // *180/PI

#define VELOCITY_TO_VALUE_RATIO 42.71

#define BAUDRATE_NUM 5

#define TIMER_MILLIS 20

#define ADDR_DYNAMIXEL_GOAL_POSITION 116
#define LEN_DYNAMIXEL_GOAL_POSITION  4

#define ADDR_DYNAMIXEL_PRESENT_POSITION 132
#define LEN_DYNAMIXEL_PRESENT_POSITION  4

typedef struct
{
 bool error;
 uint32_t time;
} output_info;

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

  void writeSingleDXL(float goal_degree);
  void writeMultiDXL(uint8_t dxl_num, float goal_degree);

  int32_t readPosition(uint8_t id);
  int32_t readVelocity(uint8_t id);
  int32_t* readTemp(uint8_t id);
  int32_t* readIMU(uint8_t id);
  int32_t* readColor(uint8_t id);
  int32_t* readADC(uint8_t id);
  int32_t* readTime(uint8_t id);
  int32_t* readIRTemp(uint8_t id);
  int32_t* readMag(uint8_t id);

  void initSyncWrite();
  output_info syncWrite(uint8_t tool_num, int32_t *data);

  void initSyncRead();
  output_info syncRead(uint8_t tools_num, uint16_t address, uint8_t data_length, int32_t *data);

  int32_t convertRadian2Value(int8_t id, float radian);
  float convertValue2Radian(int8_t id, int32_t value);

  void showData(const std::string &msg, int64_t value);
  void showData(const std::string &msg);

  void log(const std::string &msg, int64_t value);
  void log(const std::string &msg);

  void writeLine(QString qstr);

  uint32_t micros();

private slots:

  void updateData();

  void on_single_read_write_button_clicked();

  void on_connect_pushButton_clicked();

  void on_close_pushButton_clicked();

  void on_multi_read_write_button_clicked();

  void on_radioButton_57600_clicked();

  void on_radioButton_115200_clicked();

  void on_radioButton_1000000_clicked();

  void on_radioButton_2000000_clicked();

  void on_radioButton_3000000_clicked();

  void on_all_tools_read_button_clicked();

private:
  Ui::MainWindow *ui;

  QTimer* qtimer_;

  QStringListModel logging_model_;
  int64_t row_count_;

  QStringListModel time_logging_model_;

  QFile *file_;

  dynamixel::PortHandler   *portHandler_;
  dynamixel::PacketHandler *packetHandler_;

  dynamixel::GroupSyncWrite *dxlSyncWrite_;
  dynamixel::GroupSyncRead  *dxlSyncRead_;

  dynamixel::GroupSyncRead  *allToolsSyncRead_;

  DynamixelTool tools_[150];

  uint8_t get_id_[150];
  uint8_t tools_cnt_;

  uint32_t baud_rate_[BAUDRATE_NUM];
  uint32_t get_baud_rate_;
};

#endif // MAINWINDOW_H
