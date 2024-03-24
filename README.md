# Digital Clock with Alarm and Settings

The Digital Clock with Alarm and Settings is a project implemented using LPC2129 microcontroller, 8051, DS1307 RTC, I2C protocol, LCD, buzzer, and three switches. It displays the time (AM/PM), date, day of the week, and alarm status on the LCD screen. The switches are used to enter settings mode, set various parameters (such as year, month, etc.), configure the alarm settings, and stop/snooze alarm.

## Features

- **DS1307 Real-Time Clock (RTC):** Utilizes an RTC module to keep track of time, date, and day of the week.
- **LCD Display:** Displays time, date, day of the week, and alarm status on the LCD screen.
- **Settings Mode:** Enters settings mode upon pressing the Set switch, allowing users to adjust various parameters such as year, month, etc.
- **Increment and Next Buttons:** Use the Inc switch to increase the value to be set, and the Next switch to save changes and move to the next option.
- **Alarm Functionality:** Allows users to set an alarm. When the alarm goes off, the Inc switch can be used to snooze the alarm for 1 minute, and the Next button can be used to stop the alarm.

## Hardware Requirements

- LPC2129 microcontroller
- 8051 microcontroller
- DS1307 RTC module
- I2C interface
- 16x2 Alphanumeric LCD display
- Buzzer
- Three switches (Set, Inc, Next)

## Usage

1. **Reset:** Upon reset set the time and date to 1st January 2024 and clear alarm.
2. **Settings Mode:** Press the Set switch to enter settings mode. Use the Inc switch to adjust parameters such as year, month, etc. Use the Next switch to save changes and move to the next option.
6. **Alarm Setting:** Enter settings mode and navigate to the alarm setting option. Use the Inc switch to set the desired alarm time. Press the Next switch to save the alarm settings.
7. **Alarm Functionality:** When the set alarm time is reached, the buzzer will sound. Press the Inc switch to snooze the alarm for 1 minute. Press the Next switch to stop the alarm.

