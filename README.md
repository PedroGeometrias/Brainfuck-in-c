# Brainfuck Interpreter

Author: Pedro De Oliveira Haro
Date: 28 Dec 2023

## Description

This is a simple Brainfuck interpreter created during my free time.

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

To use the Brainfuck Interpreter, follow these steps:

1. Compile the source code using a C compiler (e.g., GCC):

    ```bash
    gcc -o brainfuck_interpreter brainfuck_interpreter.c
    ```

2. Run the executable with the path to the Brainfuck program as an argument:

    ```bash
    ./brainfuck_interpreter my_program.bf
    ```

## Implementation Details

- Maximum amount of cells in this version is set to 30000, which is likely sufficient for most programs.
- The interpreter utilizes a stack for loop start and end positions, with a maximum nested loop count of 1000.
- Each command is executed based on the Brainfuck specification.
- Input and output are handled through standard input and output streams.

## File Structure

- `brainfuck_interpreter.c`: Main source code file containing the Brainfuck interpreter implementation.
- `my_program.bf`: Example Brainfuck program for testing.

## Dependencies

- C Standard Library

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

## Usage

To use the this interpreter, compile the source code and provide the Brainfuck program file as a command-line argument:

