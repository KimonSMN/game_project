#pragma once
#include <raylib.h>

class Player {

    public: 
        Player();
        ~Player();

        void Draw();
        void Update();
        void MoveUp();
        void MoveDown();
        void MoveRight();
        void MoveLeft();
        void Idle();
        // void Attack();

    private:
        Texture2D image_idle;
        Texture2D image_walking;
        Vector2 position = {0, 0};

        // Animation-related variables
        float frameWidth;
        float frameHeight;
        float currentFrame;
        float totalFramesIdle;
        float totalFramesWalking;
        float frameSpeed;
        float framesCounter;
        
        bool isMoving;
        bool facingLeft;
        
        // Scale factor
        float scale;
};
