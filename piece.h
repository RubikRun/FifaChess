#ifndef PIECE_H
#define PIECE_H

#include "board.h"
#include "qgraphicsitem.h"

enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King };

class Piece
{
public:
    Piece(const Board *board, PieceType type, bool color, int row, int col, const QPixmap *bigPixmap);

    void draw(QGraphicsScene &scene) const;

private:
    void initPixmap();
    void initPixmapPos();

    /// Returns the region of this piece's image inside the big image
    const QRect &getImageRegion() const;

private:
    /// The board this piece belongs to
    const Board *board = nullptr;
    /// Chess type of piece
    PieceType type;
    /// Color of the piece. True is white, false is black
    bool color = true;
    /// Position piece on board
    int row = -1;
    int col = -1;

    /// Pixel data of the piece's image
    QPixmap pixmap;
    /// Position of the pixmap item on screen
    QPointF pixmapPos;

    /// Pixel data of the big image, inside of which there is a region that is the image of this piece
    const QPixmap *bigPixmap = nullptr;

    static constexpr float ratioWidthPieceToSquare = 0.5f;
    static constexpr float ratioLeftOfPieceOnSquare = 0.21;
    static constexpr float ratioBottomOfPieceOnSquare = 0.05f;

    /// The images for all 12 pieces are in a single big image.
    /// The image of each piece is a region of the big image.
    /// This array here contains the region coordinates inside the big image for each piece.
    /// First are the 6 white pieces, then the 6 black ones,
    /// in this order: Pawn, Rook, Knight, Bishop, Queen, King
    static constexpr QRect imageRegions[] {
        QRect(3397, 786, 399, 635),
        QRect(2817, 558, 511, 869),
        QRect(2164, 438, 583, 990),
        QRect(1586, 335, 491, 1090),
        QRect(987, 293, 541, 1129),
        QRect(299, 116, 621, 1309),
        QRect(338, 2188, 399, 640),
        QRect(806, 1967, 511, 868),
        QRect(1387, 1846, 583, 991),
        QRect(2057, 1744, 491, 1089),
        QRect(2607, 1704, 541, 1126),
        QRect(3214, 1531, 622, 1304)
    };
};

#endif // PIECE_H
