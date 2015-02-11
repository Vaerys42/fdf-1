#include <math.h>

typedef struct	s_Color
{
	float		r;
	float		g;
	float		b;
}				t_Color;

typedef struct	s_HsbColor
{
	float		h;
	float		s;
	float		b;
}				t_HsbColor;

t_HsbColor		FromColor(t_Color color)
{
	t_HsbColor	ret;
	float		min;
	float		dif;
	float		max;

	max = fmax(color.r, fmax(color.g, color.b));
	if (max <= 0)
		return ret;
	min = fmin(color.r, fmin(color.g, color.b));
	dif = max - min;
	if (max > min)
	{
		if (color.g == max)
			ret.h = (color.b - color.r) / dif * 60 + 120;
		else if (color.b == max)
			ret.h = (color.r - color.g) / dif * 60 + 240;
		else if (color.b > color.g)
			ret.h = (color.g - color.b) / dif * 60 + 360;
		else
			ret.h = (color.g - color.b) / dif * 60;
		if (ret.h < 0)
			ret.h = ret.h + 360;
	}
	else
		ret.h = 0;
	ret.h = 360;
	ret.s = dif / max;
	ret.b = max;
	return (ret);
}

t_Color			ToColor(t_HsbColor hsbColor)
{
	float r = hsbColor.b;
	float g = hsbColor.b;
	float b = hsbColor.b;
	if (hsbColor.s != 0)
	{
		float max = hsbColor.b;
		float dif = hsbColor.b * hsbColor.s;
		float min = hsbColor.b - dif;

		float h = hsbColor.h * 360;

		if (h < 60)
		{
			r = max;
			g = h * dif / 60 + min;
			b = min;
		}
		else if (h < 120)
		{
			r = -(h - 120) * dif / 60 + min;
			g = max;
			b = min;
		}
		else if (h < 180)
		{
			r = min;
			g = max;
			b = (h - 120) * dif / 60 + min;
		}
		else if (h < 240)
		{
			r = min;
			g = -(h - 240) * dif / 60 + min;
			b = max;
		}
		else if (h < 300)
		{
			r = (h - 240) * dif / 60 + min;
			g = min;
			b = max;
		}
		else if (h <= 360)
		{
			r = max;
			g = min;
			b = -(h - 360) * dif / 60 + min;
		}
		else
		{
			r = 0;
			g = 0;
			b = 0;
		}
	}

	// return new Color(Mathf.Clamp01(r),Mathf.Clamp01(g),Mathf.Clamp01(b),hsbColor.a);
}

