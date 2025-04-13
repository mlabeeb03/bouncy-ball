#include "raylib.h"
#include "stdio.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define PIXEL_X 1280		// Screen width
#define PIXEL_Y 800			// Screen height
#define BALL_SIZE 40		// Radius
#define BALL_GROUNDED_Y 760 // Y cord for ball on ground (PIXEL_Y - BALL_SIZE)
#define JUMP_STRENGTH -20

void update_ball_location(int *ball_x, int *ball_y, int *ball_velocity) {
	if (*ball_y < BALL_GROUNDED_Y || *ball_velocity < 0) {
		(*ball_velocity)++;
		*ball_y = MIN(BALL_GROUNDED_Y, *ball_y + *ball_velocity);
	} else {
		*ball_velocity = 0;
	}
}

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(PIXEL_X, PIXEL_Y, "cgame");

	int ball_x = PIXEL_X / 2, ball_y = BALL_GROUNDED_Y - 400;
	int ball_velocity = 0;

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (IsKeyPressed(KEY_SPACE)) {
			ball_velocity = JUMP_STRENGTH;
		}

		update_ball_location(&ball_x, &ball_y, &ball_velocity);

		DrawCircle(ball_x, ball_y, BALL_SIZE, RED);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
