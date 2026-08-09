# 🧮 Math Game

A console-based Math Game implemented in C++.

## Overview

Math Game generates random arithmetic questions based on the selected difficulty level and operation type. The player answers each question, receives immediate feedback, and gets a final result summary at the end of the round.

## Features

- Multiple questions in one round
- Random question generation
- Easy, Medium, Hard, and Mixed difficulty levels
- Addition, Subtraction, Multiplication, Division, and Mixed operations
- Exact integer division questions
- Colored console feedback for correct and wrong answers
- Final game statistics
- Play again option
- Organized code using `struct`, `enum`, arrays, loops, and functions

## Concepts Used

- Functions
- Structs
- Enums
- Arrays
- Loops
- Random Number Generation
- Switch Statements
- Pass by Reference
- Conditional Operator
- Console Programming
- Basic Problem Solving

## Project Structure

```text
Math-Game
│
├── Math-Game.cpp
├── README.md
├── LICENSE
├── .gitignore
└── Screenshots
    ├── Game Start.png
    ├── Correct Answer.png
    ├── Wrong Answer.png
    ├── Final Result - Pass.png
    └── Final Result - Fail.png
```

## How to Run

### Using a C++ Compiler

Compile the source file with a C++ compiler such as GCC/MinGW:

```bash
g++ Math-Game.cpp -o Math-Game
```

Then run:

```bash
./Math-Game
```

### Windows

If you are using Windows with MinGW, the generated executable can be started with:

```bash
Math-Game.exe
```

> The colored console output uses Windows `color` and `cls` commands, so the visual experience is designed primarily for Windows terminals.

## Screenshots

### Game Start

![Game Start](Screenshots/Game%20Start.png)

### Correct Answer

![Correct Answer](Screenshots/Correct%20Answer.png)

### Wrong Answer

![Wrong Answer](Screenshots/Wrong%20Answer.png)

### Final Result - Pass

![Final Result Pass](Screenshots/Final%20Result%20-%20Pass.png)

### Final Result - Fail

![Final Result Fail](Screenshots/Final%20Result%20-%20Fail.png)

## Language

**C++**

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Author

**Ahmed Hamdy**