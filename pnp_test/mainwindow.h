#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <DynamixelWorkbench/src/DynamixelWorkbench.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  bool jointMode(uint8_t id, uint16_t vel, uint16_t acc);
  bool torque(uint8_t id, bool onoff);

  bool goalPosition(uint8_t id, float deg);

  int32_t readPosition(uint8_t id);
  int32_t readVelocity(uint8_t id);
  bool showReadData(int32_t pos, int32_t vel);

private slots:

  void on_baudrate_button_57600_clicked();

  void on_baudrate_button_115200_clicked();

  void on_baudrate_button_1000000_clicked();

  void on_baudrate_button_2000000_clicked();

  void on_baudrate_button_3000000_clicked();

  void on_read_write_button_clicked();

private:
  Ui::MainWindow *ui;

  DynamixelDriver dxl_driver_;

  uint8_t get_id_[5];
  uint8_t tool_cnt_;

  uint32_t baud_rate_[5];
};

#endif // MAINWINDOW_H
