#include "game.hpp"

Game::Game(){
    background = LoadTexture("assets/background.png");
}

Game::~Game(){
    UnloadTexture(background);
}

void Game::Draw(){
    DrawTexture(background, 0, 0, WHITE);
    player.Draw();
}

void Game::Update(){
    player.Update();
}

void Game::HandleInput(){
    bool keyPressed = false;

    if (IsKeyDown(KEY_UP)) {
        player.MoveUp();
        keyPressed = true;
    }
    
    if (IsKeyDown(KEY_DOWN)) {
        player.MoveDown();
        keyPressed = true;
    }
    
    if (IsKeyDown(KEY_LEFT)) {
        player.MoveLeft();
        keyPressed = true;
    }
    
    if (IsKeyDown(KEY_RIGHT)) {
        player.MoveRight();
        keyPressed = true;
    }
    if (!keyPressed) {
        player.Idle();
    }
}

