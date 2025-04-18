#include "raylib.h"
#include "stdio.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define PIXEL_X 1280 // Screen width
#define PIXEL_Y 800	 // Screen height
#define BALL_SIZE 40 // Radius
#define BALL_GROUNDED (PIXEL_Y - BALL_SIZE)
#define BALL_LEFT_LIMIT (BALL_SIZE)
#define BALL_RIGHT_LIMIT (PIXEL_X - BALL_SIZE)
#define JUMP_STRENGTH -25

typedef struct {
	int x, y, size, jump_strength, velocity;
} Ball;

void update_vertical_location(Ball *ball) {
	if ((*ball).y < BALL_GROUNDED || (*ball).velocity < 0) {
		((*ball).velocity)++;
		(*ball).y = MIN(BALL_GROUNDED, (*ball).y + (*ball).velocity);
	} else {
		(*ball).velocity = 0;
	}
}

int ball_on_ground(Ball *ball) { return (*ball).y == BALL_GROUNDED ? 1 : 0; }

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(PIXEL_X, PIXEL_Y, "cgame");

	Ball ball = {.x = PIXEL_X / 2,
				 .y = BALL_GROUNDED,
				 .size = BALL_SIZE,
				 .jump_strength = JUMP_STRENGTH,
				 .velocity = 0};

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// Control horizontal movement
		if (IsKeyDown(KEY_LEFT)) {
			ball.x = MAX(BALL_LEFT_LIMIT, ball.x - 8);
		}
		if (IsKeyDown(KEY_RIGHT)) {
			ball.x = MIN(BALL_RIGHT_LIMIT, ball.x + 8);
		}

		// Control vertical movement
		if (ball_on_ground(&ball) && IsKeyPressed(KEY_SPACE)) {
			ball.velocity = JUMP_STRENGTH;
		}
		update_vertical_location(&ball);

		DrawCircle(ball.x, ball.y, ball.size, RED);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
