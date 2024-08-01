#pragma once
#include <raylib.h>

class Arrow {

    public: 

        Arrow(Vector2 position, int speed);
        ~Arrow();
        void Update();
        void Draw();

        bool active;
    private:

        Texture2D arrow;
        Vector2 position;
        int speed;
};
