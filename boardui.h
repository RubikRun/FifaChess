#ifndef BOARDUI_H
#define BOARDUI_H

#include "board.h"
#include "qgraphicsscene.h"

#include "chesscontroller.h"

/// User interface of the chess board.
/// This class keeps track of selected pieces, their allowed moves, etc.
/// and draws appropriate UI elements on the scene
class BoardUI
{
public:
    BoardUI(const Board *board, const ChessController *chessController);

    /// Draws the board's UI on the scene
    void draw(QGraphicsScene &scene) const;

    QPoint getSelectedByFirst() const;
    void setSelectedByFirst(QPoint newSelectedByFirst);

    QPoint getSelectedBySecond() const;
    void setSelectedBySecond(QPoint newSelectedBySecond);

private:
    void drawSelectedHighlight(QGraphicsScene &scene, QPoint square) const;
    void drawIndicatorOfMoves(QGraphicsScene &scene, QPoint square) const;
    void drawIndicatorOfMove(QGraphicsScene &scene, QPoint square) const;

private:
    const Board *board = nullptr;
    const ChessController *chessController = nullptr;
    /// Coordinates of the piece selected by player 1
    QPoint selectedByFirst = QPoint(-1, -1);
    /// Coordinates of the piece selected by player 2
    QPoint selectedBySecond = QPoint(-1, -1);

    /// Color with which the selected pieces will be highlighted
    static constexpr QColor highlightColor = QColor(50, 200, 50, 100);
    /// Color of the indicator of possible moves of the selected piece
    static constexpr QColor indicatorColor = QColor(200, 50, 50, 50);
    /// The indicator of possible moves is a circle centered at the square's center.
    /// This parameter here controls the radius of that circle,
    /// as a ratio of the square's diagonal.
    static constexpr float ratioRadiusOfIndicatorOfMove = 0.10f;
};

#endif // BOARDUI_H
