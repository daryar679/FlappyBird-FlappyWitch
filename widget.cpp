#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new Scene(this);//создание сцены
    scene -> setSceneRect(-250,-300,500,600);//создание области видимости сцены

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/Images/Sky.png"));//задний фон игры
    scene->addItem(pixItem);//добавление заднего фона на сцену

    pixItem->setPos(QPointF(0,0)- QPointF(pixItem->boundingRect().width()/2, pixItem->boundingRect().height()/2));//установка положения для корректного отображения заднего фона


    ui->graphicsView->setScene(scene);
    scene -> addBird();//добавление "Птицы" на сцену
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_startGameButton_clicked()
{
    scene->startGame();
}
