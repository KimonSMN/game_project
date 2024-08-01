#include "arrow.hpp"
#include <iostream>

Arrow::Arrow(Vector2 position, int speed){

    arrow = LoadTexture("assets/arrow.png");

    this -> position = position;
    this -> speed = speed;
    active = true;

}

Arrow::~Arrow(){
    // UnloadTexture(arrow); // this makes it go brrrrr (bad)
}

void Arrow::Draw(){
    if(active){
        // Destination rectangle (where to draw the part of the texture)
        Rectangle destRec = { position.x, position.y, arrow.width * 3.0f, arrow.height * 3.0f };

        // Origin of the texture (rotation point)
        Vector2 origin = { 0.0f, 0.0f };

        // Source rectangle (part of the texture to draw)
        Rectangle sourceRec = { 0, 0, float(arrow.width), float(arrow.height) };
        
        if(IsKeyDown(KEY_LEFT))
            sourceRec.width = -arrow.width;
    
        DrawTexturePro(arrow, sourceRec, destRec, origin, 0.0f, WHITE);
    }

}

void Arrow::Update(){
    position.x += speed;
    if(active){
        if(position.y > GetScreenHeight() || position.y < 0 ||
            position.x > GetScreenWidth() || position.x < 0){
            active = false;
            std::cout << "Arrow Inactive" << std:: endl;
        }
    }
}