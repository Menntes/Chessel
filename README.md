# Chessel ♟️

### Day 1: Project Setup & Sliding Moves
Today I got started in **C++**. I moved everything into a modular setup with a `Board` class and a `MoveGenerator`, which was way better than having one giant file. I set up **CMake** to handle the building so I don't have to mess with the terminal as much. The coolest part was implementing the **FEN loader** to set up positions and pre-calculating the **"Distance to Edge"** math. It basically creates a lookup table so the engine knows where the board ends before it even starts looking for moves. By the end of the day, I got the **sliding logic** working for Rooks, Bishops, and Queens—tested it with a Queen on d4 and it correctly found all 27 moves.
