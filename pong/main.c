#include "raylib.h"

typedef enum { MENU, DOIS_JOGADORES, UM_JOGADOR, SAIR } GameScreen;

Font fonteMenu;
Texture2D menuFundo;


void TelaDoisJogadores();
void TelaUmJogador();

int main() {
    InitWindow(1800, 900, "PONG");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    fonteMenu = LoadFont("gadugi-2.ttf");
    menuFundo = LoadTexture("menu.png");

    GameScreen interface = MENU;
    int selecionado = 0;

    while (!WindowShouldClose()) {


        if (interface == MENU) {


            if (IsKeyPressed(KEY_DOWN)) selecionado++;
            if (IsKeyPressed(KEY_UP))   selecionado--;

            if (selecionado > 2) selecionado = 0;
            if (selecionado < 0) selecionado = 2;


            if (IsKeyPressed(KEY_ENTER)) {
                if (selecionado == 0) interface = DOIS_JOGADORES;
                if (selecionado == 1) interface = UM_JOGADOR;
                if (selecionado == 2) interface = SAIR;
            }


            BeginDrawing();
            ClearBackground(DARKGREEN);

            DrawTexturePro(
                menuFundo,
                (Rectangle){0, 0, menuFundo.width, menuFundo.height},
                (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                (Vector2){0, 0}, 0, WHITE
            );

            Color c1 = (selecionado == 0) ? YELLOW : WHITE;
            Color c2 = (selecionado == 1) ? YELLOW : WHITE;
            Color c3 = (selecionado == 2) ? YELLOW : WHITE;

            DrawTextEx(fonteMenu, "DOIS JOGADORES", (Vector2){1255, 510}, 50, 2, c1);
            DrawTextEx(fonteMenu, "UM JOGADOR",    (Vector2){1290, 610}, 50, 2, c2);
            DrawTextEx(fonteMenu, "SAIR",          (Vector2){1370, 710}, 50, 2, c3);

            EndDrawing();
        }


        if (interface == SAIR) break;


        if (interface == DOIS_JOGADORES) {
            TelaDoisJogadores();
            interface = MENU;
        }

        if (interface == UM_JOGADOR) {
            TelaUmJogador();
            interface = MENU;
        }
    }

    UnloadFont(fonteMenu);
    UnloadTexture(menuFundo);
    CloseWindow();
    return 0;
}


void TelaDoisJogadores() {

    Texture2D fundo = LoadTexture("fundo.png");

    Vector2 bola = {900, 425};
    Vector2 vel = {10, 10};

    Rectangle p1 = {50, 400, 20, 200};
    Rectangle p2 = {1730, 400, 20, 200};

    int pts1 = 0, pts2 = 0;

    while (!WindowShouldClose()) {


        if (IsKeyPressed(KEY_ESCAPE)) break;


        if (IsKeyDown(KEY_W) && p1.y > 0) p1.y -= 12;
        if (IsKeyDown(KEY_S) && p1.y < GetScreenHeight() - p1.height) p1.y += 12;
        if (IsKeyDown(KEY_UP) && p2.y > 0) p2.y -= 12;
        if (IsKeyDown(KEY_DOWN) && p2.y < GetScreenHeight() - p2.height) p2.y += 12;


        bola.x += vel.x;
        bola.y += vel.y;

        float mult = 1.02f;

        if (bola.y <= 0 || bola.y >= GetScreenHeight()) {
            vel.y *= -1;
            vel.x *= mult;
            vel.y *= mult;
        }

        if (CheckCollisionCircleRec(bola, 16, p1) && vel.x < 0) {
            vel.x *= -1; vel.x *= mult; vel.y *= mult;
        }

        if (CheckCollisionCircleRec(bola, 16, p2) && vel.x > 0) {
            vel.x *= -1; vel.x *= mult; vel.y *= mult;
        }


        if (bola.x <= 0) {
            pts2++;
            bola = (Vector2){900, 425};
            vel = (Vector2){10 * (GetRandomValue(0,1)?1:-1),
                            10 * (GetRandomValue(0,1)?1:-1)};
        }

        if (bola.x >= GetScreenWidth()) {
            pts1++;
            bola = (Vector2){900, 425};
            vel = (Vector2){10 * (GetRandomValue(0,1)?1:-1),
                            10 * (GetRandomValue(0,1)?1:-1)};
        }


        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            fundo,
            (Rectangle){0, 0, fundo.width, fundo.height},
            (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
            (Vector2){0, 0}, 0, WHITE
        );

        DrawCircleV(bola, 16, WHITE);
        DrawRectangleRec(p1, WHITE);
        DrawRectangleRec(p2, WHITE);

        DrawText(TextFormat("%d", pts1), GetScreenWidth()/4, 40, 60, WHITE);
        DrawText(TextFormat("%d", pts2), 3*GetScreenWidth()/4, 40, 60, WHITE);

        EndDrawing();
    }

    UnloadTexture(fundo);
}


void TelaUmJogador() {

    Texture2D fundo = LoadTexture("fundo.png");

    Vector2 bola = {900, 425};
    Vector2 vel = {10, 10};

    Rectangle p1 = {50, 400, 20, 200};
    Rectangle ia = {1730, 400, 20, 200};

    int pts1 = 0, pts2 = 0;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ESCAPE)) break;


        if (IsKeyDown(KEY_W) && p1.y > 0) p1.y -= 12;
        if (IsKeyDown(KEY_S) && p1.y < GetScreenHeight() - p1.height) p1.y += 12;


        if (bola.y < ia.y + ia.height/2) ia.y -= 16;
        if (bola.y > ia.y + ia.height/2) ia.y += 16;

        if (ia.y < 0) ia.y = 0;
        if (ia.y > GetScreenHeight() - ia.height) ia.y = GetScreenHeight() - ia.height;


        bola.x += vel.x;
        bola.y += vel.y;

        float mult = 1.02f;

        if (bola.y <= 0 || bola.y >= GetScreenHeight()) {
            vel.y *= -1; vel.x *= mult; vel.y *= mult;
        }

        if (CheckCollisionCircleRec(bola, 16, p1) && vel.x < 0) {
            vel.x *= -1; vel.x *= mult; vel.y *= mult;
        }

        if (CheckCollisionCircleRec(bola, 16, ia) && vel.x > 0) {
            vel.x *= -1; vel.x *= mult; vel.y *= mult;
        }


        if (bola.x <= 0) {
            pts2++;
            bola = (Vector2){900, 425};
            vel = (Vector2){10 * (GetRandomValue(0,1)?1:-1),
                            10 * (GetRandomValue(0,1)?1:-1)};
        }

        if (bola.x >= GetScreenWidth()) {
            pts1++;
            bola = (Vector2){900, 425};
            vel = (Vector2){10 * (GetRandomValue(0,1)?1:-1),
                            10 * (GetRandomValue(0,1)?1:-1)};
        }


        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            fundo,
            (Rectangle){0, 0, fundo.width, fundo.height},
            (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
            (Vector2){0, 0}, 0, WHITE
        );

        DrawCircleV(bola, 16, WHITE);
        DrawRectangleRec(p1, WHITE);
        DrawRectangleRec(ia, WHITE);

        DrawText(TextFormat("%d", pts1), GetScreenWidth()/4, 40, 60, WHITE);
        DrawText(TextFormat("%d", pts2), 3*GetScreenWidth()/4, 40, 60, WHITE);

        EndDrawing();
    }

    UnloadTexture(fundo);
}
















