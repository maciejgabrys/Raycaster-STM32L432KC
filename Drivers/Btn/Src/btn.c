#include "btn.h"
#include "main.h"

static uint8_t btn_held = 0x00;
static GPIO_TypeDef* btn_gpio[] =
{
	BTN_A_GPIO_Port,
	BTN_B_GPIO_Port,
	BTN_C_GPIO_Port,
	BTN_UP_GPIO_Port,
	BTN_DOWN_GPIO_Port,
	BTN_LEFT_GPIO_Port,
	BTN_RIGHT_GPIO_Port
};
static uint16_t btn_pin[] =
{
	BTN_A_Pin,
	BTN_B_Pin,
	BTN_C_Pin,
	BTN_UP_Pin,
	BTN_DOWN_Pin,
	BTN_LEFT_Pin,
	BTN_RIGHT_Pin
};

state_t BtnRead(btn_t btn)
{
	uint8_t ret;
	if (HAL_GPIO_ReadPin(btn_gpio[btn], btn_pin[btn]) == GPIO_PIN_RESET)
	{
		if (btn_held & (1 << btn))
		{
			ret = BTN_HELD;
		}
		else
		{
			ret = BTN_PRESSED;
		}
		btn_held |= 1 << btn;
	}
	else
	{
		ret = BTN_RELEASED;
		btn_held &= ~(1 << btn);
	}
	return ret;
}
