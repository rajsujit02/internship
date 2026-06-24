#include <iostream>

using namespace std;

// Function prototypes
void displayBoard(const char board[3][3]);
bool makeMove(char board[3][3], int slot, char player);
bool checkWin(const char board[3][3], char player);
bool checkDraw(const char board[3][3]);
void resetBoard(char board[3][3]);

int main() {
    char board[3][3];
    char currentPlayer;
    bool gameRunning = true;

    cout << "=================================\n";
    cout << "   Welcome to C++ Tic-Tac-Toe!   \n";
    cout << "=================================\n";

    while (gameRunning) {
        resetBoard(board);
        currentPlayer = 'X';
        bool roundRunning = true;

        while (roundRunning) {
            displayBoard(board);
            int choice;
            cout << "Player " << currentPlayer << ", enter a slot (1-9): ";
            
            // Input validation for integers
            if (!(cin >> choice) || choice < 1 || choice > 9) {
                cout << "Invalid input! Please enter a number between 1 and 9.\n";
                cin.clear(); // clear error flag
                cin.ignore(10000, '\n'); // discard invalid input
                continue;
            }

            // Try to place the marker
            if (!makeMove(board, choice, currentPlayer)) {
                cout << "That slot is already taken! Try again.\n";
                continue;
            }

            // Check if current player won
            if (checkWin(board, currentPlayer)) {
                displayBoard(board);
                cout << "Congratulations! Player " << currentPlayer << " wins!\n";
                roundRunning = false;
            } 
            // Check for a draw
            else if (checkDraw(board)) {
                displayBoard(board);
                cout << "It's a draw!\n";
                roundRunning = false;
            } 
            // Switch players
            else {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        // Replay Functionality
        char replay;
        cout << "\nDo you want to play again? (y/n): ";
        cin >> replay;
        if (replay != 'y' && replay != 'Y') {
            gameRunning = false;
        }
    }

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}

// Resets the board to digits 1-9
void resetBoard(char board[3][3]) {
    char initial = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = initial++;
        }
    }
}

// Renders the board dynamically in the console
void displayBoard(const char board[3][3]) {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
    cout << "\n";
}

// Maps 1-9 input to 2D array grid coordinates and updates it
bool makeMove(char board[3][3], int slot, char player) {
    // Convert 1-9 into row and column
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    // Check if slot is already occupied by 'X' or 'O'
    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return false; 
    }

    board[row][col] = player;
    return true;
}

// Evaluates rows, columns, and diagonals for a win state
bool checkWin(const char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Checks if the board is completely full without a winner
bool checkDraw(const char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return false; // Found an open slot, not a draw
            }
        }
    }
    return true;
}