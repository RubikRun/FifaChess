#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

class GameView : public QGraphicsView {
public:
    GameView(QWidget *parent = nullptr);
};

#endif // GAMEVIEW_H
