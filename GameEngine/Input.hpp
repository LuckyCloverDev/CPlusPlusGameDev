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
	BUTTON_W,
	BUTTON_S,
	BUTTON_A,
	BUTTON_D,

	BUTTON_P,

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