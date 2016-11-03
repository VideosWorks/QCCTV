#
# Copyright (c) 2016 Alex Spataru
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

QT += core
QT += network
QT += multimedia

CONFIG += c++11
INCLUDEPATH += $$PWD/src

HEADERS += \
    $$PWD/src/QCCTV_Discovery.h \
    $$PWD/src/QCCTV_LocalCamera.h \
    $$PWD/src/QCCTV_Station.h \
    $$PWD/src/QCCTV_RemoteCamera.h \
    $$PWD/src/QCCTV.h \
    $$PWD/src/QCCTV_Watchdog.h \
    $$PWD/src/QCCTV_FrameGrabber.h \
    $$PWD/src/QCCTV_ImageProvider.h \
    $$PWD/src/QCCTV_CRC32.h

SOURCES += \
    $$PWD/src/QCCTV_Discovery.cpp \
    $$PWD/src/QCCTV_LocalCamera.cpp \
    $$PWD/src/QCCTV_Station.cpp \
    $$PWD/src/QCCTV_RemoteCamera.cpp \
    $$PWD/src/QCCTV.cpp \
    $$PWD/src/QCCTV_Watchdog.cpp \
    $$PWD/src/QCCTV_FrameGrabber.cpp \
    $$PWD/src/QCCTV_ImageProvider.cpp \
    $$PWD/src/QCCTV_CRC32.cpp
