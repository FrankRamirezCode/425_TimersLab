 /*
 * @file main.c
 *
 * @brief Main source code for the Timers program.
 *
 * This file contains the main entry point and function definitions for the Timers program.
 * It interfaces with the following:
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *	- EduBase Board Seven-Segment Display
 *
 * The following timers are used to demonstrate periodic interrupts: Timer 0A and Timer 1A.
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */
 
#include "TM4C123GH6PM.h"
#include "Timer_0A_Interrupt.h"
#include "GPIO.h"
#include "SysTick_Delay.h"
#include "Seven_Segment_Display.h"

void Timer_0A_Periodic_Task(void);

uint32_t Timer_0A_ms_elapsed = 0;

uint32_t toggle_rate_ms = 0;

uint8_t count =0;

int main(void)
{
	EduBase_LEDs_Init();
	
	EduBase_Button_Init();
	
	Timer_0A_Interrupt_Init(&Timer_0A_Periodic_Task);
	
	SysTick_Delay_Init();
	
	Seven_Segment_Display_Init();
	
	while(1)
	{
		uint8_t button_status = Get_EduBase_Button_Status();
		toggle_rate_ms = Change_Counter_Speed(button_status);
		Seven_Segment_Display(count);
	}
}

void Timer_0A_Periodic_Task(void)
{
	Timer_0A_ms_elapsed++;
	if (Timer_0A_ms_elapsed >= toggle_rate_ms)
		{
		Timer_0A_ms_elapsed = 0;
		GPIOB->DATA = GPIOB->DATA ^ 0x01;
		
		if (count >= 15)
			{
			count = 0;
			}
		else {
			count += 1;
				}
		}
}
