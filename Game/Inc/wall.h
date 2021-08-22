#ifndef __WALL_H_
#define __WALL_H_

#include <stdint.h>
#include <complex.h>
#include "list.h"

typedef struct
{
	uint8_t width;
	uint8_t height;
	uint8_t texels[];
} texture_t;

typedef struct
{
	float complex pos1;
	float complex pos2;
	texture_t* texture;
} wall_t;

extern texture_t texture_brick;
extern texture_t texture_stone;
extern texture_t texture_wood;
extern texture_t texture_clouds;
extern texture_t texture_grass;

int16_t WallAdd(list_t* list, wall_t wall);
uint8_t GetTexel(texture_t* texture, float x, float y);

#endif /* __WALL_H_ */
