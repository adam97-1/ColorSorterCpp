#include "ServiceUart.h"
#include <stm32f446xx.h>


void ServiceUart_Init( )
{

	RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN);

	GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk 		| GPIO_MODER_MODE3_Msk);
	GPIOA->MODER |= (2 << GPIO_MODER_MODE2_Pos 	| 2 << GPIO_MODER_MODE3_Pos);

	GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD2_Msk 		| GPIO_PUPDR_PUPD3_Msk);
	GPIOA->PUPDR |= (2 << GPIO_PUPDR_PUPD2_Pos 	| 2 << GPIO_PUPDR_PUPD3_Pos);

	GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2_Msk 			| GPIO_AFRL_AFSEL3_Msk);
	GPIOA->AFR[0] |= (0b0111 << GPIO_AFRL_AFSEL2_Pos	| 0b0111 << GPIO_AFRL_AFSEL3_Pos);

	RCC->APB1ENR |= (RCC_APB1ENR_USART2EN);

	USART2->CR1 |= (USART_CR1_UE);
	USART2->CR1 &= ~(USART_CR1_M);

	USART2->CR2 &= ~(USART_CR2_STOP_Msk);
	USART2->CR2 |= (0 << USART_CR2_STOP_Pos);

	USART2->BRR |= 45000000 / 115200;

	USART2->CR1 |= (USART_CR1_TE);

}
