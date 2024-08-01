#pragma once
#include "player.hpp"

class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
    private:
        Player player;
        Texture background;
        float lastFireTime;
};