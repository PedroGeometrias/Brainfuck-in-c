# Brainfuck Interpreter

Author: Pedro De Oliveira Haro
Date: 28 Dec 2023

## Description

This is a simple Brainfuck interpreter created during my free time. The Brainfuck interpreter is a program that can execute Brainfuck programs, a minimalist programming language.

### Brainfuck Commands

- `>`: Increment (move to the next cell)
- `<`: Decrement (move to the previous cell)
- `+`: Adds one to the selected cell
- `-`: Subtracts one from the selected cell
- `.`: Print the value of the selected cell
- `,`: Scan and save value in the selected cell
- `[`: Start loop (repeats commands until the selected cell is zero)
- `]`: End loop structure

For more details on Brainfuck commands, refer to [Brainfuck - Wikipedia](https://en.wikipedia.org/wiki/Brainfuck).

## Usage

To use the this interpreter, compile the source code and provide the Brainfuck program file as a command-line argument:

