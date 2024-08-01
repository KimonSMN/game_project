#include "game.hpp"

Game::Game(){
    background = LoadTexture("assets/background.png");
}

Game::~Game(){
    UnloadTexture(background); 
}
void Game::Update(){
    player.Update();    // Update the Player

    for(auto& arrow : player.arrows){
        arrow.Update();
    }
}

void Game::Draw(){
    DrawTexture(background, 0, 0, WHITE); // Draw the Background
    player.Draw();      // Draw the Player
    
    for(auto arrow : player.arrows){
        arrow.Draw();
    }
}

void Game::HandleInput(){
    bool keyPressed = false; // Variable to check if keys are pressed

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
    if (!keyPressed) {  // When no key is pressed, call Idle Function
        player.Idle();
    }
    if(IsKeyDown(KEY_SPACE)){
        player.FireArrow();
    }
}

