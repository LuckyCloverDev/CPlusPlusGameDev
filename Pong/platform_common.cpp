enum Keys {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_W,
	BUTTON_S,
	BUTTON_A,
	BUTTON_D,

	BUTTON_COUNT,
};

struct Button_State
{
	bool is_down;
	bool changed;
};

struct Input
{
	Button_State buttons[BUTTON_COUNT];

	bool is_action_pressed(Input input, Keys key)
	{
		return input.buttons[key].is_down;
	}

	bool is_action_just_pressed(Input input, Keys key)
	{
		return input.buttons[key].is_down && input.buttons[key].changed;
	}

	bool is_action_released(Input input, Keys key)
	{
		return !(input.buttons[key].is_down);
	}

	bool is_action_just_released(Input input, Keys key)
	{
		return !(input.buttons[key].is_down) && input.buttons[key].changed;
	}

	int get_axis(Input input, Keys key_negative, Keys key_positive)
	{
		return (int)(input.is_action_pressed(input, key_positive)) - (int)(input.is_action_pressed(input, key_negative));
	}

	int get_axis_pressed(Input input, Keys key_negative, Keys key_positive)
	{
		return (int)(input.is_action_just_pressed(input, key_positive)) - (int)(input.is_action_just_pressed(input, key_negative));
	}
};