#include "pillar.h"
#include <QRandomGenerator>
#include <QGraphicsScene>
#include "scene.h"
#include "bird.h"

Pillar::Pillar():topPillar(new QGraphicsPixmapItem(QPixmap(":/Images/Pillar.png"))),bottomPillar(new QGraphicsPixmapItem(QPixmap(":/Images/Pillar.png"))),pastBird(false)
{
    topPillar->setPos(QPointF(0,0) - QPointF(topPillar->boundingRect().width()/2,topPillar->boundingRect().height() + 70));//установка положения для верхнего столба
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,70));//установка положения для нижнего столба

    //объединяем верхний и нижний столбы для того,чтобы использовать их как одно целое
    addToGroup(topPillar);
    addToGroup(bottomPillar);

    //создание случайной позиции для столбов
    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPoint(0,0) + QPoint(260 + xRandomizer, yPos));//установка позиции

    xAnimation = new QPropertyAnimation(this,"x",this);//конструктор для свойства перемещения
    xAnimation -> setStartValue(260 + xRandomizer);//стартовое значение для появления столбов
    xAnimation -> setEndValue(-300);//конечное значение для исчезновения столбов
    xAnimation -> setEasingCurve(QEasingCurve::Linear);//установление управления анимацией(столбы двигаются по прямой линии)
    xAnimation -> setDuration(1500);//установление продолжительности движения столбов

    //удаление столбов, когда они уходят из зоны видимости
    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        scene() -> removeItem(this);
        delete this;
    });

    xAnimation -> start();//начало анимации

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
    //прекращение анимации
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
    QList<QGraphicsItem*> collidingItems = topPillar -> collidingItems();//заполняем список объектами, с которыми может столкнуться "Птица"
    collidingItems.append(bottomPillar -> collidingItems());//добавляем в список нижний столб
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
