#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

#include "board.h"

class GameView : public QGraphicsView {
public:
    GameView(QWidget *parent = nullptr);

private:
    void update();
    void draw();

private:
    QGraphicsScene *scene;
    Board board;

    /// Time in seconds since the creation of this GameView
    float time;

    QTimer* gameLoopTimer;

    static constexpr QColor backgroundColor = QColor(38, 89, 52);
    /// Interval in milliseconds between update calls
    /// 16 milliseconds is about 60 FPS
    static const int updateInterval = 16;
};

#endif // GAMEVIEW_H
