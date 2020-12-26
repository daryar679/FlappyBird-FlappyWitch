#ifndef BIRD_H
#define BIRD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Bird : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    explicit Bird(QPixmap pixmap);

    qreal rotation() const;//геттер для вращения

    qreal y() const;//геттер для перемещения по у

    void shootUp();//взлет "Птицы"

    void startFlying();//начало движения "Птицы" при старте игры

    void freezeInPlace();//замирание "Птицы" на месте в случае окончания игры

public slots:
    void setRotation(qreal rotation);//сеттер для вращения

    void setY(qreal y);//сеттер для перемещения по у

    void rotateTo(const qreal &end, const int& duration, const QEasingCurve& curve);//вращение "Птицы"

    void fallToGroudIfNecessary();//падение "Птицы" после взлета

signals:

private:
    qreal m_rotation;
    qreal m_y;
    QPropertyAnimation * yAnimation;//свойство перемещения "Птицы" по у
    QPropertyAnimation * rotationAnimation;//свойство вращения "Птицы"
    qreal groundPosition;//позиция земли
};

#endif // BIRD_H
