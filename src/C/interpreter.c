#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000
// this follows the more traditional tape rather than the python interpreter

void execute_brainfuck_program(const char* program) {
    unsigned char tape[TAPE_SIZE] = {0};
    size_t cell_index = 0;
    size_t ip = 0;

    // Build the loop_table to map opening '[' and closing ']' brackets
    size_t loop_table[TAPE_SIZE] = {0};
    size_t loop_stack[TAPE_SIZE] = {0};
    size_t loop_stack_index = 0;

    for (size_t i = 0; i < strlen(program); i++) {
        char instruction = program[i];
        if (instruction == '[') {
            loop_stack[loop_stack_index++] = i;
        } else if (instruction == ']') {
            if (loop_stack_index > 0) {
                size_t open_bracket_index = loop_stack[--loop_stack_index];
                loop_table[i] = open_bracket_index;
                loop_table[open_bracket_index] = i;
            }
        }
    }

    while (ip < strlen(program)) {
        char instruction = program[ip];

        switch (instruction) {
            case '+':
                // Increment the value at the current memory cell
                tape[cell_index]++;
                break;
            case '-':
                // Decrement the value at the current memory cell
                tape[cell_index]--;
                break;
            case '<':
                // Move the memory pointer to the left
                if (cell_index > 0) {
                    cell_index--;
                }
                break;
            case '>':
                // Move the memory pointer to the right
                cell_index++;
                if (cell_index >= TAPE_SIZE) {
                    printf("Tape overflow!\n");
                    exit(1);
                }
                break;
            case '.':
                // Output the ASCII value of the current cell as a character
                putchar(tape[cell_index]);
                break;
            case ',':
                // Input a character and store its ASCII value in the current memory cell
                tape[cell_index] = getchar();
                break;
            case '[':
                // Jump past the closing ']' if the current memory cell is 0
                if (tape[cell_index] == 0) {
                    ip = loop_table[ip];
                }
                break;
            case ']':
                // Jump back to the matching opening '[' if the current memory cell is not 0
                if (tape[cell_index] != 0) {
                    ip = loop_table[ip];
                }
                break;
            default:
                // Ignore other characters
                // Good enough for now but will need to add either comments or errors
                break;
        }

        ip++;
    }
}

int main() {
    char program[10000]; // Adjust the size as needed
    printf("Enter Brainfuck code: ");
    fgets(program, sizeof(program), stdin);

    execute_brainfuck_program(program);

    return 0;
}