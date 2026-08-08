#include <raylib.h>

class Board {
private:
    char grid[3][3];

public:
    Board() {
        reset();
    }

    void reset() {
        for (int a = 0; a < 3; a++) {
            for (int b = 0; b < 3; b++) {
                grid[a][b] = ' '; 
            }
        }
    }

    bool makeMove(int row, int col, char mark) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && grid[row][col] == ' ') {
            grid[row][col] = mark;
            return true;
        }
        return false;
    }

    char getMark(int row, int col) const {
        return grid[row][col];
    }

    char checkWin() const {
        for (int i = 0; i < 3; i++) {
            if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
                return grid[i][0];
            if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
                return grid[0][i];
        }
        if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
            return grid[0][0];
        if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
            return grid[0][2];

        return ' ';
    }

    bool isFull() const {
        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                if (grid[r][c] == ' ')
                    return false;
            }
        }
        return true;
    }
}; // 🛠️ Class closed properly here

int main(void) {
    InitWindow(600, 600, "Tic Tac Toe");
    SetTargetFPS(60);

    Board board;
    char currentTurn = 'X';
    bool gameOver = false;
    char winner = ' ';

    while (!WindowShouldClose()) {
        if (!gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int col = GetMouseX() / 200;
            int row = GetMouseY() / 200;
            if (board.makeMove(row, col, currentTurn)) {
                winner = board.checkWin();
                if (winner != ' ' || board.isFull()) {
                    gameOver = true;
                } else {
                    currentTurn = (currentTurn == 'X') ? 'O' : 'X';
                }
            }
        }

        if (IsKeyPressed(KEY_R)) {
            board.reset();
            currentTurn = 'X';
            gameOver = false;
            winner = ' ';
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 📏 Draw Grid Lines
        DrawLine(200, 0, 200, 600, BLACK);
        DrawLine(400, 0, 400, 600, BLACK);
        DrawLine(0, 200, 600, 200, BLACK); // 🛠️ Fixed line length
        DrawLine(0, 400, 600, 400, BLACK);

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {
                char mark = board.getMark(r, c);
                int centerX = c * 200 + 75;
                int centerY = r * 200 + 50;
                if (mark == 'X') {
                    DrawText("X", centerX, centerY, 100, RED);
                } else if (mark == 'O') {
                    DrawText("O", centerX, centerY, 100, BLUE);
                }
            }
        }

        if (gameOver) {
            DrawRectangle(50, 220, 500, 160, Fade(DARKGRAY, 0.9f));
            if (winner != ' ') {
                DrawText(TextFormat("Player %c Wins!", winner), 140, 250, 40, GOLD);
            } else {
                DrawText("It's a Draw!", 180, 250, 40, LIGHTGRAY);
            }
            DrawText("Press 'R' to Restart", 170, 310, 24, RAYWHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}