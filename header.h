typedef unsigned int u32;
typedef unsigned char u8;
typedef int s32;
typedef char s8;
typedef short int u16;

extern void delay_ms(unsigned int);
extern void delay_sec(unsigned int);
extern void delay_us(unsigned int);

extern void lcd_data(unsigned char);
extern void lcd_cmd(unsigned char);
extern void lcd_init(void);
extern void lcd_string(char *);
extern void lcd_integer(int);
extern void lcd_float(float);
extern void custom_symbol(unsigned char *, unsigned char);

extern void uart0_init(u32);
extern void uart0_tx(u8);
extern u8 uart0_rx(void);
extern void uart0_tx_string(char *);
extern void uart0_rx_string(char *, int);
extern void uart0_tx_integer(s32);
extern void uart0_tx_float(float);
extern void uart0_hex(int);
extern void gsm_rx(u8 *, s32);

extern void i2c_init(void);
extern void i2c_byte_write_frame(char sa, char mr, char data);
extern char i2c_byte_read_frame(char sa, char mr);

extern void reset_clock(void);
extern void get_data(char *yr, char *mo, char *dt, char *dow, char *h, char *m, char *s);
extern void display_data(char yr, char mo, char dt, char dow, char h, char m, char s);
extern void setting_mode(void);
extern void set_alarm(void);
extern void alarm_handler(char h, char m, char s);
extern int check_alarm(char h, char m, char s);

extern void config_vic_eint(void);
extern void en_int(void);
