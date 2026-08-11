#include <raylib.h>
#include <raymath.h>

const Color A = { 20, 24, 33, 255 };
const Color B = { 28, 34, 46, 255 };
const Color C = { 36, 44, 60, 255 };
const Color D = { 50, 62, 84, 255 };
const Color E = { 255, 85, 115, 255 };
const Color F = { 78, 205, 196, 255 };
const Color G = { 255, 209, 102, 255 };
const Color H = { 140, 152, 172, 255 };

const int WW = 600;
const int WH = 700;
const int HH = 100;
const int BS = 600;
const int CS = BS / 3;
const float CM = 12.0f;

enum class GS { M, P, GO };
enum class WT { N, R, CO, DM, DA };

struct WS {
    char w = ' ';
    WT t = WT::N;
    int i = -1;
};

class Bd {
private:
    char g[3][3];
public:
    Bd() { rst(); }
    void rst() { for(int i=0;i<3;i++) for(int j=0;j<3;j++) g[i][j]=' '; }
    bool mv(int r, int c, char m) {
        if(r>=0&&r<3&&c>=0&&c<3&&g[r][c]==' ') { g[r][c]=m; return true; }
        return false;
    }
    char gm(int r, int c) const { return g[r][c]; }
    WS cw() const {
        for(int i=0;i<3;i++) {
            if(g[i][0]!=' '&&g[i][0]==g[i][1]&&g[i][1]==g[i][2]) return {g[i][0], WT::R, i};
            if(g[0][i]!=' '&&g[0][i]==g[1][i]&&g[1][i]==g[2][i]) return {g[0][i], WT::CO, i};
        }
        if(g[0][0]!=' '&&g[0][0]==g[1][1]&&g[1][1]==g[2][2]) return {g[0][0], WT::DM, 0};
        if(g[0][2]!=' '&&g[0][2]==g[1][1]&&g[1][1]==g[2][0]) return {g[0][2], WT::DA, 0};
        return {' ', WT::N, -1};
    }
    bool ful() const {
        for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(g[i][j]==' ') return false;
        return true;
    }
};

void DX(Vector2 z, float s, float t, Color col) {
    float h = s/2.0f;
    DrawLineEx({z.x-h, z.y-h}, {z.x+h, z.y+h}, t, col);
    DrawLineEx({z.x-h, z.y+h}, {z.x+h, z.y-h}, t, col);
}

void DO(Vector2 z, float rad, float t, Color col) {
    DrawRing(z, rad - t/2.0f, rad + t/2.0f, 0, 360, 36, col);
}

void DW(WS ws) {
    if(ws.t == WT::N) return;
    Vector2 s = {0}, e = {0}; float th = 10.0f;
    if(ws.t == WT::R) { float y = HH + ws.i * CS + (CS/2.0f); s = {40.0f, y}; e = {(float)WW-40.0f, y}; }
    else if(ws.t == WT::CO) { float x = ws.i * CS + (CS/2.0f); s = {x, (float)HH+40.0f}; e = {x, (float)WH-40.0f}; }
    else if(ws.t == WT::DM) { s = {40.0f, (float)HH+40.0f}; e = {(float)WW-40.0f, (float)WH-40.0f}; }
    else if(ws.t == WT::DA) { s = {(float)WW-40.0f, (float)HH+40.0f}; e = {40.0f, (float)WH-40.0f}; }
    DrawLineEx(s, e, th, G);
}

int main() {
    InitWindow(WW, WH, "Tic Tac Toe");
    SetTargetFPS(60);
    Bd b; char tu = 'X'; GS st = GS::M; WS ws = {' ', WT::N, -1};
    while(!WindowShouldClose()) {
        Vector2 mp = GetMousePosition();
        switch(st) {
            case GS::M:
                if(IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    b.rst(); tu = 'X'; ws = {' ', WT::N, -1}; st = GS::P;
                }
                break;
            case GS::P:
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mp.y > HH) {
                    int c = mp.x / CS; int r = (mp.y - HH) / CS;
                    if(b.mv(r, c, tu)) {
                        ws = b.cw();
                        if(ws.w != ' ' || b.ful()) st = GS::GO;
                        else tu = (tu == 'X') ? 'O' : 'X';
                    }
                }
                break;
            case GS::GO:
                if(IsKeyPressed(KEY_R)) { b.rst(); tu = 'X'; ws = {' ', WT::N, -1}; st = GS::P; }
                else if(IsKeyPressed(KEY_M)) { st = GS::M; }
                break;
        }
        BeginDrawing();
        ClearBackground(A);
        switch(st) {
            case GS::M: {
                int tw = MeasureText("TIC TAC TOE", 48);
                DrawText("TIC TAC TOE", (WW - tw)/2, 220, 48, E);
                int sw = MeasureText("Press ENTER or Click anywhere to Play", 20);
                DrawText("Press ENTER or Click anywhere to Play", (WW - sw)/2, 340, 20, H);
                DX({220, 480}, 60, 10, E);
                DO({380, 480}, 35, 10, F);
                break;
            }
            case GS::P:
            case GS::GO: {
                DrawRectangle(0, 0, WW, HH, B);
                if(st == GS::P) {
                    DrawText(TextFormat("Turn: Player %c", tu), 30, 35, 32, (tu == 'X') ? E : F);
                } else {
                    if(ws.w != ' ') DrawText(TextFormat("Player %c Wins!", ws.w), 30, 35, 32, (ws.w == 'X') ? E : F);
                    else DrawText("It's a Draw!", 30, 35, 32, H);
                    DrawText("[R] Restart   [M] Menu", WW - 260, 42, 20, H);
                }
                for(int r=0; r<3; r++) {
                    for(int c=0; c<3; c++) {
                        Rectangle cr = {c*CS + CM, HH + r*CS + CM, CS - (CM*2), CS - (CM*2)};
                        bool ih = CheckCollisionPointRec(mp, cr) && st == GS::P && b.gm(r, c) == ' ';
                        DrawRectangleRounded(cr, 0.15f, 4, ih ? D : C);
                        Vector2 cen = {cr.x + cr.width/2.0f, cr.y + cr.height/2.0f};
                        char m = b.gm(r, c);
                        if(m == 'X') DX(cen, 70.0f, 12.0f, E);
                        else if(m == 'O') DO(cen, 40.0f, 12.0f, F);
                    }
                }
                if(st == GS::GO && ws.w != ' ') DW(ws);
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
