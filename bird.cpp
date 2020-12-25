#include "bird.h"
#include <QGraphicsScene>

Bird::Bird(QPixmap pixmap)
{
    setPixmap(pixmap);

    groundPosition = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation -> setStartValue(scenePos().y());
    yAnimation -> setEndValue(groundPosition);
    yAnimation -> setEasingCurve(QEasingCurve::InQuad);
    yAnimation -> setDuration(1000);

    rotationAnimation = new QPropertyAnimation(this,"rotation",this);

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
    yAnimation -> stop();
    rotationAnimation -> stop();

    qreal curPosY = y();
    yAnimation -> setStartValue(curPosY);
    yAnimation -> setEndValue(curPosY - scene() ->sceneRect().height()/10);
    yAnimation -> setDuration(285);

    connect(yAnimation,&QPropertyAnimation::finished,[=](){
        fallToGroudIfNecessary();
    });

    yAnimation -> start();

    rotateTo(-20,200,QEasingCurve::OutCubic);
}

void Bird::startFlying()
{
    yAnimation -> start();
    rotateTo(90,1200,QEasingCurve::InQuad);

}

void Bird::freezeInPlace()
{
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
    moveBy(0, y - m_y);
    m_y = y;
}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation -> setStartValue(rotation());
    rotationAnimation -> setEndValue(end);
    rotationAnimation -> setEasingCurve(curve);
    rotationAnimation -> setDuration(duration);

    rotationAnimation -> start();
}

void Bird::fallToGroudIfNecessary()
{
    if(y() < groundPosition)
    {
        rotationAnimation -> stop();

        yAnimation -> setStartValue(y());
        yAnimation -> setEasingCurve(QEasingCurve::InQuad);
        yAnimation -> setEndValue(groundPosition);
        yAnimation -> setDuration(1200);
        yAnimation -> start();

        rotateTo(90,1100,QEasingCurve::InCubic);
    }
}
