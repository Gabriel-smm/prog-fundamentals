Lab 6 — Conway's Game of Life

Overview
- playlife.c with lifefunc.c implements Conway's Game of Life on a 40x40 board (see lifefunc.h for symbols and size).
- Supports manual commands or scripted input files (e.g., myscene.txt) containing actions.

Build
- make
  - Builds the playlife executable using the provided Makefile.

Run
- ./playlife               # interactive mode
- ./playlife myscene.txt   # run commands from file, then animate if a p action is present

Controls (interactive)
- a x y: add a live cell at (x,y)
- r x y: remove a cell at (x,y)
- n: advance one generation
- p: continuous play (Ctrl+C to stop if needed)
- q: quit

Notes
- Coordinates are zero-based and must be within the board; invalid positions are rejected.
