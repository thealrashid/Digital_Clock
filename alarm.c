/* Alarm */

#include<LPC21XX.H>
#include"header.h"

#define ALARM (1<<21) // Alarm buzzer P0.21

char al_h, al_m, al_s; // Variables to store alarm time
int f; // Variable to store AM/PM

extern unsigned int next, inc, alarm;

/* Set Alarm */
void set_alarm()
{   
    // Set hour
    al_h = 1; // Initialize hour to zero
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Hours");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((al_h/10)+48); // Display set hour
        lcd_data((al_h%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(al_h < 12) al_h++; // Increment when inc button is pressed
        else al_h = 1; // Roll over to 1 after 12
        inc = 0; // Set inc back to 0
    }
    al_h = (al_h/10)*16 + (al_h%10); // Hexadecimal representation

    // Set AM/PM
    f = 0; // Initialize flag to AM
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
    if(f == 1) al_h += 0x60; //  // Set PM and 12 hours mode
    else al_h += 0x40; // Set AM and 12 hours mode

    // Set minute
    al_m = 0; // Initialize minute to 0
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Minutes");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((al_m/10)+48); // Display set minute
        lcd_data((al_m%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop and go the next setting
        }
        if(al_m < 59) al_m++; // Increment when inc button is pressed
        else al_m = 0; // Roll over to 0 after 59
        inc = 0; // Set inc back to 0
    }
    al_m = (al_m/10)*16 + (al_m%10); // Hexadecimal representation
    

    // Set second
    al_s = 0; // Initialize second to 0
    while(1) // Enter infinite loop until next button is pressed
    {
        lcd_cmd(0x01); // Clear screen
        lcd_string("Enter Seconds");
        lcd_cmd(0xC0); // Cursor at second row first column
        lcd_data((al_s/10)+48); // Display set second
        lcd_data((al_s%10)+48);
        while(inc == 0 && next == 0); // Wait while set or increment buttons are not pressed
        if(next == 1) // If next button is pressed
        {
            next = 0; // Set next back to 0
            inc = 0; // Set inc back to zero
            break; // Break from the loop
        }
        if(al_s < 59) al_s++; // Increment when inc button is pressed
        else al_s = 0; // Roll over to 0 after 59
        inc = 0; // Set inc back to 0
    }
    al_s = (al_s/10)*16 + (al_s%10); // Hexadecimal representation
}

/* Function to set off/stop/snooze alarm */
void alarm_handler(char h, char m, char s)
{
    int p; // Variable to check AM/PM

    /* Stop alarm */
    if(next == 1) // If next button is pressed
    {
        next = 0; // Set next back to 0
        IOCLR0 = ALARM; // Stop alarm
        alarm = 0; // Set alarm flag to zero
    }

    /* Snooze alarm */
    if(inc == 1) // If inc button is pressed
    {
        inc = 0; // Set inc back to 0
        IOCLR0 = ALARM; // Stop alarm
        al_m = (al_m/0x10)*10 + al_m%0x10; // Get decimal value to minute
        al_m++; // Snooze alarm for 1 minute
        if(al_m == 60) // Check if minute is 60
        {
            al_m = 0; // Set minute back to 0
            p = (al_h>>5)&1; // Check AM/PM
            al_h = ((al_h&0x1F)/0x10)*10 + (al_h&0x1F)%0x10; // Get decimal value of hour from the first 5 bits of Hour register
            al_h++; // Increment hour
            if(al_h == 12) // If hour is 12
            {
                al_h = (al_h/10)*16 + (al_h%10); // Hexadecimal representation
                if(p == 1)  al_h += 0x40; // If previously PM then set AM
                else al_h += 0x60; // If previously AM then set PM
            }
            else if(al_h == 13) // If hour is 13
            {
                al_h = 1; // Set hour as 1
                al_h = (al_h/10)*16 + (al_h%10); // Headecimal representation
            }
        }
    }
    if(check_alarm(h, m, s) == 1) // Check alarm
    {
        IOSET0 = ALARM; // Set off alarm
    }
}

/* Function to check alarm */
int check_alarm(char h, char m, char s)
{
    if(h != al_h) return 0;
    if(m != al_m) return 0;
    if(s != al_s) return 0;

    return 1;
}
