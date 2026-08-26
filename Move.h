#pragma once

struct Move{
    int startSquare;
    int targetSquare;

    Move(int start, int target) : startSquare(start), targetSquare(target) {}
};