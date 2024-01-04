#include "gameview.h"
#include "qtimer.h"

#include <QGraphicsRectItem>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , board(QPointF(-400.0f, -400.0f), QPointF(-300.0f, 400.0f), 800.0f)
    , boardUI(&board)
    , time(0.0f)
{
    setScene(scene);
    setRenderHint(QPainter::Antialiasing, true);
    setBackgroundBrush(backgroundColor);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    initPieces();
    // Select some initial pieces in UI, for testing
    boardUI.setSelectedByFirst(QPoint(2, 1));
    boardUI.setSelectedBySecond(QPoint(6, 6));

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

GameView::~GameView()
{
    for (int i = 0; i < 32; i++) {
        delete pieces[i];
    }
}

void GameView::update()
{
    // Testing if game loop works correctly
    if (false) {
        const float r = 5.0f;
        board = Board(
            QPointF(-400.0f + cosf(time * 1.0f) * r, -400.0f + sinf(time * 2.0f) * r),
            QPointF(-300.0f + cosf(time * 3.0f) * r, 400.0f + sinf(time * 4.0f) * r),
            800.0f
        );
    }
}

void GameView::draw() const
{
    scene->clear();
    board.draw(*scene);
    for (int i = 31; i >= 0; i--) {
        pieces[i]->draw(*scene);
    }
    boardUI.draw(*scene);
}

void GameView::initPieces()
{
    const QPixmap bigPixmap("C:/dev/FifaChess/res/images/chess_pieces.png");
    for (int i = 0; i < 8; i++) {
        pieces[i] = new Piece(&board, orderOfPieces[i], true, 0, i, &bigPixmap);
        pieces[8 + i] = new Piece(&board, Pawn, true, 1, i, &bigPixmap);
        pieces[16 + i] = new Piece(&board, Pawn, false, 6, i, &bigPixmap);
        pieces[24 + i] = new Piece(&board, orderOfPieces[i], false, 7, i, &bigPixmap);
    }
}
