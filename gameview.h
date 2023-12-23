#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

#include "board.h"

class GameView : public QGraphicsView {
public:
    GameView(QWidget *parent = nullptr);

private:
    QGraphicsScene *scene;
    Board board;
    QColor backgroundColor = QColor(38, 89, 52);
};

#endif // GAMEVIEW_H
