/*
    TIC TAC TOE - DSA Course Project
    Language: C++

    DSA concepts demonstrated:
    - 2D array as game board (matrix representation)
    - Recursion (Minimax algorithm)
    - Backtracking (trying a move, undoing it)
    - Game tree search / decision making
    - Modular functions, enums, basic OOP (struct/class usage)

    Modes:
    1. Player vs Player
    2. Player vs Computer (unbeatable AI using Minimax)
*/

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const char EMPTY = ' ';
const char PLAYER_X = 'X';   // Human (or Player 1)
const char PLAYER_O = 'O';   // Computer (or Player 2)

class TicTacToe {
private:
    vector<vector<char>> board;

public:
    TicTacToe() {
        board = vector<vector<char>>(3, vector<char>(3, EMPTY));
    }

    void printBoard() {
        cout << "\n";
        for (int i = 0; i < 3; i++) {
            cout << " ";
            for (int j = 0; j < 3; j++) {
                cout << board[i][j];
                if (j < 2) cout << " | ";
            }
            cout << "\n";
            if (i < 2) cout << "-----------\n";
        }
        cout << "\n";
    }

    bool isMovesLeft() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == EMPTY)
                    return true;
        return false;
    }

    // Returns +10 if 'O' (computer) wins, -10 if 'X' wins, 0 otherwise
    int evaluate() {
        // Check rows
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
                if (board[row][0] == PLAYER_O) return +10;
                else if (board[row][0] == PLAYER_X) return -10;
            }
        }
        // Check columns
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
                if (board[0][col] == PLAYER_O) return +10;
                else if (board[0][col] == PLAYER_X) return -10;
            }
        }
        // Check diagonals
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            if (board[0][0] == PLAYER_O) return +10;
            else if (board[0][0] == PLAYER_X) return -10;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            if (board[0][2] == PLAYER_O) return +10;
            else if (board[0][2] == PLAYER_X) return -10;
        }
        return 0;
    }

    // Minimax recursive algorithm
    int minimax(int depth, bool isMax) {
        int score = evaluate();

        if (score == 10) return score - depth;   // Prefer faster wins
        if (score == -10) return score + depth;  // Prefer slower losses
        if (!isMovesLeft()) return 0;             // Draw

        if (isMax) {
            int best = numeric_limits<int>::min();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = PLAYER_O;
                        best = max(best, minimax(depth + 1, false));
                        board[i][j] = EMPTY; // backtrack
                    }
                }
            }
            return best;
        } else {
            int best = numeric_limits<int>::max();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == EMPTY) {
                        board[i][j] = PLAYER_X;
                        best = min(best, minimax(depth + 1, true));
                        board[i][j] = EMPTY; // backtrack
                    }
                }
            }
            return best;
        }
    }

    // Finds the best move for the computer (PLAYER_O)
    pair<int, int> findBestMove() {
        int bestVal = numeric_limits<int>::min();
        pair<int, int> bestMove = {-1, -1};

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    int moveVal = minimax(0, false);
                    board[i][j] = EMPTY; // backtrack

                    if (moveVal > bestVal) {
                        bestMove = {i, j};
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    bool isCellEmpty(int row, int col) {
        return board[row][col] == EMPTY;
    }

    void makeMove(int row, int col, char player) {
        board[row][col] = player;
    }

    bool isGameOver() {
        return evaluate() != 0 || !isMovesLeft();
    }

    int getWinner() {
        return evaluate(); // +10 -> O wins, -10 -> X wins, 0 -> draw/ongoing
    }
};

void playPlayerVsPlayer() {
    TicTacToe game;
    char currentPlayer = PLAYER_X;
    int row, col;

    game.printBoard();

    while (!game.isGameOver()) {
        cout << "Player " << currentPlayer << ", enter row and column (0-2 0-2): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || !game.isCellEmpty(row, col)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        game.makeMove(row, col, currentPlayer);
        game.printBoard();

        if (game.isGameOver()) break;

        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
    }

    int result = game.getWinner();
    if (result == 10) cout << "Player O wins!\n";
    else if (result == -10) cout << "Player X wins!\n";
    else cout << "It's a draw!\n";
}

void playPlayerVsComputer() {
    TicTacToe game;
    int row, col;

    cout << "You are 'X'. Computer is 'O'.\n";
    game.printBoard();

    while (!game.isGameOver()) {
        // Human move
        cout << "Enter row and column (0-2 0-2): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2 || !game.isCellEmpty(row, col)) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        game.makeMove(row, col, PLAYER_X);
        game.printBoard();

        if (game.isGameOver()) break;

        // Computer move
        cout << "Computer is thinking...\n";
        pair<int, int> bestMove = game.findBestMove();
        game.makeMove(bestMove.first, bestMove.second, PLAYER_O);
        cout << "Computer played (" << bestMove.first << ", " << bestMove.second << ")\n";
        game.printBoard();
    }

    int result = game.getWinner();
    if (result == 10) cout << "Computer wins!\n";
    else if (result == -10) cout << "You win!\n";
    else cout << "It's a draw!\n";
}

int main() {
    cout << "===== TIC TAC TOE (DSA Project) =====\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Computer (Minimax AI)\n";
    cout << "Choose mode: ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        playPlayerVsPlayer();
    } else if (choice == 2) {
        playPlayerVsComputer();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
