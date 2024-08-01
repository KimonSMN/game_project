#pragma once
#include <raylib.h>

class Arrow {

    public: 

        Arrow(Vector2 position, int speed, bool facingLeft);
        ~Arrow();
        void Update();
        void Draw();

        bool active;
    private:

        Texture2D arrow;
        Vector2 position;
        int speed;
        bool facingLeft;
};
