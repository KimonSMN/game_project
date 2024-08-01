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
        // void Attack();

    private:
        Texture2D image;
        Vector2 position = {0, 0};

        // Animation-related variables
        float frameWidth;
        float frameHeight;
        float currentFrame;
        float totalFrames;
        float frameSpeed;
        float framesCounter;

        // Scale factor
        float scale;
};
