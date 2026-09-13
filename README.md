# Tic Tac Toe — Minimax AI

A Tic Tac Toe project built to demonstrate the **Minimax algorithm** — a classic DSA technique for adversarial game search using recursion and backtracking. Comes in two versions: a C++ console app and a browser-based web UI.


## Features

- Unbeatable AI opponent powered by Minimax (best case for a human is a draw)
- Two-player mode (share the same screen, no AI involved)
- Live algorithm stats panel — shows nodes evaluated, max search depth, and move time for every AI move
- Scoreboard tracking wins/draws across games

## DSA Concepts Demonstrated

| Concept | Where it shows up |
|---|---|
| Recursion | `minimax()` calls itself for every possible future move |
| Backtracking | Each recursive call places a move, explores it, then undoes it before trying the next |
| Game tree search | Every board state is a node; leaves are scored based on win/loss/draw |
| Time complexity | Worst case `O(b^d)` — branching factor up to 9, depth up to 9 |

The AI always wins ties by preferring the **fastest win** and the **slowest loss**, achieved by adjusting the score with search depth (`10 - depth` for an AI win, `depth - 10` for a human win).

## Project Structure

```
.
├── index.html       # Web version — click-to-play UI with live algorithm stats
├── tictactoe.cpp     # C++ console version
└── README.md
```

## Running the Web Version

No build step or server required — it's a single self-contained HTML file.

```bash
open index.html
```

Or just double-click `index.html` in Finder/Explorer, or open it from GitHub Pages: https://pranjalll1.github.io/TicTacToe-MinimaxAI/

## Running the C++ Console Version

Requires a C++17-compatible compiler (g++ or clang++).

```bash
g++ -std=c++17 -O2 -o tictactoe tictactoe.cpp
./tictactoe
```

## Tech Stack

- **Console version:** C++17
- **Web version:** HTML, CSS, vanilla JavaScript (no frameworks or dependencies)

## Author

Deepak  — B.Tech CSE, Lovely Professional University
