/*
 * Brainfuck Interpreter
 * Author: Pedro De Oliveira Haro
 * Date: 28 Dec 2023
 * Description: This program interprets Brainfuck programs, made on my free time.
 *
 * OBJECTIVES --> Create a simple Brainfuck interpreter;
 * BRAINFUCK commands:
 * > : increment (access next cell);
 * < : decrement (access previous cell);
 * + : adds one to the selected cell;
 * - : subtracts one from the selected cell;
 * . : print value to selected cell;
 * , : scans and saves value in the selected cell;
 * [ : starts loop, which repeats commands until the selected cell is zero;
 * ] : ends loop structure;
 * source of the commands --> https://en.wikipedia.org/wiki/Brainfuck
 */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

//maximum amount for Cells in this version is 30000, which is probably sufficient
#define AMOUNT_OF_CELLS 30000
#define MAX_LOOPS 1000

// Definition of the cell abstraction 
struct Cell {
    unsigned char data;
};

// Definition of a loop
struct Loop {
    long start;
    long end;
};

// Definition of the interpreter state
struct InterpreterState {
    struct Cell *ptrToCell; // Pointer to the current cell being used
    long instructionPointer; // Instruction pointer
    struct Loop loops[MAX_LOOPS]; // Stack for loop start and end positions
    int loopCount; // Counter for nested loops
};

// Enumeration for Brainfuck commands, makes the program look really good
enum BrainfuckCommand {
    INC_PTR = '>',
    DEC_PTR = '<',
    INC_VAL = '+',
    DEC_VAL = '-',
    OUT_VAL = '.',
    IN_VAL = ',',
    LOOP_START = '[',
    LOOP_END = ']',
};

// Function prototypes
void incrementPointer(struct Cell **ptrToCell);
void decrementPointer(struct Cell **ptrToCell);
void incrementValue(struct Cell *ptrToCell);
void decrementValue(struct Cell *ptrToCell);
void printValue(struct Cell *ptrToCell);
void handleInput(struct Cell *ptrToCell);
void executeProgram(FILE *file, struct Cell arrOfCells[AMOUNT_OF_CELLS], struct InterpreterState *state);
void startLoop(FILE *file, struct Cell arrOfCells[AMOUNT_OF_CELLS], struct InterpreterState *state);
void endLoop(FILE *file, struct InterpreterState *state);

// Main function
// argc : number of arguments
// argv : array of Strings, that represents the arguments
int main(int argc, char **argv) {
    // Command-line argument check, cant be less than two
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments: %s \n", argv[0]);
        return 1;
    }
    // Open the program that is being interpreted
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    //creating all the cells
    struct Cell arrOfCells[AMOUNT_OF_CELLS]; 
    memset(arrOfCells, 0, sizeof(arrOfCells));
    //setting the state
    struct InterpreterState state;
    state.ptrToCell = arrOfCells;
    state.instructionPointer = 0;
    state.loopCount = 0;

    executeProgram(file, arrOfCells, &state);

    fclose(file);
    return 0;
}
// handling the cells
void incrementPointer(struct Cell **ptrToCell) { (*ptrToCell)++; }

void decrementPointer(struct Cell **ptrToCell) { (*ptrToCell)--; }

void incrementValue(struct Cell *ptrToCell) { (ptrToCell->data)++; }

void decrementValue(struct Cell *ptrToCell) { (ptrToCell->data)--; }

void printValue(struct Cell *ptrToCell) { putchar(ptrToCell->data); }

void handleInput(struct Cell *ptrToCell) {
    int input = getchar();
    if (input == EOF) {
        ptrToCell->data = 0;
    } else {
        // Saving the input to the current cell
        ptrToCell->data = (unsigned char)input;
    }
}

//handdling the loops
//long int ftell(FILE *stream) : returns the current file position of the given stream
void startLoop(FILE *file, struct Cell arrOfCells[AMOUNT_OF_CELLS], struct InterpreterState *state) {
    // Check if the loop should be skipped
    if (state->loopCount < MAX_LOOPS && state->ptrToCell->data == 0) {
        int nestedLoops = 1; // Initialize the nested loop counter to 1 (current loop)

        // Find the matching end of the loop
        while (nestedLoops > 0) {
            char ch = fgetc(file);
            state->instructionPointer = ftell(file);

            if (ch == LOOP_START) {
                nestedLoops++; // Increase the nested loop counter for each nested loop start
            } else if (ch == LOOP_END) {
                nestedLoops--; // Decrease the nested loop counter for each nested loop end
            }
        }
    } else {
        // Save the start position of the loop
        state->loops[state->loopCount].start = state->instructionPointer;
        state->loopCount++;
    }
}

void endLoop(FILE *file, struct InterpreterState *state) {
    // Check if the loop should be terminated
    if (state->ptrToCell->data == 0) {
        state->loopCount--;
    } else {
        // Jump back to the start of the loop
        fseek(file, state->loops[state->loopCount - 1].start, SEEK_SET);
    }
}

// Main function to execute the Brainfuck program
void executeProgram(FILE *file, struct Cell arrOfCells[AMOUNT_OF_CELLS], struct InterpreterState *state) {
    char ch;
    // Process each character in the Brainfuck program
    while ((ch = fgetc(file)) != EOF) {
        state->instructionPointer = ftell(file);

        // Execute the corresponding Brainfuck command
        switch (ch) {
            case INC_PTR:
                incrementPointer(&(state->ptrToCell));
                break;
            case DEC_PTR:
                decrementPointer(&(state->ptrToCell));
                break;
            case INC_VAL:
                incrementValue(state->ptrToCell);
                break;
            case DEC_VAL:
                decrementValue(state->ptrToCell);
                break;
            case OUT_VAL:
                printValue(state->ptrToCell);
                break;
            case IN_VAL:
                handleInput(state->ptrToCell);
                break;
            case LOOP_START:
                startLoop(file, arrOfCells, state);
                break;
            case LOOP_END:
                endLoop(file, state);
                break;
            default:
                break;
        }
    }
}

