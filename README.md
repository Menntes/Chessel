# Chessel ♟️

### Day 1: Project Setup & Sliding Moves

I asked Gemini to make something for me, which had a good UI in javascript but it didn't work with stockfish.  I decided to see if I could make it myself in C++. I started by moving everything into a modular setup with a `Board` class and a `MoveGenerator`. I watched some videos on programming chess engines, learned about FEN poistions and used those to pre-calculate the distance to edges. That gave me a lookup table so the engine knows where the board ends before it even starts looking for moves. By the end of the day, I got the **sliding logic** working for Rooks, Bishops, and Queens, tested it with a Queen on d4 and it correctly found all 27 moves.
