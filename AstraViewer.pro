QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    MyQopenWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    MyQOpenglWidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#INCLUDEPATH +=  E:/BaiduNetdiskDownload/AstraSDK-v2.1.1-24f74b8b15-20200424T114650Z-vs2015-win64/include
#LIBS += E:/BaiduNetdiskDownload/AstraSDK-v2.1.1-24f74b8b15-20200424T114650Z-vs2015-win64/lib/*.lib

INCLUDEPATH += D:/software/OpenCV4.9.0/opencv/build/include
LIBS += D:/software/OpenCV4.9.0/opencv/build/x64/vc16/lib/*.lib

INCLUDEPATH += E:/BaiduNetdiskDownload/OpenNI_v2.3.0.85_20220615_1b09bbfd_windows_x64_x86_release/samples/samples/ThirdParty/OpenNI2/Include
LIBS += E:/BaiduNetdiskDownload/OpenNI_v2.3.0.85_20220615_1b09bbfd_windows_x64_x86_release/samples/samples/ThirdParty/OpenNI2/windows/x64-Release/*.lib

