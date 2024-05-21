QT += widgets serialport

TARGET = terminal
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    can_msg.cpp \
    get_radar_config.cpp \
    set_radar_config.cpp \
    can_message.cpp \
    set_radar_filter.cpp \
    position_view.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    can_msg.h \
    get_radar_config.h \
    set_radar_config.h \
    can_message.h \
    set_radar_filter.h \
    position_view.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    get_radar_config.ui \
    set_radar_config.ui \
    set_radar_filter.ui \
    position_view.ui

RESOURCES += \
    terminal.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
INSTALLS += target
