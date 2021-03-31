#include <stm32g431xx.h>

void dummy_delay(uint32_t);

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);

	while(1)
	{
		if(GPIOA->IDR & GPIO_IDR_ID0)
		{
			GPIOA->ODR |= GPIO_ODR_OD5;
		}
		else
		{
			GPIOA->ODR &= ~GPIO_ODR_OD5;
		}
		if(GPIOA->IDR & GPIO_IDR_ID1)
		{
			GPIOA->ODR |= GPIO_ODR_OD6;
		}
		else
		{
			GPIOA->ODR &= ~GPIO_ODR_OD6;
		}
		if(GPIOC->IDR & GPIO_IDR_ID3)
		{
			GPIOA->ODR |= GPIO_ODR_OD7;
		}
		else
		{
			GPIOA->ODR &= ~GPIO_ODR_OD7;
		}
		if(GPIOC->IDR & GPIO_IDR_ID2)
		{
			GPIOA->ODR |= GPIO_ODR_OD8;
		}
		else
		{
			GPIOA->ODR &= ~GPIO_ODR_OD8;
		}
	}
}

void dummy_delay(uint32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
