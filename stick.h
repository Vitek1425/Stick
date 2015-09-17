// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef STICK_H
#define STICK_H

#include <QWidget>

class Stick : public QWidget
{
    Q_OBJECT

public:
    Stick(QWidget *parent = 0);
    ~Stick();
protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
private:
    void moveCircle(const QPoint &point);

    QPoint m_centerBigCircle;
    QPoint m_centerSmallCircle;
    QRect m_stickArea;

    int m_radiusBigCircle;
    int m_radiusSmallCircle;
    int m_radiusCatching;

    QPixmap m_textureBigCircle;
    QPixmap m_textureSmallCircle;

    QPixmap m_resizedTextureBigCircle;
    QPixmap m_resizedTextureSmallCircle;

    bool m_isMoving;
};

#endif // STICK_H
