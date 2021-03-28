#include <stm32g431xx.h>
/*
 * логика в том,что можно зажечь 2 диода
 * можно зажечь один,затем второй,но когда отпускаешь один,то он не гаснет,т.к. нет проверки,потух он или нет,если какая-либо из кнопок не нажата
 * задержки для плавного отключения
 */
int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
	while(1)
	{
		if(GPIOC->IDR & GPIO_IDR_ID2 && GPIOC->IDR & GPIO_IDR_ID3)
		{
			GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD8;
		}
		else if(GPIOC->IDR & GPIO_IDR_ID2)
		{
			if(GPIOA->ODR & GPIO_ODR_OD8)
			{
				dummy_delay(250000);
				GPIOA->ODR &= ~GPIO_ODR_OD8;
			}
			GPIOA->ODR |= GPIO_ODR_OD5;
		}
		else if(GPIOC->IDR & GPIO_IDR_ID3)
		{
			if(GPIOA->ODR & GPIO_ODR_OD5)
			{
				dummy_delay(250000);
				GPIOA->ODR &= ~GPIO_ODR_OD5;
			}
			GPIOA->ODR |= GPIO_ODR_OD8;
		}
		else
		{
			dummy_delay(250000);
			GPIOA->ODR &= ~(GPIO_ODR_OD5 | GPIO_ODR_OD8);
		}
	}
}
void dummy_delay(int32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
