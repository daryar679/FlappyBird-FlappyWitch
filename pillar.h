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
    qreal x() const;
    void freezeInPlace();

signals:

    void collideFail();

public slots:

    void setx(qreal x);

private:
    bool collidesWithBird();
    QGraphicsPixmapItem * topPillar;
    QGraphicsPixmapItem * bottomPillar;
    QPropertyAnimation * xAnimation;
    int yPos;
    qreal m_x;
    bool pastBird;
};

#endif // PILLAR_H
