#include "renderer.cpp"

float player1_pos = 0.f;
float player1_velocity = 0.f;
float player2_pos = 0.f;
float player2_velocity = 0.f;

float ball_pos_x, ball_pos_y = 0.f;
float ball_velocity_x = 20.f;
float ball_velocity_y = 0.f;
float ball_half_size = 1.f;
int ball_dir = 1;

float arena_half_size_x = 85.f;
float arena_half_size_y = 45.f;

float player_half_size_x = 2.5f;
float player_half_size_y = 12.f;

int score_1, score_2 = 0;

bool is_colliding(float pos_1_x, float pos_1_y, float size_1_x, float size_1_y, float pos_2_x, float pos_2_y, float size_2_x, float size_2_y)
{
	return (pos_1_x + size_1_x > pos_2_x - size_2_x) && (pos_1_x - size_1_x < pos_2_x + size_2_x) && (pos_1_y + size_1_y > pos_2_y - size_2_y) && (pos_1_y - size_1_y < pos_2_y + size_2_y);
}

static void simulate_game(Input* input, float delta)
{
	clear_screen(0x220055);
	draw_rect(0.f, 0.f, arena_half_size_x, arena_half_size_y, 0x000022);

	float speed = 50.f;

	player1_velocity = lerpf(player1_velocity, input->get_axis(*input, BUTTON_DOWN, BUTTON_UP) * speed * delta, 0.025);
	player1_pos += player1_velocity;
	player1_pos = clampf(player1_pos, -32.f, 32.f);

	player2_velocity = lerpf(player2_velocity, input->get_axis(*input, BUTTON_S, BUTTON_W) * speed * delta, 0.025);
	player2_pos += player2_velocity;
	player2_pos = clampf(player2_pos, -32.f, 32.f);

	ball_velocity_x += delta * ball_dir * 3;
	ball_pos_x += ball_velocity_x * delta;
	ball_pos_y += ball_velocity_y * delta;

	draw_rect(ball_pos_x, ball_pos_y, ball_half_size, ball_half_size, 0x8888ff);

	// Ball logic
	{
		if (is_colliding(ball_pos_x, ball_pos_y, ball_half_size, ball_half_size, 80.f, player1_pos, player_half_size_x, player_half_size_y))
		{
			ball_pos_x = 80 - player_half_size_x - ball_half_size;
			ball_velocity_x *= -1.f;
			ball_velocity_y = (ball_pos_y - player1_pos) * 2.f + player1_velocity * 0.75f;
			ball_dir *= -1;
		}
		if (is_colliding(ball_pos_x, ball_pos_y, ball_half_size, ball_half_size, -80.f, player2_pos, player_half_size_x, player_half_size_y))
		{
			ball_pos_x = -80 + player_half_size_x + ball_half_size;
			ball_velocity_x *= -1.f;
			ball_velocity_y = (ball_pos_y - player2_pos) * 2.f + player2_velocity * 0.75f;
			ball_dir *= -1;
		}

		if (ball_pos_y + ball_half_size > arena_half_size_y)
		{
			ball_pos_y = arena_half_size_y - ball_half_size;
			ball_velocity_y *= -1;
		}
		if (ball_pos_y - ball_half_size < -arena_half_size_y)
		{
			ball_pos_y = -arena_half_size_y + ball_half_size;
			ball_velocity_y *= -1;
		}

		if (ball_pos_x + ball_half_size > arena_half_size_x)
		{
			ball_pos_x = 0.f;
			ball_pos_y = 0.f;
			ball_velocity_x = 20.f;
			ball_velocity_y = 0.f;
			ball_dir = 1;
			score_2++;
		}
		if (ball_pos_x - ball_half_size < -arena_half_size_x)
		{
			ball_pos_x = 0.f;
			ball_pos_y = 0.f;
			ball_velocity_x = 20.f;
			ball_velocity_y = 0.f;
			ball_dir = 1;
			score_1++;
		}
	}

	for (int i = 0; i < score_1; i++)
	{
		draw_circle(87.5 - 6.f * i, 44.f, 2.5f, 0xffffff);
	}
	for (int i = 0; i < score_2; i++)
	{
		draw_circle(-87.5f + 6.f * i, 44.f, 2.5f, 0xffffff);
	}

	draw_rect(80.f, player1_pos, player_half_size_x, player_half_size_y, 0x0000ff);
	draw_rect(-80.f, player2_pos, player_half_size_x, player_half_size_y, 0x0000ff);
}