/*delay*/
#include<LPC21XX.H>

void delay_sec(unsigned int sec)
{
	int a[] = {15, 60, 30, 0};
	unsigned int pclk;
	if(VPBDIV%4 == 3) return;
	pclk = a[VPBDIV%4]*1000000;
	T0PC = 0;
	T0PR = pclk - 1;
	T0TC = 0;
	T0TCR = 1;
	while(T0TC<sec);
	T0TCR = 0;
}

void delay_ms(unsigned int ms)
{
	int a[] = {15, 60, 30, 0};
	unsigned int pclk;
	if(VPBDIV%4 == 3) return;
	pclk = a[VPBDIV%4]*1000;
	T0PC = 0;
	T0PR = pclk - 1;
	T0TC = 0;
	T0TCR = 1;
	while(T0TC<ms);
	T0TCR = 0;
}

void delay_us(unsigned int us)
{
	int a[] = {15, 60, 30, 0};
	unsigned int pclk;
	if(VPBDIV%4 == 3) return;
	pclk = a[VPBDIV%4];
	T0PC = 0;
	T0PR = pclk - 1;
	T0TC = 0;
	T0TCR = 1;
	while(T0TC<us);
	T0TCR = 0;
}
