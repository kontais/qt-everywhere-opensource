/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the QtDataVisualization API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Q3DSCATTER_P_H
#define Q3DSCATTER_P_H

#include "scatter3dcontroller_p.h"
#include "qabstract3dgraph_p.h"

QT_BEGIN_NAMESPACE_DATAVISUALIZATION

class Q3DScatter;

class Q3DScatterPrivate : public QAbstract3DGraphPrivate
{
    Q_OBJECT
public:
    Q3DScatterPrivate(Q3DScatter *q);
    ~Q3DScatterPrivate();

    void handleAxisXChanged(QAbstract3DAxis *axis);
    void handleAxisYChanged(QAbstract3DAxis *axis);
    void handleAxisZChanged(QAbstract3DAxis *axis);

    Q3DScatter *qptr();

    Scatter3DController *m_shared;
};

QT_END_NAMESPACE_DATAVISUALIZATION

#endif
