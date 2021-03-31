#include <stm32g431xx.h>

void dummy_delay(uint32_t);
void turnoff_leds();

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~(GPIO_MODER_MODE3_Msk);

	uint32_t score = 0;
	while(1)
	{
		if(GPIOC->IDR & GPIO_IDR_ID3 && (GPIOA->IDR & GPIO_IDR_ID0) == 0 && (GPIOA->IDR & GPIO_IDR_ID1) == 0)
		{
			score = 0;
		}
		if(GPIOA->IDR & GPIO_IDR_ID1 && (GPIOA->IDR & GPIO_IDR_ID0) == 0 && (GPIOC->IDR & GPIO_IDR_ID3) == 0 && score > 0)
		{
			score -= 1;
			while(GPIOA->IDR & GPIO_IDR_ID1);
		}
		if(GPIOA->IDR & GPIO_IDR_ID0 && (GPIOA->IDR & GPIO_IDR_ID1) == 0 && (GPIOC->IDR & GPIO_IDR_ID3) == 0)
		{
			score += 1;
			while(GPIOA->IDR & GPIO_IDR_ID0);
		}
		turnoff_leds();
		GPIOA->ODR |= (score & 15) << 5;
		dummy_delay(250000);
	}
}

void turnoff_leds()
{
	GPIOA->ODR &= ~(GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8);
}

void dummy_delay(uint32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
