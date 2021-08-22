#include <string.h>
#include "scr.h"
#include "main.h"

uint8_t scr_buf[SCR_WIDTH * SCR_HEIGHT] = { 0 };
static volatile uint8_t scr_busy = 1;

void ScrInit(void)
{
	HAL_GPIO_WritePin(SPI1_RES_GPIO_Port, SPI1_RES_Pin, GPIO_PIN_SET);		// Not reset
	HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, GPIO_PIN_RESET);		// Transmit commands
	uint8_t data[] =
	{
		0xAE,							// Display off
		0x81, 0xFF,						// Set contrast A (100%)
		0x82, 0xFF,						// Set contrast B (100%)
		0x83, 0xFF,						// Set contrast C (100%)
		0x87, 0x06,						// Master current control (7/16)
		0x8A, 0x64,						// Second pre-charge speed A (100?)
		0x8B, 0x78,						// Second pre-charge speed B (120?)
		0x8C, 0x64,						// Second pre-charge speed C (100?)
		0xA0, 0x20,						// Remap and color set (flip horizontally and vertically, use 256 colors)
		0xA1, 0x00,						// Display start line (0)
		0xA2, 0x00,						// Display offset (0)
		0xA4,							// Normal display mode
		0xA8, 0x3F,						// Multiplexer ratio
		0xAD, 0x8E,						// Master configuration
		0xB0, 0x0B,						// Power save mode
		0xB1, 0x31,						// Phase 1 and 2 period adjustment
		0xB3, 0xF0,						// Display clock divider (none) / oscillator frequency (max)
		0xBB, 0x3A,						// Pre-charge level (0.45 * Vcc)
		0xBE, 0x3E,						// COM deselect voltage level (0.83 * Vcc)
		0x2E,							// Deactivate scrolling
		0x15, 0x00, 0x5F,				// Column address (0 to 63)
		0x75, 0x00, 0x3F,				// Row address (0 to 95)
		0x25, 0x00, 0x00, 0x5F, 0x3F,	// Clear screen
		0xAF							// Display on
	};
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);		// Chip selected
	HAL_SPI_Transmit(&hspi1, data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);		// Chip unselected
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET);		// Chip selected
	HAL_SPI_Transmit(&hspi1, data + 1, sizeof(data) - 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, GPIO_PIN_SET);		// Transmit data
	scr_busy = 0;
}

void ScrWait(void)
{
	while (scr_busy)
	{
		//HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	}
}

void ScrRefresh(void)
{
	ScrWait();
	scr_busy = 1;
	HAL_SPI_Transmit_DMA(&hspi1, scr_buf, sizeof(scr_buf));
}

void ScrDeinit(void)
{
	HAL_SPI_DMAStop(&hspi1);
	HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, GPIO_PIN_RESET);		// Transmit commands
	uint8_t data = 0xAE;	// Display off
	HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
	scr_busy = 0;
}
