#pragma once

#include "raylib.h"
#include "ADTList.h"

// Χαρακτηριστικά αντικειμένων
#define ASTEROID_NUM 6
#define ASTEROID_MIN_SIZE 10
#define ASTEROID_MAX_SIZE 80
#define ASTEROID_MIN_SPEED 1
#define ASTEROID_MAX_SPEED 1.5
#define ASTEROID_MIN_DIST 300
#define ASTEROID_MAX_DIST 400
#define BULLET_SPEED 10
#define BULLET_SIZE 3
#define BULLET_DELAY 15
#define PLAYER_SIZE 20
#define SPACESHIP_ROTATION (PI/32)

#define PLAYER_MOVEMENT_SPEED 5
#define SPACESHIP_SLOWDOWN 0.98

#define SCREEN_WIDTH 900	// Πλάτος της οθόνης
#define SCREEN_HEIGHT 700	// Υψος της οθόνης

//////////////////// Animation /////////////////////////////

// Player when idle
#define PLAYER_IDLE_TIME 13
#define PLAYER_IDLE_COUNT 5 // number of sprites
#define PLAYER_IDLE_HEIGHT 54
#define PLAYER_IDLE_WIDTH 45

// Player when walking
#define PLAYER_WALK_TIME 8
#define PLAYER_WALK_COUNT 8 // number of sprites
#define PLAYER_WALK_HEIGHT 18
#define PLAYER_WALK_WIDTH 15

typedef enum {
	PLAYER, ENEMY, BULLET
} ObjectType;

typedef enum {
	IDLE, JUMPING, FALLING
} VerticalMovement;

// Πληροφορίες για κάθε αντικείμενο
typedef struct object {
	ObjectType type;			// Τύπος (Παιχτης, Εχθρος, Σφαίρα)
	Vector2 position;			// Θέση
	Vector2 speed;				// Ταχύτητα (pixels/frame)
	double size;				// Μέγεθος (pixels)
	Vector2 orientation;		// Κατεύθυνση (μόνο για διαστημόπλοιο)
}* Object;

// Γενικές πληροφορίες για την κατάσταση του παιχνιδιού
typedef struct state_info {
	Object player;					// πληροφορίες για τη τον παικτη
	bool paused;					// true αν το παιχνίδι είναι paused
	int score;						// το τρέχον σκορ
}* StateInfo;

// Πληροφορίες για το ποια πλήκτρα είναι πατημένα
typedef struct key_state {
	bool up;						// true αν το αντίστοιχο πλήκτρο είναι πατημένο
	bool down;
	bool left;
	bool right;
	bool enter;
	bool space;
	bool n;
	bool p;
}* KeyState;

// Η κατάσταση του παιχνιδιού (handle)
typedef struct state* State;

// Δημιουργεί και επιστρέφει την αρχική κατάσταση του παιχνιδιού

State state_create();

// Επιστρέφει τις βασικές πληροφορίες του παιχνιδιού στην κατάσταση state

StateInfo state_info(State state);

// Επιστρέφει μια λίστα με όλα τα αντικείμενα του παιχνιδιού στην κατάσταση state,
// των οποίων η θέση position βρίσκεται εντός του παραλληλογράμμου με πάνω αριστερή
// γωνία top_left και κάτω δεξιά bottom_right.

List state_objects(State state, Vector2 top_left, Vector2 bottom_right);

// Ενημερώνει την κατάσταση state του παιχνιδιού μετά την πάροδο 1 frame.
// Το keys περιέχει τα πλήκτρα τα οποία ήταν πατημένα κατά το frame αυτό.

void state_update(State state, KeyState keys);

// Καταστρέφει την κατάσταση state ελευθερώνοντας τη δεσμευμένη μνήμη.

void state_destroy(State state);
