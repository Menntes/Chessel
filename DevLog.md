# Chessel ♟️

### Day 1: Project Setup & Sliding Moves

I asked Gemini to make something for me, which had a good UI in javascript but it didn't work with stockfish.  I decided to see if I could make it myself in C++. I watched some videos on programming chess engines, learned about FEN poistions and used those to pre-calculate the distance to edges. That gave me a lookup table so the engine knows where the board ends before it even starts looking for moves. By the end of the day, I got the sliding logic working for Rooks, Bishops, and Queens, tested it with a Queen on d4 and it correctly found all 27 moves.

### Day 2:Suedo-Legal
Finished the suedo-legal moves for all the rest of the pieces. Did some thinking on how I want to present the finished product and did some googling. Decided that at the end of this il have it on a website using web assembly. That's honestly gonna be hard for me cause I don't know much about it... yet. But that for a far future thing, next step is gonna be making it you can only make legal moves, like checks. 

### Day 3: Coming Back & Cleaning Up
Hadn't touched this in a while, so before adding anything new I came back and cleaned up stuff that was quietly broken.I had claude look over to find any issues and it caught that  board.h and board.cpp were named differently than what the rest of the project expected (board.h vs Board.h), which only worked cause Windows doesn't care about filename casing, which would've broken on Linux/Mac. Also had a leftover functions.h/functions.cpp that were basically empty and wired up wrong, an off-by-one in the king moves, and turns out I'd been committing the whole build folder to git this entire time lol. Fixed all that now.

While it was searching, another bug from Day 1 came up: my East and West edge-distance numbers were swapped, so sliding pieces going east were missing a square and pieces going west could wrap right off the edge of the board. Kinda funny that my "27 moves" test from Day 1 still passed even with this bug in it, cause the east and west mistakes cancelled out in the total count, so I never caught it. Cleaned up how piece color/type get read too, and made the board actually print letters now instead of a wall of numbers, way easier to look at. Also spent way too long fighting VS Code cause reconfiguring the build broke my IntelliSense for a bit, but got it sorted. Next step is still legal moves (checks and stuff) instead of just pseudo-legal.

### Day 4: Move Flags & a Crash

My test FEN in main.cpp only had the piece layout, none of the side-to-move / castling / en-passant / move-counter fields the parser wants now. So loadFromFen choked halfway through, left the en-passant field empty, printed a warning and then just kept going instead of stopping, so it tried to read character [1] of an empty string and crashed with an assertion fail. Fixed it so loadFromFen actually bails when the FEN is incomplete, and gave the test FEN all six fields like it should've had.

After that I started setting up for legal move filtering, which meant Move had to carry more than just a start and target square. Added a MoveFlag enum (Quiet, DoublePawnPush, Capture for now, plus stubs for castling / en-passant / promotion i'm not generating yet) and went through every generator tagging each move. Doing that turned up a real bug: the knight and king generators only ever added a move when there was an enemy piece on the target, so they could capture but couldn't move to an empty square. Fixed both to add the move on empty-or-enemy like the sliding pieces already did. Also had claude line up all my commit messages with the days.

### Day 5: Make / Unmake

Also dropping the daily commit thing, just gonna commit per feature now.

Started on makeMove / unmakeMove so the engine can play a move and take it back, need it for legal moves later. Annoying part was working out what you have to save to undo a move, cause makeMove overwrites stuff thats then just gone (captured piece, en passant square, move clocks). Made an Undo struct that saves it first and a history vector to hold em, unmakeMove pops the last one and puts everything back. Had a dumb bug too, typed == instead of = for switching turns so it never actually switched lol, compiler caught it once i built with -Wall. En passant still half broken, gonna come back to it. Wrote a quick test that makes then unmakes every move and checks the board matches, works 3 deep so the core's fine. Next is legal moves and a perft test.

