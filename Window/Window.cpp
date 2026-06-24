#include "raylib.h"


void OpenWindow(){
    InitWindow(GetScreenWidth(),GetScreenHeight(), "Game_title");
    BeginDrawing();
}


void CloseWindow(){
    EndDrawing();
    CloseWindow();
}


