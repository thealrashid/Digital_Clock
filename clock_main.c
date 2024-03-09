/* Main function */

#include<LPC21XX.H>
#include"header.h"

#define ALARM (1<<21) // Alarm buzzer P0.21

unsigned int set = 0; // Varibale to enter setting mode
unsigned int next = 0; // Varible to set next parameter/Stop alarm
unsigned int inc = 0; // Variable to increment parameter value/Snooze alarm
unsigned int alarm = 0; // Variable to turn ON/OFF alarm

int main()
{
    char yr, mo, dt, dow, h, m, s; // Variables to store parameter values

	IODIR0 = ALARM; // Set buzzer as output direction
	IOCLR0 = ALARM; // Turn off buzzer
    
    i2c_init(); // Set up I2C peripheral
    lcd_init(); // Set up LCD
    uart0_init(9600); // Set up UART0 with 9600 baud rate
    config_vic_eint(); // Configure external interrupt
    en_int(); // Enable external interrupt

    reset_clock(); // Reset time in clock

    while(1)
    {
        lcd_cmd(0x01); // Clear LCD screen
		delay_ms(100);

        if(set) // If setting mode button is pressed
        {
            setting_mode(); // Enter setting mode
        }

        get_data(&yr, &mo, &dt, &dow, &h, &m, &s); // Get data from RTC

        if(alarm == 1) // If Alarm is ON
        {
            alarm_handler(h, m, s); // Set off/snooze/stop alarm
        }

        display_data(yr, mo, dt, dow, h, m, s); // Display data on LCD
		delay_ms(250);
    }
}
