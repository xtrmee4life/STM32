#include <stm32g431xx.h>

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE5_Pos);
	GPIOA->ODR |= GPIO_ODR_OD5;
	while(1)
	{

    	dummy_delay(1000000);
    	GPIOA->ODR ^= GPIO_ODR_OD5 | GPIO_ODR_OD8;
    	dummy_delay(1000000);
    	GPIOA->ODR ^= GPIO_ODR_OD5 | GPIO_ODR_OD8;
	}
}
void dummy_delay(int32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
