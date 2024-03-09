/* External Interrupt */

#include<LPC21XX.H>
#include"header.h"

extern unsigned int set, next, inc;

/* External interrupt 0 using P0.16 to enter setting mode */
void EINT0_Handler(void) __irq
{
    EXTINT |= 0x1; // Clear interrupt
	set = 1;
    VICVectAddr = 0; // Clear ISR address
}

/* External interrupt 1 using P0.14 to get next option/stop alarm */
void EINT1_Handler(void) __irq
{
    EXTINT |= 0x2; // Clear interrupt
	next = 1;
    VICVectAddr = 0; // Clear ISR address
}

/* External interrupt 2 using P0.15 to increment parameter value/snooze alarm */
void EINT2_Handler(void) __irq
{
    EXTINT |= 0x4; // Clear interrupt
	inc = 1;
    VICVectAddr = 0; // Clear ISR address
}

/* Configure external interrupt */
void config_vic_eint(void)
{
    VICIntSelect = 0; // All interrupts are IRQ
    VICVectCntl0 = 0xE | (1<<5); // Assign interrupt number 0xE to slot 0 and enable slot 0
    VICVectAddr0 = (int)EINT0_Handler; // Assign EINT0 ISR address to slot 0
    VICVectCntl1 = 0xF | (1<<5); // Assign interrupt number 0xF to slot 1 and enable slot 1
    VICVectAddr1 = (int)EINT1_Handler; // Assign EINT1 ISR address to slot 1
    VICVectCntl2 = 0x10 | (1<<5); // Assign interrupt number 0x10 to slot 2 and enable slot 2
    VICVectAddr2 = (int)EINT2_Handler; // Assign EINT2 ISR address to slot 2
	VICIntEnable |= (1<<14) | (1<<15) | (1<<16);
}

/* Enable interrupt */
void en_int(void)
{
    EXTMODE = 0x0; // All interrups are edge-triggered
    EXTPOLAR = 0x0; // All interrupts are active low
    PINSEL0 |= 0xA0000000; // Configure P0.14 and P0.15 as external interrupt pins
    PINSEL1 |= 0x1; // Configure P0.16 as external interrupt pin
	//EXTINT &= ~(0x7);
}
