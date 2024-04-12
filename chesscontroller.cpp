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
    // Initialize all moves to invalid
    for (int i = 0; i < 28; i++) {
        moves[i] = QPoint(-1, -1);
    }
    if (!getSquareHasPiece(square)) {
        return;
    }
    const PieceType pieceType = getSquarePiece(square);
    switch (pieceType.shape)
    {
        case Pawn: findMovesOfPawn(square, pieceType.color, moves); break;
        case Rook: findMovesOfRook(square, pieceType.color, moves); break;
        case Knight: findMovesOfKnight(square, pieceType.color, moves); break;
        case Bishop: findMovesOfBishop(square, pieceType.color, moves); break;
        case Queen: findMovesOfQueen(square, pieceType.color, moves); break;
        case King: findMovesOfKing(square, pieceType.color, moves); break;
    }
}

void ChessController::findMovesOfPawn(QPoint square, bool color, QPoint *moves) const
{
    int movesFilled = 0;
    if (color) {
        QPoint nextMove = QPoint(square.x(), square.y() + 1);
        if (!isValidSquare(nextMove) || getSquareHasPiece(nextMove)) {
            return;
        }
        moves[movesFilled++] = nextMove;
        if (square.y() == 1) {
            nextMove = QPoint(square.x(), square.y() + 2);
            if (getSquareHasPiece(nextMove)) {
                return;
            }
            moves[movesFilled++] = nextMove;
        }
        nextMove = QPoint(square.x() + 1, square.y() + 1);
    }
    else {
        QPoint nextMove = QPoint(square.x(), square.y() - 1);
        if (!isValidSquare(nextMove) || getSquareHasPiece(nextMove)) {
            return;
        }
        moves[movesFilled++] = nextMove;
        if (square.y() == 6) {
            nextMove = QPoint(square.x(), square.y() - 2);
            if (getSquareHasPiece(nextMove)) {
                return;
            }
            moves[movesFilled++] = nextMove;
        }
    }
}

#define HANDLE_NEXTMOVE \
if (getSquareHasPiece(nextMove)) { \
    if (getSquarePiece(nextMove).color != color) { \
        moves[movesFilled++] = nextMove; \
    } \
    break; \
} \
moves[movesFilled++] = nextMove

#define HANDLE_SINGLE_NEXTMOVE \
if (isValidSquare(nextMove) && (!getSquareHasPiece(nextMove) || getSquarePiece(nextMove).color != color)) { \
    moves[movesFilled++] = nextMove; \
}

void ChessController::findMovesOfRook(QPoint square, bool color, QPoint *moves) const
{
    int movesFilled = 0;
    QPoint nextMove(-1, -1);

    for (nextMove = QPoint(square.x() + 1, square.y()); nextMove.x() < 8; nextMove.setX(nextMove.x() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() - 1, square.y()); nextMove.x() >= 0; nextMove.setX(nextMove.x() - 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x(), square.y() + 1); nextMove.y() < 8; nextMove.setY(nextMove.y() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x(), square.y() - 1); nextMove.y() >= 0; nextMove.setY(nextMove.y() - 1)) {
        HANDLE_NEXTMOVE;
    }
}

void ChessController::findMovesOfKnight(QPoint square, bool color, QPoint *moves) const
{

}

void ChessController::findMovesOfBishop(QPoint square, bool color, QPoint *moves) const
{
    int movesFilled = 0;
    QPoint nextMove(-1, -1);

    for (nextMove = QPoint(square.x() + 1, square.y() + 1); nextMove.x() < 8 && nextMove.y() < 8; nextMove.setX(nextMove.x() + 1), nextMove.setY(nextMove.y() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() + 1, square.y() - 1); nextMove.x() < 8 && nextMove.y() >= 0; nextMove.setX(nextMove.x() + 1), nextMove.setY(nextMove.y() - 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() -1, square.y() + 1); nextMove.x() >= 0 && nextMove.y() < 8; nextMove.setX(nextMove.x() - 1), nextMove.setY(nextMove.y() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() - 1, square.y() - 1); nextMove.x() >= 0 && nextMove.y() >= 0; nextMove.setX(nextMove.x() - 1), nextMove.setY(nextMove.y() - 1)) {
        HANDLE_NEXTMOVE;
    }

}

void ChessController::findMovesOfQueen(QPoint square, bool color, QPoint *moves) const
{
    int movesFilled = 0;
    QPoint nextMove(-1, -1);

    for (nextMove = QPoint(square.x() + 1, square.y()); nextMove.x() < 8; nextMove.setX(nextMove.x() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() - 1, square.y()); nextMove.x() >= 0; nextMove.setX(nextMove.x() - 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x(), square.y() + 1); nextMove.y() < 8; nextMove.setY(nextMove.y() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x(), square.y() - 1); nextMove.y() >= 0; nextMove.setY(nextMove.y() - 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() + 1, square.y() + 1); nextMove.x() < 8 && nextMove.y() < 8; nextMove.setX(nextMove.x() + 1), nextMove.setY(nextMove.y() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() + 1, square.y() - 1); nextMove.x() < 8 && nextMove.y() >= 0; nextMove.setX(nextMove.x() + 1), nextMove.setY(nextMove.y() - 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() -1, square.y() + 1); nextMove.x() >= 0 && nextMove.y() < 8; nextMove.setX(nextMove.x() - 1), nextMove.setY(nextMove.y() + 1)) {
        HANDLE_NEXTMOVE;
    }
    for (nextMove = QPoint(square.x() - 1, square.y() - 1); nextMove.x() >= 0 && nextMove.y() >= 0; nextMove.setX(nextMove.x() - 1), nextMove.setY(nextMove.y() - 1)) {
        HANDLE_NEXTMOVE;
    }
}

void ChessController::findMovesOfKing(QPoint square, bool color, QPoint *moves) const
{
    int movesFilled = 0;
    QPoint nextMove(-1, -1);

    nextMove = QPoint(square.x() + 1, square.y());
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x() - 1, square.y());
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x(), square.y() + 1);
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x(), square.y() - 1);
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x() + 1, square.y() + 1);
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x() + 1, square.y() - 1);
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x() -1, square.y() + 1);
    HANDLE_SINGLE_NEXTMOVE;
    nextMove = QPoint(square.x() - 1, square.y() - 1);
    HANDLE_SINGLE_NEXTMOVE;
}

bool ChessController::isValidSquare(QPoint square)
{
    return (square.x() >= 0 && square.x() < 8 && square.y() >= 0 && square.y() < 8);
}

#undef HANDLE_NEXTMOVE

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
