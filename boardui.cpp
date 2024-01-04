#include "boardui.h"
#include "qgraphicsitem.h"

BoardUI::BoardUI(const Board *board)
    : board(board)
{}

void BoardUI::draw(QGraphicsScene &scene) const
{
    if (selectedByFirst.x() > -1) {
        drawSelectedHighlight(scene, selectedByFirst.y(), selectedByFirst.x());
    }
    if (selectedBySecond.x() > -1) {
        drawSelectedHighlight(scene, selectedBySecond.y(), selectedBySecond.x());
    }
}

QPoint BoardUI::getSelectedByFirst() const
{
    return selectedByFirst;
}

void BoardUI::setSelectedByFirst(QPoint newSelectedByFirst)
{
    selectedByFirst = newSelectedByFirst;
}

QPoint BoardUI::getSelectedBySecond() const
{
    return selectedBySecond;
}

void BoardUI::setSelectedBySecond(QPoint newSelectedBySecond)
{
    selectedBySecond = newSelectedBySecond;
}

void BoardUI::drawSelectedHighlight(QGraphicsScene &scene, int row, int col) const
{
    QPolygonF polygon = board->getPolygonOfSquare(row, col);
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(polygon);
    polygonItem->setPen(highlightColor);
    polygonItem->setBrush(highlightColor);
    // Add polygon to the scene
    scene.addItem(polygonItem);
}
