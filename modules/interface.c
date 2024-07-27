#include "raylib.h"
#include <math.h>

#include "../include/state.h"
#include "../include/interface.h"

// Assets
Texture player_idle;
Texture player_walk;
Texture asteroid_img;
Texture bullet_img;
Texture background;


int playerIdleIndex = 0;
float playerIdleTimer = PLAYER_IDLE_TIME;

int playerWalkIndex = 0;
float playerWalkTimer = PLAYER_WALK_TIME;

bool facingRight = true;
bool playerMoving = false;

// Αρχικοποιεί το interface του παιχνιδιού

void interface_init(){
    // Initialize the window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "asteroids");
	SetTargetFPS(60);
    InitAudioDevice();
	
	// Load images
	player_idle = LoadTextureFromImage(LoadImage("assets/soldier_idle.png"));
    player_walk = LoadTextureFromImage(LoadImage("assets/soldier_walk.png"));

    asteroid_img = LoadTextureFromImage(LoadImage("assets/asteroid.png"));
    bullet_img = LoadTextureFromImage(LoadImage("assets/bullet.png"));
    background = LoadTextureFromImage(LoadImage("assets/background.png"));
    
    player_idle.height = player_idle.height * 3;
    player_idle.width = player_idle.width * 3;

}

static float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Κλείνει το interface του παιχνιδιού
void interface_close(){
	CloseAudioDevice();
	CloseWindow();
}


// Σχεδιάζει ένα frame με την τωρινή κατάσταση του παιχνδιού
void interface_draw_frame(State state) {

    // // Player Idle animation

    playerIdleTimer--;
    if (playerIdleTimer < 0) {
        playerIdleTimer = PLAYER_IDLE_TIME;
        playerIdleIndex++;
        if (playerIdleIndex >= PLAYER_IDLE_COUNT) {
            playerIdleIndex = 0;
        }
    }



    Rectangle gameplayArea = { 0, 0, 1800, 1400 }; // Example: 1600x1200 gameplay area

    int scale_factor = 5;

    Camera2D camera; // Αρχικοποιηση camera
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}; // window origin
    camera.target = (Vector2){0, 0}; 
    camera.rotation = 0;
    camera.zoom = 1;
    
    // Καμερα ακολουθει διαστημοπλοιο 
    Vector2 playerPosition = state_info(state)->player->position;
    camera.target.x = playerPosition.x;
    camera.target.y = playerPosition.y;

    // Clamp the camera target to the boundaries of the gameplay area
    Vector2 min = { gameplayArea.x + SCREEN_WIDTH / 2.0f / camera.zoom, gameplayArea.y + SCREEN_HEIGHT / 2.0f / camera.zoom };
    Vector2 max = { gameplayArea.x + gameplayArea.width - SCREEN_WIDTH / 2.0f / camera.zoom, gameplayArea.y + gameplayArea.height - SCREEN_HEIGHT / 2.0f / camera.zoom };

    camera.target.x = Clamp(camera.target.x, min.x, max.x);
    camera.target.y = Clamp(camera.target.y, min.y, max.y);

    // Clamp the player's position to the boundaries of the gameplay area
    playerPosition.x = Clamp(playerPosition.x, gameplayArea.x, gameplayArea.x + gameplayArea.width);
    playerPosition.y = Clamp(playerPosition.y, gameplayArea.y, gameplayArea.y + gameplayArea.height);

    // Update the player's position in the state
    state_info(state)->player->position = playerPosition;


    BeginDrawing();
	BeginMode2D(camera); 
    ClearBackground(RAYWHITE);
    DrawTexture(background, 0, 0, WHITE);


    // Check which direction the player is facing
    // Used for animating the player

    if (IsKeyDown(KEY_RIGHT)) {
        facingRight = true;
        playerMoving = true;

    }
    if (IsKeyDown(KEY_LEFT)) {
        facingRight = false;
        playerMoving = true;

    }

    if (!(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))) {
        playerMoving = false;
    }

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) ) {
        playerMoving = true;
    } else{
        playerMoving = false;
    }

    if (playerMoving) {
        playerWalkTimer++;
        if (playerWalkTimer >= PLAYER_WALK_TIME) {
            playerWalkTimer = 0;
            playerWalkIndex++;
            if (playerWalkIndex >= PLAYER_WALK_COUNT) {
                playerWalkIndex = 0;
            }
        }
    } 

 




    // Player Idle Drawing

    if (playerMoving){
        Rectangle source = (Rectangle){playerWalkIndex * PLAYER_WALK_WIDTH, 0, facingRight ? PLAYER_WALK_WIDTH : -PLAYER_WALK_WIDTH , PLAYER_WALK_HEIGHT};
        Rectangle dest = (Rectangle) {playerPosition.x, playerPosition.y, PLAYER_WALK_WIDTH * 3.6, PLAYER_WALK_HEIGHT * 3.6};
        DrawTexturePro(player_walk, source, dest, (Vector2){0, 0}, 0, WHITE);
    } else{
        Rectangle source = (Rectangle){playerIdleIndex * PLAYER_IDLE_WIDTH, 0, facingRight ? PLAYER_IDLE_WIDTH : -PLAYER_IDLE_WIDTH, PLAYER_IDLE_HEIGHT};
        Rectangle dest = (Rectangle) {playerPosition.x, playerPosition.y, PLAYER_IDLE_WIDTH * 1.2, PLAYER_IDLE_HEIGHT * 1.2};
        DrawTexturePro(player_idle, source, dest, (Vector2){0, 0}, 0, WHITE);
    }


	Vector2 top_left = {
		state_info(state)->player->position.x - ASTEROID_MAX_DIST, 
		state_info(state)->player->position.y + ASTEROID_MAX_DIST
	};
	Vector2 bottom_right = {
		state_info(state)->player->position.x  + ASTEROID_MAX_DIST, 
		state_info(state)->player->position.y - ASTEROID_MAX_DIST
	};

    List objects_in_range = state_objects(state,top_left,bottom_right);
    
    for(ListNode node = list_first(objects_in_range); 
        node != LIST_EOF;
		node = list_next(objects_in_range, node)){

        Object object = list_node_value(objects_in_range, node);
        if (object->type == ENEMY) {
            Rectangle source = { 0, 0, asteroid_img.width, asteroid_img.height };
            Rectangle dest = { object->position.x, object->position.y, object->size * scale_factor, object->size * scale_factor };
            Vector2 origin = { object->size * scale_factor / 2, object->size * scale_factor / 2 };
            DrawTexturePro(asteroid_img, source, dest, origin, 0, WHITE);

        }else if(object->type == BULLET){
            float radians = atan2(object->orientation.y, object->orientation.x);
            float rotation = radians * (180 / PI);
            Rectangle source = { 0, 0, bullet_img.width, bullet_img.height };
            Rectangle dest = { object->position.x, object->position.y, object->size * 30, object->size * 30 };
            Vector2 origin = { object->size * 30 / 2, object->size * 30 / 2 };
            DrawTexturePro(bullet_img, source, dest, origin, rotation, WHITE);
        }
    }
    
    EndMode2D();

    // Draw the score and the FPS counter
    DrawText(TextFormat("%04i", state_info(state)->score), 780, 20, 40, WHITE);
    DrawFPS(0, 0);

    EndDrawing();
}
