#include "raylib.h"
#include "stdio.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define PIXEL_X 1280			// Screen width
#define PIXEL_Y 800				// Screen height
#define BALL_SIZE 40			// Radius
#define BALL_GROUNDED_Y 760 	// Y cord for ball on ground (PIXEL_Y - BALL_SIZE)
#define BALL_LEFT_LIMIT 40 		// X cord for ball on left edge (BALL_SIZE)
#define BALL_RIGHT_LIMIT 1240	// X cord for ball on right edge (PIXEL_X - BALL_SIZE)
#define JUMP_STRENGTH -20

void update_vertical_location(int *ball_y, int *ball_velocity_y) {
	if (*ball_y < BALL_GROUNDED_Y || *ball_velocity_y < 0) {
		(*ball_velocity_y)++;
		*ball_y = MIN(BALL_GROUNDED_Y, *ball_y + *ball_velocity_y);
	} else {
		*ball_velocity_y = 0;
	}
}

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(PIXEL_X, PIXEL_Y, "cgame");

	int ball_x = PIXEL_X / 2, ball_y = BALL_GROUNDED_Y - 400;
	int ball_velocity_y = 0, ball_velocity_x;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// Control horizontal movement
		if (IsKeyDown(KEY_LEFT)){
			ball_x = MAX(BALL_LEFT_LIMIT, ball_x - 8);
		}
		if (IsKeyDown(KEY_RIGHT)){
			ball_x = MIN(BALL_RIGHT_LIMIT, ball_x + 8);
		}

		// Control vertical movement
		if (IsKeyPressed(KEY_SPACE)) {
			ball_velocity_y = JUMP_STRENGTH;
		}
		update_vertical_location(&ball_y, &ball_velocity_y);

		DrawCircle(ball_x, ball_y, BALL_SIZE, RED);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
