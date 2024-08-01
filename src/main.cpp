#include <raylib.h>
#include "game.hpp"

int main()
{
    const int screenWidth = 1080;
    const int screenHeight = 1080;


    InitWindow(screenWidth, screenHeight, "vampire surivior");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();
    
        BeginDrawing();
        ClearBackground(RED);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}