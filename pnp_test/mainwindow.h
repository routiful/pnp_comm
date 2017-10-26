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

  bool showControlTable(uint8_t id);

private:
  Ui::MainWindow *ui;

  DynamixelDriver dxl_driver_;
};

#endif // MAINWINDOW_H
