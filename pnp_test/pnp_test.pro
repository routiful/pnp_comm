#-------------------------------------------------
#
# Project created by QtCreator 2017-10-26T09:10:19
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
    DynamixelWorkbench/src/DynamixelWorkbench.h \

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/DynamixelSDK/c++/build/linux64/release/ -ldxl_x64_cpp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/DynamixelSDK/c++/build/linux64/debug/ -ldxl_x64_cpp
else:unix: LIBS += -L$$PWD/DynamixelSDK/c++/build/linux64/ -ldxl_x64_cpp

INCLUDEPATH += $$PWD/DynamixelSDK/c++/build/linux64
DEPENDPATH += $$PWD/DynamixelSDK/c++/build/linux64

DISTFILES += \
    DynamixelSDK/c++/build/win32/output/dxl_x86_cpp.lib \
    DynamixelSDK/c++/build/win64/output/dxl_x64_cpp.lib \
    DynamixelSDK/c++/build/win32/output/dxl_x86_cpp.dll \
    DynamixelSDK/c++/build/win64/output/dxl_x64_cpp.dll \
    DynamixelSDK/c++/build/linux64/libdxl_x64_cpp.so \
    DynamixelSDK/c++/package.xml \
    DynamixelSDK/c++/build/win32/dxl_x86_cpp/dxl_x86_cpp.vcxproj \
    DynamixelSDK/c++/build/win32/dxl_x86_cpp/dxl_x86_cpp.vcxproj.filters \
    DynamixelSDK/c++/build/win32/dxl_x86_cpp.sln \
    DynamixelSDK/c++/build/win64/dxl_x64_cpp/dxl_x64_cpp.vcxproj \
    DynamixelSDK/c++/build/win64/dxl_x64_cpp/dxl_x64_cpp.vcxproj.filters \
    DynamixelSDK/c++/build/win64/dxl_x64_cpp.sln \
    DynamixelSDK/c++/example/dxl_monitor/win32/dxl_monitor/dxl_monitor.vcxproj \
    DynamixelSDK/c++/example/dxl_monitor/win32/dxl_monitor/dxl_monitor.vcxproj.filters \
    DynamixelSDK/c++/example/dxl_monitor/win32/dxl_monitor.sln \
    DynamixelSDK/c++/example/dxl_monitor/win64/dxl_monitor/dxl_monitor.vcxproj \
    DynamixelSDK/c++/example/dxl_monitor/win64/dxl_monitor/dxl_monitor.vcxproj.filters \
    DynamixelSDK/c++/example/dxl_monitor/win64/dxl_monitor.sln \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/win32/bulk_read/bulk_read.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/win32/bulk_read/bulk_read.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/win32/bulk_read.sln \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/win64/bulk_read/bulk_read.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/win64/bulk_read/bulk_read.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/bulk_read/win64/bulk_read.sln \
    DynamixelSDK/c++/example/protocol1.0/multi_port/win32/multi_port/multi_port.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/multi_port/win32/multi_port/multi_port.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/multi_port/win32/multi_port.sln \
    DynamixelSDK/c++/example/protocol1.0/multi_port/win64/multi_port/multi_port.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/multi_port/win64/multi_port/multi_port.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/multi_port/win64/multi_port.sln \
    DynamixelSDK/c++/example/protocol1.0/ping/win32/ping/ping.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/ping/win32/ping/ping.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/ping/win32/ping.sln \
    DynamixelSDK/c++/example/protocol1.0/ping/win64/ping/ping.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/ping/win64/ping/ping.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/ping/win64/ping.sln \
    DynamixelSDK/c++/example/protocol1.0/read_write/win32/read_write/read_write.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/read_write/win32/read_write/read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/read_write/win32/read_write.sln \
    DynamixelSDK/c++/example/protocol1.0/read_write/win64/read_write/read_write.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/read_write/win64/read_write/read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/read_write/win64/read_write.sln \
    DynamixelSDK/c++/example/protocol1.0/reset/win32/reset/reset.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/reset/win32/reset/reset.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/reset/win32/reset.sln \
    DynamixelSDK/c++/example/protocol1.0/reset/win64/reset/reset.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/reset/win64/reset/reset.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/reset/win64/reset.sln \
    DynamixelSDK/c++/example/protocol1.0/sync_write/win32/sync_write/sync_write.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/sync_write/win32/sync_write/sync_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/sync_write/win32/sync_write.sln \
    DynamixelSDK/c++/example/protocol1.0/sync_write/win64/sync_write/sync_write.vcxproj \
    DynamixelSDK/c++/example/protocol1.0/sync_write/win64/sync_write/sync_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol1.0/sync_write/win64/sync_write.sln \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/win32/broadcast_ping/broadcast_ping.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/win32/broadcast_ping/broadcast_ping.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/win32/broadcast_ping.sln \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/win64/broadcast_ping/broadcast_ping.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/win64/broadcast_ping/broadcast_ping.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/broadcast_ping/win64/broadcast_ping.sln \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/win32/bulk_read_write/bulk_read_write.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/win32/bulk_read_write/bulk_read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/win32/bulk_read_write.sln \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/win64/bulk_read_write/bulk_read_write.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/win64/bulk_read_write/bulk_read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/bulk_read_write/win64/bulk_read_write.sln \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/win32/factory_reset/factory_reset.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/win32/factory_reset/factory_reset.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/win32/factory_reset.sln \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/win64/factory_reset/factory_reset.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/win64/factory_reset/factory_reset.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/factory_reset/win64/factory_reset.sln \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/win32/indirect_address/indirect_address.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/win32/indirect_address/indirect_address.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/win32/indirect_address.sln \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/win64/indirect_address/indirect_address.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/win64/indirect_address/indirect_address.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/indirect_address/win64/indirect_address.sln \
    DynamixelSDK/c++/example/protocol2.0/multi_port/win32/multi_port/multi_port.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/multi_port/win32/multi_port/multi_port.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/multi_port/win32/multi_port.sln \
    DynamixelSDK/c++/example/protocol2.0/multi_port/win64/multi_port/multi_port.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/multi_port/win64/multi_port/multi_port.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/multi_port/win64/multi_port.sln \
    DynamixelSDK/c++/example/protocol2.0/ping/win32/ping/ping.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/ping/win32/ping/ping.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/ping/win32/ping.sln \
    DynamixelSDK/c++/example/protocol2.0/ping/win64/ping/ping.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/ping/win64/ping/ping.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/ping/win64/ping.sln \
    DynamixelSDK/c++/example/protocol2.0/read_write/win32/read_write/read_write.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/read_write/win32/read_write/read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/read_write/win32/read_write.sln \
    DynamixelSDK/c++/example/protocol2.0/read_write/win64/read_write/read_write.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/read_write/win64/read_write/read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/read_write/win64/read_write.sln \
    DynamixelSDK/c++/example/protocol2.0/reboot/win32/reboot/reboot.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/reboot/win32/reboot/reboot.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/reboot/win32/reboot.sln \
    DynamixelSDK/c++/example/protocol2.0/reboot/win64/reboot/reboot.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/reboot/win64/reboot/reboot.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/reboot/win64/reboot.sln \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/win32/sync_read_write/sync_read_write.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/win32/sync_read_write/sync_read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/win32/sync_read_write.sln \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/win64/sync_read_write/sync_read_write.vcxproj \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/win64/sync_read_write/sync_read_write.vcxproj.filters \
    DynamixelSDK/c++/example/protocol2.0/sync_read_write/win64/sync_read_write.sln \
    DynamixelSDK/c++/example/protocol_combined/win32/protocol_combined/protocol_combined.vcxproj \
    DynamixelSDK/c++/example/protocol_combined/win32/protocol_combined/protocol_combined.vcxproj.filters \
    DynamixelSDK/c++/example/protocol_combined/win32/protocol_combined.sln \
    DynamixelSDK/c++/example/protocol_combined/win64/protocol_combined/protocol_combined.vcxproj \
    DynamixelSDK/c++/example/protocol_combined/win64/protocol_combined/protocol_combined.vcxproj.filters \
    DynamixelSDK/c++/example/protocol_combined/win64/protocol_combined.sln \
    DynamixelSDK/c++/CHANGELOG.rst \
    DynamixelSDK/c++/keywords.txt \
    DynamixelSDK/c++/library.properties \
    DynamixelSDK/c++/CMakeLists.txt \
    DynamixelSDK/c++/README.md
