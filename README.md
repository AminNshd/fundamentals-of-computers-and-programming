# Tic-Tac-Toe AI Engine

This repository contains a C implementation of an advanced Tic-Tac-Toe game featuring two game modes and a recursive AI opponent designed to be unbeatable. The project was originally developed for a "Fundamentals of Computer Science and Programming" course.

---

## 🎮 Game Features

* **Mode 1: Normal Tic-Tac-Toe** – The classic $3 \times 3$ game where players aim for three in a row.


* **Mode 2: 3x Tic-Tac-Toe** – A modified version with a 6-turn limit as per specific project guidelines.


* **Unbeatable AI** – Utilizes a recursive state-space search to ensure the computer never loses if played optimally.


* **Customizable Start** – Choose whether the computer or the user takes the first turn.



---

## 🛠 Technical Overview

### AI Logic

The AI's decision-making process is handled by the `guessNextMove` function. It prioritizes moves in the following order:

1. **Win:** If a move results in an immediate victory, it is taken.


2. **Block:** If the user is one move away from winning, the AI uses the `preventThree` function to block them.


3. **Predict:** If no immediate win or block is available, the `futureState` function recursively explores all possible permutations of the board to find the path with the highest probability of success.



### Key Functions

* `futureState`: Evaluates possible game outcomes by assigning positive scores for AI wins and negative scores for user wins.


* `result`: Constantly monitors the board for a win, loss, draw, or ongoing status.


* `isItLegal`: Validates user input to ensure moves are only placed in empty cells (`N`).


* `printBoard`: Renders the current $3 \times 3$ grid to the console.



---

## 🚀 How to Play

### 1. Coordinate System

The board is represented as a $3 \times 3$ matrix. To make a move, enter a **two-digit number** where the first digit is the **row** and the second digit is the **column**.

|  | Col 0 | Col 1 | Col 2 |
| --- | --- | --- | --- |
| **Row 0** | 00 | 01 | 02 |
| **Row 1** | 10 | 11 | 12 |
| **Row 2** | 20 | 21 | 22 |

### 2. Compilation and Execution

Compile the program using any standard C compiler (like GCC):

```bash
gcc tictactoe.c -o tictactoe
./tictactoe

```

### 3. Gameplay Steps

1. **Select Mode:** Enter `1` for Normal or `2` for 3x mode.


2. **Set Order:** Enter `1` for Computer first or `2` for User first.


3. **Input Move:** When prompted, enter your coordinates (e.g., `11` for the center).



---

## 🎓 Academic Credits

* **Course:** Fundamentals of Computer Science and Programming 


* **Instructor:** Dr. Rasoul Ramezanian 


* **Developer:** Amirhossein Noshadi 


* **Date:** February 2022 (Bahman 1400)
