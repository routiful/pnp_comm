#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DynamixelWorkbench/src/DynamixelWorkbench.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  DynamixelWorkbench dxl_wb_;
};

#endif // MAINWINDOW_H
