#include "piece.h"

Piece::Piece(const Board *board, PieceType type, bool color, int row, int col, const QPixmap *bigPixmap)
    : board(board)
    , type(type)
    , color(color)
    , row(row)
    , col(col)
    , bigPixmap(bigPixmap)
{
    initPixmap();
    initPixmapPos();
}

void Piece::draw(QGraphicsScene &scene) const
{
    if (pixmap.isNull()) {
        qCritical() << "Invalid pixmap of piece when trying to draw";
        return;
    }
    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem(pixmap);
    pixmapItem->setPos(pixmapPos);
    scene.addItem(pixmapItem);
}

void Piece::initPixmap()
{
    if (bigPixmap == nullptr) {
        qCritical() << "Trying to initialize a pixmap of a piece with a null bigPixmap";
        return;
    }
    const QPointF toTopLeftVec = board->getTopLeftPoint() - board->getBottomLeftPoint();

    const QPixmap croppedPixmap = bigPixmap->copy(getImageRegion());
    pixmap = croppedPixmap.scaled(QSize(int(board->getWidth() * ratioWidthPieceToSquare / 8.0f), -toTopLeftVec.y()), Qt::KeepAspectRatio);
}

void Piece::initPixmapPos()
{
    const QPointF toTopLeftVec = board->getTopLeftPoint() - board->getBottomLeftPoint();
    // Calculate bottom left point of the current square
    const QPointF blp(
        board->getBottomLeftPoint().x() + row * toTopLeftVec.x() / 8.0f + col * board->getWidth() / 8.0f,
        board->getBottomLeftPoint().y() + row * toTopLeftVec.y() / 8.0f
        );
    pixmapPos = QPointF(
        blp.x() + ratioLeftOfPieceOnSquare * board->getWidth() / 8.0f,
        blp.y() + ratioBottomOfPieceOnSquare * toTopLeftVec.y() / 8.0f - float(pixmap.height())
    );
}

const QRect &Piece::getImageRegion() const
{
    if (color) {
        return imageRegions[type];
    }
    return imageRegions[6 + type];
}
