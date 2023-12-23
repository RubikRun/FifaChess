#include "gameview.h"

#include <QGraphicsRectItem>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
    , board(QPointF(-400.0f, -400.0f), QPointF(-300.0f, 400.0f), 800.0f)
    , scene(new QGraphicsScene(this))
{
    setScene(scene);
    setRenderHint(QPainter::Antialiasing, true);
    setBackgroundBrush(backgroundColor);

    board.draw(*scene);
}
