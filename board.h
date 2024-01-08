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

    QPointF getTopLeftPoint() const;
    QPointF getBottomLeftPoint() const;
    float getWidth() const;

    /// Returns a 4-point polygon (parallelogram) in scene coordinates
    /// that represents the requested square of the chess board
    /// the way it is projected on the scene
    QPolygonF getPolygonOfSquare(QPoint square) const;

private:
    /// Draws the border of the board on the scene
    void drawBorder(QGraphicsScene &scene) const;
    void drawSquares(QGraphicsScene &scene) const;
    void drawSquare(QGraphicsScene &scene, QPoint square) const;

    void drawDebug(QGraphicsScene &scene) const;
    void drawDebugPoint(QGraphicsScene &scene, const QPointF &point) const;

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

    /// Width of the border's lines in scene coordinates
    float borderWidth = 50.0f;

    static constexpr QColor primaryColor = QColor(170, 170, 170);
    static constexpr QColor secondaryColor = QColor(60, 60, 60);
    static constexpr QColor borderColor = QColor(10, 10, 10);

    static constexpr QColor debugColor = QColor(255, 0, 0, 100);
    static constexpr float debugPointRadius = 10.0f;
    static const bool doDrawDebug = false;
};

#endif // BOARD_H
