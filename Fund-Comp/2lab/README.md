Lab 2 Programs

Overview
- asciigraph.c: prints a table and ASCII plot of y = 2*(sin(x)+1) for x in [0,15].
- mortage.c: amortizes a loan, printing monthly payments until paid off; stops if the payment cannot cover monthly interest.
- table.c: builds a formatted multiplication table for user-specified dimensions.

Build
- gcc asciigraph.c -o asciigraph -lm
- gcc mortage.c -o mortage -lm
- gcc table.c -o table

Run
- ./asciigraph
- ./mortage
- ./table

Usage
- Each program prompts for its inputs (loan details, table dimensions, etc.) and prints results to the terminal.
