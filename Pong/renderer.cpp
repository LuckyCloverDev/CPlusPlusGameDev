#include <cmath>

float render_scale = 0.01f;

void clear_screen(u32 color)
{
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++)
	{
		for (int x = 0; x < render_state.width; x++)
		{
			*pixel++ = color;
		}
	}
}

void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color)
{
	x0 = clamp(x0, 0, render_state.width);
	x1= clamp(x1, 0, render_state.width);
	y0 = clamp(y0, 0, render_state.height);
	y1 = clamp(y1, 0, render_state.height);

	for (int y = y0; y < y1; y++)
	{
		u32* pixel = (u32*)render_state.memory + x0 + y*render_state.width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
}

void draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color)
{
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	int x0 = (int)(x - half_size_x);
	int x1 = (int)(x + half_size_x);
	int y0 = (int)(y - half_size_y);
	int y1 = (int)(y + half_size_y);

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

void draw_circle_in_pixels(int x0, int y0, int x1, int y1, int radius, u32 color)
{
	x0 = clamp(x0, 0, render_state.width);
	x1 = clamp(x1, 0, render_state.width);
	y0 = clamp(y0, 0, render_state.height);
	y1 = clamp(y1, 0, render_state.height);

	for (int y = y0; y < y1; y++)
	{
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++)
		{
			if (sqrt(x * x + y * y) <= radius)
				*pixel++ = color;
			else
				*pixel++;
		}
	}
}

void draw_circle(float x, float y, float radius, u32 color)
{
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	radius *= render_state.height * render_scale;

	int x0 = (int)(x - radius);
	int x1 = (int)(x + radius);
	int y0 = (int)(y - radius);
	int y1 = (int)(y + radius);

	draw_circle_in_pixels(x0, y0, x1, y1, (int)radius, color);
}