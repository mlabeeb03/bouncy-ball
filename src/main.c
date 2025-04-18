#include "raylib.h"
#include "stdio.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define PIXEL_X 1280 // Screen width
#define PIXEL_Y 800	 // Screen height
#define BALL_SIZE 40 // Radius
#define BALL_LEFT_LIMIT (BALL_SIZE)
#define BALL_RIGHT_LIMIT (PIXEL_X - BALL_SIZE)
#define JUMP_STRENGTH -25 // Lower number means a higher jump

typedef struct {
	float x, y, size, jump_strength, velocity;
} Ball;

typedef struct {
	float x, y, width, height;
} Platform;

int ball_bottom(Ball *ball) { return (*ball).y + (*ball).size; }

int ball_on_platform(Ball *ball, Platform *platform) {
	Vector2 center = {.x = (*ball).x, .y = (*ball).y};
	Rectangle rectangle = *(Rectangle *)platform;
	if (CheckCollisionCircleRec(center, (*ball).size, rectangle)) {
		return 1;
	}
	return 0;
}

void update_vertical_location(Ball *ball, Platform *platform) {
	if (!ball_on_platform(ball, platform) || (*ball).velocity < 0) {
		((*ball).velocity)++;
		(*ball).y =
			MIN((*platform).y - (*ball).size, (*ball).y + (*ball).velocity);
	} else {
		(*ball).velocity = 0;
	}
}

int main() {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(PIXEL_X, PIXEL_Y, "cgame");

	Ball ball = {.x = PIXEL_X / 2,
				 .y = PIXEL_Y / 2,
				 .size = BALL_SIZE,
				 .jump_strength = JUMP_STRENGTH,
				 .velocity = 0};

	Platform platform = {
		.x = 0, .y = PIXEL_Y - 20, .width = PIXEL_X, .height = 20};

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawRectangle(platform.x, platform.y, platform.width, platform.height,
					  BLACK);

		// Control horizontal movement
		if (IsKeyDown(KEY_LEFT)) {
			ball.x = MAX(BALL_LEFT_LIMIT, ball.x - 8);
		}
		if (IsKeyDown(KEY_RIGHT)) {
			ball.x = MIN(BALL_RIGHT_LIMIT, ball.x + 8);
		}

		// Control vertical movement
		if ((ball_on_platform(&ball, &platform)) && IsKeyPressed(KEY_SPACE)) {
			ball.velocity = JUMP_STRENGTH;
		}
		update_vertical_location(&ball, &platform);

		DrawCircle(ball.x, ball.y, ball.size, RED);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
