#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>

#include "board.h"
#include "boardui.h"
#include "piece.h"
#include <QKeyEvent>

class GameView : public QGraphicsView {
public:
    GameView(QWidget *parent = nullptr);
    ~GameView();

private:
    void update();
    void draw() const;

    /// Initializes the 32 pieces on the board
    void initPieces();

    void initBoardUI();

    void keyPressEvent(QKeyEvent *event) override;

private:
    QGraphicsScene *scene;
    Board board;
    BoardUI boardUI;
    Piece *pieces[32];

    /// Time in seconds since the creation of this GameView
    float time;
    /// Timer for the game loop that will call the update() function repeatedly
    QTimer* gameLoopTimer;
    static constexpr QColor backgroundColor = QColor(38, 89, 52);
    /// Interval in milliseconds between update calls
    /// 16 milliseconds is about 60 FPS
    static const int updateInterval = 16;
    /// The standard order of pieces on the first and last row of a chess board
    static constexpr PieceType orderOfPieces[8] = { Rook, Knight, Bishop, Queen, King, Bishop, Knight, Rook };
    /// The initially selected pieces by each player when game is started
    static constexpr QPoint initialSelectedPieceByFirst = QPoint(3, 1);
    static constexpr QPoint initialSelectedPieceBySecond = QPoint(4, 6);
};

#endif // GAMEVIEW_H
