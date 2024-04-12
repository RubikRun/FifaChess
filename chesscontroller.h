#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include "piece.h"

class ChessController
{
public:
    ChessController();

    /// Updates the chess controller with given pieces using their current positions
    void update(const Piece* const* pieces);

    bool getSquareHasPiece(QPoint square) const;
    PieceType getSquarePiece(QPoint square) const;

    void findMoves(QPoint square, QPoint *moves) const;

private:
    void findMovesOfPawn(QPoint square, bool color, QPoint *moves) const;
    void findMovesOfRook(QPoint square, bool color, QPoint *moves) const;
    void findMovesOfKnight(QPoint square, bool color, QPoint *moves) const;
    void findMovesOfBishop(QPoint square, bool color, QPoint *moves) const;
    void findMovesOfQueen(QPoint square, bool color, QPoint *moves) const;
    void findMovesOfKing(QPoint square, bool color, QPoint *moves) const;

    static bool isValidSquare(QPoint square);

    void setSquareHasPiece(QPoint square, bool hasPiece);
    void setSquarePiece(QPoint square, PieceType piece);

    int getIndexFromCoord(QPoint square) const;

private:
    bool squareHasPiece[8*8];
    PieceType squarePiece[8*8];
};

#endif // CHESSCONTROLLER_H
