#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "game.h"
#include "btn.h"
#include "scr.h"
#include "list.h"
#include "wall.h"

float z_buf[SCR_WIDTH * SCR_HEIGHT];
float tan_val[SCR_WIDTH];
float atan_val[SCR_WIDTH];
float atancos_val[SCR_WIDTH];
float pplussin_val[SCR_WIDTH];
float ppluscos_val[SCR_WIDTH];
float ddist_val[SCR_WIDTH * SCR_HEIGHT];
const float fov = 60.0f / 180.0f * M_PI;	// = 1.0471975512
float depth;								// = 83.1384387633
uint32_t uptime = 0;

player_t player = { .pos = -2.0f + 0.0fi, .arg = 0.7f };
list_t* walls = NULL;

void GameInit(void)
{
	ScrInit();
	depth = (float)SCR_WIDTH / 2.0f / tanf(fov / 2.0f);
	for (uint8_t w = 0; w < SCR_WIDTH; w++)
	{
		tan_val[w] = (float)(SCR_WIDTH / 2 - w) / depth;
		atan_val[w] = atanf(tan_val[w]);
		atancos_val[w] = cosf(atan_val[w]);
		for (uint8_t h = 0; h < SCR_HEIGHT; h++)
		{
			ddist_val[h * SCR_WIDTH + w] = (float)(SCR_HEIGHT / 2) / (((double)(h - SCR_HEIGHT / 2) + 0.5f) * cosf(atan_val[w]));
		}
	}

	walls = ListNew();
	/*WallAdd(walls, (wall_t){ 1.0f + 1.0fi, 1.0f + 2.0fi, &texture_brick });
	WallAdd(walls, (wall_t){ 1.0f + 3.0fi, 1.0f + 4.0fi, &texture_brick });
	WallAdd(walls, (wall_t){ 1.0f + 4.0fi, 4.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 4.0f + 4.0fi, 4.0f + 1.0fi, &texture_wood });
	WallAdd(walls, (wall_t){ 4.0f + 1.0fi, 1.0f + 1.0fi, &texture_stone });*/

	WallAdd(walls, (wall_t){ 1.0f + 1.0fi, 1.0f + 2.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 1.0f + 2.0fi, 2.0f + 2.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 2.0f + 2.0fi, 2.0f + 1.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 2.0f + 1.0fi, 1.0f + 1.0fi, &texture_stone });

	WallAdd(walls, (wall_t){ 1.0f + 3.0fi, 1.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 1.0f + 4.0fi, 2.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 2.0f + 4.0fi, 2.0f + 3.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 2.0f + 3.0fi, 1.0f + 3.0fi, &texture_stone });

	WallAdd(walls, (wall_t){ 3.0f + 1.0fi, 3.0f + 2.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 3.0f + 2.0fi, 4.0f + 2.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 4.0f + 2.0fi, 4.0f + 1.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 4.0f + 1.0fi, 3.0f + 1.0fi, &texture_stone });

	WallAdd(walls, (wall_t){ 3.0f + 3.0fi, 3.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 3.0f + 4.0fi, 4.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 4.0f + 4.0fi, 4.0f + 3.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 4.0f + 3.0fi, 3.0f + 3.0fi, &texture_stone });

	WallAdd(walls, (wall_t){ 5.0f + 1.0fi, 5.0f + 2.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 5.0f + 2.0fi, 6.0f + 2.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 6.0f + 2.0fi, 6.0f + 1.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 6.0f + 1.0fi, 5.0f + 1.0fi, &texture_stone });

	WallAdd(walls, (wall_t){ 5.0f + 3.0fi, 5.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 5.0f + 4.0fi, 6.0f + 4.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 6.0f + 4.0fi, 6.0f + 3.0fi, &texture_stone });
	WallAdd(walls, (wall_t){ 6.0f + 3.0fi, 5.0f + 3.0fi, &texture_stone });

	WallAdd(walls, (wall_t){ 7.0f + 2.0fi, 7.0f + 0.0fi, &texture_brick });
	WallAdd(walls, (wall_t){ 7.0f + 0.0fi, 11.0f + 0.0fi, &texture_brick });
	WallAdd(walls, (wall_t){ 11.0f + 0.0fi, 11.0f + 5.0fi, &texture_brick });
	WallAdd(walls, (wall_t){ 11.0f + 5.0fi, 7.0f + 5.0fi, &texture_brick });
	WallAdd(walls, (wall_t){ 7.0f + 5.0fi, 7.0f + 3.0fi, &texture_brick });

	WallAdd(walls, (wall_t){ 7.0f + 2.0fi, 8.0f + 3.0fi, &texture_wood });
}

void GameLoop(void)
{
	// Clearing Z-buffer:
	for (uint16_t i = 0; i < SCR_WIDTH * SCR_HEIGHT; i++)
	{
		z_buf[i] = INFINITY;
	}

	// Rotating player:
	if (BtnRead(BTN_B) != BTN_RELEASED)
	{
		player.arg += 0.05f;
	}
	if (BtnRead(BTN_A) != BTN_RELEASED)
	{
		player.arg -= 0.05f;
	}

	// Moving player:
	float arg = NAN;
	uint8_t dir = (BtnRead(BTN_UP) != BTN_RELEASED)
				| (BtnRead(BTN_DOWN) != BTN_RELEASED) << 1
				| (BtnRead(BTN_LEFT) != BTN_RELEASED) << 2
				| (BtnRead(BTN_RIGHT) != BTN_RELEASED) << 3;
	switch (dir)
	{
	case 0b0001:	// U
		arg = 0.0f;
		break;
	case 0b0010:	// D
		arg = M_PI;
		break;
	case 0b0100:	// L
		arg = M_PI_2;
		break;
	case 0b1000:	// R
		arg = -M_PI_2;
		break;
	case 0b0101:	// UL
		arg = M_PI_4;
		break;
	case 0b1001:	// UR
		arg = -M_PI_4;
		break;
	case 0b0110:	// DL
		arg = M_PI - M_PI_4;
		break;
	case 0b1010:	// DR
		arg = M_PI + M_PI_4;
		break;
	}
	if (!isnan(arg))
	{
		player.pos += 0.05f * cosf(player.arg + arg) + 0.05f * sinf(player.arg + arg) * I;
	}

	// Begin drawing:
	ScrWait();

	// Drawing walls:
	node_t* node = walls->front;
	while (node != NULL)
	{
		wall_t* wall = (wall_t*)node->obj;

		// Transformation relative to the player:
		float complex pole1 = wall->pos1 - player.pos;
		pole1 = cabsf(pole1) * cosf(cargf(pole1) - player.arg) + cabsf(pole1) * sinf(cargf(pole1) - player.arg) * I;
		float complex pole2 = wall->pos2 - player.pos;
		pole2 = cabsf(pole2) * cosf(cargf(pole2) - player.arg) + cabsf(pole2) * sinf(cargf(pole2) - player.arg) * I;

		// Finding the wall region:
		float re_min = fmin(crealf(pole1), crealf(pole2));
		float re_max = fmax(crealf(pole1), crealf(pole2));
		float im_min = fmin(cimagf(pole1), cimagf(pole2));
		float im_max = fmax(cimagf(pole1), cimagf(pole2));

		// Determining the line equation:
		float a = (crealf(pole1) - crealf(pole2)) / (cimagf(pole1) - cimagf(pole2));
		float b = crealf(pole1) - a * cimagf(pole1);

		// Casting rays:
		for (uint8_t w = 0; w < SCR_WIDTH; w++)
		{
			// Finding cross point:
			//float tan_val = (float)(SCR_WIDTH / 2 - w) / depth;
			float x = b / (1.0f - a * tan_val[w]);
			float y = x * tan_val[w];

			// Finding if cross point belongs to the wall and is in front of the player:
			if (x >= 0.0f && x >= re_min && x <= re_max && y >= im_min && y <= im_max)
			{
				// Drawing wall:
				float tex_h = (float)SCR_HEIGHT / x;
				uint8_t bar_h = (uint8_t)(fmin(tex_h, (float)SCR_HEIGHT)) + 1;
				float tx = modff(cabsf(pole1 - (x + y * I)), NULL);
				for (uint8_t h = SCR_HEIGHT / 2 - bar_h / 2; h < SCR_HEIGHT / 2 + bar_h / 2; h++)
				{
					if (x < z_buf[h * SCR_WIDTH + w])
					{
						z_buf[h * SCR_WIDTH + w] = x;
						float ty = (float)h / tex_h + (1.0f - x) / 2.0f;
						ScrDraw(w, h, GetTexel(wall->texture, tx, ty));
					}
				}
			}
		}

		node = node->next;
	}

	// Precalculatin stuff relative to player angle
	for (uint8_t w = 0; w < SCR_WIDTH; w++)
	{
		pplussin_val[w] = sinf(player.arg + atan_val[w]);
		ppluscos_val[w] = cosf(player.arg + atan_val[w]);
	}

	// Drawing ceiling:
	for (uint8_t h = 0; h < SCR_HEIGHT / 2; h++)
	{
		for (uint8_t w = 0; w < SCR_WIDTH; w++)
		{
			float ddist = -4.0f * ddist_val[h * SCR_WIDTH + w];
			float ddist_cos = ddist * atancos_val[w];
			if (ddist_cos < z_buf[h * SCR_WIDTH + w])
			{
				z_buf[h * SCR_WIDTH + w] = ddist_cos;
				float y_end = 1000.0f + (float)uptime / 100.0f + ddist * pplussin_val[w] + cimagf(player.pos);
				float x_end = 1000.0f + (float)uptime / 75.0f + ddist * ppluscos_val[w] + crealf(player.pos);
				ScrDraw(w, h, GetTexel(&texture_clouds, modff(x_end, NULL), modff(y_end, NULL)));
			}
		}
	}

	// Drawing floor:
	for (uint8_t h = SCR_HEIGHT / 2; h < SCR_HEIGHT; h++)
	{
		for (uint8_t w = 0; w < SCR_WIDTH; w++)
		{
			float ddist = 1.0f * ddist_val[h * SCR_WIDTH + w];
			float ddist_cos = ddist * atancos_val[w];
			if (ddist_cos < z_buf[h * SCR_WIDTH + w])
			{
				z_buf[h * SCR_WIDTH + w] = ddist_cos;
				float y_end = 1000.0f + ddist * pplussin_val[w] + cimagf(player.pos);
				float x_end = 1000.0f + ddist * ppluscos_val[w] + crealf(player.pos);
				ScrDraw(w, h, GetTexel(&texture_grass, modff(x_end, NULL), modff(y_end, NULL)));
			}
		}
	}

	// End drawing:
	ScrRefresh();
	uptime++;
	//HAL_Delay(10);
}
