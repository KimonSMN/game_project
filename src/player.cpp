#include "player.hpp"
#include <iostream>
Player::Player() {
    image_idle = LoadTexture("assets/soldier_idle.png");
    image_walking = LoadTexture("assets/soldier_walk.png");
    position.x = (GetScreenWidth() - image_idle.width / 5) / 2;
    position.y = (GetScreenHeight() - image_idle.height) / 2;

    lastFireTime = 0.0;

    // Initialize animation variables
    totalFrames = 5;    // Total frames in a sprite sheet
    frameWidth = image_idle.width / 5; // Assuming 5 frames in the sprite sheet
    frameHeight = image_idle.height;
    currentFrame = 0;
    frameSpeed = 5;     // Number of frames to wait before advancing to the next frame
    framesCounter = 0;
    scale = 3.5f;

    isMoving = false;
    facingLeft = false;
}

Player::~Player() {
    UnloadTexture(image_idle);
    UnloadTexture(image_walking);
}

void Player::Draw() {
    Texture2D currentTexture = isMoving ? image_walking : image_idle;

    // Destination rectangle (where to draw the part of the texture)
    Rectangle destRec = { position.x, position.y, frameWidth * scale, frameHeight * scale };

    // Origin of the texture (rotation point)
    Vector2 origin = { 0.0f, 0.0f };

    // Source rectangle (part of the texture to draw)
    Rectangle sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
    
    if (facingLeft) {
        sourceRec.width = -frameWidth;
    }

    DrawTexturePro(currentTexture, sourceRec, destRec, origin, 0.0f, WHITE);
}

void Player::Update() {
    framesCounter++;

    int totalFrames = isMoving ? 8 : 5; // 5 frames when idle, 8 frames when walking
    int frameSpeed = isMoving ? 6 : 3; 

    if (framesCounter >= (60 / frameSpeed)) {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame >= totalFrames) {
            currentFrame = 0;
        }
    }
}

void Player::MoveUp() {
    position.y -= 4;
    isMoving = true;
}

void Player::MoveDown() {
    position.y += 4;
    isMoving = true;
}

void Player::MoveLeft() {
    position.x -= 4;
    isMoving = true;
    facingLeft = true;
}

void Player::MoveRight() {
    position.x += 4;
    isMoving = true;
    facingLeft = false;
}

void Player::Idle() {
    isMoving = false;
}


void Player::FireArrow(){
    if(GetTime() - lastFireTime >= 0.35){
        
        arrows.push_back(Arrow({position.x, position.y}, facingLeft ? -6 : 6, facingLeft));
        lastFireTime = GetTime();
    }
}

