#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T16:12:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pnp_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    DynamixelSDK/c++/example/dxl_monitor/dxl_monitor.cpp \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/bulk_read.cpp \
    DynamixelSDK/c++/example/protocol1.0/multi_port/multi_port.cpp \
    DynamixelSDK/c++/example/protocol1.0/ping/ping.cpp \
    DynamixelSDK/c++/example/protocol1.0/read_write/read_write.cpp \
    DynamixelSDK/c++/example/protocol1.0/reset/reset.cpp \
    DynamixelSDK/c++/example/protocol1.0/sync_write/sync_write.cpp \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/broadcast_ping.cpp \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/bulk_read_write.cpp \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/factory_reset.cpp \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/indirect_address.cpp \
    DynamixelSDK/c++/example/protocol2.0/multi_port/multi_port.cpp \
    DynamixelSDK/c++/example/protocol2.0/ping/ping.cpp \
    DynamixelSDK/c++/example/protocol2.0/read_write/read_write.cpp \
    DynamixelSDK/c++/example/protocol2.0/reboot/reboot.cpp \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/sync_read_write.cpp \
    DynamixelSDK/c++/example/protocol_combined/protocol_combined.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/group_bulk_read.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/group_bulk_write.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/group_sync_read.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/group_sync_write.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/packet_handler.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/port_handler.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/port_handler_arduino.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/port_handler_linux.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/port_handler_mac.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/port_handler_windows.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/protocol1_packet_handler.cpp \
    DynamixelSDK/c++/src/dynamixel_sdk/protocol2_packet_handler.cpp \
    DynamixelWorkbench/src/dynamixel_workbench/dynamixel_driver.cpp \
    DynamixelWorkbench/src/dynamixel_workbench/dynamixel_item.cpp \
    DynamixelWorkbench/src/dynamixel_workbench/dynamixel_tool.cpp \
    DynamixelWorkbench/src/dynamixel_workbench/dynamixel_workbench.cpp

HEADERS  += mainwindow.h \
    DynamixelWorkbench/include/dynamixel_workbench/control_table_item.h \
    DynamixelWorkbench/include/dynamixel_workbench/dynamixel_driver.h \
    DynamixelWorkbench/include/dynamixel_workbench/dynamixel_item.h \
    DynamixelWorkbench/include/dynamixel_workbench/dynamixel_tool.h \
    DynamixelWorkbench/include/dynamixel_workbench/dynamixel_workbench.h \
    DynamixelSDK/c++/include/dynamixel_sdk/dynamixel_sdk.h \
    DynamixelSDK/c++/include/dynamixel_sdk/group_bulk_read.h \
    DynamixelSDK/c++/include/dynamixel_sdk/group_bulk_write.h \
    DynamixelSDK/c++/include/dynamixel_sdk/group_sync_read.h \
    DynamixelSDK/c++/include/dynamixel_sdk/group_sync_write.h \
    DynamixelSDK/c++/include/dynamixel_sdk/packet_handler.h \
    DynamixelSDK/c++/include/dynamixel_sdk/port_handler.h \
    DynamixelSDK/c++/include/dynamixel_sdk/port_handler_arduino.h \
    DynamixelSDK/c++/include/dynamixel_sdk/port_handler_linux.h \
    DynamixelSDK/c++/include/dynamixel_sdk/port_handler_mac.h \
    DynamixelSDK/c++/include/dynamixel_sdk/port_handler_windows.h \
    DynamixelSDK/c++/include/dynamixel_sdk/protocol1_packet_handler.h \
    DynamixelSDK/c++/include/dynamixel_sdk/protocol2_packet_handler.h \
    DynamixelSDK/c++/src/DynamixelSDK.h \
    DynamixelWorkbench/src/DynamixelWorkbench.h

FORMS    += mainwindow.ui
