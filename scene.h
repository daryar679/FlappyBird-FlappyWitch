#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include "pillar.h"
#include "bird.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool value);

    void incrementScore();

    void setScore(int value);

signals:
public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;

private:
    void showGameOverGraphics();
    void hideGameOverGraphics();
    void cleanPillars();
    void setUpPillarTimer();
    void freezeBirdAndPillarsInPlace();
    QTimer * pillarTimer;
    Bird * bird;
    bool gameOn;
    int score;
    int bestScore;
    QGraphicsTextItem *scoreTextItem;
};

#endif // SCENE_H
