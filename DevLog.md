# Chessel ♟️

### Day 1: Project Setup & Sliding Moves

I asked Gemini to make something for me, which had a good UI in javascript but it didn't work with stockfish.  I decided to see if I could make it myself in C++. I watched some videos on programming chess engines, learned about FEN poistions and used those to pre-calculate the distance to edges. That gave me a lookup table so the engine knows where the board ends before it even starts looking for moves. By the end of the day, I got the sliding logic working for Rooks, Bishops, and Queens, tested it with a Queen on d4 and it correctly found all 27 moves.

### Day 2:Suedo-Legal
Finished the suedo-legal moves for all the rest of the pieces. Did some thinking on how I want to present the finished product and did some googling. Decided that at the end of this il have it on a website using web assembly. That's honestly gonna be hard for me cause I don't know much about it... yet. But that for a far future thing, next step is gonna be making it you can only make legal moves, like checks. 

### Day 3: Coming Back & Cleaning Up
Hadn't touched this in a while, so before adding anything new I came back and cleaned up stuff that was quietly broken. board.h and board.cpp were named differently than what the rest of the project expected (board.h vs Board.h), which only worked cause Windows doesn't care about filename casing — would've broken on Linux/Mac. Also had a leftover functions.h/functions.cpp that were basically empty and wired up wrong, an off-by-one in the king moves, and turns out I'd been committing the whole build folder to git this entire time lol. Fixed all that and added a proper .gitignore.

While I was in there I found an actual bug from Day 1: my East and West edge-distance numbers were swapped, so sliding pieces going east were missing a square and pieces going west could wrap right off the edge of the board. Kinda funny that my "27 moves" test from Day 1 still passed even with this bug in it, cause the east and west mistakes cancelled out in the total count, so I never caught it. Cleaned up how piece color/type get read too, and made the board actually print letters now instead of a wall of numbers, way easier to look at. Also spent way too long fighting VS Code cause reconfiguring the build broke my IntelliSense for a bit, but got it sorted. Next step is still legal moves (checks and stuff) instead of just pseudo-legal.
