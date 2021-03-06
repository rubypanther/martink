#include <arch/soc.h>
#include "stm32.h"
#include "time.h"

static volatile long long _ticks = 0; 

#define SYSTICK_DIV 10000UL
#define SYSTICK_INTERVAL (1000000UL / SYSTICK_DIV)

void SysTick_Handler(void); 
void SysTick_Handler(void){
	_ticks ++; 
}
    
void tsc_init(void)
{
	RCC_ClocksTypeDef RCC_Clocks;

  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.SYSCLK_Frequency / SYSTICK_DIV); 
	//SysTick_Config (SystemCoreClock / 1000000UL); 
	
	//set systick interrupt priority
	//4 bits for preemp priority 0 bit for sub priority
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);    
	NVIC_SetPriority(SysTick_IRQn, 0);
}

timestamp_t tsc_read(void)
{
	return _ticks * SYSTICK_INTERVAL; 
}
/*
uint32_t millis(void)
{
	return _millis;
}

void delay_ms(uint32_t ms)
{
	int32_t curTime = _millis;
	while((ms-(_millis-curTime)) > 0);
}

void delay_us(uint32_t us)
{
	int32_t curTime = _micros;
	while((us-(Micros-curTime)) > 0);
}
*/
timestamp_t tsc_us_to_ticks(timestamp_t us){
	return us; 
}

timestamp_t tsc_ticks_to_us(timestamp_t ticks){
	return ticks; 
}

