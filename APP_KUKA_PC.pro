QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += D:/Opencv_411/opencv/build/include
LIBS += "D:\\Opencv_411\\opencv\\build\\x64\\vc15\\lib\\opencv_world411.lib"
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myvideocapture.cpp

HEADERS += \
    mainwindow.h \
    myvideocapture.h

#INCLUDEPATH += "D:\\Opencv_411\\opencv\\build\\include"
#LIBS += D:\Opencv_411\opencv\build\x64\vc14\bin\world411.dll


INCLUDEPATH += D:\Opencv_411\opencv\build\include
LIBS += D:\Build_opencv\bin\libopencv_core411.dll
LIBS += D:\Build_opencv\bin\libopencv_highgui411.dll
LIBS += D:\Build_opencv\bin\libopencv_imgcodecs411.dll
LIBS += D:\Build_opencv\bin\libopencv_imgproc411.dll
LIBS += D:\Build_opencv\bin\libopencv_features2d411.dll
LIBS += D:\Build_opencv\bin\libopencv_calib3d411.dll
LIBS += D:\Build_opencv\bin\libopencv_video411.dll
LIBS += D:\Build_opencv\bin\libopencv_videoio411.dll


QMAKE_CXXFLAGS += -std=gnu++14
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target









#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc15/lib/ -lopencv_world430
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc15/lib/ -lopencv_world430d
#else:unix: LIBS += -L$$PWD/../../opencv/build/x64/vc15/lib/ -lopencv_world430

#INCLUDEPATH += D:\opencv\build\include\opencv2
#DEPENDPATH +=D:\opencv\build\include\opencv2



#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc15/lib/ -lopencv_world450
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../opencv/build/x64/vc15/lib/ -lopencv_world450d
#else:unix: LIBS += -L$$PWD/../../opencv/build/x64/vc15/lib/ -lopencv_world450

#INCLUDEPATH += $$PWD/../../opencv/build/include
#DEPENDPATH += $$PWD/../../opencv/build/include

FORMS += \
    mainwindow.ui

RESOURCES += \
    IMAGENS.qrc

