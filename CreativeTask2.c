#include <stm32g431xx.h>
#define LED1 5
#define LED2 10
#define LED3 85
#define LED4 115
uint32_t count_score();
void blink_leds(uint32_t),turnoff_leds(),dummy_delay(uint32_t);
int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);
	uint32_t score;
	while(1)
	{
		score = count_score();
		blink_leds(score);
		dummy_delay(500000);
		if(count_score() != score)
		{
			score = count_score();
			turnoff_leds();
			blink_leds(score);
		}
	}
}
uint32_t count_score()
{
	uint32_t score = 0;
	if(GPIOC->IDR & GPIO_IDR_ID2)score+=LED4;
	if(GPIOC->IDR & GPIO_IDR_ID3)score+=LED3;
	if(GPIOA->IDR & GPIO_IDR_ID1)score+=LED2;
	if(GPIOA->IDR & GPIO_IDR_ID0)score+=LED1;
	return score;
}
void blink_leds(uint32_t score)
{
	switch(score)
	{
		case LED1:GPIOA->ODR |= GPIO_ODR_OD5;break;
		case LED2:GPIOA->ODR |= GPIO_ODR_OD6;break;
		case LED3:GPIOA->ODR |= GPIO_ODR_OD7;break;
		case LED4:GPIOA->ODR |= GPIO_ODR_OD8;break;
		case LED1+LED2:GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD6;break;
		case LED1+LED3:GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD7;break;
		case LED1+LED4:GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD8;break;
		case LED2+LED3:GPIOA->ODR |= GPIO_ODR_OD6 | GPIO_ODR_OD7;break;
		case LED2+LED4:GPIOA->ODR |= GPIO_ODR_OD6 | GPIO_ODR_OD8;break;
		case LED3+LED4:GPIOA->ODR |= GPIO_ODR_OD7 | GPIO_ODR_OD8;break;
		case LED1+LED2+LED3:GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7;break;
		case LED1+LED2+LED4:GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD8;break;
		case LED1+LED3+LED4:GPIOA->ODR |= GPIO_ODR_OD5 | GPIO_ODR_OD7 | GPIO_ODR_OD8;break;
		case LED2+LED3+LED4:GPIOA->ODR |= GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8;break;
		case LED1+LED2+LED3+LED4:GPIOA->ODR |= GPIO_ODR_OD5 |  GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8;break;
		default:turnoff_leds();
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
