Lab 8 — Crossword Generator

Overview
- crossword.c with crossfunc.c builds a crossword-style puzzle: places words on a 15x15 board, prints a blank puzzle, solution, and anagram clues.
- Words are validated (letters only, length limits) and sorted by length before placement; oversize lists are truncated.

Build
- make
  - Or: gcc crossword.c crossfunc.c -o crossword

Run
- ./crossword                 # choose manual entry or file input when prompted
- ./crossword ndwords.txt     # read words from file
- ./crossword ndwords.txt out.txt  # read from file and write boards/clues to out.txt

Notes
- Enter "." on its own line to end manual entry; at least two valid words are required.
