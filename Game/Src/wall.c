#include <stdlib.h>
#include "wall.h"

//#define max(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define min(a, b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })

texture_t texture_brick =
{
	8,
	8,
	{
		0b11101000, 0b11101000, 0b11011010, 0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11101000,
		0b11101000, 0b11101000, 0b11011010, 0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11101000,
		0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010,
		0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11011010, 0b11101000,
		0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11011010, 0b11101000,
		0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010, 0b11011010,
		0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11011010, 0b11101000, 0b11101000, 0b11101000,
		0b11101000, 0b11101000, 0b11101000, 0b11101000, 0b11011010, 0b11101000, 0b11101000, 0b11101000
	}
};

texture_t texture_stone =
{
	4,
	3,
	{
		0b00000011, 0b00000010, 0b00000011, 0b00000010,
		0b00000010, 0b00000011, 0b00000010, 0b00000011,
		0b00000011, 0b00000010, 0b00000011, 0b00000010
	}
};

texture_t texture_wood =
{
	4,
	1,
	{
		0b01101100, 0b01001000, 0b01101100, 0b10010000
	}
};

texture_t texture_clouds =
{
	3,
	3,
	{
		0b11111111, 0b01101110, 0b01101110,
		0b01101110, 0b01101110, 0b01101110,
		0b01101110, 0b01101110, 0b01101110
	}
};

texture_t texture_grass =
{
	2,
	2,
	{
		0b01111000, 0b01010000,
		0b01010000, 0b01111000
	}
};


int16_t WallAdd(list_t* list, wall_t wall)
{
	int16_t ret = -1;
	wall_t* new = (wall_t*)malloc(sizeof(wall_t));
	if (new != NULL)
	{
		new->pos1 = wall.pos1;
		new->pos2 = wall.pos2;
		new->texture = wall.texture;
		if (ListPushBack(list, new) != -1)
		{
			ret = 0;
		}
		else
		{
			free(new);
		}
	}
	return ret;
}

uint8_t GetTexel(texture_t* texture, float x, float y)
{
	uint8_t tx = /*min(*/(uint8_t)(x * (float)texture->width)/*, texture->width - 1)*/;
	uint8_t ty = /*min(*/(uint8_t)(y * (float)texture->height)/*, texture->height - 1)*/;
	return texture->texels[ty * texture->width + tx];
}
