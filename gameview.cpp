#include "gameview.h"

GameView::GameView(QWidget *parent) : QGraphicsView(parent) {
    QGraphicsScene *scene = new QGraphicsScene(this);
    setScene(scene);

    QGraphicsRectItem *rectangleItem = new QGraphicsRectItem(0, 0, 100, 100);
    rectangleItem->setBrush(QBrush(Qt::red));
    scene->addItem(rectangleItem);

    setBackgroundBrush(QBrush(Qt::blue));
}
