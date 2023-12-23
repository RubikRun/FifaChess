#include "board.h"
#include "qgraphicsitem.h"
#include "qpainterpath.h"

Board::Board(const QPointF &topLeftPoint, const QPointF &bottomLeftPoint, const float width)
    : topLeftPoint(topLeftPoint)
    , bottomLeftPoint(bottomLeftPoint)
    , width(width)
{}

void Board::draw(QGraphicsScene &scene) const
{
    drawBorder(scene);
}

void Board::drawBorder(QGraphicsScene &scene) const
{
    QPainterPath path;
    path.moveTo(topLeftPoint.x(), topLeftPoint.y());
    path.lineTo(topLeftPoint.x() + width, topLeftPoint.y());
    path.lineTo(bottomLeftPoint.x() + width, bottomLeftPoint.y());
    path.lineTo(bottomLeftPoint.x(), bottomLeftPoint.y());
    path.closeSubpath();
    QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
    pathItem->setPen(QPen(borderColor, 10.0f));
    scene.addItem(pathItem);
}
