#include "pillar.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "scene.h"
#include "bird.h"

Pillar::Pillar():topPillar(new QGraphicsPixmapItem(QPixmap(":/Images/Pillar.png"))),bottomPillar(new QGraphicsPixmapItem(QPixmap(":/Images/Pillar.png"))),pastBird(false)
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,topPillar->boundingRect().height() + 70));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,70));

    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));

    xAnimation = new QPropertyAnimation(this,"x",this);
    xAnimation -> setStartValue(260 + xRandomizer);
    xAnimation -> setEndValue(-300);
    xAnimation -> setEasingCurve(QEasingCurve::Linear);
    xAnimation -> setDuration(1500);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        scene() -> removeItem(this);
        delete this;
    });

    xAnimation -> start();

}

Pillar::~Pillar()
{
    delete topPillar;
    delete bottomPillar;
}

qreal Pillar::x() const
{
    return m_x;
}

void Pillar::freezeInPlace()
{
    xAnimation -> stop();
}

void Pillar::setx(qreal x)
{
    m_x = x;

    if(x < 0 && !pastBird)
    {
        pastBird = true;
        QGraphicsScene *mScene = scene();
        Scene *myScene = dynamic_cast<Scene*>(mScene);
        if(myScene)
        {
            myScene -> incrementScore();
        }

    }

    if(collidesWithBird())
    {
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));
}

bool Pillar::collidesWithBird()
{
    QList<QGraphicsItem*> collidingItems = topPillar -> collidingItems();
    collidingItems.append(bottomPillar -> collidingItems());
    foreach(QGraphicsItem *item, collidingItems)
    {
        Bird *bird = dynamic_cast<Bird*>(item);
        if(bird)
        {
            return true;
        }
    }
    return false;
}
