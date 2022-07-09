#ifndef _LCD16X2_H_
#define _LCD16X2_H_

#include "main.h"
#include <inttypes.h>
#include <string.h>
#include "swI2C.h" 

#define LCD_ADDR 		0x27
#define LCD_ROWS		2
#define LCD_COLUMNS 		16

// commands
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON           0x04
#define LCD_DISPLAYOFF          0x00
#define LCD_CURSORON            0x02
#define LCD_CURSOROFF           0x00
#define LCD_BLINKON             0x01
#define LCD_BLINKOFF            0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

// flags for function set
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

// flags for backlight control
#define LCD_BACKLIGHT           0x08
#define LCD_NOBACKLIGHT         0x00

#define En                      0x04  // Enable bit
#define Rw                      0x02  // Read/Write bit
#define Rs                      0x01  // Register select bitt

class LCD {
    public:
        LCD();
        virtual ~LCD();
        void putCmd(unsigned char cmd);
        void init();
        void setCursor(unsigned char x, unsigned char y);
        void putChar(char data);
        void putChars(char *s);
    private:
        void write4bits(uint8_t value);
        void expanderWrite(uint8_t _data);
        void pulseEnable(uint8_t _data);
};
#endif
