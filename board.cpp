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
    drawSquares(scene);

    if (doDrawDebug) {
        drawDebug(scene);
    }
}

QPointF Board::getTopLeftPoint() const
{
    return topLeftPoint;
}

QPointF Board::getBottomLeftPoint() const
{
    return bottomLeftPoint;
}

float Board::getWidth() const
{
    return width;
}

QPolygonF Board::getPolygonOfSquare(QPoint square) const
{
    const QPointF toTopLeftVec = topLeftPoint - bottomLeftPoint;
    // Calculate bottom left point of the current square
    const QPointF blp(bottomLeftPoint.x() + square.y() * toTopLeftVec.x() / 8.0f + square.x() * width / 8.0f, bottomLeftPoint.y() + square.y() * toTopLeftVec.y() / 8.0f);
    // Create a polygon with the 4 vertices of the current square
    QPolygonF polygon;
    polygon
        << blp
        << QPointF(blp.x() + width / 8.0f, blp.y())
        << QPointF(blp.x() + width / 8.0f + toTopLeftVec.x() / 8.0f, blp.y() + toTopLeftVec.y() / 8.0f)
        << QPointF(blp.x() + toTopLeftVec.x() / 8.0f, blp.y() + toTopLeftVec.y() / 8.0f);
    return polygon;
}

void Board::drawBorder(QGraphicsScene &scene) const
{
    QPainterPath path;
    path.moveTo(topLeftPoint.x() - borderWidth * 0.45f, topLeftPoint.y() - borderWidth * 0.45f);
    path.lineTo(topLeftPoint.x() + width + borderWidth * 0.45f, topLeftPoint.y() - borderWidth * 0.45f);
    path.lineTo(bottomLeftPoint.x() + width + borderWidth * 0.45f, bottomLeftPoint.y() + borderWidth * 0.45f);
    path.lineTo(bottomLeftPoint.x() - borderWidth * 0.45f, bottomLeftPoint.y() + borderWidth * 0.45f);
    path.closeSubpath();
    QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
    pathItem->setPen(QPen(borderColor, borderWidth));
    scene.addItem(pathItem);
}

void Board::drawSquares(QGraphicsScene &scene) const
{
    for (QPoint square(0, 0); square.y() < 8; square.setY(square.y() + 1)) {
        for (square.setX(0); square.x() < 8; square.setX(square.x() + 1)) {
            drawSquare(scene, square);
        }
    }
}

void Board::drawSquare(QGraphicsScene &scene, QPoint square) const
{
    QPolygonF polygon = getPolygonOfSquare(square);
    QGraphicsPolygonItem *polygonItem = new QGraphicsPolygonItem(polygon);
    // Choose a color for the current square so that they are altering between primary and secondary color
    const QColor color = (square.x() + square.y()) % 2 == 0 ? primaryColor : secondaryColor;
    polygonItem->setPen(color);
    polygonItem->setBrush(color);
    // Add polygon to the scene
    scene.addItem(polygonItem);
}

void Board::drawDebug(QGraphicsScene &scene) const
{
    drawDebugPoint(scene, topLeftPoint);
    drawDebugPoint(scene, bottomLeftPoint);
}

void Board::drawDebugPoint(QGraphicsScene &scene, const QPointF &point) const
{
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(
        point.x() - debugPointRadius,
        point.y() - debugPointRadius,
        debugPointRadius * 2.0f,
        debugPointRadius * 2.0f
    );
    circle->setBrush(debugColor);
    scene.addItem(circle);
}
