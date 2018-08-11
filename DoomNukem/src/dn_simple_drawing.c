#include "dn_simple_drawing.h"
#include "dn.h"

// WHY THE F**K THIS IS NOT WORKING?!?!
void draw_vline(t_renderable *renderable, t_simple_vline line)
{
	//int						*pixels;
	int						y;

	//line.y1 = CLAMP(line.y1, 0, renderable->h);
	//line.y2 = CLAMP(line.y2, 0, renderable->h);
	if (line.y2 < line.y1)
		return;
	//renderable->pixels[(line.y1 * renderable->w) + line.x] = 0xFF00FFFF;
	y = line.y1;
	while (y <= line.y2)
	{
		renderable->pixels[(y * renderable->w) + line.x] = 0x0FFFF;
		++y;
	}
	//renderable->pixels[line.y2 * renderable->w + line.x] = 0x00FFFFFF;
	for (int i = 0; i < renderable->h * renderable->w; i += 100)
	{
		renderable->pixels[i] = 0xFF00FF;
	}
}
