#include <stm32g431xx.h>

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE5_Pos);
	while(1)
	{
		GPIOA->BSRR = GPIO_BSRR_BS5 | GPIO_BSRR_BR8;
		dummy_delay(1000000);
		GPIOA->BSRR = GPIO_BSRR_BR5 | GPIO_BSRR_BS8;
		dummy_delay(1000000);
	}
}
void dummy_delay(int32_t duration)
{
   for(int32_t i = 0; i < duration; ++i);
}
//ODR для чтения и записи,BSRR только для чтения
//если возникает прерывание,то при попытке записи в ODR в прерывании и просто (из main к примеру) может потеряться значение,которое было в прерывании. Поэтому при операциях с ODR выключаются прерывания?
//
