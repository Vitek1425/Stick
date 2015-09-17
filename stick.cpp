// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "stick.h"
#include <QPainter>
#include <QLineF>
#include <qmath.h>
#include <QMouseEvent>
#include <QDebug>

Stick::Stick(QWidget *parent)
    : QWidget(parent)
{
    m_centerBigCircle = QPoint(0, 0);
    m_centerSmallCircle = QPoint(0, 0);
    m_stickArea = QRect(0, 0, width(), height());

    m_radiusBigCircle = 50;
    m_radiusSmallCircle = 25;
    m_radiusCatching = 70;

    m_textureBigCircle = QPixmap("://Textures/shadedDark07.png");
    m_textureSmallCircle = QPixmap("://Textures/shadedDark01.png");

    m_resizedTextureBigCircle = m_textureBigCircle;
    m_resizedTextureSmallCircle = m_textureSmallCircle;

    m_isMoving = false;
}

Stick::~Stick()
{

}

void Stick::resizeEvent(QResizeEvent *)
{
    m_stickArea = QRect(0, 0, width(), height());


    m_resizedTextureBigCircle = m_textureBigCircle.scaled(QSize(2 * m_radiusBigCircle, 2 * m_radiusBigCircle));
    m_resizedTextureSmallCircle = m_textureSmallCircle.scaled(QSize(2 * m_radiusSmallCircle, 2 * m_radiusSmallCircle));

    m_centerBigCircle = QPoint(m_stickArea.width()/2, m_stickArea.height()/2);
    m_centerSmallCircle = QPoint(m_stickArea.width()/2, m_stickArea.height()/2);
}

void Stick::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(m_centerBigCircle.x() - m_radiusBigCircle,
                       m_centerBigCircle.y() - m_radiusBigCircle,
                       m_resizedTextureBigCircle);
    painter.drawPixmap(m_centerSmallCircle.x() - m_radiusSmallCircle,
                       m_centerSmallCircle.y() - m_radiusSmallCircle,
                       m_resizedTextureSmallCircle);
}

void Stick::mousePressEvent(QMouseEvent *event)
{
    if (QLineF(event->pos(), m_centerBigCircle).length() < m_radiusCatching)
    {
        m_isMoving = true;
        moveCircle(event->pos());
    }
}

void Stick::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMoving)
    {
        moveCircle(event->pos());
    }
}

void Stick::mouseReleaseEvent(QMouseEvent *)
{
    m_centerBigCircle = QPoint(m_stickArea.width()/2,
                               m_stickArea.height()/2);
    m_isMoving = false;
    moveCircle(m_centerBigCircle);
}

void Stick::moveCircle(const QPoint &point)
{
    qreal anglePoint = qAtan2(-(point.y() - m_centerBigCircle.y()),
                                point.x() - m_centerBigCircle.x());
    qreal range = QLineF(point, m_centerBigCircle).length() / m_radiusBigCircle;
    if(range > 1)
        range = 1;
    m_centerSmallCircle = QPoint(m_centerBigCircle.x() + qCos(anglePoint) * range * m_radiusBigCircle,
                                 m_centerBigCircle.y() - qSin(anglePoint) * range * m_radiusBigCircle);
    update();
    qDebug() << range << anglePoint;
}
