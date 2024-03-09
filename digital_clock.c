/* Digital Clock */

#include"header.h"

#define t ((h>>5)&1) // AM/PM

extern unsigned int alarm;

/* Reset time in clock */
void reset_clock(void)
{
    i2c_byte_write_frame(0xD0, 0x06, 0x24); // Year
    i2c_byte_write_frame(0xD0, 0x05, 0x01); // Month
    i2c_byte_write_frame(0xD0, 0x04, 0x01); // Date
    i2c_byte_write_frame(0xD0, 0x03, 0x02); // Day of the week
    i2c_byte_write_frame(0xD0, 0x02, 0x52); // Hour
    i2c_byte_write_frame(0xD0, 0x01, 0x00); // Minute
    i2c_byte_write_frame(0xD0, 0x00, 0x00); // Second
}

/* Get data from RTC DS1307 using I2C protocol */
void get_data(char *yr, char *mo, char *dt, char *dow, char *h, char *m, char *s)
{
    *yr = i2c_byte_read_frame(0xD0, 0x06); // Year
    *mo = i2c_byte_read_frame(0xD0, 0x05); // Month
    *dt = i2c_byte_read_frame(0xD0, 0x04); // Date
    *dow = i2c_byte_read_frame(0xD0, 0x03); // Day of the week
    *h = i2c_byte_read_frame(0xD0, 0x02); // Hour
    *m = i2c_byte_read_frame(0xD0, 0x01); // Minute
    *s = i2c_byte_read_frame(0xD0, 0x00); // Second
}

/* Display data on the LCD */
void display_data(char yr, char mo, char dt, char dow, char h, char m, char s)
{
    unsigned char alarm_sym[] = {0x04, 0x0A, 0x0A, 0x0A, 0x0A, 0x1F, 0x04}; // Custom character for alarm
    unsigned char no_alarm_sym[] = {0x04, 0x0B, 0x0E, 0x1A, 0x0A, 0x1F, 0x04}; // Custom character for no alarm
    
    // Display hours
    lcd_cmd(0x80); // Cursor at home position
    lcd_data(((h&0x1F)/0x10)+48); // Get first 5 bits of Hour register
    lcd_data(((h&0x1F)%0x10)+48);
    lcd_data(':');

    // Display minutes
    lcd_data((m/0x10)+48);
    lcd_data((m%0x10)+48);
    lcd_data(':');

    // Display seconds
    lcd_data((s/0x10)+48);
    lcd_data((s%0x10)+48);
    lcd_data(' ');

    // Display AM/PM
    if(t == 1) lcd_string("PM");
    else lcd_string("AM");
	lcd_data(' ');
        
    // Display alarm symbol
    if(alarm == 1) // Alarm ON
    {
        custom_symbol(alarm_sym, 0);
		lcd_cmd(0x80+13);
		lcd_data(0);

    }
    else // Alarm OFF
    {
        custom_symbol(no_alarm_sym, 1);
		lcd_cmd(0x80+13);
		lcd_data(1);
    }
	
	// Display date
    lcd_cmd(0xC0); // Cursor at 2nd row first column
    lcd_data((dt/0x10)+48);
    lcd_data((dt%0x10)+48);
    lcd_data('.');

    // Display month
    lcd_data((mo/0x10)+48);
    lcd_data((mo%0x10)+48);
    lcd_data('.');

    // Display year
    lcd_string("20");
    lcd_data((yr/0x10)+48);
    lcd_data((yr%0x10)+48);
    lcd_data(' ');

    // Display day of the week
    switch(dow)
    {
        case 1: lcd_string("SUN"); break;
        case 2: lcd_string("MON"); break;
        case 3: lcd_string("TUE"); break;
        case 4: lcd_string("WED"); break;
        case 5: lcd_string("THU"); break;
        case 6: lcd_string("FRI"); break;
        case 7: lcd_string("SAT"); break;
    }
}
