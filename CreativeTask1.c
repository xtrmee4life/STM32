#include <stm32g431xx.h>

void dummy_delay();
void run_victory_animation();
void run_error_animation();

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~ GPIO_MODER_MODE2_Msk;
	uint32_t mode = 0;
	while(1)
	{
		if(GPIOC->IDR & GPIO_IDR_ID2)
		{
			mode = !mode;
			while(GPIOC->IDR & GPIO_IDR_ID2);
		}
		if(mode == 0)
		{
			run_error_animation();
		}
		if(mode == 1)
		{
			run_victory_animation();
			mode = 2;
		}
	}
}
void dummy_delay(int32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}

void run_victory_animation()
{
	GPIOA->ODR |= GPIO_ODR_OD5;
	dummy_delay(500000);
	GPIOA->ODR |= GPIO_ODR_OD6;
	dummy_delay(500000);
	GPIOA->ODR |= GPIO_ODR_OD7;
	GPIOA->ODR &= ~GPIO_ODR_OD5;
	dummy_delay(500000);
	GPIOA->ODR |= GPIO_ODR_OD8;
	GPIOA->ODR &= ~GPIO_ODR_OD6;
	dummy_delay(500000);
	GPIOA->ODR &= ~GPIO_ODR_OD7;
	dummy_delay(500000);
	GPIOA->ODR &= ~GPIO_ODR_OD8;
	dummy_delay(500000);
}

void run_error_animation()
{
	GPIOA->ODR |= (GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
	dummy_delay(1000000);
	GPIOA->ODR &= ~(GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
	dummy_delay(1000000);
}
