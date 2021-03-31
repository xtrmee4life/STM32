#include <stm32g431xx.h>

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
	while(1)
	{
		if(GPIOC->IDR & GPIO_IDR_ID2)
		{
			GPIOA->ODR |= GPIO_ODR_OD5;
		}
		else
		{
			GPIOA->ODR &= ~(GPIO_ODR_OD5);
		}
		if(GPIOC->IDR & GPIO_IDR_ID3)
		{
			GPIOA->ODR |= GPIO_ODR_OD8;
		}
		else
		{
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
		}
	}
}
void dummy_delay(int32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
