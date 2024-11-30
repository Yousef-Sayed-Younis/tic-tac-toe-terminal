#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

char PLAYER, COMPUTER;
vector<char> MATRIX(10);

const vector<vector<int>> WIN_PATTERNS = {
    {1, 5, 9}, {3, 5, 7}, // Diagonals
    {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, // Rows
    {1, 4, 7}, {2, 5, 8}, {3, 6, 9}  // Columns
};

const vector<vector<int>> WIN_CONDITIONS = {
    {2, 4, 1}, {2, 7, 1}, {8, 4, 7},
    {8, 1, 7}, {2, 6, 3}, {2, 9, 3},
    {8, 6, 9}, {8, 3, 9}, {3, 7, 8}, {6, 7, 9}
};

bool canChoose(char pos) { return (pos != 'X' && pos != 'O'); }

void startMatrix() { for (char i = 1; i <= 9; i++) MATRIX[i] = '0' + i; }

void displayBoard() {
    cout << "\n";
    for (int i = 1; i <= 7; i += 3)
        cout << "| " << MATRIX[i] << " | " << MATRIX[i + 1] << " | " << MATRIX[i + 2] << " |\n";
}

char checkWinner() {
    for (const auto &pattern : WIN_PATTERNS)
        if (MATRIX[pattern[0]] == MATRIX[pattern[1]] && MATRIX[pattern[1]] == MATRIX[pattern[2]]) return MATRIX[pattern[1]];

    return any_of(MATRIX.begin() + 1, MATRIX.begin() + 10, canChoose) ? '*' : '='; // No winner yet, or draw
}

int findWinningMove() {
    for (const auto &pattern : WIN_PATTERNS) {
        int x = pattern[0], y = pattern[1], z = pattern[2];
        if (MATRIX[x] == MATRIX[y] && canChoose(MATRIX[z])) return z;
        if (MATRIX[x] == MATRIX[z] && canChoose(MATRIX[y])) return y;
        if (MATRIX[y] == MATRIX[z] && canChoose(MATRIX[x])) return x;
    }

    for (const auto &condition : WIN_CONDITIONS)
        if (MATRIX[condition[0]] == MATRIX[condition[1]] && canChoose(condition[2])) return condition[2];

    return -1; // No winning move found
}

void playComputer() {
    int move = findWinningMove();
    if (canChoose(MATRIX[5])) move = 5;
    else if (move == -1) for (int i = 1; i <= 9; i++) if (canChoose(MATRIX[i])) { move = i; break; }

    MATRIX[move] = COMPUTER;
}

void playGame(bool againstComputer) {
    while (checkWinner() == '*') {
        displayBoard();

        char pos;
        if (!againstComputer || PLAYER == 'X') {
            cout << "\nEnter Your Move (" << PLAYER << "): ";
            cin >> pos;

            while (pos < '1' || pos > '9' || MATRIX[pos - '0'] == 'X' || MATRIX[pos - '0'] == 'O') {
                cout << "Invalid move, Try again: ";
                cin >> pos;
            }

            MATRIX[pos - '0'] = PLAYER;
            if (!againstComputer) PLAYER = (PLAYER == 'X') ? 'O' : 'X';
        }

        if (againstComputer && checkWinner() == '*') playComputer();
    }

    displayBoard();
    char winner = checkWinner();
    if (winner == '=') cout << "\nIt's a Draw!\n";
    else cout << "\nThe Winner is " << winner << "!\n";
}

int main() {
    cout << "Welcome to Tic Tac Toe!\n";
    char playAgain = 'y';

    while (tolower(playAgain) == 'y') {
        startMatrix();

        cout << "Play against Computer? (y/n): ";
        char choice;
        cin >> choice;

        bool againstComputer = tolower(choice) == 'y';
        if (againstComputer) {
            cout << "Choose X or O: ";
            cin >> PLAYER;

            PLAYER = toupper(PLAYER);
            COMPUTER = (PLAYER == 'X') ? 'O' : 'X';
        } else {
            cout << "Which Player Starts? (X/O): ";
            cin >> PLAYER;

            PLAYER = toupper(PLAYER);
        }

        playGame(againstComputer);

        cout << "\nPlay Again? (y/n): ";
        cin >> playAgain;
    }

    return 0;
}