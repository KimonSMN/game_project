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
    if (IsKeyDown(KEY_UP))
        player.MoveUp();
    
    if(IsKeyDown(KEY_DOWN))
        player.MoveDown();
    
    if (IsKeyDown(KEY_LEFT))
        player.MoveLeft();
    
    if(IsKeyDown(KEY_RIGHT))
        player.MoveRight();
}

