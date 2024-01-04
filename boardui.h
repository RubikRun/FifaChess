#ifndef BOARDUI_H
#define BOARDUI_H

#include "board.h"
#include "qgraphicsscene.h"

/// User interface of the chess board.
/// This class keeps track of selected pieces, their allowed moves, etc.
/// and draws appropriate UI elements on the scene
class BoardUI
{
public:
    BoardUI(const Board *board);

    /// Draws the board's UI on the scene
    void draw(QGraphicsScene &scene) const;

    QPoint getSelectedByFirst() const;
    void setSelectedByFirst(QPoint newSelectedByFirst);

    QPoint getSelectedBySecond() const;
    void setSelectedBySecond(QPoint newSelectedBySecond);

private:
    void drawSelectedHighlight(QGraphicsScene &scene, int row, int col) const;

private:
    const Board *board = nullptr;
    /// Coordinates of the piece selected by player 1
    QPoint selectedByFirst = QPoint(-1, -1);
    /// Coordinates of the piece selected by player 2
    QPoint selectedBySecond = QPoint(-1, -1);

    /// Color with which the selected pieces will be highlighted
    static constexpr QColor highlightColor = QColor(50, 200, 50, 100);
};

#endif // BOARDUI_H
