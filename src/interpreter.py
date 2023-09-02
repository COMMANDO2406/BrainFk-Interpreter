# get input
program = input()

# Initialize the memory tape with one cell and set the cell index to 0
tape = [0]
cell_index = 0

# Initialize user input, loop table, and loop stack
user_input = []
loop_table = {}
loop_stack = []

# Build the loop_table to map opening '[' and closing ']' brackets
for ip, instruction in enumerate(program):
    if instruction == "[":
        loop_stack.append(ip)
    elif instruction == "]":
        loop_beginning_index = loop_stack.pop()
        loop_table[loop_beginning_index] = ip
        loop_table[ip] = loop_beginning_index

# Initialize the instruction pointer (ip)
ip = 0

# Execute instructions
while ip < len(program):
    instruction = program[ip]

    if instruction == "+":
        # Increment the value at the current memory cell
        tape[cell_index] += 1
        if tape[cell_index] == 256:
            tape[cell_index] = 0

    elif instruction == "-":
        # Decrement the value at the current memory cell
        tape[cell_index] -= 1
        if tape[cell_index] == -1:
            tape[cell_index] = 255

    elif instruction == "<":
        # Move the memory pointer to the left
        cell_index -= 1

    elif instruction == ">":
        # Move the memory pointer to the right
        cell_index += 1
        if cell_index == len(tape):
            tape.append(0)  # Add another cell if we move beyond the end of the tape

    elif instruction == ".":
        # Output the ASCII value of the current cell as a character
        print(chr(tape[cell_index]), end="")

    elif instruction == ",":
        # Input a character and store its ASCII value in the current memory cell
        if user_input == []:
            user_input = list(input() + "\n")
        tape[cell_index] = ord(user_input.pop(0))

    elif instruction == "[":
        if not tape[cell_index]:
            # Jump past the closing ']' if the current memory cell is 0
            ip = loop_table[ip]

    elif instruction == "]":
        if tape[cell_index]:
            # Jump back to the matching opening '[' if the current memory cell is not 0
            ip = loop_table[ip]

    # Move to the next instruction
    ip += 1