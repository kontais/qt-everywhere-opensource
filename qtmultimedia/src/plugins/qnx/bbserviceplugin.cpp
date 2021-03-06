/****************************************************************************
**
** Copyright (C) 2016 Research In Motion
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "bbserviceplugin.h"

#include "bbcamerainfocontrol.h"
#include "bbcameraservice.h"
#include "bbcamerasession.h"
#include "bbvideodeviceselectorcontrol.h"
#include "mmrenderermediaplayerservice.h"

#include <QDebug>

QT_BEGIN_NAMESPACE

BbServicePlugin::BbServicePlugin()
{
}

QMediaService *BbServicePlugin::create(const QString &key)
{
    if (key == QLatin1String(Q_MEDIASERVICE_CAMERA))
        return new BbCameraService();

    if (key == QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER))
        return new MmRendererMediaPlayerService();

    return 0;
}

void BbServicePlugin::release(QMediaService *service)
{
    delete service;
}

QMediaServiceProviderHint::Features BbServicePlugin::supportedFeatures(const QByteArray &service) const
{
    Q_UNUSED(service)
    return QMediaServiceProviderHint::Features();
}

QByteArray BbServicePlugin::defaultDevice(const QByteArray &service) const
{
    if (service == Q_MEDIASERVICE_CAMERA) {
        if (m_cameraDevices.isEmpty())
            updateDevices();

        return m_defaultCameraDevice;
    }

    return QByteArray();
}

QList<QByteArray> BbServicePlugin::devices(const QByteArray &service) const
{
    if (service == Q_MEDIASERVICE_CAMERA) {
        if (m_cameraDevices.isEmpty())
            updateDevices();

        return m_cameraDevices;
    }

    return QList<QByteArray>();
}

QString BbServicePlugin::deviceDescription(const QByteArray &service, const QByteArray &device)
{
    if (service == Q_MEDIASERVICE_CAMERA) {
        if (m_cameraDevices.isEmpty())
            updateDevices();

        for (int i = 0; i < m_cameraDevices.count(); i++)
            if (m_cameraDevices[i] == device)
                return m_cameraDescriptions[i];
    }

    return QString();
}

void BbServicePlugin::updateDevices() const
{
    m_defaultCameraDevice.clear();
    BbVideoDeviceSelectorControl::enumerateDevices(&m_cameraDevices, &m_cameraDescriptions);

    if (m_cameraDevices.isEmpty()) {
        qWarning() << "No camera devices found";
    } else {
        m_defaultCameraDevice = m_cameraDevices.contains(BbCameraSession::cameraIdentifierRear())
                                ? BbCameraSession::cameraIdentifierRear()
                                : m_cameraDevices.first();
    }
}

QCamera::Position BbServicePlugin::cameraPosition(const QByteArray &device) const
{
    return BbCameraInfoControl::position(device);
}

int BbServicePlugin::cameraOrientation(const QByteArray &device) const
{
    return BbCameraInfoControl::orientation(device);
}

QT_END_NAMESPACE
