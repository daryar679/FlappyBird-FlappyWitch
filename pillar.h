#ifndef PILLAR_H
#define PILLAR_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Pillar :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setx)
public:
    explicit Pillar();
    ~Pillar();
    qreal x() const;//геттер для  перемещения по х
    void freezeInPlace();//замирание столбов на месте

signals:

    void collideFail();//сигнал для окончания игры при столкновении "Птицы" и столба

public slots:

    void setx(qreal x);//сеттер для перемещения по х

private:
    bool collidesWithBird();//столкновение с "Птицей"(==true при столкновении)
    QGraphicsPixmapItem * topPillar;//верхний столб
    QGraphicsPixmapItem * bottomPillar;//нижний столб
    QPropertyAnimation * xAnimation;//свойство перемещения столбов справа налево
    int yPos;
    qreal m_x;
    bool pastBird;//флаг для отслеживания прохождения "Птицы" через столбы
};

#endif // PILLAR_H
