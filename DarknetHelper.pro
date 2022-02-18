QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DarknetHelper.cpp \
    ImageMarkListView.cpp \
    ImageMarkWidget.cpp \
    ImageMarkWindow.cpp \
    NewProjectDialog.cpp \
    SettingDialog.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    DarknetHelper.h \
    ImageMarkListView.h \
    ImageMarkWidget.h \
    ImageMarkWindow.h \
    MainWindow.h \
    NewProjectDialog.h \
    SettingDialog.h

FORMS += \
    ImageMarkWindow.ui \
    MainWindow.ui \
    NewProjectDialog.ui \
    SettingDialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}

target.path = $$PWD/bin
dlltarget.path = $$PWD/bin

INSTALLS += target dlltarget

VERSION = 1.2.3.4

RESOURCES += \
    resource.qrc
