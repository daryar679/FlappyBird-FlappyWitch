#include "bird.h"
#include <QGraphicsScene>

Bird::Bird(QPixmap pixmap)
{
    setPixmap(pixmap);

    groundPosition = scenePos().y() + 290;//позиция земли

    yAnimation = new QPropertyAnimation(this,"y",this);//конструктор для перемещения по у
    yAnimation -> setStartValue(scenePos().y());//стартовое значение(является текущей позицией)
    yAnimation -> setEndValue(groundPosition);//конечное значение(позиция земли)
    yAnimation -> setEasingCurve(QEasingCurve::InQuad);//установление управления анимацией
    yAnimation -> setDuration(1000);//установление продолжительности движения "Птицы"

    rotationAnimation = new QPropertyAnimation(this,"rotation",this);//конструктор для вращения

}

qreal Bird::rotation() const
{
    return m_rotation;
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::shootUp()
{
    //прекращение анимации
    yAnimation -> stop();
    rotationAnimation -> stop();

    qreal curPosY = y();//текущее положение "Птицы"
    yAnimation -> setStartValue(curPosY);//начальное значение для перемещения по у
    yAnimation -> setEndValue(curPosY - scene() ->sceneRect().height()/10);//позиция, на которую "Птица" взлетает
    yAnimation -> setDuration(285);//продолжительность взлета

    //когда взлет заканчивается,"Птица" начинает падать
    connect(yAnimation,&QPropertyAnimation::finished,[=](){
        fallToGroudIfNecessary();
    });

    yAnimation -> start();//начало анимации

    rotateTo(-20,200,QEasingCurve::OutCubic);//установка значений для вращения "Птицы" вверх
}

void Bird::startFlying()
{
    //начало анимации при старте игры
    yAnimation -> start();
    rotateTo(90,1200,QEasingCurve::InQuad);

}

void Bird::freezeInPlace()
{
    //прекращение анимации
    yAnimation -> stop();
    rotationAnimation -> stop();
}

void Bird::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void Bird::setY(qreal y)
{
    moveBy(0, y - m_y);//падение "Птицы" после старта игры
    m_y = y;
}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation -> setStartValue(rotation());//положение, с которого начинается вращение
    rotationAnimation -> setEndValue(end);//конечное положение
    rotationAnimation -> setEasingCurve(curve);//установление управления анимацией(каким образом нужно вращаться)
    rotationAnimation -> setDuration(duration);//установление продолжительности движения

    rotationAnimation -> start();//начало вращения
}

void Bird::fallToGroudIfNecessary()
{
    if(y() < groundPosition)//пока "Птица" не упала на землю
    {
        rotationAnimation -> stop();//прежнее вращение прекращается

        //анимация падения "Птицы"
        yAnimation -> setStartValue(y());
        yAnimation -> setEasingCurve(QEasingCurve::InQuad);
        yAnimation -> setEndValue(groundPosition);
        yAnimation -> setDuration(1200);
        yAnimation -> start();

        rotateTo(90,1100,QEasingCurve::InCubic);//установка значений для вращения "Птицы" вниз
    }
}
