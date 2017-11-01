/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *dynamixel_groupbox;
    QGroupBox *baudrate_groupbox;
    QRadioButton *radioButton_57600;
    QRadioButton *radioButton_115200;
    QRadioButton *radioButton_1000000;
    QRadioButton *radioButton_2000000;
    QRadioButton *radioButton_3000000;
    QPushButton *connect_pushButton;
    QPushButton *close_pushButton;
    QGroupBox *command_groupbox;
    QPushButton *single_read_write_button;
    QPushButton *multi_read_write_button;
    QPushButton *all_tools_read_button;
    QProgressBar *begin_progressBar;
    QListView *pnp_listView;
    QListView *log_listView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(710, 814);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dynamixel_groupbox = new QGroupBox(centralWidget);
        dynamixel_groupbox->setObjectName(QStringLiteral("dynamixel_groupbox"));
        dynamixel_groupbox->setGeometry(QRect(10, 10, 691, 301));
        QFont font;
        font.setPointSize(12);
        dynamixel_groupbox->setFont(font);
        baudrate_groupbox = new QGroupBox(dynamixel_groupbox);
        baudrate_groupbox->setObjectName(QStringLiteral("baudrate_groupbox"));
        baudrate_groupbox->setGeometry(QRect(15, 30, 661, 131));
        baudrate_groupbox->setFont(font);
        radioButton_57600 = new QRadioButton(baudrate_groupbox);
        radioButton_57600->setObjectName(QStringLiteral("radioButton_57600"));
        radioButton_57600->setGeometry(QRect(20, 100, 100, 20));
        radioButton_57600->setCheckable(true);
        radioButton_57600->setChecked(false);
        radioButton_115200 = new QRadioButton(baudrate_groupbox);
        radioButton_115200->setObjectName(QStringLiteral("radioButton_115200"));
        radioButton_115200->setGeometry(QRect(150, 100, 100, 20));
        radioButton_115200->setChecked(false);
        radioButton_1000000 = new QRadioButton(baudrate_groupbox);
        radioButton_1000000->setObjectName(QStringLiteral("radioButton_1000000"));
        radioButton_1000000->setGeometry(QRect(280, 100, 100, 20));
        radioButton_1000000->setChecked(false);
        radioButton_2000000 = new QRadioButton(baudrate_groupbox);
        radioButton_2000000->setObjectName(QStringLiteral("radioButton_2000000"));
        radioButton_2000000->setGeometry(QRect(410, 100, 100, 20));
        radioButton_3000000 = new QRadioButton(baudrate_groupbox);
        radioButton_3000000->setObjectName(QStringLiteral("radioButton_3000000"));
        radioButton_3000000->setGeometry(QRect(550, 100, 100, 20));
        radioButton_3000000->setChecked(true);
        connect_pushButton = new QPushButton(baudrate_groupbox);
        connect_pushButton->setObjectName(QStringLiteral("connect_pushButton"));
        connect_pushButton->setGeometry(QRect(10, 30, 321, 51));
        connect_pushButton->setCheckable(false);
        close_pushButton = new QPushButton(baudrate_groupbox);
        close_pushButton->setObjectName(QStringLiteral("close_pushButton"));
        close_pushButton->setGeometry(QRect(340, 30, 311, 51));
        close_pushButton->setFont(font);
        command_groupbox = new QGroupBox(dynamixel_groupbox);
        command_groupbox->setObjectName(QStringLiteral("command_groupbox"));
        command_groupbox->setGeometry(QRect(15, 210, 661, 81));
        command_groupbox->setFont(font);
        single_read_write_button = new QPushButton(command_groupbox);
        single_read_write_button->setObjectName(QStringLiteral("single_read_write_button"));
        single_read_write_button->setGeometry(QRect(10, 30, 201, 41));
        single_read_write_button->setCheckable(false);
        multi_read_write_button = new QPushButton(command_groupbox);
        multi_read_write_button->setObjectName(QStringLiteral("multi_read_write_button"));
        multi_read_write_button->setGeometry(QRect(220, 30, 201, 41));
        multi_read_write_button->setCheckable(false);
        all_tools_read_button = new QPushButton(command_groupbox);
        all_tools_read_button->setObjectName(QStringLiteral("all_tools_read_button"));
        all_tools_read_button->setGeometry(QRect(430, 30, 221, 41));
        begin_progressBar = new QProgressBar(dynamixel_groupbox);
        begin_progressBar->setObjectName(QStringLiteral("begin_progressBar"));
        begin_progressBar->setGeometry(QRect(10, 170, 661, 31));
        begin_progressBar->setValue(0);
        begin_progressBar->setTextVisible(false);
        pnp_listView = new QListView(centralWidget);
        pnp_listView->setObjectName(QStringLiteral("pnp_listView"));
        pnp_listView->setGeometry(QRect(10, 320, 201, 431));
        QFont font1;
        font1.setPointSize(10);
        pnp_listView->setFont(font1);
        pnp_listView->setDragEnabled(true);
        log_listView = new QListView(centralWidget);
        log_listView->setObjectName(QStringLiteral("log_listView"));
        log_listView->setGeometry(QRect(220, 320, 471, 431));
        log_listView->setFont(font1);
        log_listView->setDragEnabled(true);
        log_listView->setDragDropOverwriteMode(true);
        log_listView->setDragDropMode(QAbstractItemView::DragOnly);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 710, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ROBOTIS", Q_NULLPTR));
        dynamixel_groupbox->setTitle(QApplication::translate("MainWindow", "TEST ENVIRONENT", Q_NULLPTR));
        baudrate_groupbox->setTitle(QApplication::translate("MainWindow", "BaudRate", Q_NULLPTR));
        radioButton_57600->setText(QApplication::translate("MainWindow", "57600", Q_NULLPTR));
        radioButton_115200->setText(QApplication::translate("MainWindow", "115200", Q_NULLPTR));
        radioButton_1000000->setText(QApplication::translate("MainWindow", "1000000", Q_NULLPTR));
        radioButton_2000000->setText(QApplication::translate("MainWindow", "2000000", Q_NULLPTR));
        radioButton_3000000->setText(QApplication::translate("MainWindow", "3000000", Q_NULLPTR));
        connect_pushButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        close_pushButton->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        command_groupbox->setTitle(QApplication::translate("MainWindow", "Command", Q_NULLPTR));
        single_read_write_button->setText(QString());
        multi_read_write_button->setText(QString());
        all_tools_read_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
