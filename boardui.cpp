#include "boardui.h"
#include "qgraphicsitem.h"

BoardUI::BoardUI(const Board *board, const ChessController *chessController)
    : board(board)
    , chessController(chessController)
{}

void BoardUI::draw(QGraphicsScene &scene) const
{
    if (selectedByFirst.x() > -1 && selectedByFirst.y() > -1) {
        drawSelectedHighlight(scene, selectedByFirst);
        drawIndicatorOfMoves(scene, selectedByFirst);
    }
    if (selectedBySecond.x() > -1 && selectedBySecond.y() > -1) {
        drawSelectedHighlight(scene, selectedBySecond);
        drawIndicatorOfMoves(scene, selectedBySecond);
    }
}

QPoint BoardUI::getSelectedByFirst() const
{
    return selectedByFirst;
}

static void clampQPoint(QPoint &point, QPoint min, QPoint max) {
    point.setX(qBound(min.x(), point.x(), max.x()));
    point.setY(qBound(min.y(), point.y(), max.y()));
}

void BoardUI::setSelectedByFirst(QPoint newSelectedByFirst)
{
    clampQPoint(newSelectedByFirst, QPoint(0, 0), QPoint(7, 7));
    selectedByFirst = newSelectedByFirst;
}

QPoint BoardUI::getSelectedBySecond() const
{
    return selectedBySecond;
}

void BoardUI::setSelectedBySecond(QPoint newSelectedBySecond)
{
    clampQPoint(newSelectedBySecond, QPoint(0, 0), QPoint(7, 7));
    selectedBySecond = newSelectedBySecond;
}

void BoardUI::drawSelectedHighlight(QGraphicsScene &scene, QPoint square) const
{
    const QPolygonF polygon = board->getPolygonOfSquare(square);
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(polygon);
    polygonItem->setPen(highlightColor);
    polygonItem->setBrush(highlightColor);
    // Add polygon to the scene
    scene.addItem(polygonItem);
}

void BoardUI::drawIndicatorOfMoves(QGraphicsScene &scene, QPoint square) const
{
    QPoint moves[7];
    chessController->findMoves(square, moves);

    for (int i = 0; i < 7; i++) {
        if (moves[i].x() > -1 && moves[i].y() > -1) {
            drawIndicatorOfMove(scene, moves[i]);
        }
    }
}

void BoardUI::drawIndicatorOfMove(QGraphicsScene &scene, QPoint square) const
{
    const QPolygonF polygon = board->getPolygonOfSquare(square);
    const QPointF center = (polygon.at(0) + polygon.at(2)) * 0.5f;
    const float radius = ratioRadiusOfIndicatorOfMove * QLineF(polygon.at(0), polygon.at(2)).length();

    QGraphicsEllipseItem *circleItem = new QGraphicsEllipseItem(
        center.x() - radius,
        center.y() - radius,
        radius * 2.0f,
        radius * 2.0f
    );
    circleItem->setBrush(QBrush(indicatorColor));
    circleItem->setPen(QPen(indicatorColor));
    scene.addItem(circleItem);
}
