/* Setting Mode */

#include"header.h"

extern unsigned int set, next, inc, alarm;

/* Function to set parameters in RTC */
void setting_mode(void)
{
    char set_yr, set_mo, set_dt, set_dow, set_h, set_m, set_s; // Varibles to store set values
    char yr_hex, mo_hex, dt_hex; // Hexadecimal values
    int f; // Flag to set AM/PM
    int year = 2000; // Variable to store year
    char K, J; // Variables to calculate day of the week
    
    lcd_string("Setting Mode"); //Display setting mode for 1 sec
    delay_ms(1000);

    // Set year
    set_yr = 0; // Initialize year to 0
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Year");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_string("20"); // Display set year
        lcd_data((set_yr/10)+48);
        lcd_data((set_yr%10)+48);
        while((inc == 0) && (next == 0)); // Wait while set or increment buttons are not pressed
		inc = 0; // Set inc back to 0
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(set_yr < 99) set_yr++; // Increment when inc button is pressed
        else set_yr = 0; // Roll over to 2000 after 2099
    }
    yr_hex = (set_yr/10)*16 + (set_yr%10); // Hexadecimal representation
    

    //Set month
    set_mo = 1; // Initialize month to 1
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Month");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((set_mo/10)+48); // Display set year
        lcd_data((set_mo%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(set_mo < 12) set_mo++; // Increment when inc button is pressed
        else set_mo = 1; // Roll over to 1 after 12
        inc = 0; // Set inc back to 0
    }
    mo_hex = (set_mo/10)*16 + (set_mo%10); // Hexadecimal representation

    // Set date
    set_dt = 1; // Initialize date to 1
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Date");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((set_dt/10)+48); // Display set month
        lcd_data((set_dt%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        // Increment when inc button is pressed
        if(set_mo == 1 || set_mo == 3 || set_mo == 5 || set_mo == 7 || set_mo == 8 || set_mo == 10 || set_mo == 12 && set_dt < 31) set_dt++; // When the month has 31 days
        else if(set_mo == 4 || set_mo == 6 || set_mo == 9 || set_mo == 11 && set_dt < 30) set_dt++; // When the month has 30 days
        else if(set_mo == 2 && set_yr%4 == 0 && set_dt < 29) set_dt++; // When it is February in a leap year
        else if(set_mo == 2 && set_yr%4 != 0 && set_dt < 28) set_dt++; // When it is February in a non leap year
        else set_dt = 1; // Roll over to 1
        inc = 0; // Set inc back to 0
    }
    dt_hex = (set_dt/10)*16 + (set_dt%10); // Hexadecimal representation

    // Calculate day of the week based on year, month, date with the help of Zeller's Congruence
    if(set_mo < 3) // If January or February
    {
        set_mo += 12; // These are treated as 13th and 14th respectively
        set_yr--; // of the previous year
    }

    year += set_yr; // Add set year with 2000

    K = year % 100; // year of the century
    J = year / 100; // Zero based century

    set_dow = (set_dt + ((13 * (set_mo + 1)) / 5) + K + (K / 4) + (J / 4) - 2 * J) % 7; // Calculate day of the week
    set_dow = set_dow % 7;
    set_dow = (set_dow/10)*16 + (set_dow%10); // Hexadecimal representation

    // Set hour
    set_h = 1; // Initialize hour to 1
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Hours");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((set_h/10)+48); // Display set hour
        lcd_data((set_h%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(set_h < 12) set_h++; // Increment when inc button is pressed
        else set_h = 1; // Roll over to 1 after 12
        inc = 0; // Set inc back to 0
    }
    set_h = (set_h/10)*16 + (set_h%10); // Hexadecimal representation

    // Set AM/PM
    f = 0; // Initialize flag as AM
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter AM/PM");
        lcd_cmd(0xC0); // Cursor at second row first column
        if(f == 0) lcd_string("AM");
        else lcd_string("PM");
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(f == 0) f = 1; // Toggle AM to PM
        else f = 0; // Else toggle PM to AM
        inc = 0; // Set inc back to 0
    }
    if(f == 1) set_h += 0x60; // Set PM and 12 hours mode in Hours register
    else set_h += 0x40; // Set AM and 12 hours mode in Hours register

    // Set minute
    set_m = 0; // Initialize minute to 0
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Minutes");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((set_m/10)+48); // Display set minute
        lcd_data((set_m%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(set_m < 59) set_m++; // Increment when inc button is pressed
        else set_m = 0; // Roll over to 0 after 59
        inc = 0; // Set inc back to 0
    }
    set_m = (set_m/10)*16 + (set_m%10); // Hexadecimal representation

    // Set second
    set_s = 0; // Initialize second to 0
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Seconds");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((set_s/10)+48); // Display set second
        lcd_data((set_s%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(set_s < 59) set_s++; // Increment when inc button is pressed
        else set_s = 0; // Roll over to 0 after 59
        inc = 0; // Set inc back to 0
    }
    set_s = (set_s/10)*16 + (set_s%10); // Hexadecimal representation
    
    // Send data to RTC
    i2c_byte_write_frame(0xD0, 0x06, yr_hex); // Send year to RTC
    i2c_byte_write_frame(0xD0, 0x05, mo_hex); // Send month to RTC
    i2c_byte_write_frame(0xD0, 0x04, dt_hex); // Send data to RTC
    i2c_byte_write_frame(0xD0, 0x03, set_dow); // Send data to RTC
    i2c_byte_write_frame(0xD0, 0x02, set_h); // Send data to RTC
    i2c_byte_write_frame(0xD0, 0x01, set_m); // Send minute to RTC
    i2c_byte_write_frame(0xD0, 0x00, set_s); // Send second to RTC

    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Set Alarm");
        lcd_cmd(0xC0); // Cursor at second row first column
        if(alarm == 1) lcd_string("Yes");
        else lcd_string("No");
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop
        }
        if(alarm == 0) alarm = 1; // Set alarm
        else alarm = 0; // Clear alarm
        inc = 0; // Set inc back to 0
    }
    if(alarm == 1) // If alarm flag is set
    {
        set_alarm(); // Set alarm
    }
    lcd_cmd(0x01); // Clear LCD screen

    set = 0; // Turn off setting mode
}
