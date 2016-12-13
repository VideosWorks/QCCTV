﻿/*
 * Copyright (c) 2016 Alex Spataru
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE
 */

#include "QCCTV.h"

#include <QBuffer>
#include <QObject>
#include <QPixmap>
#include <QPainter>

/**
 * If a is not empty, the function appends \a b to \a a and adds a separator.
 * Otherwise, this function shall return \a b
 */
static QString append_str (const QString a, QString b)
{
    if (a.isEmpty())
        return b;

    else
        return a + " | " + b;
}

/**
 * Returns a valid watchdog timeout value
 */
int QCCTV_WATCHDOG_TIME (const int fps)
{
    return qMax (QCCTV_MIN_WATCHDOG_TIME,
                 qMin (fps * 50, QCCTV_MAX_WATCHDOG_TIME));
}

/**
 * Returns a valid FPS value
 */
int QCCTV_GET_VALID_FPS (const int fps)
{
    return qMax (qMin (fps, QCCTV_MAX_FPS), QCCTV_MIN_FPS);
}

/**
 * Parses the given status flags as a string
 */
QString QCCTV_STATUS_STRING (const int status)
{
    QString str;

    if (status & QCCTV_CAMSTATUS_LOW_BATTERY)
        str = append_str (str, QObject::tr ("Low Battery"));

    if (status & QCCTV_CAMSTATUS_DISCHARING)
        str = append_str (str, QObject::tr ("Discharging"));

    if (status & QCCTV_CAMSTATUS_LIGHT_FAILURE)
        str = append_str (str, QObject::tr ("Flashlight Failure"));

    if (status & QCCTV_CAMSTATUS_VIDEO_FAILURE)
        str = append_str (str, QObject::tr ("Video Failure"));

    if (status == QCCTV_CAMSTATUS_DEFAULT)
        str = QObject::tr ("Camera OK");

    return str;
}

/**
 * Returns the available image resolutions
 */
extern QStringList QCCTV_AVAILABLE_RESOLUTIONS()
{
    QStringList list;

    list.append (QObject::tr ("QCIF (176x120)"));
    list.append (QObject::tr ("CIF (352x240)"));
    list.append (QObject::tr ("2CIF (704x240)"));
    list.append (QObject::tr ("4CIF (704x480)"));
    list.append (QObject::tr ("D1 (720x480)"));
    list.append (QObject::tr ("720p (1280x720)"));
    list.append (QObject::tr ("960p (1280x960)"));
    list.append (QObject::tr ("Original Resolution"));

    return list;
}

/**
 * Returns the raw bytes of the encoded \a image
 */
QByteArray QCCTV_ENCODE_IMAGE (const QImage& image, QCCTV_Resolution res)
{
    /* Obtain image resolution */
    int width = 0;
    int height = 0;
    switch (res) {
    case QCCTV_QCIF:
        width = 176;
        height = 144;
        break;
    case QCCTV_CIF:
        width = 352;
        height = 240;
        break;
    case QCCTV_2CIF:
        width = 704;
        height = 240;
        break;
    case QCCTV_4CIF:
        width = 704;
        height = 480;
        break;
    case QCCTV_D1:
        width = 720;
        height = 480;
        break;
    case QCCTV_720p:
        width = 1280;
        height = 720;
        break;
    case QCCTV_960p:
        width = 1280;
        height = 960;
        break;
    case QCCTV_Original:
        width = image.width();
        height = image.height();
    default:
        width = image.width();
        height = image.height();
        break;
    }

    /* Scale the image */
    QImage final = image;
    final = final.scaled (width, height,
                          Qt::KeepAspectRatio,
                          Qt::FastTransformation);

    /* Save image to byte array */
    QByteArray raw_bytes;
    QBuffer buffer (&raw_bytes);
    final.save (&buffer, QCCTV_IMAGE_FORMAT);
    buffer.close();

    /* Return image bytes */
    return raw_bytes;
}

/**
 * Generates a image from the given \a data
 */
QImage QCCTV_DECODE_IMAGE (const QByteArray& data)
{
    return QImage::fromData (data, QCCTV_IMAGE_FORMAT);
}

/**
 * Generates an image with the given \a size and \a text
 */
QImage QCCTV_GET_STATUS_IMAGE (const QSize& size, const QString& text)
{
    QPixmap pixmap = QPixmap (size);
    pixmap.fill (QColor ("#000").rgb());
    QPainter painter (&pixmap);

    painter.setPen (Qt::white);
    painter.setFont (QFont ("Arial"));
    painter.drawText (QRectF (0, 0, size.width(), size.height()),
                      Qt::AlignCenter, text);

    return pixmap.toImage();
}
