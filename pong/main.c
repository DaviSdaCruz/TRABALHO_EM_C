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

        // -------------------- MENU --------------------
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

            DrawText("P O N G", 80, 160, 160, WHITE);
            DrawRectangleLines(45, 145, 700, 165, WHITE);
            DrawText("Use as setas e ENTER para escolher", 50, 330, 20, BLACK);

            DrawText("CONTROLES:", 20, 810, 30, WHITE);
            DrawText("Jogador esquerdo: teclas W e S", 20, 840, 28, BLACK);
            DrawText("Jogador direito: setas do teclado", 20, 870, 28, BLACK);

            Color c1 = (selecionado == 0) ? YELLOW : WHITE;
            Color c2 = (selecionado == 1) ? YELLOW : WHITE;
            Color c3 = (selecionado == 2) ? YELLOW : WHITE;

            DrawText("Dois Jogadores", 1240, 390, 50, c1);
            DrawText("Um Jogador", 1240, 470, 50, c2);
            DrawText("Sair", 1240, 550, 50, c3);
            DrawRectangleLines(1200, 297, 470, 390, WHITE);

            EndDrawing();
        }

        if (interface == SAIR) break;



        // --------------------- DOIS JOGADORES ---------------------
        if (interface == DOIS_JOGADORES) {

            Texture2D fundo = LoadTexture("fundo.png");

            Vector2 bola = {900, 425};
            Vector2 velocidadebola = {10, 10};
            Rectangle jogador1 = {50, 400, 20, 200};
            Rectangle jogador2 = {1730, 400, 20, 200};
            int pontos1 = 0, pontos2 = 0;

            while (!WindowShouldClose()) {

                // ----------- MOVIMENTOS -----------
                if (IsKeyDown(KEY_W) && jogador1.y > 0) jogador1.y -= 12;
                if (IsKeyDown(KEY_S) && jogador1.y < GetScreenHeight() - jogador1.height) jogador1.y += 12;
                if (IsKeyDown(KEY_UP) && jogador2.y > 0) jogador2.y -= 12;
                if (IsKeyDown(KEY_DOWN) && jogador2.y < GetScreenHeight() - jogador2.height) jogador2.y += 12;

                // ----------- FÍSICA DA BOLA -----------
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

                    float dirX = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                    float dirY = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                    velocidadebola = (Vector2){10 * dirX, 10 * dirY};
                }

                if (bola.x >= GetScreenWidth()) {
                    pontos1++;
                    bola = (Vector2){900, 425};

                    float dirX = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                    float dirY = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                    velocidadebola = (Vector2){10 * dirX, 10 * dirY};
                }

                // ----------- DESENHO -----------
                BeginDrawing();
                ClearBackground(BLACK);

                DrawTexturePro(
                    fundo,
                    (Rectangle){0, 0, fundo.width, fundo.height},
                    (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                    (Vector2){0, 0},
                    0,
                    WHITE
                );

                DrawCircleV(bola, 16, ORANGE);
                DrawRectangleRec(jogador1, RED);
                DrawRectangleRec(jogador2, BLUE);
                DrawText(TextFormat("%d", pontos1), GetScreenWidth()/4, 40, 60, WHITE);
                DrawText(TextFormat("%d", pontos2), 3*GetScreenWidth()/4, 40, 60, WHITE);

                EndDrawing();
            }

        }



        // --------------------- UM JOGADOR ---------------------
        if (interface == UM_JOGADOR) {

            Texture2D fundo = LoadTexture("fundo.png");

            Vector2 bola = {900, 425};
            Vector2 velocidadebola = {10, 10};
            Rectangle jogador1 = {50, 400, 20, 200};
            Rectangle ia = {1730, 400, 20, 200};

            int pontos1 = 0, pontos2 = 0;

            while (!WindowShouldClose()) {

                // MOVIMENTO DO JOGADOR
                if (IsKeyDown(KEY_W) && jogador1.y > 0) jogador1.y -= 12;
                if (IsKeyDown(KEY_S) && jogador1.y < GetScreenHeight() - jogador1.height) jogador1.y += 12;

                // IA DO OPONENTE
                if (bola.y < ia.y + ia.height/2) ia.y -= 16;
                if (bola.y > ia.y + ia.height/2) ia.y += 16;

                if (ia.y < 0) ia.y = 0;
                if (ia.y > GetScreenHeight() - ia.height)
                    ia.y = GetScreenHeight() - ia.height;

                // FÍSICA DA BOLA
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

                // PONTUAÇÃO
                if (bola.x <= 0) {
                    pontos2++;
                    bola = (Vector2){900, 425};

                    float dirX = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                    float dirY = (GetRandomValue(0, 1) == 0) ? -1 : 1;

                    velocidadebola = (Vector2){10 * dirX, 10 * dirY};
                }

                if (bola.x >= GetScreenWidth()) {
                    pontos1++;
                    bola = (Vector2){900, 425};

                    float dirX = (GetRandomValue(0, 1) == 0) ? -1 : 1;
                    float dirY = (GetRandomValue(0, 1) == 0) ? -1 : 1;

                    velocidadebola = (Vector2){10 * dirX, 10 * dirY};
                }

                // DESENHO
                BeginDrawing();
                ClearBackground(BLACK);

                DrawTexturePro(
                    fundo,
                    (Rectangle){0, 0, fundo.width, fundo.height},
                    (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                    (Vector2){0, 0},
                    0,
                    WHITE
                );

                DrawCircleV(bola, 16, ORANGE);
                DrawRectangleRec(jogador1, RED);
                DrawRectangleRec(ia, BLUE);

                DrawText(TextFormat("%d", pontos1), GetScreenWidth()/4, 40, 60, WHITE);
                DrawText(TextFormat("%d", pontos2), 3*GetScreenWidth()/4, 40, 60, WHITE);

                EndDrawing();
            }

        }

    }

    CloseWindow();
    return 0;
}
















