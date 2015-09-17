// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef STICK_H
#define STICK_H

#include <QWidget>

class Stick : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Color)
    Q_PROPERTY(Color color READ getColor WRITE setColor)
    Q_PROPERTY(QMargins margins READ getMargins WRITE setMargins)
    Q_PROPERTY(int radiusBigCircle READ getRadiusBigCircle WRITE setRadiusBigCircle)
    Q_PROPERTY(int radiusSmallCircle READ getRadiusSmallCircle WRITE setRadiusSmallCircle)
    Q_PROPERTY(int radiusCatching READ getRadiusCatching WRITE setRadiusCatching)
public:
    Stick(QWidget *parent = 0);
    ~Stick();
    enum Color{Dark, Light};

    Color getColor() const;
    void setColor(const Color& color);

    QMargins getMargins() const;
    void setMargins(const QMargins &margins);

    int getRadiusBigCircle() const;
    void setRadiusBigCircle(int radiusBigCircle);

    int getRadiusSmallCircle() const;
    void setRadiusSmallCircle(int radiusSmallCircle);

    int getRadiusCatching() const;
    void setRadiusCatching(int radiusCatching);
protected:
    virtual void resizeEvent(QResizeEvent *);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
signals:
    //расстояние от 0 до 1, угол от -3.14 до 3.14
    void newValue(qreal range, qreal angle);
private:
    void moveCircle(const QPoint &point);
    void resizeTextures();
    void updateAreaStick();
    void updateMinimumSize();

    QPoint m_centerBigCircle;
    QPoint m_centerSmallCircle;

    Color m_color;

    int m_radiusBigCircle;
    int m_radiusSmallCircle;
    int m_radiusCatching;

    QPixmap m_textureBigCircle;
    QPixmap m_textureSmallCircle;

    QPixmap m_resizedTextureBigCircle;
    QPixmap m_resizedTextureSmallCircle;

    bool m_isMoving;

    QMargins m_margins;
    QRect m_areaStick;
};

#endif // STICK_H
