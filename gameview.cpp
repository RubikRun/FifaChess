#include "gameview.h"
#include "qtimer.h"

#include <QGraphicsRectItem>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , board(QPointF(-400.0f, -400.0f), QPointF(-300.0f, 400.0f), 800.0f)
    , time(0.0f)
{
    setScene(scene);
    setRenderHint(QPainter::Antialiasing, true);
    setBackgroundBrush(backgroundColor);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    // Create the game loop timer,
    gameLoopTimer = new QTimer(this);
    // make it call update() and draw()
    connect(
        gameLoopTimer,
        &QTimer::timeout,
        this,
        [this]()
        {
            update();
            draw();
            time += float(updateInterval) / 1000.0f;
        }
    );
    // repeatedly whenever the fixed time interval passes
    gameLoopTimer->start(updateInterval);
}

void GameView::update()
{
    // Testing if game loop works correctly
    if (true) {
        const float r = 5.0f;
        board = Board(
            QPointF(-400.0f + cosf(time * 1.0f) * r, -400.0f + sinf(time * 2.0f) * r),
            QPointF(-300.0f + cosf(time * 3.0f) * r, 400.0f + sinf(time * 4.0f) * r),
            800.0f
        );
    }
}

void GameView::draw()
{
    scene->clear();
    board.draw(*scene);
}
