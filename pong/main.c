// --- TRABALHO DE PROGRAMAÇÃO DE COMPUTADORES I ---
// --- ALUNO: DAVI SZEREMETA DA CRUZ             ---
// --- RA: 25106623                              ---
// --- CURSO: ENGENHARIA DE SOFTWARE(NOTURNO)    ---

#include "raylib.h"

typedef enum { MENU, DOIS_JOGADORES, UM_JOGADOR, SAIR } GameScreen;

int main() {
    InitWindow(1800, 900, "PONG");
    SetTargetFPS(60);

    GameScreen interface = MENU;
    int selecionado = 0;

    while (!WindowShouldClose()) {

        if (interface == MENU) {
            if (IsKeyPressed(KEY_DOWN)) selecionado++;
            if (IsKeyPressed(KEY_UP)) selecionado--;
            if (selecionado > 2) selecionado = 0;
            if (selecionado < 0) selecionado = 2;

            if (IsKeyPressed(KEY_ENTER)) {
                switch (selecionado) {
                    case 0: interface = DOIS_JOGADORES; break;
                    case 1: interface = UM_JOGADOR; break;
                    case 2: interface = SAIR; break;
                }
            }
        }

        if (interface == SAIR) break;


        BeginDrawing();
        ClearBackground(BLACK);

        if (interface == MENU) {

    DrawText("P O N G", 80, 160, 160, RAYWHITE);
    DrawRectangleLines(45, 145, 700, 165, RAYWHITE);
    DrawText("Use as setas e ENTER para escolher", 50, 330, 20, GRAY);


    DrawText("CONTROLES:", 20, 780, 30, WHITE);
    DrawText("Jogador esquerdo: teclas W e S", 20, 810, 28, RED);
    DrawText("Jogador direito: setas do teclado", 20, 840, 28, BLUE);
    DrawText("Pressione ESC para voltar ao menu", 20, 870, 28, PURPLE);


    Color c1 = (selecionado == 0) ? YELLOW : RAYWHITE;
    Color c2 = (selecionado == 1) ? YELLOW : RAYWHITE;
    Color c3 = (selecionado == 2) ? YELLOW : RAYWHITE;

    DrawText("Dois Jogadores", 1240, 390, 50, c1);
    DrawText("Um Jogador", 1240, 470, 50, c2);
    DrawText("Sair", 1240, 550, 50, c3);
    DrawRectangleLines(1200, 297, 470, 390, RAYWHITE);
}


        if (interface == DOIS_JOGADORES) {

    SetTargetFPS(60);


    Vector2 bola = {900, 425};
    Vector2 velocidadebola = {10, 10};
    Rectangle jogador1 = {50, 400, 20, 200};
    Rectangle jogador2 = {1730, 400, 20, 200};
    int pontos1 = 0, pontos2 = 0;

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_W) && jogador1.y > 0) jogador1.y -= 12;
        if (IsKeyDown(KEY_S) && jogador1.y < GetScreenHeight() - jogador1.height) jogador1.y += 12;
        if (IsKeyDown(KEY_UP) && jogador2.y > 0) jogador2.y -= 12;
        if (IsKeyDown(KEY_DOWN) && jogador2.y < GetScreenHeight() - jogador2.height) jogador2.y += 12;


        bola.x += velocidadebola.x;
        bola.y += velocidadebola.y;

        float aumentarvelocidade = 1.02f;


if (bola.y <= 0 || bola.y >= GetScreenHeight()) {
    velocidadebola.y *= -1;
    velocidadebola.x *= aumentarvelocidade;
    velocidadebola.y *= aumentarvelocidade;
}


if (CheckCollisionCircleRec(bola, 16, jogador1) && velocidadebola.x < 0) {
    velocidadebola.x *= -1;
    velocidadebola.x *= aumentarvelocidade;
    velocidadebola.y *= aumentarvelocidade;
}

if (CheckCollisionCircleRec(bola, 16, jogador2) && velocidadebola.x > 0) {
    velocidadebola.x *= -1;
    velocidadebola.x *= aumentarvelocidade;
    velocidadebola.y *= aumentarvelocidade;
}


        if (bola.x <= 0) {
        pontos2++;
        bola = (Vector2){900, 425};

            float dirX = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
            float dirY = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;

        velocidadebola = (Vector2){10 * dirX, 10 * dirY};
}

        if (bola.x >= GetScreenWidth()) {
        pontos1++;
        bola = (Vector2){900, 425};


            float dirX = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
            float dirY = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;

        velocidadebola = (Vector2){10 * dirX, 10 * dirY};
}


        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), GRAY);
            DrawCircleV(bola, 16, RAYWHITE);
            DrawRectangleRec(jogador1, RED);
            DrawRectangleRec(jogador2, BLUE);
            DrawText(TextFormat("%d", pontos1), GetScreenWidth()/4, 40, 60, WHITE);
            DrawText(TextFormat("%d", pontos2), 3*GetScreenWidth()/4, 40, 60, WHITE);

        EndDrawing();
    }

            if (IsKeyPressed(KEY_ESCAPE)) interface = MENU;
        }
        if (interface == UM_JOGADOR) {

    SetTargetFPS(60);

    Vector2 bola = {900, 425};
    Vector2 velocidadebola = {10, 10};
    Rectangle jogador1 = {50, 400, 20, 200};
    Rectangle ia = {1730, 400, 20, 200};
    int pontos1 = 0, pontos2 = 0;

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_W) && jogador1.y > 0) jogador1.y -= 12;
        if (IsKeyDown(KEY_S) && jogador1.y < GetScreenHeight() - jogador1.height) jogador1.y += 12;

        if (bola.y < ia.y + ia.height / 2) ia.y -= 16;
        if (bola.y > ia.y + ia.height / 2) ia.y += 16;

        if (ia.y < 0) ia.y = 0;
        if (ia.y > GetScreenHeight() - ia.height) ia.y = GetScreenHeight() - ia.height;


        bola.x += velocidadebola.x;
        bola.y += velocidadebola.y;

        float aumentarvelocidade = 1.02f;


if (bola.y <= 0 || bola.y >= GetScreenHeight()) {
    velocidadebola.y *= -1;
    velocidadebola.x *= aumentarvelocidade;
    velocidadebola.y *= aumentarvelocidade;

}


if (CheckCollisionCircleRec(bola, 16, jogador1) && velocidadebola.x < 0) {
    velocidadebola.x *= -1;
    velocidadebola.x *= aumentarvelocidade;
    velocidadebola.y *= aumentarvelocidade;

}

if (CheckCollisionCircleRec(bola, 16, ia) && velocidadebola.x > 0) {
    velocidadebola.x *= -1;
    velocidadebola.x *= aumentarvelocidade;
    velocidadebola.y *= aumentarvelocidade;

}

        if (bola.x <= 0) {
        pontos2++;
        bola = (Vector2){900, 425};

            float dirX = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
            float dirY = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;

        velocidadebola = (Vector2){10 * dirX, 10 * dirY};
}

        if (bola.x >= GetScreenWidth()) {
        pontos1++;
        bola = (Vector2){900, 425};


            float dirX = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;
            float dirY = (GetRandomValue(0, 1) == 0) ? -1.0f : 1.0f;

        velocidadebola = (Vector2){10 * dirX, 10 * dirY};
}

        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), GRAY);
            DrawCircleV(bola, 16, RAYWHITE);
            DrawRectangleRec(jogador1, RED);
            DrawRectangleRec(ia, BLUE);
            DrawText(TextFormat("%d", pontos1), GetScreenWidth()/4, 40, 60, WHITE);
            DrawText(TextFormat("%d", pontos2), 3*GetScreenWidth()/4, 40, 60, WHITE);

        EndDrawing();
    }


            if (IsKeyPressed(KEY_ESCAPE)) interface = MENU;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}





