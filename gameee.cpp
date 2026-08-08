#include <raylib.h>

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
            };

class Board    {
  private:char grid[3][3];

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
    };

int main(void) {
InitWindow(600, 600, "Tic Tac Toe");
    SetTargetFPS(60);

    Board board;
    char currentTurn = 'X';
    char winner = ' ';
    GameState currentState = GameState::MENU;

    while (!WindowShouldClose()) {
        switch (currentState) {
    case GameState::MENU:
if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                     board.reset();
                currentTurn = 'X';
                     winner = ' ';
            currentState = GameState::PLAYING;
                }
                break;

            case GameState::PLAYING:
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    int col = GetMouseX() / 200;
                    int row = GetMouseY() / 200;

                    if (board.makeMove(row, col, currentTurn)) {
                        winner = board.checkWin();
                        if (winner != ' ' || board.isFull()) {
                            currentState = GameState::GAME_OVER;
                        } else {
                            currentTurn = (currentTurn == 'X') ? 'O' : 'X';
                        }
                    }
                }
                break;

            case GameState::GAME_OVER:
                if (IsKeyPressed(KEY_R)) {
                    board.reset();
                    currentTurn = 'X';
                    winner = ' ';
                    currentState = GameState::PLAYING;
                } else if (IsKeyPressed(KEY_M)) {
                    currentState = GameState::MENU;
                }
                break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
            case GameState::MENU:
                DrawText("TIC TAC TOE", 130, 200, 50, DARKBLUE);
                DrawText("Press ENTER or Click to Play", 120, 320, 24, DARKGRAY);
                break;

            case GameState::PLAYING:
                DrawLine(200, 0, 200, 600, BLACK);
                DrawLine(400, 0, 400, 600, BLACK);
                DrawLine(0, 200, 600, 200, BLACK);
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
                break;

            case GameState::GAME_OVER:
                DrawRectangle(50, 180, 500, 240, Fade(DARKGRAY, 0.95f));
                
                if (winner != ' ') {
                    DrawText(TextFormat("Player %c Wins!", winner), 140, 220, 40, GOLD);
                } else {
                    DrawText("It's a Draw!", 180, 220, 40, LIGHTGRAY);
                }

                DrawText("Press 'R' to Restart", 170, 300, 24, RAYWHITE);
                DrawText("Press 'M' for Main Menu", 160, 340, 24, LIGHTGRAY);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
