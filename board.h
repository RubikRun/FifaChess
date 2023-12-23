#ifndef BOARD_H
#define BOARD_H

#include "qgraphicsscene.h"
#include "qpoint.h"

/// Board on which the game is played - a chess board with 8x8 squares.
/// The game uses ortographic projection
/// and so the board is projected as a parallelogram on screen.
class Board
{
public:
    Board(const QPointF &topLeftPoint, const QPointF &bottomLeftPoint, const float width);

    /// Draws the board on the scene
    void draw(QGraphicsScene &scene) const;

private:
    /// Draws the border of the board on the scene
    void drawBorder(QGraphicsScene &scene) const;

private:
    /// Top-left corner of the board in scene coordinates
    QPointF topLeftPoint;
    /// Bottom-left corner of the board in scene coordinates
    QPointF bottomLeftPoint;
    /// Width of the board in scene coordinates.
    /// More precisely the board is a parallelogram on screen
    /// and the width is the length of the upper side
    /// between the top-left corner and the top-right corner.
    float width;

    QColor primaryColor = QColor(170, 170, 170);
    QColor secondaryColor = QColor(50, 50, 50);
    QColor borderColor = QColor(220, 220, 220);
};

#endif // BOARD_H
