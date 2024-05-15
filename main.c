// TIctactoe using minmax algo 
#include <stdio.h>
#include <stdbool.h>

#define PLAYER 'X'
#define COMPUTER 'O'

// Functions Declarations
void printBoard(char board[3][3]);
void initializeBoard(char board[3][3]);
bool checkFreeSpaces(char board[3][3]);
int checkWinner(char board[3][3]);
void playerMove(char board[3][3]);
void computerMove(char board[3][3]);
int minimax(char board[3][3], bool isMaximizing);
int evaluate(char board[3][3]);

int main() {
    char board[3][3];
    int gameStatus;

    initializeBoard(board);  // Initializes the board with empty spaces

    while (true) {
        printBoard(board);
        playerMove(board);
        gameStatus = checkWinner(board);
        if (gameStatus != 0) break;
        computerMove(board);
        gameStatus = checkWinner(board);
        if (gameStatus != 0) break;
    }

    printBoard(board);
    if (gameStatus == PLAYER) {
        printf("You win!\n");
    } else if (gameStatus == COMPUTER) {
        printf("Computer wins!\n");
    } else {
        printf("It's a draw!\n");
    }

    return 0;
}

// Prints the current state of the board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Initializes the board with empty spaces
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Checks if there are any free spaces left on the board
bool checkFreeSpaces(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

// Evaluates the board to see if there is a winner
int checkWinner(char board[3][3]) {
    int score = evaluate(board);
    if (score == 10) return COMPUTER;
    if (score == -10) return PLAYER;
    if (!checkFreeSpaces(board)) return 'T'; // T for Tie
    return 0;
}

// Player makes a move
void playerMove(char board[3][3]) {
    int x, y, result;
    do {
        printf("Enter row and column numbers (1-3) to make your move: ");
        result = scanf("%d %d", &x, &y);
        while(getchar() != '\n');  // Clear the buffer
        if(result != 2) {
            printf("Invalid input, please enter numbers.\n");
            continue;
        }
        x--; y--;
    } while (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ');
    board[x][y] = PLAYER;
}


// Computer makes a move using the minimax algorithm
void computerMove(char board[3][3]) {
    int bestScore = -1000;
    int move[2];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int score = minimax(board, false);
                board[i][j] = ' ';
                if (score > bestScore) {
                    bestScore = score;
                    move[0] = i;
                    move[1] = j;
                }
            }
        }
    }

    board[move[0]][move[1]] = COMPUTER;
}

// Minimax algorithm to determine the best move
int minimax(char board[3][3], bool isMaximizing) {
    int score = evaluate(board);

    if (score == 10) return score;
    if (score == -10) return score;
    if (!checkFreeSpaces(board)) return 0;

    int bestScore = isMaximizing ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = isMaximizing ? COMPUTER : PLAYER;
                int currentScore = minimax(board, !isMaximizing);
                board[i][j] = ' ';
                if (isMaximizing) {
                    bestScore = currentScore > bestScore ? currentScore : bestScore;
                } else {
                    bestScore = currentScore < bestScore ? currentScore : bestScore;
                }
            }
        }
    }

    return bestScore;
}

// Evaluates the board and returns a score based on the board state
int evaluate(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == COMPUTER) return 10;
            if (board[row][0] == PLAYER) return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == COMPUTER) return 10;
            if (board[0][col] == PLAYER) return -10;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == COMPUTER) return 10;
        if (board[0][0] == PLAYER) return -10;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == COMPUTER) return 10;
        if (board[0][2] == PLAYER) return -10;
    }

    return 0;
}
