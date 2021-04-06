#include <stm32g431xx.h>

enum sequence
{
	first = 1<<3,
	second = 1<<2,
	third = 1<<1,
	fourth = 1<<0
};

uint32_t count_score();
void turnoff_leds();
void dummy_delay(uint32_t);
void run_victory_animation();
void run_error_animation();

uint32_t attempt = 1;
uint32_t led1_pos = 0;
uint32_t led2_pos = 0;
uint32_t led3_pos = 0;
uint32_t led4_pos = 0;
uint32_t current_pos = 0;

int main()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA | SYSCFG_EXTICR1_EXTI1_PA | SYSCFG_EXTICR1_EXTI2_PC | SYSCFG_EXTICR1_EXTI3_PC;

	EXTI->IMR1 |= EXTI_IMR1_IM0 | EXTI_IMR1_IM1 | EXTI_IMR1_IM2 | EXTI_IMR1_IM3;
	EXTI->RTSR1 |= EXTI_RTSR1_RT0 | EXTI_RTSR1_RT1 | EXTI_RTSR1_RT2 | EXTI_RTSR1_RT3;
	EXTI->FTSR1 |= EXTI_FTSR1_FT0 | EXTI_FTSR1_FT1 | EXTI_FTSR1_FT2 | EXTI_FTSR1_FT3;

	GPIOA->MODER &= ~(GPIO_MODER_MODE8_Msk | GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE5_Msk);
	GPIOA->MODER |= (1 << GPIO_MODER_MODE8_Pos | 1 << GPIO_MODER_MODE7_Pos | 1 << GPIO_MODER_MODE6_Pos | 1 << GPIO_MODER_MODE5_Pos);

	GPIOA->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk);
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);

	while(1)
	{
		if(current_pos == 4)
		{
			NVIC_DisableIRQ(EXTI0_IRQn);
			NVIC_DisableIRQ(EXTI1_IRQn);
			NVIC_DisableIRQ(EXTI2_IRQn);
			NVIC_DisableIRQ(EXTI3_IRQn);
			EXTI->IMR1 &= ~(EXTI_IMR1_IM0 | EXTI_IMR1_IM1 | EXTI_IMR1_IM2 | EXTI_IMR1_IM3);
			turnoff_leds();
			if(led1_pos == first && led2_pos == second && led3_pos == third && led4_pos == fourth)
			{
				while(1)
				{
					run_victory_animation();
				}
			}
			else
			{
				for(uint32_t i = 0;i<=3;i++)
				{
					run_error_animation();
				}
			}
			if(attempt == 3)
			{
				while(1)
				{
					run_error_animation();
				}
			}
			attempt++;
			current_pos = 0;
			led1_pos = led2_pos = led3_pos = led4_pos = 0;
			NVIC_EnableIRQ(EXTI0_IRQn);
			NVIC_EnableIRQ(EXTI1_IRQn);
			NVIC_EnableIRQ(EXTI2_IRQn);
			NVIC_EnableIRQ(EXTI3_IRQn);
			EXTI->IMR1 |= EXTI_IMR1_IM0 | EXTI_IMR1_IM1 | EXTI_IMR1_IM2 | EXTI_IMR1_IM3;
		}
	}
}

void EXTI0_IRQHandler()
{
	if(led1_pos == 0)
	{
		GPIOA->BSRR = GPIO_BSRR_BS5;
		led1_pos |= 1 << current_pos;
		current_pos++;
		while(GPIOA->IDR & GPIO_IDR_ID0);
	}
	EXTI->PR1 = EXTI_PR1_PIF0;
}
void EXTI1_IRQHandler()
{
	if(led2_pos == 0)
	{
		GPIOA->BSRR = GPIO_BSRR_BS6;
		led2_pos |= 1 << current_pos;
		current_pos++;
		while(GPIOA->IDR & GPIO_IDR_ID1);
	}
	EXTI->PR1 = EXTI_PR1_PIF1;
}
void EXTI2_IRQHandler()
{
	if(led3_pos == 0)
	{
		GPIOA->BSRR = GPIO_BSRR_BS7;
		led3_pos |= 1 << current_pos;
		current_pos++;
		while(GPIOC->IDR & GPIO_IDR_ID2);
	}
	EXTI->PR1 = EXTI_PR1_PIF2;
}
void EXTI3_IRQHandler()
{
	if(led4_pos == 0)
	{
		GPIOA->BSRR = GPIO_BSRR_BS8;
		led4_pos |= 1 << current_pos;
		current_pos++;
		while(GPIOC->IDR & GPIO_IDR_ID3);
	}
	EXTI->PR1 = EXTI_PR1_PIF3;
}
void turnoff_leds()
{
	GPIOA->ODR &= ~( GPIO_ODR_OD5 | GPIO_ODR_OD6 | GPIO_ODR_OD7 | GPIO_ODR_OD8 );
}

void dummy_delay(uint32_t duration)
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
