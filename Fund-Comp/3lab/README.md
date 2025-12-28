Lab 3 Programs

Overview
- quadratic.c: repeatedly solves quadratic equations until coefficient a is 0; reports zero, one, or two real roots.
- polar.c: converts a Cartesian point to polar form (radius, angle) and quadrant.
- menucalc.c: menu-driven four-function calculator with input validation and divide-by-zero handling.

Build
- gcc quadratic.c -o quadratic -lm
- gcc polar.c -o polar -lm
- gcc menucalc.c -o menucalc -lm

Run
- ./quadratic
- ./polar
- ./menucalc

Usage
- Respond to the prompts; programs loop as documented until the exit condition is met (a==0 for quadratic, menu option 5 for menucalc).
