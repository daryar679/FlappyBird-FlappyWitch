#include "birditem.h"
#include <QGraphicsScene>

BirdItem::BirdItem(QPixmap pixmap)
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

qreal BirdItem::rotation() const
{
    return m_rotation;
}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::shootUp()
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

void BirdItem::startFlying()
{
    yAnimation -> start();
    rotateTo(90,1200,QEasingCurve::InQuad);

}

void BirdItem::freezeInPlace()
{
    yAnimation -> stop();
    rotationAnimation -> stop();
}

void BirdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(rotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void BirdItem::setY(qreal y)
{
    moveBy(0, y - m_y);
    m_y = y;
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation -> setStartValue(rotation());
    rotationAnimation -> setEndValue(end);
    rotationAnimation -> setEasingCurve(curve);
    rotationAnimation -> setDuration(duration);

    rotationAnimation -> start();
}

void BirdItem::fallToGroudIfNecessary()
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
