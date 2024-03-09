#include<LPC21XX.H>
#include"header.h"
#include<stdio.h>

#define RS 1<<17
#define RW 1<<18
#define EN 1<<19

void lcd_init(void)
{
	IODIR1|= 0x00FE0000;
	PINSEL2 = 0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
}

void lcd_cmd(unsigned char cmd)
{
	unsigned int temp;
	IOCLR1 = 0x00FE0000;
	temp = (cmd&0xF0)<<16;
	IOSET1 = temp;
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
	IOCLR1 = 0x00FE0000;
	temp = (cmd & 0x0F)<<20;
	IOSET1 = temp;
	IOCLR1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
}

void lcd_data(unsigned char data)
{
	unsigned int temp;
	IOCLR1 = 0x00FE0000;
	temp = (data&0xF0)<<16;
	IOSET1 = temp;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
	IOCLR1 = 0x00FE0000;
	temp = (data & 0x0F)<<20;
	IOSET1 = temp;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
}

void lcd_string(char *str)
{
	while(*str != 0)
	{
		lcd_data(*str);
		str++;
	}
}

void lcd_integer(int num)
{
	int arr[10], i;
	if(num==0)
	{
		lcd_data('0');
		return;
	}
	if(num<0)
	{
		lcd_data('-');
		num = -num;
	}

	i=0;
	while(num>0)
	{
		arr[i] = num%10;
		num = num/10;
		i++;
	}

	for(--i;i>=0;i--)
	{
		lcd_data(arr[i]+'0');
	}

	/*
	char s[10];
	sprintf(s, "%d", num);
	lcd_string(s);
	*/
}

void lcd_float(float f)
{
	int n = (int)f, p;
	float m = f-n;
	while(m != (int)m) m *= 10;
	p = (int)m;
	lcd_integer(n);
	lcd_data('.');
	lcd_integer(p);
}

void custom_symbol(unsigned char *arr, unsigned char p)
{
	int i;
	unsigned char page = 0x40+p*8;
	lcd_cmd(page);
	for(i=0;i<8;i++) lcd_data(arr[i]);
}
