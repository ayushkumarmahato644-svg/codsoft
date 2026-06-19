#include <bits/stdc++.h>
using namespace std;

vector<char> board(9, ' ');

void printBoard() {
    cout << "\n " << board[0] << " | " << board[1] << " | " << board[2] << " \n";
    cout << "-----------\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " \n";
    cout << "-----------\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " \n\n";
}

bool isWinner(const vector<char>& b, char player) {
    int winStates[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
        {0, 4, 8}, {2, 4, 6}             
    };
    for(int i = 0; i < 8; ++i) {
        if(b[winStates[i][0]] == player && b[winStates[i][1]] == player && b[winStates[i][2]] == player)
            return true;
    }
    return false;
}

bool isBoardFull(const vector<char>& b) {
    for(char cell : b) {
        if(cell == ' ') return false;
    }
    return true;
}

int minimax(vector<char>& currentBoard, int depth, bool isMaximizing) {
    if (isWinner(currentBoard, 'O')) return 10 - depth;
    if (isWinner(currentBoard, 'X')) return depth - 10;
    if (isBoardFull(currentBoard)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; ++i) {
            if (currentBoard[i] == ' ') {
                currentBoard[i] = 'O';
                int score = minimax(currentBoard, depth + 1, false);
                currentBoard[i] = ' '; 
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; ++i) {
            if (currentBoard[i] == ' ') {
                currentBoard[i] = 'X';
                int score = minimax(currentBoard, depth + 1, true);
                currentBoard[i] = ' '; 
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

int getBestMove() {
    int bestScore = -1000;
    int move = -1;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(board, 0, false);
            board[i] = ' ';
            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int main() {
    cout << "Welcome to Tic-Tac-Toe AI (C++)!\n";
    cout << "Positions are mapped 1-9 from top-left to bottom-right.\n";
    printBoard();

    while (true) {
    
        int move;
        while (true) {
            cout << "Your move (1-9): ";
            if (cin >> move) {
                move -= 1; 
                if (move >= 0 && move <= 8 && board[move] == ' ') {
                    board[move] = 'X';
                    break;
                }
            } else {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cout << "Invalid move. Try again.\n";
        }

        printBoard();
        if (isWinner(board, 'X')) { cout << "You won!\n"; break; }
        if (isBoardFull(board)) { cout << "It's a draw!\n"; break; }

     
        cout << "AI is thinking...\n";
        int aiMove = getBestMove();
        board[aiMove] = 'O';
        printBoard();

        if (isWinner(board, 'O')) { cout << "AI Wins!\n"; break; }
        if (isBoardFull(board)) { cout << "It's a draw!\n"; break; }
    }
    return 0;
}