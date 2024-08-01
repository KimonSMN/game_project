#pragma once
#include <raylib.h>
#include "arrow.hpp"
#include <vector>

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
    
        void FireArrow();

        std::vector<Arrow> arrows;

    private:
        Texture2D image_idle;
        Texture2D image_walking;
        Vector2 position;

        // Animation-related variables
        float frameWidth;
        float frameHeight;
        int currentFrame;
        int totalFrames;
        int frameSpeed;
        int framesCounter;

        bool isMoving;
        bool facingLeft;
        // Scale factor
        float scale;

        double lastFireTime;
};
