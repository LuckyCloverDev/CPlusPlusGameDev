
typedef unsigned int u32;

inline int clamp(int val, int min, int max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

inline float clampf(float val, float min, float max)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}

inline float lerpf(float val, float target, float strength)
{
	return val + (target - val) * strength;
}