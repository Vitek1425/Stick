// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "stick.h"
#include <QPainter>
#include <QLineF>
#include <qmath.h>
#include <QMouseEvent>
#include <QDebug>

Stick::Stick(QWidget *parent)
    : QWidget(parent),
      m_centerBigCircle(width() / 2, height() / 2),
      m_centerSmallCircle(width() / 2, height() / 2),
      m_color(Dark),
      m_radiusBigCircle(50),
      m_radiusSmallCircle(25),
      m_radiusCatching(70),
      m_textureBigCircle(":/textures/Textures/shadedDark07.png"),
      m_textureSmallCircle(":/textures/Textures/shadedDark01.png"),
      m_isMoving(false),
      m_margins(m_radiusSmallCircle, m_radiusSmallCircle, m_radiusSmallCircle, m_radiusSmallCircle)
{
    updateAreaStick();
    resizeTextures();
    setMinimumSize(m_margins.left() + m_margins.right() + 2 * m_radiusBigCircle,
                   m_margins.top() + m_margins.bottom() + 2 * m_radiusBigCircle);
    updateMinimumSize();
}

Stick::~Stick()
{

}

Stick::Color Stick::getColor() const
{
    return m_color;
}

void Stick::setColor(const Stick::Color &color)
{
    if(m_color == color)
        return;
    m_color = color;
    switch (m_color) {
    case Dark:
    {
        m_textureBigCircle = QPixmap(":/textures/Textures/shadedDark07.png");
        m_textureSmallCircle = QPixmap(":/textures/Textures/shadedDark01.png");
        break;
    }
    case Light:
    {
        m_textureBigCircle = QPixmap(":/textures/Textures/shadedLight07.png");
        m_textureSmallCircle = QPixmap(":/textures/Textures/shadedLight01.png");
        break;
    }
    default:
        break;
    }
    update();
}

QMargins Stick::getMargins() const
{
    return m_margins;
}

void Stick::setMargins(const QMargins &margins)
{
    m_margins = margins;
    updateAreaStick();
    update();
    updateMinimumSize();
}


int Stick::getRadiusBigCircle() const
{
    return m_radiusBigCircle;
}

void Stick::setRadiusBigCircle(int radiusBigCircle)
{
    if(radiusBigCircle <= 0)
        return;
    m_radiusBigCircle = radiusBigCircle;
    resizeTextures();
    update();
}

int Stick::getRadiusSmallCircle() const
{
    return m_radiusSmallCircle;
}

void Stick::setRadiusSmallCircle(int radiusSmallCircle)
{
    if(radiusSmallCircle <= 0)
        return;
    m_radiusSmallCircle = radiusSmallCircle;
    resizeTextures();
    update();
}

void Stick::resizeEvent(QResizeEvent *)
{
    resizeTextures();
    m_centerBigCircle = QPoint(width()/2, height()/2);
    m_centerSmallCircle = QPoint(width()/2, height()/2);
}

int Stick::getRadiusCatching() const
{
    return m_radiusCatching;
}

void Stick::setRadiusCatching(int radiusCatching)
{
    m_radiusCatching = radiusCatching;
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
    //проверка на попадание клика в область захвата
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
    m_centerBigCircle = QPoint(width()/2, height()/2);
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
    emit newValue(range, anglePoint);
    update();
}

void Stick::resizeTextures()
{
    m_resizedTextureBigCircle = m_textureBigCircle.scaled(QSize(2 * m_radiusBigCircle,
                                                                2 * m_radiusBigCircle),
                                                          Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    m_resizedTextureSmallCircle = m_textureSmallCircle.scaled(QSize(2 * m_radiusSmallCircle,
                                                                    2 * m_radiusSmallCircle),
                                                              Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void Stick::updateAreaStick()
{
    m_areaStick = QRect(m_margins.left(), m_margins.top(),
                        width() + m_margins.right(),
                        height() + m_margins.bottom());
}

void Stick::updateMinimumSize()
{
    setMinimumSize(m_margins.left() + m_margins.right() + 2 * m_radiusBigCircle,
                   m_margins.top() + m_margins.bottom() + 2 * m_radiusBigCircle);
}

