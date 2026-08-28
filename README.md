# Chessel ♟️

A C++ tool to be able to either enter a chess game or play a game where, by using Stockfish, have each move rated by the engine and output an evaluation bar showing the current advantage. 

Read my [DevLog](DevLog.md) to see my current progress. I try to update it each day I work on the project!

## Project layout

```
include/    public headers (Board.h, Move.h, MoveGenerator.h)
src/        implementation + entry point (main.cpp)
build/      CMake output — generated, not committed
```

## Build & run

```
cmake -B build
cmake --build build
./build/Chessel        # ./build/Chessel.exe on Windows
```
