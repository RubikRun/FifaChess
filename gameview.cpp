#include "gameview.h"
#include "qtimer.h"

#include <QGraphicsRectItem>

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
    , scene(new QGraphicsScene(this))
    , board(QPointF(-400.0f, -400.0f), QPointF(-300.0f, 400.0f), 800.0f)
    , boardUI(&board, &chessController)
    , time(0.0f)
{
    setScene(scene);
    setRenderHint(QPainter::Antialiasing, true);
    setBackgroundBrush(backgroundColor);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    initPieces();
    chessController.update(pieces);
    initBoardUI();

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
    chessController.update(pieces);
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
        pieces[i] = new Piece(&board, PieceType(orderOfPieces[i], true), QPoint(i, 0), &bigPixmap);
        pieces[8 + i] = new Piece(&board, PieceType(Pawn, true), QPoint(i, 1), &bigPixmap);
        pieces[16 + i] = new Piece(&board, PieceType(Pawn, false), QPoint(i, 6), &bigPixmap);
        pieces[24 + i] = new Piece(&board, PieceType(orderOfPieces[i], false), QPoint(i, 7), &bigPixmap);
    }
}

void GameView::initBoardUI()
{
    boardUI.setSelectedByFirst(initialSelectedPieceByFirst);
    boardUI.setSelectedBySecond(initialSelectedPieceBySecond);
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        boardUI.setSelectedByFirst(boardUI.getSelectedByFirst() + QPoint(-1, 0));
        break;
    case Qt::Key_D:
        boardUI.setSelectedByFirst(boardUI.getSelectedByFirst() + QPoint(+1, 0));
        break;
    case Qt::Key_S:
        boardUI.setSelectedByFirst(boardUI.getSelectedByFirst() + QPoint(0, -1));
        break;
    case Qt::Key_W:
        boardUI.setSelectedByFirst(boardUI.getSelectedByFirst() + QPoint(0, +1));
        break;
    case Qt::Key_Left:
        boardUI.setSelectedBySecond(boardUI.getSelectedBySecond() + QPoint(-1, 0));
        break;
    case Qt::Key_Right:
        boardUI.setSelectedBySecond(boardUI.getSelectedBySecond() + QPoint(+1, 0));
        break;
    case Qt::Key_Down:
        boardUI.setSelectedBySecond(boardUI.getSelectedBySecond() + QPoint(0, -1));
        break;
    case Qt::Key_Up:
        boardUI.setSelectedBySecond(boardUI.getSelectedBySecond() + QPoint(0, +1));
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
