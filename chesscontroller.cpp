#include "chesscontroller.h"

ChessController::ChessController() {}

void ChessController::update(const Piece* const* pieces)
{
    for (int i = 0; i < 8*8; i++) {
        squareHasPiece[i] = false;
    }
    for (int i = 0; i < 32; i++) {
        const QPoint square = pieces[i]->getSquare();
        if (square.x() > -1 && square.y() > -1) {
            setSquareHasPiece(square, true);
            setSquarePiece(square, pieces[i]->getPieceType());
        }
    }
}

bool ChessController::getSquareHasPiece(QPoint square) const
{
    Q_ASSERT(square.y() >= 0 && square.y() < 8 && square.x() >= 0 && square.x() < 8);
    const int index = getIndexFromCoord(square);
    Q_ASSERT(index >= 0 && index < 8*8);
    return squareHasPiece[index];
}

PieceType ChessController::getSquarePiece(QPoint square) const
{
    Q_ASSERT(square.y() >= 0 && square.y() < 8 && square.x() >= 0 && square.x() < 8);
    const int index = getIndexFromCoord(square);
    Q_ASSERT(index >= 0 && index < 8*8);
    return squarePiece[index];
}

void ChessController::findMoves(QPoint square, QPoint *moves) const
{
    const PieceType pieceType = getSquarePiece(square);
    // Initialize all moves to invalid
    for (int i = 0; i < 7; i++) {
        moves[i] = QPoint(-1, -1);
    }
    findMovesAsIfAlone(square, pieceType, moves);
    removeMovesThatOverlapOwnPiece(pieceType.color, moves);
}

void ChessController::findMovesAsIfAlone(QPoint square, PieceType pieceType, QPoint *moves) const
{
    if (pieceType.shape == PieceShape::Pawn) {
        if (pieceType.color) {
            moves[0] = QPoint(square.x(), square.y() + 1);
            if (square.y() == 1) {
                moves[1] = QPoint(square.x(), square.y() + 2);
            }
        }
        else {
            moves[0] = QPoint(square.x(), square.y() - 1);
            if (square.y() == 6) {
                moves[1] = QPoint(square.x(), square.y() - 2);
            }
        }
    }
}

void ChessController::removeMovesThatOverlapOwnPiece(bool color, QPoint *moves) const
{
    for (int i = 0; i < 7; i++) {
        if (moves[i].x() > -1 && moves[i].y() > -1) {
            if (getSquareHasPiece(moves[i]) && getSquarePiece(moves[i]).color == color) {
                moves[i].setX(-1);
                moves[i].setY(-1);
            }
        }
    }
}

void ChessController::setSquareHasPiece(QPoint square, bool hasPiece)
{
    Q_ASSERT(square.y() >= 0 && square.y() < 8 && square.x() >= 0 && square.x() < 8);
    const int index = getIndexFromCoord(square);
    Q_ASSERT(index >= 0 && index < 8*8);
    squareHasPiece[index] = hasPiece;
}

void ChessController::setSquarePiece(QPoint square, PieceType piece)
{
    Q_ASSERT(square.y() >= 0 && square.y() < 8 && square.x() >= 0 && square.x() < 8);
    const int index = getIndexFromCoord(square);
    Q_ASSERT(index >= 0 && index < 8*8);
    squarePiece[index] = piece;
}

int ChessController::getIndexFromCoord(QPoint square) const
{
    return square.y() * 8 + square.x();
}
