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

    void addBird();//добавление "Птицы" на сцену

    void startGame();//начало игры

    bool getGameOn() const;//геттер для определения статуса игры
    void setGameOn(bool value);//сеттер для определения статуса игры

    void incrementScore();//счет

    void setScore(int value);//сеттер для счета

signals:
public slots:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;//управление "Птицей" с помощью мыши

private:
    void showGameOverGraphics();//показ графики завершения игры
    void hideGameOverGraphics();//очищение сцены от графики завершения игры
    void cleanPillars();//очищение сцены от столбов
    void setUpPillarTimer();//добавление новой пары столбов через заданный промежуток времени
    void freezeBirdAndPillarsInPlace();//замирание "Птицы" и столбов на месте
    QTimer * pillarTimer;
    Bird * bird;
    bool gameOn;//==true, если игра начата
    int score;
    int bestScore;
    QGraphicsTextItem *scoreTextItem;
};

#endif // SCENE_H
