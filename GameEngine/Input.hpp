#pragma once

#define process_button(b, vk)\
case vk:\
{\
	m_input.buttons[b].changed = (!(event.type - 5)) != m_input.buttons[b].is_down;\
	m_input.buttons[b].is_down = (!(event.type - 5));\
} break;

#define process_mouse_button(b, vk)\
case vk:\
{\
	m_input.buttons[b].changed = (!(event.type - 9)) != m_input.buttons[b].is_down;\
	m_input.buttons[b].is_down = (!(event.type - 9));\
} break;

enum Keys {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,

	BUTTON_LEFT_SHIFT,
	BUTTON_RIGHT_SHIFT,

	BUTTON_A,
	BUTTON_B,
	BUTTON_C,
	BUTTON_D,
	BUTTON_E,
	BUTTON_F,
	BUTTON_G,
	BUTTON_H,
	BUTTON_I,
	BUTTON_J,
	BUTTON_K,
	BUTTON_L,
	BUTTON_M,
	BUTTON_N,
	BUTTON_O,
	BUTTON_P,
	BUTTON_Q,
	BUTTON_R,
	BUTTON_S,
	BUTTON_T,
	BUTTON_U,
	BUTTON_V,
	BUTTON_W,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_Z,

	MOUSE_LEFT,
	MOUSE_RIGHT,

	BUTTON_COUNT,
};

struct Button_State
{
	bool is_down;
	bool changed;
};

class Input
{
public:
	Button_State buttons[BUTTON_COUNT];

	bool is_action_pressed(Keys key)
	{
		return buttons[key].is_down;
	}

	bool is_action_just_pressed(Keys key)
	{
		return buttons[key].is_down && buttons[key].changed;
	}

	bool is_action_released(Keys key)
	{
		return !(buttons[key].is_down);
	}

	bool is_action_just_released(Keys key)
	{
		return !(buttons[key].is_down) && buttons[key].changed;
	}

	int get_axis(Keys key_negative, Keys key_positive)
	{
		return (int)(is_action_pressed(key_positive)) - (int)(is_action_pressed(key_negative));
	}

	int get_axis_pressed(Keys key_negative, Keys key_positive)
	{
		return (int)(is_action_just_pressed(key_positive)) - (int)(is_action_just_pressed(key_negative));
	}
};