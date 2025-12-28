Lab 7 Part 1 — Polygon Perimeter/Area

Overview
- polygon.c read up to 30 (x,y) vertices from a file and compute perimeter and area (shoelace formula), echoing the points.

Build
- make
  - Or: gcc polygon.c polyfunc.c -o polygon -lm

Run
- ./polygon points.txt
- ./polygon points2.txt

Notes
- Input files list integer coordinates, one point per line; the program wraps the last point to the first when computing metrics.
