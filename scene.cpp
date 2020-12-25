#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>


Scene::Scene(QObject *parent) : QGraphicsScene(parent), gameOn(false),score(0),bestScore(0)
{
    setUpPillarTimer();
}

void Scene::addBird()
{
    bird = new Bird(QPixmap(":/Images/Circle.png"));
    addItem(bird);
}

void Scene::startGame()
{
    bird -> startFlying();
    if(!pillarTimer -> isActive())
    {
        cleanPillars();
        setGameOn(true);
        setScore(0);
        hideGameOverGraphics();
        pillarTimer -> start(1000);
    }
}

void Scene::setUpPillarTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer,&QTimer::timeout,[=](){
       Pillar * pillar = new Pillar();

       connect(pillar,&Pillar::collideFail,[=](){
          pillarTimer -> stop();
          freezeBirdAndPillarsInPlace();
          setGameOn(false);
          showGameOverGraphics();
       });

       addItem(pillar);
    });
}

void Scene::freezeBirdAndPillarsInPlace()
{
    bird -> freezeInPlace();
    QList <QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem* item, sceneItems)
    {
        PillarItem *pillar = dynamic_cast<PillarItem*>(item);
        if(pillar)
        {
            pillar -> freezeInPlace();
        }
    }
}

void Scene::setScore(int value)
{
    score = value;
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool value)
{
    gameOn = value;
}

void Scene::incrementScore()
{
    ++score;
    if(score > bestScore)
    {
        bestScore = score;
    }
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event -> button() == Qt::LeftButton)
    {
        if(gameOn)
        {
            bird ->shootUp();
        }
    }
    QGraphicsScene:: mousePressEvent(event);
}

void Scene::showGameOverGraphics()
{
    scoreTextItem = new QGraphicsTextItem();
    QString htmlString = "<p> Game Over </p><p> Score: " +QString::number(score) +"</p" + "<p> Best Score: " +QString::number(bestScore) + "</p>";
    QFont mFont("Consolas",30,QFont::Bold);
    scoreTextItem -> setHtml(htmlString);
    scoreTextItem -> setFont(mFont);
    scoreTextItem -> setDefaultTextColor(Qt::white);
    addItem(scoreTextItem);

    scoreTextItem -> setPos(QPointF(0,0)-QPointF(scoreTextItem->boundingRect().width()/2,scoreTextItem->boundingRect().height()/2));
}

void Scene::hideGameOverGraphics()
{
    if(scoreTextItem)
    {
        removeItem(scoreTextItem);
        delete scoreTextItem;
        scoreTextItem = nullptr;
    }
}

void Scene::cleanPillars()
{
    QList <QGraphicsItem*> sceneItems = items();
    foreach(QGraphicsItem* item, sceneItems)
    {
        Pillar *pillar = dynamic_cast<Pillar*>(item);
        if(pillar)
        {
            removeItem(pillar);
            delete pillar;
        }
    }
}
