#pragma once

enum class MoveFlag{
    Quiet,
    DoublePawnPush,
    Capture,
    EnPassantCapture,
    KingCastle,
    QueenCastle,
    PromoteToQueen,
    PromoteToRook,
    PromoteToBishop,
    PromoteToKnight
};

struct Move{
    int startSquare;
    int targetSquare;
    MoveFlag flag = MoveFlag::Quiet;
    Move(int start, int target, MoveFlag flag) : startSquare(start), targetSquare(target), flag(flag) {}
};