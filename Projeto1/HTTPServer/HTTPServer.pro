QT += qml quick network

CONFIG += c++11

SOURCES += main.cpp \
    networkmanager.cpp \
    server.cpp \
    client.cpp 

RESOURCES += qml.qrc

HEADERS += \
    networkmanager.h \
    server.h \
    client.h 
