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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QGroupBox *command_groupbox;
    QPushButton *read_write_button;
    QPushButton *bulk_read_write_button;
    QGroupBox *id_1_groupbox;
    QLineEdit *id_1_position_lineedit;
    QLabel *label;
    QGroupBox *id_2_groupbox;
    QLineEdit *id_2_position_lineedit;
    QLabel *label_3;
    QProgressBar *begin_progressBar;
    QPushButton *close_pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(715, 780);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        dynamixel_groupbox = new QGroupBox(centralWidget);
        dynamixel_groupbox->setObjectName(QStringLiteral("dynamixel_groupbox"));
        dynamixel_groupbox->setGeometry(QRect(10, 10, 691, 651));
        QFont font;
        font.setPointSize(13);
        dynamixel_groupbox->setFont(font);
        baudrate_groupbox = new QGroupBox(dynamixel_groupbox);
        baudrate_groupbox->setObjectName(QStringLiteral("baudrate_groupbox"));
        baudrate_groupbox->setGeometry(QRect(10, 30, 661, 201));
        baudrate_groupbox->setFont(font);
        radioButton_57600 = new QRadioButton(baudrate_groupbox);
        radioButton_57600->setObjectName(QStringLiteral("radioButton_57600"));
        radioButton_57600->setGeometry(QRect(20, 150, 100, 20));
        radioButton_57600->setCheckable(true);
        radioButton_57600->setChecked(false);
        radioButton_115200 = new QRadioButton(baudrate_groupbox);
        radioButton_115200->setObjectName(QStringLiteral("radioButton_115200"));
        radioButton_115200->setGeometry(QRect(150, 150, 100, 20));
        radioButton_115200->setChecked(false);
        radioButton_1000000 = new QRadioButton(baudrate_groupbox);
        radioButton_1000000->setObjectName(QStringLiteral("radioButton_1000000"));
        radioButton_1000000->setGeometry(QRect(280, 150, 100, 20));
        radioButton_1000000->setChecked(false);
        radioButton_2000000 = new QRadioButton(baudrate_groupbox);
        radioButton_2000000->setObjectName(QStringLiteral("radioButton_2000000"));
        radioButton_2000000->setGeometry(QRect(410, 150, 100, 20));
        radioButton_3000000 = new QRadioButton(baudrate_groupbox);
        radioButton_3000000->setObjectName(QStringLiteral("radioButton_3000000"));
        radioButton_3000000->setGeometry(QRect(550, 150, 100, 20));
        radioButton_3000000->setChecked(true);
        connect_pushButton = new QPushButton(baudrate_groupbox);
        connect_pushButton->setObjectName(QStringLiteral("connect_pushButton"));
        connect_pushButton->setGeometry(QRect(10, 30, 641, 91));
        command_groupbox = new QGroupBox(dynamixel_groupbox);
        command_groupbox->setObjectName(QStringLiteral("command_groupbox"));
        command_groupbox->setGeometry(QRect(10, 310, 661, 141));
        command_groupbox->setFont(font);
        read_write_button = new QPushButton(command_groupbox);
        read_write_button->setObjectName(QStringLiteral("read_write_button"));
        read_write_button->setGeometry(QRect(10, 30, 311, 101));
        read_write_button->setCheckable(false);
        bulk_read_write_button = new QPushButton(command_groupbox);
        bulk_read_write_button->setObjectName(QStringLiteral("bulk_read_write_button"));
        bulk_read_write_button->setGeometry(QRect(330, 30, 311, 101));
        bulk_read_write_button->setCheckable(false);
        id_1_groupbox = new QGroupBox(dynamixel_groupbox);
        id_1_groupbox->setObjectName(QStringLiteral("id_1_groupbox"));
        id_1_groupbox->setGeometry(QRect(10, 470, 321, 71));
        id_1_groupbox->setFont(font);
        id_1_position_lineedit = new QLineEdit(id_1_groupbox);
        id_1_position_lineedit->setObjectName(QStringLiteral("id_1_position_lineedit"));
        id_1_position_lineedit->setGeometry(QRect(100, 30, 211, 31));
        id_1_position_lineedit->setReadOnly(true);
        label = new QLabel(id_1_groupbox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 81, 16));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        id_2_groupbox = new QGroupBox(dynamixel_groupbox);
        id_2_groupbox->setObjectName(QStringLiteral("id_2_groupbox"));
        id_2_groupbox->setGeometry(QRect(340, 470, 331, 71));
        id_2_groupbox->setFont(font);
        id_2_position_lineedit = new QLineEdit(id_2_groupbox);
        id_2_position_lineedit->setObjectName(QStringLiteral("id_2_position_lineedit"));
        id_2_position_lineedit->setGeometry(QRect(110, 30, 201, 31));
        id_2_position_lineedit->setReadOnly(true);
        label_3 = new QLabel(id_2_groupbox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 81, 16));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        begin_progressBar = new QProgressBar(dynamixel_groupbox);
        begin_progressBar->setObjectName(QStringLiteral("begin_progressBar"));
        begin_progressBar->setGeometry(QRect(10, 250, 661, 41));
        begin_progressBar->setValue(0);
        close_pushButton = new QPushButton(centralWidget);
        close_pushButton->setObjectName(QStringLiteral("close_pushButton"));
        close_pushButton->setGeometry(QRect(10, 670, 691, 61));
        close_pushButton->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 715, 19));
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
        dynamixel_groupbox->setTitle(QApplication::translate("MainWindow", "Dynamixel", Q_NULLPTR));
        baudrate_groupbox->setTitle(QApplication::translate("MainWindow", "BaudRate", Q_NULLPTR));
        radioButton_57600->setText(QApplication::translate("MainWindow", "57600", Q_NULLPTR));
        radioButton_115200->setText(QApplication::translate("MainWindow", "115200", Q_NULLPTR));
        radioButton_1000000->setText(QApplication::translate("MainWindow", "1000000", Q_NULLPTR));
        radioButton_2000000->setText(QApplication::translate("MainWindow", "2000000", Q_NULLPTR));
        radioButton_3000000->setText(QApplication::translate("MainWindow", "3000000", Q_NULLPTR));
        connect_pushButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        command_groupbox->setTitle(QApplication::translate("MainWindow", "Command", Q_NULLPTR));
        read_write_button->setText(QString());
        bulk_read_write_button->setText(QString());
        id_1_groupbox->setTitle(QApplication::translate("MainWindow", "ID 1 ", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Position", Q_NULLPTR));
        id_2_groupbox->setTitle(QApplication::translate("MainWindow", "ID 2 ", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Position", Q_NULLPTR));
        close_pushButton->setText(QApplication::translate("MainWindow", "CLOSE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
