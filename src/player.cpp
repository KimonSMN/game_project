#include "player.hpp"

Player::Player() {
    image = LoadTexture("assets/soldier_idle.png");
    position.x = (GetScreenWidth() ) / 2;
    position.y = (GetScreenHeight()) / 2;
    
    // Initialize animation variables
    frameWidth = image.width / 5; // Assuming 5 frames in the sprite sheet
    frameHeight = image.height;
    currentFrame = 0;
    totalFrames = 5;
    frameSpeed = 8; // Number of frames to wait before advancing to the next frame
    framesCounter = 0;
    scale = 3.0f;
}

Player::~Player() {
    UnloadTexture(image);
}

void Player::Draw() {
    // Source rectangle (part of the texture to draw)
    Rectangle sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
    // Destination rectangle (where to draw the part of the texture)
    Rectangle destRec = { position.x, position.y, frameWidth * scale, frameHeight * scale};
    // Origin of the texture (rotation point)
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(image, sourceRec, destRec, origin, 0.0f, WHITE);
}

void Player::Update() {
    framesCounter++;
    if (framesCounter >= (60 / frameSpeed)) {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame >= totalFrames) {
            currentFrame = 0;
        }
    }
}

void Player::MoveUp() {
    position.y -= 7;
}

void Player::MoveDown() {
    position.y += 7;
}

void Player::MoveLeft() {
    position.x -= 7;
}

void Player::MoveRight() {
    position.x += 7;
}
